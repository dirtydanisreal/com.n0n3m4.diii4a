#ifndef _KARIN_GLSL_SHADER_330_H
#define _KARIN_GLSL_SHADER_330_H

// Unuse C++11 raw string literals for Traditional C++98

// diffuse map
GLSL_SHADER const char ES3_DEFAULT_VERT[] =
"#version 300 es\n"
"//#pragma optimize(off)\n"
"\n"
"precision mediump float;\n"
"\n"
"in lowp vec4 attr_Color;\n"
"in vec4 attr_TexCoord;\n"
"in highp vec4 attr_Vertex;\n"
"\n"
"uniform highp mat4 u_modelViewProjectionMatrix;\n"
"uniform mat4 u_textureMatrix;\n"
"uniform lowp vec4 u_colorAdd;\n"
"uniform lowp vec4 u_colorModulate;\n"
"\n"
"out vec2 var_TexDiffuse;\n"
"out lowp vec4 var_Color;\n"
"\n"
"void main(void)\n"
"{\n"
	"var_TexDiffuse = (u_textureMatrix * attr_TexCoord).xy;\n"
"\n"
	"var_Color = (attr_Color / 255.0) * u_colorModulate + u_colorAdd;\n"
"\n"
	"gl_Position = u_modelViewProjectionMatrix * attr_Vertex;\n"
"}\n"
;
GLSL_SHADER const char ES3_DEFAULT_FRAG[] =
"#version 300 es\n"
"//#pragma optimize(off)\n"
"\n"
"precision mediump float;\n"
"\n"
"uniform sampler2D u_fragmentMap0;\n"
"uniform lowp vec4 u_glColor;\n"
"\n"
"in vec2 var_TexDiffuse;\n"
"in lowp vec4 var_Color;\n"
"out vec4 _gl_FragColor;\n"
"\n"
"void main(void)\n"
"{\n"
	"_gl_FragColor = texture(u_fragmentMap0, var_TexDiffuse) * u_glColor * var_Color;\n"
"}\n"
;

// shadow
GLSL_SHADER const char ES3_SHADOW_VERT[] =
"#version 300 es\n"
"//#pragma optimize(off)\n"
"\n"
"precision mediump float;\n"
"\n"
"in highp vec4 attr_Vertex;\n"
"\n"
"uniform highp mat4 u_modelViewProjectionMatrix;\n"
"uniform lowp vec4 u_glColor;\n"
"uniform vec4 u_lightOrigin;\n"
"\n"
"out lowp vec4 var_Color;\n"
"\n"
"void main(void)\n"
"{\n"
	"gl_Position = u_modelViewProjectionMatrix * (attr_Vertex.w * u_lightOrigin + attr_Vertex - u_lightOrigin);\n"
"\n"
	"var_Color = u_glColor;\n"
"}\n"
;
GLSL_SHADER const char ES3_SHADOW_FRAG[] =
"#version 300 es\n"
"//#pragma optimize(off)\n"
"\n"
"precision lowp float;\n"
"\n"
"in lowp vec4 var_Color;\n"
"out vec4 _gl_FragColor;\n"
"\n"
"void main(void)\n"
"{\n"
	"_gl_FragColor = var_Color;\n"
"}\n"
;

// UNUSED
GLSL_SHADER const char ES3_HEATHAZE_VERT[] =
"#version 300 es\n"
"//#pragma optimize(off)\n"
"\n"
"precision mediump float;\n"
"\n"
"in vec3 attr_Bitangent;\n"
"in vec3 attr_Normal;\n"
"in vec3 attr_Tangent;\n"
"in lowp vec4 attr_Color;\n"
"in vec4 attr_TexCoord;\n"
"in highp vec4 attr_Vertex;\n"
"\n"
"uniform highp mat4 u_modelViewProjectionMatrix;\n"
"\n"
"void main(void)\n"
"{\n"
	"gl_Position = u_modelViewProjectionMatrix * attr_Vertex;\n"
"}\n"
;
GLSL_SHADER const char ES3_HEATHAZE_FRAG[] =
"#version 300 es\n"
"//#pragma optimize(off)\n"
"\n"
"precision mediump float;\n"
"\n"
"uniform sampler2D u_fragmentMap0;\n"
"uniform sampler2D u_fragmentMap1;\n"
"uniform sampler2D u_fragmentMap2;\n"
"uniform sampler2D u_fragmentMap3;\n"
"out vec4 _gl_FragColor;\n"
"\n"
"void main(void)\n"
"{\n"
	"//_gl_FragColor = texture(u_fragmentMap0, vec2(0.5, 0.5));\n"
	"_gl_FragColor = vec4(1.0, 0.0, 0.0, 1.0);\n"
"}\n"
;

// interaction
GLSL_SHADER const char ES3_INTERACTION_VERT[] =
"#version 300 es\n"
"//#pragma optimize(off)\n"
"\n"
"precision mediump float;\n"
"\n"
"//#define BLINN_PHONG\n"
"\n"
"out vec2 var_TexDiffuse;\n"
"out vec2 var_TexNormal;\n"
"out vec2 var_TexSpecular;\n"
"out vec4 var_TexLight;\n"
"out lowp vec4 var_Color;\n"
"out vec3 var_L;\n"
"#if defined(BLINN_PHONG)\n"
"out vec3 var_H;\n"
"#else\n"
"out vec3 var_V;\n"
"#endif\n"
"\n"
"in vec4 attr_TexCoord;\n"
"in vec3 attr_Tangent;\n"
"in vec3 attr_Bitangent;\n"
"in vec3 attr_Normal;\n"
"in highp vec4 attr_Vertex;\n"
"in lowp vec4 attr_Color;\n"
"\n"
"uniform vec4 u_lightProjectionS;\n"
"uniform vec4 u_lightProjectionT;\n"
"uniform vec4 u_lightFalloff;\n"
"uniform vec4 u_lightProjectionQ;\n"
"uniform lowp vec4 u_colorModulate;\n"
"uniform lowp vec4 u_colorAdd;\n"
"uniform lowp vec4 u_glColor;\n"
"\n"
"uniform vec4 u_lightOrigin;\n"
"uniform vec4 u_viewOrigin;\n"
"\n"
"uniform vec4 u_bumpMatrixS;\n"
"uniform vec4 u_bumpMatrixT;\n"
"uniform vec4 u_diffuseMatrixS;\n"
"uniform vec4 u_diffuseMatrixT;\n"
"uniform vec4 u_specularMatrixS;\n"
"uniform vec4 u_specularMatrixT;\n"
"\n"
"uniform highp mat4 u_modelViewProjectionMatrix;\n"
"\n"
"void main(void)\n"
"{\n"
	"mat3 M = mat3(attr_Tangent, attr_Bitangent, attr_Normal);\n"
