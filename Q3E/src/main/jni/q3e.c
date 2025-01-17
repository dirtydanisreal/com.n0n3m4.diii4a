/*
	Copyright (C) 2012 n0n3m4	
	This file contains some code from kwaak3:
	Copyright (C) 2010 Roderick Colenbrander

    This file is part of Q3E.

    Q3E is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 2 of the License, or
    (at your option) any later version.

    Q3E is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with Q3E.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <dlfcn.h>
#include <stdio.h>
#include <string.h>
#include <android/log.h>
#include <ctype.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <stdarg.h>
#include <android/native_window.h>
#include <android/native_window_jni.h>
#include "q3e.h"

#include "doom3/neo/sys/android/doom3_android.h"

#define LOG_TAG "Q3E_JNI"

#define JNI_Version JNI_VERSION_1_4

// call DOOM3
static void (*setResolution)(int width, int height);
static void (*Q3E_SetInitialContext)(const void *context);
static void (*setCallbacks)(const void *func);
static void (*set_gl_context)(ANativeWindow *window);

static int  (*qmain)(int argc, char **argv);
static void (*onFrame)();
static void (*onKeyEvent)(int state, int key,int chr);
static void (*onAnalog)(int enable, float x, float y);
static void (*onMotionEvent)(float x, float y);
static void (*vidRestart)();
static void (*on_pause)(void);
static void (*on_resume)(void);
static void (*qexit)(void);

// Android function
static void pull_input_event(int execCmd);
static void grab_mouse(int grab);
static FILE * android_tmpfile(void);
static void copy_to_clipboard(const char *text);
static char * get_clipboard_text(void);

// data
static char *game_data_dir = NULL;
static char *arg_str = NULL;
// static char *audio_track_buffer = NULL;

static void *libdl;
static ANativeWindow *window = NULL;

// Java object ref
static JavaVM *jVM;
static jobject audioBuffer=0;
static jobject q3eCallbackObj=0;

// Java method
static jmethodID android_PullEvent_method;
static jmethodID android_GrabMouse_method;
static jmethodID android_CopyToClipboard_method;
static jmethodID android_GetClipboardText_method;

static jmethodID android_initAudio;
static jmethodID android_writeAudio;
static jmethodID android_setState;
static jmethodID android_writeAudio_direct;

static void Android_AttachThread(void)
{
	JNIEnv *env = 0;

	if (((*jVM)->GetEnv(jVM, (void**) &env, JNI_VERSION_1_4)) < 0)
	{
		(*jVM)->AttachCurrentThread(jVM, &env, NULL);
	}
}

static void print_interface(void)
{
	__android_log_print(ANDROID_LOG_INFO, LOG_TAG, "DOOM3 interface ---------> ");

	__android_log_print(ANDROID_LOG_INFO, LOG_TAG, "Main function: %p", qmain);
	__android_log_print(ANDROID_LOG_INFO, LOG_TAG, "Setup callbacks: %p", setCallbacks);
	__android_log_print(ANDROID_LOG_INFO, LOG_TAG, "Setup initial context: %p", Q3E_SetInitialContext);
	__android_log_print(ANDROID_LOG_INFO, LOG_TAG, "Setup resolution: %p", setResolution);
	__android_log_print(ANDROID_LOG_INFO, LOG_TAG, "On pause: %p", on_pause);
	__android_log_print(ANDROID_LOG_INFO, LOG_TAG, "On resume: %p", on_resume);
	__android_log_print(ANDROID_LOG_INFO, LOG_TAG, "Exit function: %p", qexit);

	__android_log_print(ANDROID_LOG_INFO, LOG_TAG, "Setup OpenGL context: %p", set_gl_context);

	__android_log_print(ANDROID_LOG_INFO, LOG_TAG, "On frame: %p", onFrame);
	__android_log_print(ANDROID_LOG_INFO, LOG_TAG, "Restart OpenGL: %p", vidRestart);

	__android_log_print(ANDROID_LOG_INFO, LOG_TAG, "Key event: %p", onKeyEvent);
	__android_log_print(ANDROID_LOG_INFO, LOG_TAG, "Analog event: %p", onAnalog);
	__android_log_print(ANDROID_LOG_INFO, LOG_TAG, "Motion event: %p", onMotionEvent);

	__android_log_print(ANDROID_LOG_INFO, LOG_TAG, "<---------");
}

static void loadLib(const char* libpath)
{
    libdl = dlopen(libpath, RTLD_NOW | RTLD_GLOBAL);
    if(!libdl)
    {
        __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, "Unable to load library: %s\n", dlerror());
        return;
    }
	void (*GetDOOM3API)(void *);

	GetDOOM3API = dlsym(libdl, "GetDOOM3API");
	Q3E_Interface_t d3interface;
	GetDOOM3API(&d3interface);

	qmain = (int (*)(int, char **)) d3interface.main;
	setCallbacks = d3interface.setCallbacks;
	Q3E_SetInitialContext = d3interface.setInitialContext;
	setResolution = d3interface.setResolution;

	on_pause = d3interface.pause;
	on_resume = d3interface.resume;
	qexit = d3interface.exit;

	set_gl_context = d3interface.setGLContext;

	onFrame = d3interface.frame;
	vidRestart = d3interface.vidRestart;

	onKeyEvent = d3interface.keyEvent;
	onAnalog = d3interface.analogEvent;
	onMotionEvent = d3interface.motionEvent;

#if 0
    qmain = dlsym(libdl, "main");
    onFrame = dlsym(libdl, "Q3E_DrawFrame");
    onKeyEvent = dlsym(libdl, "Q3E_KeyEvent");
    onAnalog = dlsym(libdl, "Q3E_Analog");
    onMotionEvent = dlsym(libdl, "Q3E_MotionEvent");
    setCallbacks = dlsym(libdl, "Q3E_SetCallbacks");
    setResolution = dlsym(libdl, "Q3E_SetResolution");
	vidRestart = dlsym(libdl, "Q3E_OGLRestart");

    on_pause = dlsym(libdl, "Q3E_OnPause");
    on_resume = dlsym(libdl, "Q3E_OnResume");
	Q3E_SetInitialContext = dlsym(libdl, "Q3E_SetInitialContext");
    qexit = dlsym(libdl, "Q3E_exit");
	set_gl_context = dlsym(libdl, "Q3E_SetGLContext");
#endif

	print_interface();
}

void initAudio(void *buffer, int size)
{
    JNIEnv *env;
    jobject tmp;
    if (((*jVM)->GetEnv(jVM, (void**) &env, JNI_VERSION_1_4))<0)
    {
        (*jVM)->AttachCurrentThread(jVM,&env, NULL);
    }
    tmp = (*env)->NewDirectByteBuffer(env, buffer, size);
    audioBuffer = (jobject)(*env)->NewGlobalRef(env, tmp);
    return (*env)->CallVoidMethod(env, q3eCallbackObj, android_initAudio, size);
}

//k NEW: 
// if offset >= 0 and length > 0, only write.
// if offset >= 0 and length < 0, length = -length, then write and flush.
// If offset < 0 and length == 0, only flush.
int writeAudio(int offset, int length)
{
	if (audioBuffer==0) return 0;
    JNIEnv *env;
    if (((*jVM)->GetEnv(jVM, (void**) &env, JNI_VERSION_1_4))<0)
    {
    	(*jVM)->AttachCurrentThread(jVM,&env, NULL);
    }
    return (*env)->CallIntMethod(env, q3eCallbackObj, android_writeAudio, audioBuffer, offset, length);
}

void setState(int state)
{
    JNIEnv *env;
    if (((*jVM)->GetEnv(jVM, (void**) &env, JNI_VERSION_1_4))<0)
    {
        (*jVM)->AttachCurrentThread(jVM,&env, NULL);
    }
    (*env)->CallVoidMethod(env, q3eCallbackObj, android_setState, state);
}

#if 0
void initAudio_direct(void *buffer, int size)
{
	JNIEnv *env;
	if (((*jVM)->GetEnv(jVM, (void**) &env, JNI_VERSION_1_4))<0)
	{
		(*jVM)->AttachCurrentThread(jVM,&env, NULL);
	}
	audio_track_buffer = buffer;
	return (*env)->CallVoidMethod(env, q3eCallbackObj, android_initAudio, size);
}

int writeAudio_direct(int offset, int length)
{
	if (!audio_track_buffer)
		return 0;
	JNIEnv *env;
	if (((*jVM)->GetEnv(jVM, (void**) &env, JNI_VERSION_1_4))<0)
	{
		(*jVM)->AttachCurrentThread(jVM,&env, NULL);
	}
	jbyteArray buf = NULL;
	if(offset >= 0)
	{
		int len = abs(length);
		if(len > 0)
		{
			buf = (*env)->NewByteArray(env, len);
			jbyte *buf_mem = (*env)->GetByteArrayElements(env, buf, NULL);
			memcpy(buf_mem, audio_track_buffer + offset, len);
			(*env)->ReleaseByteArrayElements(env, buf, buf_mem, JNI_ABORT);
		}
	}
	jobject jbuf = (*env)->NewWeakGlobalRef(env, buf); // weak ref for auto release
	(*env)->DeleteLocalRef(env, buf);
	int r = (*env)->CallIntMethod(env, q3eCallbackObj, android_writeAudio_direct, jbuf, offset, length);
	return r;
}
#endif

static void q3e_exit(void)
{
	__android_log_print(ANDROID_LOG_INFO, LOG_TAG, "Q3E JNI exit");
	if(game_data_dir)
	{
		free(game_data_dir);
		game_data_dir = NULL;
	}
	if(arg_str)
	{
		free(arg_str);
		arg_str = NULL;
	}
	if(libdl)
	{
		dlclose(libdl);
		libdl = NULL;
	}
}

int JNI_OnLoad(JavaVM* vm, void* reserved)
{
    JNIEnv *env;
    jVM = vm;
    if((*vm)->GetEnv(vm, (void**) &env, JNI_VERSION_1_4) != JNI_OK)
    {
        __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, "JNI fatal error");
        return -1;
    }

	atexit(q3e_exit);
	__android_log_print(ANDROID_LOG_INFO, LOG_TAG, "JNI loaded %d", JNI_Version);

    return JNI_Version;
}

void JNI_OnUnload(JavaVM *vm, void *reserved)
{
	__android_log_print(ANDROID_LOG_INFO, LOG_TAG, "JNI unload");
	JNIEnv *env;
	if((*vm)->GetEnv(vm, (void**) &env, JNI_Version) != JNI_OK)
	{
		__android_log_print(ANDROID_LOG_ERROR, LOG_TAG, "JNI unload error");
		if(q3eCallbackObj)
		{
			(*env)->DeleteGlobalRef(env, q3eCallbackObj);
			q3eCallbackObj = NULL;
		}
		if(audioBuffer)
		{
			(*env)->DeleteGlobalRef(env, audioBuffer);
			audioBuffer = NULL;
		}
	}
	jVM = NULL;
	__android_log_print(ANDROID_LOG_INFO, LOG_TAG, "JNI unload done");
}

JNIEXPORT void JNICALL Java_com_n0n3m4_q3e_Q3EJNI_setCallbackObject(JNIEnv *env, jclass c, jobject obj)
{
    q3eCallbackObj = obj;
    jclass q3eCallbackClass;

    (*jVM)->GetEnv(jVM, (void**) &env, JNI_VERSION_1_4);
    q3eCallbackObj = (jobject)(*env)->NewGlobalRef(env, obj);
    q3eCallbackClass = (*env)->GetObjectClass(env, q3eCallbackObj);
    
    android_initAudio = (*env)->GetMethodID(env,q3eCallbackClass,"init","(I)V");
    android_writeAudio = (*env)->GetMethodID(env,q3eCallbackClass,"writeAudio","(Ljava/nio/ByteBuffer;II)I");
	android_setState = (*env)->GetMethodID(env,q3eCallbackClass,"setState","(I)V");
	android_writeAudio_direct = (*env)->GetMethodID(env,q3eCallbackClass, "writeAudio_direct", "([BII)I");
	
	//k
	android_PullEvent_method = (*env)->GetMethodID(env, q3eCallbackClass, "PullEvent", "(Z)V");
	android_GrabMouse_method = (*env)->GetMethodID(env, q3eCallbackClass, "GrabMouse", "(Z)V");
	android_CopyToClipboard_method = (*env)->GetMethodID(env, q3eCallbackClass, "CopyToClipboard", "(Ljava/lang/String;)V");
	android_GetClipboardText_method = (*env)->GetMethodID(env, q3eCallbackClass, "GetClipboardText", "()Ljava/lang/String;");
}

static void UnEscapeQuotes( char *arg )
{
	char *last = NULL;
	while( *arg ) {
		if( *arg == '"' && *last == '\\' ) {
			char *c_curr = arg;
			char *c_last = last;
			while( *c_curr ) {
				*c_last = *c_curr;
				c_last = c_curr;
				c_curr++;
			}
			*c_last = '\0';
		}
		last = arg;
		arg++;
	}
}

static int ParseCommandLine(char *cmdline, char **argv)
{
	char *bufp;
	char *lastp = NULL;
	int argc, last_argc;
	argc = last_argc = 0;
	for ( bufp = cmdline; *bufp; ) {		
		while ( isspace(*bufp) ) {
			++bufp;
		}		
		if ( *bufp == '"' ) {
			++bufp;
			if ( *bufp ) {
				if ( argv ) {
					argv[argc] = bufp;
				}
				++argc;
			}			
			while ( *bufp && ( *bufp != '"' || *lastp == '\\' ) ) {
				lastp = bufp;
				++bufp;
			}
		} else {
			if ( *bufp ) {
				if ( argv ) {
					argv[argc] = bufp;
				}
				++argc;
			}			
			while ( *bufp && ! isspace(*bufp) ) {
				++bufp;
			}
		}
		if ( *bufp ) {
			if ( argv ) {
				*bufp = '\0';
			}
			++bufp;
		}
		if( argv && last_argc != argc ) {
			UnEscapeQuotes( argv[last_argc] );	
		}
		last_argc = argc;	
	}
	if ( argv ) {
		argv[argc] = NULL;
	}
	return(argc);
}

static void setup_Q3E_callback(void)
{
	Q3E_Callback_t callback;
	memset(&callback, 0, sizeof(callback));

	callback.AudioTrack_init = &initAudio; // initAudio_direct
	callback.AudioTrack_write = &writeAudio; // writeAudio_direct

	callback.Input_grabMouse = &grab_mouse;
	callback.Input_pullEvent = &pull_input_event;

	callback.Sys_attachThread = &Android_AttachThread;

	callback.set_state = &setState;
	callback.Sys_tmpfile = &android_tmpfile;
	callback.Sys_copyToClipboard = &copy_to_clipboard;
	callback.Sys_getClipboardText = &get_clipboard_text;

	setCallbacks(&callback);
}

static void print_initial_context(const Q3E_InitialContext_t *context)
{
	__android_log_print(ANDROID_LOG_INFO, LOG_TAG, "DOOM3 initial context ---------> ");

	__android_log_print(ANDROID_LOG_INFO, LOG_TAG, "Native library directory: %s", context->nativeLibraryDir);
	__android_log_print(ANDROID_LOG_INFO, LOG_TAG, "Redirect output to file: %d", context->redirectOutputToFile);
	__android_log_print(ANDROID_LOG_INFO, LOG_TAG, "Don't handle signals: %d", context->noHandleSignals);
	__android_log_print(ANDROID_LOG_INFO, LOG_TAG, "Enable multi-thread: %d", context->multithread);
	__android_log_print(ANDROID_LOG_INFO, LOG_TAG, "OpenGL format: 0x%X", context->openGL_format);
	__android_log_print(ANDROID_LOG_INFO, LOG_TAG, "OpenGL MSAA: %d", context->openGL_msaa);
	__android_log_print(ANDROID_LOG_INFO, LOG_TAG, "OpenGL Version: %x", context->openGL_version);
    __android_log_print(ANDROID_LOG_INFO, LOG_TAG, "Continue when missing OpenGL context: %d", context->continueWhenNoGLContext);

	__android_log_print(ANDROID_LOG_INFO, LOG_TAG, "<---------");
}

JNIEXPORT void JNICALL Java_com_n0n3m4_q3e_Q3EJNI_init(JNIEnv *env, jclass c, jstring LibPath, jstring nativeLibPath, jint width, jint height, jstring GameDir, jstring Cmdline, jobject view, jint format, jint msaa, jint glVersion, jboolean redirectOutputToFile, jboolean noHandleSignals, jboolean bMultithread, jboolean bContinueNoGLContext)
{
    char **argv;
    int argc=0;
	jboolean iscopy;

	const char *dir = (*env)->GetStringUTFChars(env, GameDir, &iscopy);
    game_data_dir = strdup(dir);
	chdir(game_data_dir);
	(*env)->ReleaseStringUTFChars(env, GameDir, dir);

	const char *arg = (*env)->GetStringUTFChars(env, Cmdline, &iscopy);
	argv = malloc(sizeof(char*) * 255);
    arg_str = strdup(arg);
	argc = ParseCommandLine(arg_str, argv);
	(*env)->ReleaseStringUTFChars(env, Cmdline, arg);    
	
	const char *engineLibPath = (*env)->GetStringUTFChars(env, LibPath, &iscopy);
	__android_log_print(ANDROID_LOG_INFO, LOG_TAG, "DOOM3 engine native library file: %s", engineLibPath);
	loadLib(engineLibPath);
	(*env)->ReleaseStringUTFChars(env, LibPath, engineLibPath);

	setup_Q3E_callback();

	setResolution(width, height);
	char *doom3_path = NULL;
	if(Q3E_SetInitialContext)
	{
		const char *native_lib_path = (*env)->GetStringUTFChars(env, nativeLibPath, &iscopy);
		doom3_path = strdup(native_lib_path);
		(*env)->ReleaseStringUTFChars(env, nativeLibPath, native_lib_path);
		Q3E_InitialContext_t context;
		memset(&context, 0, sizeof(context));

		context.openGL_format = format;
		context.openGL_msaa = msaa;
		context.openGL_version = glVersion;

		context.nativeLibraryDir = doom3_path;
		context.redirectOutputToFile = redirectOutputToFile ? 1 : 0;
		context.noHandleSignals = noHandleSignals ? 1 : 0;
		context.multithread = bMultithread ? 1 : 0;
        context.continueWhenNoGLContext = bContinueNoGLContext ? 1 : 0;

		print_initial_context(&context);

		Q3E_SetInitialContext(&context);
	}

	window = ANativeWindow_fromSurface(env, view);
	set_gl_context(window);
    
    qmain(argc, argv);
	free(argv);
    free(doom3_path);
}

JNIEXPORT void JNICALL Java_com_n0n3m4_q3e_Q3EJNI_drawFrame(JNIEnv *env, jclass c)
{
    onFrame();
}

JNIEXPORT void JNICALL Java_com_n0n3m4_q3e_Q3EJNI_sendKeyEvent(JNIEnv *env, jclass c, jint state, jint key, jint chr)
{
    onKeyEvent(state,key,chr);
}

JNIEXPORT void JNICALL Java_com_n0n3m4_q3e_Q3EJNI_sendAnalog(JNIEnv *env, jclass c, jint enable, jfloat x, jfloat y)
{
    onAnalog(enable,x,y);
}

JNIEXPORT void JNICALL Java_com_n0n3m4_q3e_Q3EJNI_sendMotionEvent(JNIEnv *env, jclass c, jfloat x, jfloat y)
{
    onMotionEvent(x, y);
}

JNIEXPORT void JNICALL Java_com_n0n3m4_q3e_Q3EJNI_vidRestart(JNIEnv *env, jclass c)
{    
	vidRestart();
}


JNIEXPORT void JNICALL Java_com_n0n3m4_q3e_Q3EJNI_shutdown(JNIEnv *env, jclass c)
{
    if(qexit)  
        qexit();
}

JNIEXPORT jboolean JNICALL Java_com_n0n3m4_q3e_Q3EJNI_Is64(JNIEnv *env, jclass c)
{    
    return sizeof(void *) == 8 ? JNI_TRUE : JNI_FALSE;
}

JNIEXPORT void JNICALL
Java_com_n0n3m4_q3e_Q3EJNI_OnPause(JNIEnv *env, jclass clazz)
{
	if(on_pause)
		on_pause();
}

JNIEXPORT void JNICALL
Java_com_n0n3m4_q3e_Q3EJNI_OnResume(JNIEnv *env, jclass clazz)
{
	if(on_resume)
    	on_resume();
}

JNIEXPORT void JNICALL
Java_com_n0n3m4_q3e_Q3EJNI_SetSurface(JNIEnv *env, jclass clazz, jobject view) {
	if(window)
	{
		window = NULL;
	}
	if(view)
	{
		window = ANativeWindow_fromSurface(env, view);
	}
	set_gl_context(window);
}

void pull_input_event(int execCmd)
{
    JNIEnv *env = 0;

    if (((*jVM)->GetEnv(jVM, (void**) &env, JNI_VERSION_1_4))<0)
    {
        (*jVM)->AttachCurrentThread(jVM,&env, NULL);
    }

    (*env)->CallVoidMethod(env, q3eCallbackObj, android_PullEvent_method, (jboolean)execCmd);
}

void grab_mouse(int grab)
{
	JNIEnv *env = 0;

	if (((*jVM)->GetEnv(jVM, (void**) &env, JNI_VERSION_1_4))<0)
	{
		(*jVM)->AttachCurrentThread(jVM,&env, NULL);
	}

	(*env)->CallVoidMethod(env, q3eCallbackObj, android_GrabMouse_method, (jboolean)grab);
}

void copy_to_clipboard(const char *text)
{
	JNIEnv *env = 0;

	if (((*jVM)->GetEnv(jVM, (void**) &env, JNI_VERSION_1_4))<0)
	{
		(*jVM)->AttachCurrentThread(jVM,&env, NULL);
	}

	if(!text)
	{
		(*env)->CallVoidMethod(env, q3eCallbackObj, android_CopyToClipboard_method, NULL);
		return;
	}

	jstring str = (*env)->NewStringUTF(env, text);
	jstring nstr = (*env)->NewWeakGlobalRef(env, str);
	(*env)->DeleteLocalRef(env, str);
	(*env)->CallVoidMethod(env, q3eCallbackObj, android_CopyToClipboard_method, nstr);
}

char * get_clipboard_text(void)
{
	JNIEnv *env = 0;

	if (((*jVM)->GetEnv(jVM, (void**) &env, JNI_VERSION_1_4))<0)
	{
		(*jVM)->AttachCurrentThread(jVM,&env, NULL);
	}

	jstring str = (*env)->CallObjectMethod(env, q3eCallbackObj, android_GetClipboardText_method);
	if(!str)
		return NULL;

	const char *nstr = (*env)->GetStringUTFChars(env, str, NULL);
	char *res = NULL;
	if(nstr)
		res = strdup(nstr);
	(*env)->ReleaseStringUTFChars(env, str, nstr);
	return res;
}

#define TMPFILE_NAME "idtech4amm_harmattan_tmpfile_XXXXXX"
FILE * android_tmpfile(void)
{
    const int Len = strlen(game_data_dir) + 1 + strlen(TMPFILE_NAME) + 1;
	char *tmp_file = malloc(Len);
    memset(tmp_file, 0, Len);
    sprintf(tmp_file, "%s/%s", game_data_dir, TMPFILE_NAME);
	int fd = mkstemp(tmp_file);
	if(fd == -1)
	{
		__android_log_print(ANDROID_LOG_ERROR, LOG_TAG, "Call mkstemp(%s) error: %s", tmp_file, strerror(errno));
		free(tmp_file);
		return NULL;
	}

	FILE *res = fdopen(fd, "w+b");
	if(!res)
	{
		__android_log_print(ANDROID_LOG_ERROR, LOG_TAG, "Call fdopen(%d) error: %s", fd, strerror(errno));
		close(fd);
		free(tmp_file);
		return NULL;
	}
	unlink(tmp_file);
    __android_log_print(ANDROID_LOG_DEBUG, LOG_TAG, "android_tmpfile create: %s", tmp_file);
	free(tmp_file);
	return res;
}
