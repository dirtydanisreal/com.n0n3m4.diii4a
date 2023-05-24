/*
	Copyright (C) 2012 n0n3m4
	
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

package com.n0n3m4.q3e;

import java.io.File;

import android.app.Activity;
import android.content.pm.ActivityInfo;
import android.os.Build;
import android.os.Bundle;
import android.preference.PreferenceManager;
import android.view.Window;
import android.view.WindowManager;
import android.widget.Toast;
import android.widget.RelativeLayout;
import android.view.ViewGroup;
import android.view.View;
import android.content.SharedPreferences;
import android.annotation.SuppressLint;
import android.graphics.Typeface;

public class Q3EMain extends Activity {
	public static Q3ECallbackObj mAudio;
	public static Q3EView mGLSurfaceView;
    public static String datadir;	
    // k
    private boolean m_hideNav = true;
    private int m_runBackground = 1;
    private int m_renderMemStatus = 0;
    @SuppressLint("InlinedApi")
    private final int m_uiOptions = View.SYSTEM_UI_FLAG_HIDE_NAVIGATION
    | View.SYSTEM_UI_FLAG_IMMERSIVE_STICKY
    | View.SYSTEM_UI_FLAG_LAYOUT_STABLE
    | View.SYSTEM_UI_FLAG_LAYOUT_HIDE_NAVIGATION
    | View.SYSTEM_UI_FLAG_FULLSCREEN;
    @SuppressLint("InlinedApi")
    private final int m_uiOptions_def = View.SYSTEM_UI_FLAG_FULLSCREEN
            | View.SYSTEM_UI_FLAG_LAYOUT_HIDE_NAVIGATION
            | View.SYSTEM_UI_FLAG_LAYOUT_STABLE;
    public static Q3EControlView mControlGLSurfaceView;
    private DebugTextView memoryUsageText;
    private RelativeLayout mainLayout;
    private boolean m_coverEdges = true;
	
	public void ShowMessage(String s)
	{
		Toast.makeText(this, s, Toast.LENGTH_LONG).show();		
	}

	public boolean checkGameFiles()
	{
		if(!new File(datadir).exists())
		{
			ShowMessage("Game files weren't found: put game files to "+datadir);
			this.finish();
			return false;
		}
		
		return true;
	}	
	
    @SuppressLint("ResourceType")
	@Override
	public void onCreate(Bundle savedInstanceState) {
		getWindow().setFlags(WindowManager.LayoutParams.FLAG_FULLSCREEN,
				WindowManager.LayoutParams.FLAG_FULLSCREEN);
		getWindow().addFlags(WindowManager.LayoutParams.FLAG_KEEP_SCREEN_ON);
		requestWindowFeature(Window.FEATURE_NO_TITLE);

        SharedPreferences preferences = PreferenceManager.getDefaultSharedPreferences(this);

        Q3EUtils.usegles20 = Q3EUtils.q3ei.isD3 || Q3EUtils.q3ei.isQ1 || Q3EUtils.q3ei.isD3BFG;
        m_coverEdges = preferences.getBoolean("harm_cover_edges", true);
        if(Build.VERSION.SDK_INT >= Build.VERSION_CODES.P && m_coverEdges)
        {
            WindowManager.LayoutParams lp = getWindow().getAttributes();
            lp.layoutInDisplayCutoutMode = WindowManager.LayoutParams.LAYOUT_IN_DISPLAY_CUTOUT_MODE_SHORT_EDGES;
            getWindow().setAttributes(lp);
        }

        if (Build.VERSION.SDK_INT >= Build.VERSION_CODES.GINGERBREAD) // 9
            setRequestedOrientation(ActivityInfo.SCREEN_ORIENTATION_SENSOR_LANDSCAPE);

        m_hideNav = preferences.getBoolean("harm_hide_nav", true);
        m_renderMemStatus = preferences.getInt("harm_render_mem_status", 0);
        String harm_run_background = preferences.getString("harm_run_background", "1");
        if(null != harm_run_background)
            m_runBackground = Integer.parseInt(harm_run_background);
        else
            m_runBackground = 1;
        Q3EUtils.q3ei.joystick_release_range = preferences.getFloat(Q3EUtils.pref_harm_joystick_release_range, 0.0f);
        //k
        SetupUIFlags();
/*        if(m_hideNav)
        {
            if (Build.VERSION.SDK_INT >= Build.VERSION_CODES.HONEYCOMB) {
				final View decorView = getWindow().getDecorView();
				decorView.setSystemUiVisibility(m_uiOptions);// This code will always hide the navigation bar
            decorView.setOnSystemUiVisibilityChangeListener(new View.OnSystemUiVisibilityChangeListener(){
                    @Override
                    public void  onSystemUiVisibilityChange(int visibility)
                    {
                        if((visibility & View.SYSTEM_UI_FLAG_FULLSCREEN) == 0)
                        {
                            decorView.setSystemUiVisibility(m_uiOptions);
                        }
                    }
                });
			}
        }*/
        Q3EUtils.q3ei.VOLUME_UP_KEY_CODE = preferences.getInt("harm_volume_up_key", Q3EKeyCodes.KeyCodes.K_F3);
        Q3EUtils.q3ei.VOLUME_DOWN_KEY_CODE = preferences.getInt("harm_volume_down_key", Q3EKeyCodes.KeyCodes.K_F2);
        Q3EUtils.q3ei.SetupEngineLib(); //k setup engine library here again
        Q3EUtils.q3ei.view_motion_control_gyro = preferences.getBoolean(Q3EUtils.pref_harm_view_motion_control_gyro, false);
        Q3EUtils.q3ei.multithread = preferences.getBoolean(Q3EUtils.pref_harm_multithreading, false);
        Q3EUtils.q3ei.function_key_toolbar = preferences.getBoolean(Q3EUtils.pref_harm_function_key_toolbar, false);
		
		super.onCreate(savedInstanceState);
		