"\n"
	"var_TexNormal.x = dot(u_bumpMatrixS, attr_TexCoord);\n"
	"var_TexNormal.y = dot(u_bumpMatrixT, attr_TexCoord);\n"
"\n"
	"var_TexDiffuse.x = dot(u_diffuseMatrixS, attr_TexCoord);\n"
	"var_TexDiffuse.y = dot(u_diffuseMatrixT, attr_TexCoord);\n"
"\n"
	"var_TexSpecular.x = dot(u_specularMatrixS, attr_TexCoord);\n"
	"var_TexSpecular.y = dot(u_specularMatrixT, attr_TexCoord);\n"
"\n"
	"var_TexLight.x = dot(u_lightProjectionS, attr_Vertex);\n"
	"var_TexLight.y = dot(u_lightProjectionT, attr_Vertex);\n"
	"var_TexLight.z = dot(u_lightFalloff, attr_Vertex);\n"
	"var_TexLight.w = dot(u_lightProjectionQ, attr_Vertex);\n"
"\n"
	"vec3 L = u_lightOrigin.xyz - attr_Vertex.xyz;\n"
	"vec3 V = u_viewOrigin.xyz - attr_Vertex.xyz;\n"
"#if defined(BLINN_PHONG)\n"
	"vec3 H = normalize(L) + normalize(V);\n"
"#endif\n"
"\n"
	"var_L = L * M;\n"
"#if defined(BLINN_PHONG)\n"
	"var_H = H * M;\n"
"#else\n"
	"var_V = V * M;\n"
"#endif\n"
"\n"
	"var_Color = (attr_Color / 255.0) * u_colorModulate + u_colorAdd;\n"
"\n"
	"gl_Position = u_modelViewProjectionMatrix * attr_Vertex;\n"
"}\n"
;
GLSL_SHADER const char ES3_INTERACTION_FRAG[] =
"#version 300 es\n"
"//#pragma optimize(off)\n"
"\n"
"precision mediump float;\n"
"\n"
"//#define BLINN_PHONG\n"
"\n"
"//#define HALF_LAMBERT\n"
"\n"
"in vec2 var_TexDiffuse;\n"
"in vec2 var_TexNormal;\n"
"in vec2 var_TexSpecular;\n"
"in vec4 var_TexLight;\n"
"in lowp vec4 var_Color;\n"
"in vec3 var_L;\n"
"#if defined(BLINN_PHONG)\n"
"in vec3 var_H;\n"
"#else\n"
"in vec3 var_V;\n"
"#endif\n"
"\n"
"uniform vec4 u_diffuseColor;\n"
"uniform vec4 u_specularColor;\n"
"uniform float u_specularExponent;\n"
"\n"
"uniform sampler2D u_fragmentMap0;	/* u_bumpTexture */\n"
"uniform sampler2D u_fragmentMap1;	/* u_lightFalloffTexture */\n"
"uniform sampler2D u_fragmentMap2;	/* u_lightProjectionTexture */\n"
"uniform sampler2D u_fragmentMap3;	/* u_diffuseTexture */\n"
"uniform sampler2D u_fragmentMap4;	/* u_specularTexture */\n"
"uniform sampler2D u_fragmentMap5;	/* u_specularFalloffTexture */\n"
"out vec4 _gl_FragColor;\n"
"\n"
"void main(void)\n"
"{\n"
	"//float u_specularExponent = 4.0;\n"
"\n"
	"vec3 L = normalize(var_L);\n"
"#if defined(BLINN_PHONG)\n"
	"vec3 H = normalize(var_H);\n"
	"vec3 N = 2.0 * texture(u_fragmentMap0, var_TexNormal.st).agb - 1.0;\n"
"#else\n"
	"vec3 V = normalize(var_V);\n"
	"vec3 N = normalize(2.0 * texture(u_fragmentMap0, var_TexNormal.st).agb - 1.0);\n"
"#endif\n"
"\n"
	"float NdotL = clamp(dot(N, L), 0.0, 1.0);\n"
"#if defined(HALF_LAMBERT)\n"
	"NdotL *= 0.5;\n"
	"NdotL += 0.5;\n"
	"NdotL = NdotL * NdotL;\n"
"#endif\n"
"#if defined(BLINN_PHONG)\n"
	"float NdotH = clamp(dot(N, H), 0.0, 1.0);\n"
"#endif\n"
"\n"
	"vec3 lightProjection = textureProj(u_fragmentMap2, var_TexLight.xyw).rgb;\n"
	"vec3 lightFalloff = texture(u_fragmentMap1, vec2(var_TexLight.z, 0.5)).rgb;\n"
	"vec3 diffuseColor = texture(u_fragmentMap3, var_TexDiffuse).rgb * u_diffuseColor.rgb;\n"
	"vec3 specularColor = 2.0 * texture(u_fragmentMap4, var_TexSpecular).rgb * u_specularColor.rgb;\n"
"\n"
"#if defined(BLINN_PHONG)\n"
	"float specularFalloff = pow(NdotH, u_specularExponent);\n"
"#else\n"
	"vec3 R = -reflect(L, N);\n"
	"float RdotV = clamp(dot(R, V), 0.0, 1.0);\n"
	"float specularFalloff = pow(RdotV, u_specularExponent);\n"
"#endif\n"
"\n"
	"vec3 color;\n"
	"color = diffuseColor;\n"
	"color += specularFalloff * specularColor;\n"
	"color *= NdotL * lightProjection;\n"
	"color *= lightFalloff;\n"
"\n"
	"_gl_FragColor = vec4(color, 1.0) * var_Color;\n"
"}\n"
;

// z-fill
GLSL_SHADER const char ES3_ZFILL_VERT[] =
"#version 300 es\n"
"//#pragma optimize(off)\n"
"\n"
"precision mediump float;\n"
"\n"
"in vec4 attr_TexCoord;\n"
"in highp vec4 attr_Vertex;\n"
"\n"
"uniform mat4 u_textureMatrix;\n"
"uniform highp mat4 u_modelViewProjectionMatrix;\n"
"\n"
"out vec2 var_TexDiffuse;\n"
"\n"
"void main(void)\n"
"{\n"
"	var_TexDiffuse = (u_textureMatrix * attr_TexCoord).xy;\n"
"\n"
"	gl_Position = u_modelViewProjectionMatrix * attr_Vertex;\n"
"}\n"
;
GLSL_SHADER const char ES3_ZFILL_FRAG[] =
"#version 300 es\n"
"//#pragma optimize(off)\n"
"\n"
"precision mediump float;\n"
"\n"
"uniform sampler2D u_fragmentMap0;\n"
"uniform lowp float u_alphaTest;\n"
"uniform lowp vec4 u_glColor;\n"
"\n"
"in vec2 var_TexDiffuse;\n"
"out vec4 _gl_FragColor;\n"
"\n"
"void main(void)\n"
"{\n"
	"if (u_alphaTest > texture(u_fragmentMap0, var_TexDiffuse).a) {\n"
		"discard;\n"
	"}\n"
"\n"
	"_gl_FragColor = u_glColor;\n"
"}\n"
;

// cubemap
GLSL_SHADER const char ES3_CUBEMAP_VERT[] =
"#version 300 es\n"
"//#pragma optimize(off)\n"
"\n"
"precision mediump float;\n"
"\n"
"in lowp vec4 attr_Color;\n"
"in vec4 attr_TexCoord;\n"
"in highp vec4 attr_Vertex;\n"
  "\n"
"uniform highp mat4 u_modelViewProjectionMatrix;\n"
"uniform mat4 u_textureMatrix;\n"
"uniform lowp vec4 u_colorAdd;\n"
"uniform lowp vec4 u_colorModulate;\n"
"uniform vec4 u_viewOrigin;\n"
"\n"
"out vec3 var_TexCoord;\n"
"out lowp vec4 var_Color;\n"
"\n"
"void main(void)\n"
"{\n"
"  var_TexCoord = (u_textureMatrix * attr_TexCoord).xyz;\n"
"\n"
  "var_Color = (attr_Color / 255.0) * u_colorModulate + u_colorAdd;\n"
"\n"
  "gl_Position = u_modelViewProjectionMatrix * attr_Vertex;\n"
"}\n"
;
GLSL_SHADER const char ES3_CUBEMAP_FRAG[] =
"#version 300 es\n"
"//#pragma optimize(off)\n"
"\n"
"precision mediump float;\n"
"\n"
"in vec3 var_TexCoord;\n"
"in lowp vec4 var_Color;\n"
"\n"
"uniform samplerCube u_fragmentCubeMap0;\n"
"uniform lowp vec4 u_glColor;\n"
"out vec4 _gl_FragColor;\n"
"\n"
"void main(void)\n"
"{\n"
  "_gl_FragColor = texture(u_fragmentCubeMap0, var_TexCoord) * u_glColor * var_Color;\n"
"}\n"
;

// reflection cubemap
GLSL_SHADER const char ES3_REFLECTION_CUBEMAP_VERT[] =
"#version 300 es\n"
"//#pragma optimize(off)\n"
"\n"
"precision mediump float;\n"
"\n"
"in highp vec4 attr_Vertex;\n"
"in lowp vec4 attr_Color;\n"
"in vec3 attr_TexCoord;\n"
"\n"
"uniform highp mat4 u_modelViewProjectionMatrix;\n"
"uniform mat4 u_modelViewMatrix;\n"
"uniform mat4 u_textureMatrix;\n"
"uniform lowp vec4 u_colorAdd;\n"
"uniform lowp vec4 u_colorModulate;\n"
"\n"
"out vec3 var_TexCoord;\n"
"out lowp vec4 var_Color;\n"
"\n"
"void main(void)\n"
"{\n"
  "var_TexCoord = (u_textureMatrix * reflect( normalize( u_modelViewMatrix * attr_Vertex ),\n"
                                            "// This suppose the modelView matrix is orthogonal\n"
                                            "// Otherwise, we should use the inverse transpose\n"
                                            "u_modelViewMatrix * vec4(attr_TexCoord,0.0) )).xyz ;\n"
"\n"
  "var_Color = (attr_Color / 255.0) * u_colorModulate + u_colorAdd;\n"
  "\n"
  "gl_Position = u_modelViewProjectionMatrix * attr_Vertex;\n"
"}\n"
;

// fog
GLSL_SHADER const char ES3_FOG_VERT[] =
"#version 300 es\n"
"//#pragma optimize(off)\n"
"\n"
"precision mediump float;\n"
"\n"
"in highp vec4 attr_Vertex;      // input Vertex Coordinates\n"
"\n"
"uniform highp mat4 u_modelViewProjectionMatrix;\n"
"uniform mat4 u_fogMatrix;        // fogPlanes 0, 1, 3 (CATION: not 2!), 2\n"
"\n"
"out vec2 var_TexFog;         // output Fog TexCoord\n"
"out vec2 var_TexFogEnter;    // output FogEnter TexCoord\n"
"\n"
"void main(void)\n"
"{\n"
  "gl_Position = u_modelViewProjectionMatrix * attr_Vertex;\n"
"\n"
  "// What will be computed:\n"
  "//\n"
  "// var_TexFog.x      = dot(u_fogMatrix[0], attr_Vertex);\n"
  "// var_TexFog.y      = dot(u_fogMatrix[1], attr_Vertex);\n"
  "// var_TexFogEnter.x = dot(u_fogMatrix[2], attr_Vertex);\n"
  "// var_TexFogEnter.y = dot(u_fogMatrix[3], attr_Vertex);\n"
"\n"
  "// Optimized version:\n"
  "var_TexFog      = vec2(dot(u_fogMatrix[0], attr_Vertex),dot(u_fogMatrix[1], attr_Vertex));\n"
  "var_TexFogEnter = vec2(dot(u_fogMatrix[2], attr_Vertex),dot(u_fogMatrix[3], attr_Vertex));\n"