/*//k		if (Q3EUtils.q3ei==null)
		{			
			finish();
			try
			{
				//k startActivity(new Intent(this,Class.forName(getPackageName()+".GameLauncher")));//Dirty hack	
				startActivity(new Intent(this,Class.forName("com.n0n3m4.DIII4A.GameLauncher")));//Dirty hack
			}			
			catch (Exception e){e.printStackTrace();};			
			return;
		}*/
		
		datadir=preferences.getString(Q3EUtils.pref_datapath, Q3EUtils.q3ei.default_path);
		if ((datadir.length()>0)&&(datadir.charAt(0)!='/'))//lolwtfisuserdoing?
		{
			datadir="/"+datadir;
			preferences.edit().putString(Q3EUtils.pref_datapath, datadir).commit();
		}
		if(checkGameFiles())
		{
            Q3EJNI.SetRedirectOutputToFile(preferences.getBoolean("harm_redirect_output_to_file", true));
            Q3EJNI.SetNoHandleSignals(preferences.getBoolean("harm_no_handle_signals", false));
            Q3EJNI.SetMultiThread(Q3EUtils.q3ei.multithread);
            if (mAudio==null)
            {
                mAudio = new Q3ECallbackObj();
            }
            Q3EUtils.q3ei.callbackObj = mAudio;
            Q3EJNI.setCallbackObject(mAudio);
			if (mGLSurfaceView==null)
                mGLSurfaceView = new Q3EView(this);
			if (mControlGLSurfaceView==null)
               mControlGLSurfaceView = new Q3EControlView(this);
            mAudio.vw=mControlGLSurfaceView;
            mControlGLSurfaceView.EnableGyroscopeControl(Q3EUtils.q3ei.view_motion_control_gyro);
            float gyroXSens = preferences.getFloat(Q3EUtils.pref_harm_view_motion_gyro_x_axis_sens, Q3EControlView.GYROSCOPE_X_AXIS_SENS); 
            float gyroYSens = preferences.getFloat(Q3EUtils.pref_harm_view_motion_gyro_y_axis_sens, Q3EControlView.GYROSCOPE_Y_AXIS_SENS);
            if(Q3EUtils.q3ei.view_motion_control_gyro && (gyroXSens != 0.0f || gyroYSens != 0.0f))
                mControlGLSurfaceView.SetGyroscopeSens(gyroXSens, gyroYSens);
            mControlGLSurfaceView.RenderView(mGLSurfaceView);
            mainLayout = new RelativeLayout(this);
            RelativeLayout.LayoutParams params;

            params = new RelativeLayout.LayoutParams(ViewGroup.LayoutParams.MATCH_PARENT, ViewGroup.LayoutParams.MATCH_PARENT);

            mainLayout.addView(mGLSurfaceView, params);

            //mControlGLSurfaceView.setZOrderOnTop();
            mControlGLSurfaceView.setZOrderMediaOverlay(true);
            mainLayout.addView(mControlGLSurfaceView, params);

            if(Q3EUtils.q3ei.function_key_toolbar)
            {
                params = new RelativeLayout.LayoutParams(ViewGroup.LayoutParams.MATCH_PARENT, getResources().getDimensionPixelSize(R.dimen.toolbarHeight));
                View key_toolbar = mControlGLSurfaceView.CreateToolbar();
                mainLayout.addView(key_toolbar, params);
            }

            if(m_renderMemStatus > 0) //k
            {
                memoryUsageText = new DebugTextView(mainLayout.getContext());
                params = new RelativeLayout.LayoutParams(ViewGroup.LayoutParams.WRAP_CONTENT, ViewGroup.LayoutParams.WRAP_CONTENT);
                mainLayout.addView(memoryUsageText, params);
                memoryUsageText.setTypeface(Typeface.MONOSPACE);
            }

            setContentView(mainLayout);

            mControlGLSurfaceView.requestFocus();
		}
		else
		{
			finish();
		}
	}

    @Override
    public void onAttachedToWindow() {
        super.onAttachedToWindow();

        if(mControlGLSurfaceView != null)
        {
            View toolbar = mControlGLSurfaceView.Toolbar();
            if(toolbar != null)
            {
                if(m_coverEdges)
                {
                    int x = Q3EUtils.GetEdgeHeight(this, true);
                    if(x != 0)
                        toolbar.setX(x);
                }
                int[] size = Q3EUtils.GetNormalScreenSize(this);
                ViewGroup.LayoutParams layoutParams = toolbar.getLayoutParams();
                layoutParams.width = size[0];
                toolbar.setLayoutParams(layoutParams);
                //mainLayout.requestLayout();
            }
        }
    }

    @Override
	protected void onDestroy() {
        if(null != mGLSurfaceView)
            mGLSurfaceView.Shutdown();
		super.onDestroy();
		if(null != mAudio)
		    mAudio.OnDestroy();
	}

	@Override
	protected void onPause() {
		super.onPause();
        
        //k
        if(memoryUsageText != null)
            memoryUsageText.Stop();

        if(m_runBackground < 2)
		if(mAudio != null)
		{
			mAudio.pause();			
		}

        if(mGLSurfaceView != null)
        {
            mGLSurfaceView.Pause();
        }

        if(mControlGLSurfaceView != null)
        {
            mControlGLSurfaceView.Pause();
        }
        Q3EUtils.CloseVKB();
	}

	@Override
	protected void onResume() {
		super.onResume();						

        //k
        if(memoryUsageText != null/* && m_renderMemStatus > 0*/)
            memoryUsageText.Start(m_renderMemStatus * 1000);

        //k if(m_runBackground < 1)
		if(mGLSurfaceView != null)
		{
			mGLSurfaceView.Resume();
		}			
        if(mControlGLSurfaceView != null)
        {
            mControlGLSurfaceView.Resume();
		}			

        //k if(m_runBackground < 2)
		if(mAudio != null)
		{			
			mAudio.resume();
		}
	}

    @Override
    public void onWindowFocusChanged(boolean hasFocus)
    {
        super.onWindowFocusChanged(hasFocus);
        SetupUIFlags();
    }

    private void SetupUIFlags()
    {
        final View decorView = getWindow().getDecorView();
        if(m_hideNav)
            decorView.setSystemUiVisibility(m_uiOptions);
        else
            decorView.setSystemUiVisibility(m_uiOptions_def);
    }
}