"}\n"
;
GLSL_SHADER const char ES3_FOG_FRAG[] =
"#version 300 es\n"
"//#pragma optimize(off)\n"
"\n"
"precision mediump float;\n"
"\n"
"in vec2 var_TexFog;            // input Fog TexCoord\n"
"in vec2 var_TexFogEnter;       // input FogEnter TexCoord\n"
"\n"
"uniform sampler2D u_fragmentMap0;   // Fog Image\n"
"uniform sampler2D u_fragmentMap1;   // Fog Enter Image\n"
"uniform lowp vec4 u_fogColor;       // Fog Color\n"
"out vec4 _gl_FragColor;\n"
"\n"
"void main(void)\n"
"{\n"
  "_gl_FragColor = texture( u_fragmentMap0, var_TexFog ) * texture( u_fragmentMap1, var_TexFogEnter ) * vec4(u_fogColor.rgb, 1.0);\n"
"}\n"
;

// blend light
GLSL_SHADER const char ES3_BLENDLIGHT_VERT[] =
"#version 300 es\n"
"//#pragma optimize(off)\n"
"\n"
"precision mediump float;\n"
"\n"
"in highp vec4 attr_Vertex;\n"
"\n"
"uniform highp mat4 u_modelViewProjectionMatrix;\n"
"uniform mat4 u_fogMatrix;\n"
"\n"
"out vec2 var_TexFog;\n"
"out vec2 var_TexFogEnter;\n"
"\n"
"void main(void)\n"
"{\n"
  "gl_Position = u_modelViewProjectionMatrix * attr_Vertex;\n"
"\n"
  "// What will be computed:\n"
  "//\n"
  "// vec4 tc;\n"
  "// tc.x = dot( u_fogMatrix[0], attr_Vertex );\n"
  "// tc.y = dot( u_fogMatrix[1], attr_Vertex );\n"
  "// tc.z = 0.0;\n"
  "// tc.w = dot( u_fogMatrix[2], attr_Vertex );\n"
  "// var_TexFog.xy = tc.xy / tc.w;\n"
  "//\n"
  "// var_TexFogEnter.x = dot( u_fogMatrix[3], attr_Vertex );\n"
  "// var_TexFogEnter.y = 0.5;\n"
"\n"
  "// Optimized version:\n"
  "//\n"
  "var_TexFog = vec2(dot( u_fogMatrix[0], attr_Vertex ), dot( u_fogMatrix[1], attr_Vertex )) / dot( u_fogMatrix[2], attr_Vertex );\n"
  "var_TexFogEnter = vec2( dot( u_fogMatrix[3], attr_Vertex ), 0.5 );\n"
"}\n"
;

// z-fill with clip plane
GLSL_SHADER const char ES3_ZFILLCLIP_VERT[] =
"#version 300 es\n"
"//#pragma optimize(off)\n"
"\n"
"precision mediump float;\n"
"\n"
"in highp vec4 attr_Vertex;\n"
"in vec4 attr_TexCoord;\n"
"\n"
"uniform highp mat4 u_modelViewProjectionMatrix;\n"
"uniform mat4 u_textureMatrix;\n"
"uniform vec4 u_clipPlane;\n"
"\n"
"out vec2 var_TexDiffuse;\n"
"out vec2 var_TexClip;\n"
"\n"
"void main(void)\n"
"{\n"
"	var_TexDiffuse = (u_textureMatrix * attr_TexCoord).xy;\n"
"\n"
  "var_TexClip = vec2( dot( u_clipPlane, attr_Vertex), 0.5 );\n"
"\n"
  "gl_Position = u_modelViewProjectionMatrix * attr_Vertex;\n"
"}\n"
;
GLSL_SHADER const char ES3_ZFILLCLIP_FRAG[] =
"#version 300 es\n"
"//#pragma optimize(off)\n"
"\n"
"precision mediump float;\n"
"\n"
"in vec2 var_TexDiffuse;\n"
"in vec2 var_TexClip;\n"
"\n"
"uniform sampler2D u_fragmentMap0;\n"
"uniform sampler2D u_fragmentMap1;\n"
"uniform lowp float u_alphaTest;\n"
"uniform lowp vec4 u_glColor;\n"
"out vec4 _gl_FragColor;\n"
"\n"
"void main(void)\n"
"{\n"
    "if (u_alphaTest > (texture(u_fragmentMap0, var_TexDiffuse).a * texture(u_fragmentMap1, var_TexClip).a) ) {\n"
      "discard;\n"
    "}\n"
	"\n"
  "_gl_FragColor = u_glColor;\n"
"}\n"
;

// interaction(Blinn-phong)
GLSL_SHADER const char ES3_INTERACTION_BLINNPHONG_VERT[] =
"#version 300 es\n"
"//#pragma optimize(off)\n"
"\n"
"precision mediump float;\n"
"\n"
"#define BLINN_PHONG\n"
"\n"
"out vec2 var_TexDiffuse;\n"
"out vec2 var_TexNormal;\n"
"out vec2 var_TexSpecular;\n"
"out vec4 var_TexLight;\n"
"out lowp vec4 var_Color;\n"
"out vec3 var_L;\n"
"#if defined(BLINN_PHONG)\n"
"out vec3 var_H;\n"
"#else\n"
"out vec3 var_V;\n"
"#endif\n"
"\n"
"in vec4 attr_TexCoord;\n"
"in vec3 attr_Tangent;\n"
"in vec3 attr_Bitangent;\n"
"in vec3 attr_Normal;\n"
"in highp vec4 attr_Vertex;\n"
"in lowp vec4 attr_Color;\n"
"\n"
"uniform vec4 u_lightProjectionS;\n"
"uniform vec4 u_lightProjectionT;\n"
"uniform vec4 u_lightFalloff;\n"
"uniform vec4 u_lightProjectionQ;\n"
"uniform lowp vec4 u_colorModulate;\n"
"uniform lowp vec4 u_colorAdd;\n"
"uniform lowp vec4 u_glColor;\n"
"\n"
"uniform vec4 u_lightOrigin;\n"
"uniform vec4 u_viewOrigin;\n"
"\n"
"uniform vec4 u_bumpMatrixS;\n"
"uniform vec4 u_bumpMatrixT;\n"
"uniform vec4 u_diffuseMatrixS;\n"
"uniform vec4 u_diffuseMatrixT;\n"
"uniform vec4 u_specularMatrixS;\n"
"uniform vec4 u_specularMatrixT;\n"
"\n"
"uniform highp mat4 u_modelViewProjectionMatrix;\n"
"\n"
"void main(void)\n"
"{\n"
	"mat3 M = mat3(attr_Tangent, attr_Bitangent, attr_Normal);\n"
"\n"
	"var_TexNormal.x = dot(u_bumpMatrixS, attr_TexCoord);\n"
	"var_TexNormal.y = dot(u_bumpMatrixT, attr_TexCoord);\n"
"\n"
	"var_TexDiffuse.x = dot(u_diffuseMatrixS, attr_TexCoord);\n"
	"var_TexDiffuse.y = dot(u_diffuseMatrixT, attr_TexCoord);\n"
"\n"
	"var_TexSpecular.x = dot(u_specularMatrixS, attr_TexCoord);\n"
	"var_TexSpecular.y = dot(u_specularMatrixT, attr_TexCoord);\n"
"\n"
	"var_TexLight.x = dot(u_lightProjectionS, attr_Vertex);\n"
	"var_TexLight.y = dot(u_lightProjectionT, attr_Vertex);\n"
	"var_TexLight.z = dot(u_lightFalloff, attr_Vertex);\n"
	"var_TexLight.w = dot(u_lightProjectionQ, attr_Vertex);\n"
"\n"
	"vec3 L = u_lightOrigin.xyz - attr_Vertex.xyz;\n"
	"vec3 V = u_viewOrigin.xyz - attr_Vertex.xyz;\n"
"#if defined(BLINN_PHONG)\n"
	"vec3 H = normalize(L) + normalize(V);\n"
"#endif\n"
"\n"
	"var_L = L * M;\n"
"#if defined(BLINN_PHONG)\n"
	"var_H = H * M;\n"
"#else\n"
    "var_V = V * M;\n"
"#endif\n"
"\n"
	"var_Color = (attr_Color / 255.0) * u_colorModulate + u_colorAdd;\n"
"\n"
	"gl_Position = u_modelViewProjectionMatrix * attr_Vertex;\n"
"}\n"
;
GLSL_SHADER const char ES3_INTERACTION_BLINNPHONG_FRAG[] =
"#version 300 es\n"
"//#pragma optimize(off)\n"
"\n"
"precision mediump float;\n"
"\n"
"#define BLINN_PHONG\n"
"\n"
"//#define HALF_LAMBERT\n"
"\n"
"in vec2 var_TexDiffuse;\n"
"in vec2 var_TexNormal;\n"
"in vec2 var_TexSpecular;\n"
"in vec4 var_TexLight;\n"
"in lowp vec4 var_Color;\n"
"in vec3 var_L;\n"
"#if defined(BLINN_PHONG)\n"
"in vec3 var_H;\n"
"#else\n"
"in vec3 var_V;\n"
"#endif\n"
"\n"
"uniform vec4 u_diffuseColor;\n"
"uniform vec4 u_specularColor;\n"
"uniform float u_specularExponent;\n"
"\n"
"uniform sampler2D u_fragmentMap0;	/* u_bumpTexture */\n"
"uniform sampler2D u_fragmentMap1;	/* u_lightFalloffTexture */\n"
"uniform sampler2D u_fragmentMap2;	/* u_lightProjectionTexture */\n"
"uniform sampler2D u_fragmentMap3;	/* u_diffuseTexture */\n"
"uniform sampler2D u_fragmentMap4;	/* u_specularTexture */\n"
"uniform sampler2D u_fragmentMap5;	/* u_specularFalloffTexture */\n"
"out vec4 _gl_FragColor;\n"
"\n"
"void main(void)\n"
"{\n"
	"//float u_specularExponent = 4.0;\n"
"\n"
	"vec3 L = normalize(var_L);\n"
"#if defined(BLINN_PHONG)\n"
	"vec3 H = normalize(var_H);\n"
	"vec3 N = 2.0 * texture(u_fragmentMap0, var_TexNormal.st).agb - 1.0;\n"
"#else\n"
	"vec3 V = normalize(var_V);\n"
	"vec3 N = normalize(2.0 * texture(u_fragmentMap0, var_TexNormal.st).agb - 1.0);\n"
"#endif\n"
"\n"
	"float NdotL = clamp(dot(N, L), 0.0, 1.0);\n"
"#if defined(HALF_LAMBERT)\n"
	"NdotL *= 0.5;\n"
	"NdotL += 0.5;\n"
	"NdotL = NdotL * NdotL;\n"
"#endif\n"
"#if defined(BLINN_PHONG)\n"
	"float NdotH = clamp(dot(N, H), 0.0, 1.0);\n"
"#endif\n"
"\n"
	"vec3 lightProjection = textureProj(u_fragmentMap2, var_TexLight.xyw).rgb;\n"
	"vec3 lightFalloff = texture(u_fragmentMap1, vec2(var_TexLight.z, 0.5)).rgb;\n"
	"vec3 diffuseColor = texture(u_fragmentMap3, var_TexDiffuse).rgb * u_diffuseColor.rgb;\n"
	"vec3 specularColor = 2.0 * texture(u_fragmentMap4, var_TexSpecular).rgb * u_specularColor.rgb;\n"
"\n"
"#if defined(BLINN_PHONG)\n"
	"float specularFalloff = pow(NdotH, u_specularExponent);\n"
"#else\n"
	"vec3 R = -reflect(L, N);\n"
	"float RdotV = clamp(dot(R, V), 0.0, 1.0);\n"
	"float specularFalloff = pow(RdotV, u_specularExponent);\n"
"#endif\n"
"\n"
	"vec3 color;\n"
	"color = diffuseColor;\n"
	"color += specularFalloff * specularColor;\n"
	"color *= NdotL * lightProjection;\n"
	"color *= lightFalloff;\n"
"\n"
	"_gl_FragColor = vec4(color, 1.0) * var_Color;\n"
"}\n"
;

// diffuse dubemap(UNUSED in game)
GLSL_SHADER const char ES3_DIFFUSE_CUBEMAP_VERT[] =
"#version 300 es\n"
"//#pragma optimize(off)\n"
"\n"
"precision mediump float;\n"
  "\n"
"// In\n"
"in highp vec4 attr_Vertex;\n"
"in lowp vec4 attr_Color;\n"
"in vec3 attr_TexCoord;\n"
  "\n"
"// Uniforms\n"
"uniform highp mat4 u_modelViewProjectionMatrix;\n"
"uniform mat4 u_textureMatrix;\n"
"uniform lowp float u_colorAdd;\n"
"uniform lowp float u_colorModulate;\n"
  "\n"
"// Out\n"
"// gl_Position\n"
"out vec3 var_TexCoord;\n"
"out lowp vec4 var_Color;\n"
  "\n"
"void main(void)\n"
"{\n"
	"var_TexCoord = (u_textureMatrix * vec4(attr_TexCoord, 0.0)).xyz;\n"
"\n"
	"var_Color = (attr_Color / 255.0) * u_colorModulate + u_colorAdd;\n"
"\n"
  "gl_Position = u_modelViewProjectionMatrix * attr_Vertex;\n"
"}\n"
;

// texgen(Only used in D3XP)
GLSL_SHADER const char ES3_TEXGEN_VERT[] =
"#version 300 es\n"
"//#pragma optimize(off)\n"
"\n"
"precision mediump float;\n"
"\n"
"in highp vec4 attr_Vertex;\n"
"in lowp vec4 attr_Color;\n"
"\n"
"uniform lowp vec4 u_colorAdd;\n"
"uniform lowp vec4 u_colorModulate;\n"
"uniform vec4 u_texgenS;\n"
"uniform vec4 u_texgenT;\n"
"uniform vec4 u_texgenQ;\n"
"uniform mat4 u_textureMatrix;\n"
"uniform highp mat4 u_modelViewProjectionMatrix;\n"
"\n"
"out vec4 var_TexCoord;\n"
"out lowp vec4 var_Color;\n"
"\n"
"void main(void)\n"
"{\n"
	"gl_Position = u_modelViewProjectionMatrix * attr_Vertex;\n"
"\n"
	"vec4 texcoord0 = vec4(dot( u_texgenS, attr_Vertex ), dot( u_texgenT, attr_Vertex ), 0.0, dot( u_texgenQ, attr_Vertex )); \n"
"\n"
	"// multiply the texture matrix in\n"
	"var_TexCoord = vec4(dot( u_textureMatrix[0], texcoord0 ), dot( u_textureMatrix[1], texcoord0), texcoord0.z, texcoord0.w);\n"
"\n"
	"// compute vertex modulation\n"
	"var_Color = (attr_Color / 255.0) * u_colorModulate + u_colorAdd;\n"
"}\n"
;
GLSL_SHADER const char ES3_TEXGEN_FRAG[] =
"#version 300 es\n"
"//#pragma optimize(off)\n"
"\n"
"precision mediump float;\n"
"\n"
"uniform sampler2D u_fragmentMap0;\n"
"uniform lowp vec4 u_glColor;\n"
"\n"
"in vec4 var_TexCoord;\n"
"in lowp vec4 var_Color;\n"
"out vec4 _gl_FragColor;\n"
"\n"
"void main(void)\n"
"{\n"
	"// we always do a projective texture lookup so that we can support texgen\n"
	"// materials without a separate shader. Basic materials will have texture\n"
	"// coordinates with w = 1 which will result in a NOP projection when tex2Dproj\n"
	"// gets called.\n"
	"_gl_FragColor = textureProj( u_fragmentMap0, var_TexCoord.xyw ) * u_glColor * var_Color;\n"
"}\n"
;

#ifdef _SHADOW_MAPPING
// shadow map
GLSL_SHADER const char ES3_DEPTH_VERT[] =
"#version 300 es\n"
"//#pragma optimize(off)\n"
"\n"
"precision mediump float;\n"
"\n"
"in highp vec4 attr_Vertex;\n"
"\n"
"uniform highp mat4 u_modelViewProjectionMatrix;\n"
"uniform highp mat4 u_modelMatrix;\n"
"uniform highp vec4 u_lightOrigin;\n"
"\n"
"uniform highp vec4 globalLightOrigin;\n"
"uniform lowp float u_uniformParm2; // .w 1.0 or 0.0\n"
"\n"
"void main(void)\n"
"{\n"
"	//vec4 pos = attr_Vertex.w * u_lightOrigin + attr_Vertex - u_lightOrigin;\n"
"	float w = max(attr_Vertex.w, u_uniformParm2);\n"
"	vec4 pos = w * u_lightOrigin + vec4(attr_Vertex.xyz, w) - u_lightOrigin;\n"
"	//pos = attr_Vertex - u_lightOrigin; pos = (pos.wwww * u_lightOrigin) + pos;\n"
"	gl_Position = pos * u_modelViewProjectionMatrix;\n"
"}\n"
;
GLSL_SHADER const char ES3_DEPTH_FRAG[] =
"#version 300 es\n"
"//#pragma optimize(off)\n"
"\n"
"precision mediump float;\n"
"\n"
"uniform highp vec4 globalLightOrigin;\n"
"uniform highp float u_uniformParm1; // frustum z-near\n"
"\n"
"out vec4 _gl_FragColor;\n"
"\n"
"void main(void)\n"
"{\n"
"    _gl_FragColor = vec4((gl_FragCoord.z + 1.0) * 0.5, 0.0, 0.0, 1.0);\n"
"}\n"
;

// interaction(shadow mapping)
GLSL_SHADER const char ES3_INTERACTION_SHADOW_MAPPING_VERT[] =
        "#version 300 es\n"
        "//#pragma optimize(off)\n"
        "\n"
        "precision mediump float;\n"
        "\n"
        "//#define BLINN_PHONG\n"
        "\n"
        "out vec2 var_TexDiffuse;\n"
        "out vec2 var_TexNormal;\n"
        "out vec2 var_TexSpecular;\n"
        "out vec4 var_TexLight;\n"
        "out lowp vec4 var_Color;\n"
        "out vec3 var_L;\n"
        "#if defined(BLINN_PHONG)\n"
        "out vec3 var_H;\n"
		"#else\n"
		"out vec3 var_V;\n"
        "#endif\n"
        "\n"
        "in vec4 attr_TexCoord;\n"
        "in vec3 attr_Tangent;\n"
        "in vec3 attr_Bitangent;\n"
        "in vec3 attr_Normal;\n"
        "in highp vec4 attr_Vertex;\n"
        "in lowp vec4 attr_Color;\n"
        "\n"
        "uniform vec4 u_lightProjectionS;\n"
        "uniform vec4 u_lightProjectionT;\n"
        "uniform vec4 u_lightFalloff;\n"
        "uniform vec4 u_lightProjectionQ;\n"
        "uniform lowp vec4 u_colorModulate;\n"
        "uniform lowp vec4 u_colorAdd;\n"
        "uniform lowp vec4 u_glColor;\n"
        "\n"
        "uniform vec4 u_lightOrigin;\n"
        "uniform vec4 u_viewOrigin;\n"
        "\n"
        "uniform vec4 u_bumpMatrixS;\n"
        "uniform vec4 u_bumpMatrixT;\n"
        "uniform vec4 u_diffuseMatrixS;\n"
        "uniform vec4 u_diffuseMatrixT;\n"
        "uniform vec4 u_specularMatrixS;\n"
        "uniform vec4 u_specularMatrixT;\n"
        "\n"
        "uniform highp mat4 u_modelViewProjectionMatrix;\n"
		"\n"
		"uniform highp mat4 u_modelMatrix;\n"
		"uniform highp vec4 globalLightOrigin;\n"
		"\n"
		"#ifdef _HARM_POINT_LIGHT\n"
        "   out highp vec4 var_VertexPosition;\n"
		"   out highp vec3 var_VertexToLight;\n"
		"#else\n"
		"   uniform highp mat4 shadowMVPMatrix;\n"
        "   out highp vec4 var_ShadowCoord;\n"
		"#endif\n"
        "\n"
        "void main(void)\n"
        "{\n"
        "	mat3 M = mat3(attr_Tangent, attr_Bitangent, attr_Normal);\n"
        "\n"
        "	var_TexNormal.x = dot(u_bumpMatrixS, attr_TexCoord);\n"
        "	var_TexNormal.y = dot(u_bumpMatrixT, attr_TexCoord);\n"
        "\n"
        "	var_TexDiffuse.x = dot(u_diffuseMatrixS, attr_TexCoord);\n"
        "	var_TexDiffuse.y = dot(u_diffuseMatrixT, attr_TexCoord);\n"
        "\n"
        "	var_TexSpecular.x = dot(u_specularMatrixS, attr_TexCoord);\n"
        "	var_TexSpecular.y = dot(u_specularMatrixT, attr_TexCoord);\n"
        "\n"
        "	var_TexLight.x = dot(u_lightProjectionS, attr_Vertex);\n"
        "	var_TexLight.y = dot(u_lightProjectionT, attr_Vertex);\n"
        "	var_TexLight.z = dot(u_lightFalloff, attr_Vertex);\n"
        "	var_TexLight.w = dot(u_lightProjectionQ, attr_Vertex);\n"
        "\n"
        "	vec3 L = u_lightOrigin.xyz - attr_Vertex.xyz;\n"
        "	vec3 V = u_viewOrigin.xyz - attr_Vertex.xyz;\n"
        "#if defined(BLINN_PHONG)\n"
        "	vec3 H = normalize(L) + normalize(V);\n"
        "#endif\n"
        "\n"
        "	var_L = L * M;\n"
        "#if defined(BLINN_PHONG)\n"
        "	var_H = H * M;\n"
		"#else\n"
		"	var_V = V * M;\n"
        "#endif\n"
        "\n"
        "	var_Color = (attr_Color / 255.0) * u_colorModulate + u_colorAdd;\n"
        "\n"
		"#ifdef _HARM_POINT_LIGHT\n"
		"	vec4 posInLight = u_modelMatrix * attr_Vertex ;\n"
		"	var_VertexToLight = globalLightOrigin.xyz - posInLight.xyz ;\n"
        "	var_VertexPosition = attr_Vertex;\n"
		"#else\n"
        "	var_ShadowCoord = attr_Vertex * shadowMVPMatrix;\n"
		"#endif\n"
        "	gl_Position = u_modelViewProjectionMatrix * attr_Vertex;\n"
        "}\n"
;
GLSL_SHADER const char ES3_INTERACTION_SHADOW_MAPPING_FRAG[] =
        "#version 300 es\n"
        "//#pragma optimize(off)\n"
        "\n"
        "precision mediump float;\n"
        "\n"
        "//#define BLINN_PHONG\n"
        "\n"
        "//#define HALF_LAMBERT\n"
        "\n"
        "in vec2 var_TexDiffuse;\n"
        "in vec2 var_TexNormal;\n"
        "in vec2 var_TexSpecular;\n"
        "in vec4 var_TexLight;\n"
        "in lowp vec4 var_Color;\n"
        "in vec3 var_L;\n"
        "#if defined(BLINN_PHONG)\n"
        "in vec3 var_H;\n"
        "#else\n"
        "in vec3 var_V;\n"
        "#endif\n"
        "\n"
        "uniform vec4 u_diffuseColor;\n"
        "uniform vec4 u_specularColor;\n"
        "uniform float u_specularExponent;\n"
        "\n"
        "uniform sampler2D u_fragmentMap0;	/* u_bumpTexture */\n"
        "uniform sampler2D u_fragmentMap1;	/* u_lightFalloffTexture */\n"
        "uniform sampler2D u_fragmentMap2;	/* u_lightProjectionTexture */\n"
        "uniform sampler2D u_fragmentMap3;	/* u_diffuseTexture */\n"
        "uniform sampler2D u_fragmentMap4;	/* u_specularTexture */\n"
        "uniform sampler2D u_fragmentMap5;	/* u_specularFalloffTexture */\n"
		"uniform sampler2DArrayShadow u_fragmentMap6;	/* u_shadowMapTexture */\n"
		"\n"
		"uniform highp vec4 globalLightOrigin;\n"
		"uniform highp float u_uniformParm0; // frustum z-far\n"
		"uniform highp float u_uniformParm1; // frustum z-near\n"
        "uniform lowp float u_uniformParm2; // sample size\n"
		"uniform lowp float u_uniformParm3; // shadow alpha\n"
		"\n"
		"#ifdef _HARM_POINT_LIGHT\n"
		"uniform highp mat4 shadowMVPMatrix[6];\n"
		"in highp vec3 var_VertexToLight;\n"
        "in highp vec4 var_VertexPosition;\n"
		"#else\n"
        "in highp vec4 var_ShadowCoord;\n"
		"#endif\n"
		"out vec4 _gl_FragColor;\n"
        "\n"
        "void main(void)\n"
        "{\n"
        "	//float u_specularExponent = 4.0;\n"
        "\n"
        "	vec3 L = normalize(var_L);\n"
        "#if defined(BLINN_PHONG)\n"
        "	vec3 H = normalize(var_H);\n"
        "	vec3 N = 2.0 * texture(u_fragmentMap0, var_TexNormal.st).agb - 1.0;\n"
        "#else\n"
        "	vec3 V = normalize(var_V);\n"
        "	vec3 N = normalize(2.0 * texture(u_fragmentMap0, var_TexNormal.st).agb - 1.0);\n"
        "#endif\n"
        "\n"
        "	float NdotL = clamp(dot(N, L), 0.0, 1.0);\n"
        "#if defined(HALF_LAMBERT)\n"
        "	NdotL *= 0.5;\n"
        "	NdotL += 0.5;\n"
        "	NdotL = NdotL * NdotL;\n"
        "#endif\n"
        "#if defined(BLINN_PHONG)\n"
        "	float NdotH = clamp(dot(N, H), 0.0, 1.0);\n"
        "#endif\n"
        "\n"
        "	vec3 lightProjection = textureProj(u_fragmentMap2, var_TexLight.xyw).rgb;\n"
        "	vec3 lightFalloff = texture(u_fragmentMap1, vec2(var_TexLight.z, 0.5)).rgb;\n"
        "	vec3 diffuseColor = texture(u_fragmentMap3, var_TexDiffuse).rgb * u_diffuseColor.rgb;\n"
        "	vec3 specularColor = 2.0 * texture(u_fragmentMap4, var_TexSpecular).rgb * u_specularColor.rgb;\n"
        "\n"
        "#if defined(BLINN_PHONG)\n"
        "	float specularFalloff = pow(NdotH, u_specularExponent);\n"
        "#else\n"
        "	vec3 R = -reflect(L, N);\n"
        "	float RdotV = clamp(dot(R, V), 0.0, 1.0);\n"
        "	float specularFalloff = pow(RdotV, u_specularExponent);\n"
        "#endif\n"
        "\n"
		" \n"
		"#define SAMPLES 9\n"
		"vec2 sampleOffsetTable[SAMPLES];\n"
		"sampleOffsetTable[0] = vec2( 0.0, 0.0);\n"
		"sampleOffsetTable[1] = vec2( 1.0, 1.0); sampleOffsetTable[2] = vec2( 1.0, -1.0); sampleOffsetTable[3] = vec2(-1.0, -1.0); sampleOffsetTable[4] = vec2(-1.0, 1.0);\n"
		"sampleOffsetTable[5] = vec2( 1.0, 0.0); sampleOffsetTable[6] = vec2( -1.0, 0.0); sampleOffsetTable[7] = vec2(0.0, -1.0); sampleOffsetTable[8] = vec2(0.0, 1.0);\n"
		"#define BIAS 0.001\n"
		"float shadow = 0.0;\n"
		"#ifdef _HARM_POINT_LIGHT\n"
		"	int shadowIndex = 0;\n"
		"	vec3 toLightGlobal = normalize( var_VertexToLight );\n"
		"	float axis[6];\n"
		"	axis[0] = -toLightGlobal.x;\n"
		"	axis[1] =  toLightGlobal.x;\n"
		"	axis[2] = -toLightGlobal.y;\n"
		"	axis[3] =  toLightGlobal.y;\n"
		"	axis[4] = -toLightGlobal.z;\n"
		"	axis[5] =  toLightGlobal.z;\n"
		"	for( int i = 0; i < 6; i++ ) {\n"
		"		//if( axis[i] > axis[shadowIndex] ) {		shadowIndex = i;	}\n"
		"		shadowIndex = axis[i] > axis[shadowIndex] ? i : shadowIndex;\n"
		"	}\n"
		"	vec4 shadowPosition = var_VertexPosition * shadowMVPMatrix[shadowIndex];\n"
		"	shadowPosition.xyz /= shadowPosition.w;\n"
		"	//shadowPosition.z = shadowPosition.z*0.9991;\n"
		"	shadowPosition.z = shadowPosition.z - BIAS;\n"
		"	shadowPosition.w = float(shadowIndex);\n"
		"	//vec3 c; if(shadowIndex == 0) c = vec3(1.0, 0.0, 0.0); else if(shadowIndex == 1) c = vec3(1.0, 1.0, 0.0); else if(shadowIndex == 2) c = vec3(0.0, 1.0, 0.0); else if(shadowIndex == 3) c = vec3(0.0, 1.0, 1.0); else if(shadowIndex == 4) c = vec3(0.0, 0.0, 1.0); else c = vec3(1.0, 0.0, 1.0);\n"
		" \n"
		"	for (int i = 0; i < SAMPLES; ++i) {\n"
		"		float shadowDepth = texture(u_fragmentMap6, vec4(shadowPosition.xy + sampleOffsetTable[i] * u_uniformParm2, shadowPosition.wz));\n"
		"		//shadow += 1.0 - step(visibility, 0.0) * u_uniformParm3;\n"
		"		shadow += shadowDepth > 0.0 ? 1.0 : u_uniformParm3;\n"
		"	}\n"
		"#else\n"
		"	vec3 shadowPosition = var_ShadowCoord.xyz / var_ShadowCoord.w;\n"
		"	float currentDepth = shadowPosition.z - BIAS;\n"
		" \n"
		"	for (int i = 0; i < SAMPLES; ++i) {\n"
		"		float shadowDepth = texture(u_fragmentMap6, vec4(shadowPosition.st + sampleOffsetTable[i] * u_uniformParm2, 0.0, currentDepth));\n"
		"		//shadow += 1.0 - step(0.0, visibility) * u_uniformParm3;\n"
		"		shadow += shadowDepth > 0.0 ? 1.0 : u_uniformParm3;\n"
		"	}\n"
		"#endif\n"
		"	const float sampleAvg = 1.0 / float(SAMPLES);\n"
        "	shadow *= sampleAvg;\n"
		"\n"
        "	vec3 color;\n"
        "	color = diffuseColor;\n"
        "	color += specularFalloff * specularColor;\n"
        "	color *= NdotL * lightProjection;\n"
        "	color *= lightFalloff;\n"
		"	color *= shadow;\n"
        "\n"
        "	_gl_FragColor = vec4(color, 1.0) * var_Color;\n"
        "}\n"
;
#endif

#endif
