#ifndef _KARIN_GLSL_SHADER_100_H
#define _KARIN_GLSL_SHADER_100_H

// Unuse C++11 raw string literals for Traditional C++98

// diffuse map
GLSL_SHADER const char DEFAULT_VERT[] = 
"#version 100\n"
"//#pragma optimize(off)\n"
"\n"
"precision mediump float;\n"
"\n"
"attribute lowp vec4 attr_Color;\n"
"attribute vec4 attr_TexCoord;\n"
"attribute highp vec4 attr_Vertex;\n"
"\n"
"uniform highp mat4 u_modelViewProjectionMatrix;\n"
"uniform mat4 u_textureMatrix;\n"
"uniform lowp vec4 u_colorAdd;\n"
"uniform lowp vec4 u_colorModulate;\n"
"\n"
"varying vec2 var_TexDiffuse;\n"
"varying lowp vec4 var_Color;\n"
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
GLSL_SHADER const char DEFAULT_FRAG[] = 
"#version 100\n"
"//#pragma optimize(off)\n"
"\n"
"precision mediump float;\n"
"\n"
"uniform sampler2D u_fragmentMap0;\n"
"uniform lowp vec4 u_glColor;\n"
"\n"
"varying vec2 var_TexDiffuse;\n"
"varying lowp vec4 var_Color;\n"
"\n"
"void main(void)\n"
"{\n"
	"gl_FragColor = texture2D(u_fragmentMap0, var_TexDiffuse) * u_glColor * var_Color;\n"
"}\n"
;

// shadow
GLSL_SHADER const char SHADOW_VERT[] = 
"#version 100\n"
"//#pragma optimize(off)\n"
"\n"
"precision mediump float;\n"
"\n"
"attribute highp vec4 attr_Vertex;\n"
"\n"
"uniform highp mat4 u_modelViewProjectionMatrix;\n"
"uniform lowp vec4 u_glColor;\n"
"uniform vec4 u_lightOrigin;\n"
"\n"
"varying lowp vec4 var_Color;\n"
"\n"
"void main(void)\n"
"{\n"
	"gl_Position = u_modelViewProjectionMatrix * (attr_Vertex.w * u_lightOrigin + attr_Vertex - u_lightOrigin);\n"
"\n"
	"var_Color = u_glColor;\n"
"}\n"
;
GLSL_SHADER const char SHADOW_FRAG[] = 
"#version 100\n"
"//#pragma optimize(off)\n"
"\n"
"precision lowp float;\n"
"\n"
"varying lowp vec4 var_Color;\n"
"\n"
"void main(void)\n"
"{\n"
	"gl_FragColor = var_Color;\n"
"}\n"
;

// UNUSED
GLSL_SHADER const char HEATHAZE_VERT[] = 
"#version 100\n"
"//#pragma optimize(off)\n"
"\n"
"precision mediump float;\n"
"\n"
"attribute vec3 attr_Bitangent;\n"
"attribute vec3 attr_Normal;\n"
"attribute vec3 attr_Tangent;\n"
"attribute lowp vec4 attr_Color;\n"
"attribute vec4 attr_TexCoord;\n"
"attribute highp vec4 attr_Vertex;\n"
"\n"
"uniform highp mat4 u_modelViewProjectionMatrix;\n"
"\n"
"void main(void)\n"
"{\n"
	"gl_Position = u_modelViewProjectionMatrix * attr_Vertex;\n"
"}\n"
;
GLSL_SHADER const char HEATHAZE_FRAG[] = 
"#version 100\n"
"//#pragma optimize(off)\n"
"\n"
"precision mediump float;\n"
"\n"
"uniform sampler2D u_fragmentMap0;\n"
"uniform sampler2D u_fragmentMap1;\n"
"uniform sampler2D u_fragmentMap2;\n"
"uniform sampler2D u_fragmentMap3;\n"
"\n"
"void main(void)\n"
"{\n"
	"//gl_FragColor = texture2D(u_fragmentMap0, vec2(0.5, 0.5));\n"
	"gl_FragColor = vec4(1.0, 0.0, 0.0, 1.0);\n"
"}\n"
;

// interaction
GLSL_SHADER const char INTERACTION_VERT[] = 
"#version 100\n"
"//#pragma optimize(off)\n"
"\n"
"precision mediump float;\n"
"\n"
"//#define BLINN_PHONG\n"
"\n"
"varying vec2 var_TexDiffuse;\n"
"varying vec2 var_TexNormal;\n"
"varying vec2 var_TexSpecular;\n"
"varying vec4 var_TexLight;\n"
"varying lowp vec4 var_Color;\n"
"varying vec3 var_L;\n"
"#if defined(BLINN_PHONG)\n"
"varying vec3 var_H;\n"
"#else\n"
"varying vec3 var_V;\n"
"#endif\n"
"\n"
"attribute vec4 attr_TexCoord;\n"
"attribute vec3 attr_Tangent;\n"
"attribute vec3 attr_Bitangent;\n"
"attribute vec3 attr_Normal;\n"
"attribute highp vec4 attr_Vertex;\n"
"attribute lowp vec4 attr_Color;\n"
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
GLSL_SHADER const char INTERACTION_FRAG[] = 
"#version 100\n"
"//#pragma optimize(off)\n"
"\n"
"precision mediump float;\n"
"\n"
"//#define BLINN_PHONG\n"
"\n"
"//#define HALF_LAMBERT\n"
"\n"
"varying vec2 var_TexDiffuse;\n"
"varying vec2 var_TexNormal;\n"
"varying vec2 var_TexSpecular;\n"
"varying vec4 var_TexLight;\n"
"varying lowp vec4 var_Color;\n"
"varying vec3 var_L;\n"
"#if defined(BLINN_PHONG)\n"
"varying vec3 var_H;\n"
"#else\n"
"varying vec3 var_V;\n"
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
"\n"
"void main(void)\n"
"{\n"
	"//float u_specularExponent = 4.0;\n"
"\n"
	"vec3 L = normalize(var_L);\n"
"#if defined(BLINN_PHONG)\n"
	"vec3 H = normalize(var_H);\n"
	"vec3 N = 2.0 * texture2D(u_fragmentMap0, var_TexNormal.st).agb - 1.0;\n"
"#else\n"
	"vec3 V = normalize(var_V);\n"
	"vec3 N = normalize(2.0 * texture2D(u_fragmentMap0, var_TexNormal.st).agb - 1.0);\n"
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
	"vec3 lightProjection = texture2DProj(u_fragmentMap2, var_TexLight.xyw).rgb;\n"
	"vec3 lightFalloff = texture2D(u_fragmentMap1, vec2(var_TexLight.z, 0.5)).rgb;\n"
	"vec3 diffuseColor = texture2D(u_fragmentMap3, var_TexDiffuse).rgb * u_diffuseColor.rgb;\n"
	"vec3 specularColor = 2.0 * texture2D(u_fragmentMap4, var_TexSpecular).rgb * u_specularColor.rgb;\n"
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
	"gl_FragColor = vec4(color, 1.0) * var_Color;\n"
"}\n"
;

// z-fill
GLSL_SHADER const char ZFILL_VERT[] = 
"#version 100\n"
"//#pragma optimize(off)\n"
"\n"
"precision mediump float;\n"
"\n"
"attribute vec4 attr_TexCoord;\n"
"attribute highp vec4 attr_Vertex;\n"
"\n"
"uniform mat4 u_textureMatrix;\n"
"uniform highp mat4 u_modelViewProjectionMatrix;\n"
"\n"
"varying vec2 var_TexDiffuse;\n"
"\n"
"void main(void)\n"
"{\n"
"	var_TexDiffuse = (u_textureMatrix * attr_TexCoord).xy;\n"
"\n"
"	gl_Position = u_modelViewProjectionMatrix * attr_Vertex;\n"
"}\n"
;
GLSL_SHADER const char ZFILL_FRAG[] = 
"#version 100\n"
"//#pragma optimize(off)\n"
"\n"
"precision mediump float;\n"
"\n"
"uniform sampler2D u_fragmentMap0;\n"
"uniform lowp float u_alphaTest;\n"
"uniform lowp vec4 u_glColor;\n"
"\n"
"varying vec2 var_TexDiffuse;\n"
"\n"
"void main(void)\n"
"{\n"
	"if (u_alphaTest > texture2D(u_fragmentMap0, var_TexDiffuse).a) {\n"
		"discard;\n"
	"}\n"
"\n"
	"gl_FragColor = u_glColor;\n"
"}\n"
;

// cubemap
GLSL_SHADER const char CUBEMAP_VERT[] = 
"#version 100\n"
"//#pragma optimize(off)\n"
"\n"
"precision mediump float;\n"
"\n"
"attribute lowp vec4 attr_Color;\n"
"attribute vec4 attr_TexCoord;\n"
"attribute highp vec4 attr_Vertex;\n"
  "\n"
"uniform highp mat4 u_modelViewProjectionMatrix;\n"
"uniform mat4 u_textureMatrix;\n"
"uniform lowp vec4 u_colorAdd;\n"
"uniform lowp vec4 u_colorModulate;\n"
"uniform vec4 u_viewOrigin;\n"
"\n"
"varying vec3 var_TexCoord;\n"
"varying lowp vec4 var_Color;\n"
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
GLSL_SHADER const char CUBEMAP_FRAG[] = 
"#version 100\n"
"//#pragma optimize(off)\n"
"\n"
"precision mediump float;\n"
"\n"
"varying vec3 var_TexCoord;\n"
"varying lowp vec4 var_Color;\n"
"\n"
"uniform samplerCube u_fragmentCubeMap0;\n"
"uniform lowp vec4 u_glColor;\n"
"\n"
"void main(void)\n"
"{\n"
  "gl_FragColor = textureCube(u_fragmentCubeMap0, var_TexCoord) * u_glColor * var_Color;\n"
"}\n"
;

// reflection cubemap
GLSL_SHADER const char REFLECTION_CUBEMAP_VERT[] = 
"#version 100\n"
"//#pragma optimize(off)\n"
"\n"
"precision mediump float;\n"
"\n"
"attribute highp vec4 attr_Vertex;\n"
"attribute lowp vec4 attr_Color;\n"
"attribute vec3 attr_TexCoord;\n"
"\n"
"uniform highp mat4 u_modelViewProjectionMatrix;\n"
"uniform mat4 u_modelViewMatrix;\n"
"uniform mat4 u_textureMatrix;\n"
"uniform lowp vec4 u_colorAdd;\n"
"uniform lowp vec4 u_colorModulate;\n"
"\n"
"varying vec3 var_TexCoord;\n"
"varying lowp vec4 var_Color;\n"
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
GLSL_SHADER const char FOG_VERT[] = 
"#version 100\n"
"//#pragma optimize(off)\n"
"\n"
"precision mediump float;\n"
"\n"
"attribute highp vec4 attr_Vertex;      // input Vertex Coordinates\n"
"\n"
"uniform highp mat4 u_modelViewProjectionMatrix;\n"
"uniform mat4 u_fogMatrix;        // fogPlanes 0, 1, 3 (CATION: not 2!), 2\n"
"\n"
"varying vec2 var_TexFog;         // output Fog TexCoord\n"
"varying vec2 var_TexFogEnter;    // output FogEnter TexCoord\n"
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
GLSL_SHADER const char FOG_FRAG[] =
"#version 100\n"
"//#pragma optimize(off)\n"
"\n"
"precision mediump float;\n"
"\n"
"varying vec2 var_TexFog;            // input Fog TexCoord\n"
"varying vec2 var_TexFogEnter;       // input FogEnter TexCoord\n"
"\n"
"uniform sampler2D u_fragmentMap0;   // Fog Image\n"
"uniform sampler2D u_fragmentMap1;   // Fog Enter Image\n"
"uniform lowp vec4 u_fogColor;       // Fog Color\n"
"\n"
"void main(void)\n"
"{\n"
  "gl_FragColor = texture2D( u_fragmentMap0, var_TexFog ) * texture2D( u_fragmentMap1, var_TexFogEnter ) * vec4(u_fogColor.rgb, 1.0);\n"
"}\n"
;

// blend light
GLSL_SHADER const char BLENDLIGHT_VERT[] = 
"#version 100\n"
"//#pragma optimize(off)\n"
"\n"
"precision mediump float;\n"
"\n"
"attribute highp vec4 attr_Vertex;\n"
"\n"
"uniform highp mat4 u_modelViewProjectionMatrix;\n"
"uniform mat4 u_fogMatrix;\n"
"\n"
"varying vec2 var_TexFog;\n"
"varying vec2 var_TexFogEnter;\n"
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
GLSL_SHADER const char ZFILLCLIP_VERT[] = 
"#version 100\n"
"//#pragma optimize(off)\n"
"\n"
"precision mediump float;\n"
"\n"
"attribute highp vec4 attr_Vertex;\n"
"attribute vec4 attr_TexCoord;\n"
"\n"
"uniform highp mat4 u_modelViewProjectionMatrix;\n"
"uniform mat4 u_textureMatrix;\n"
"uniform vec4 u_clipPlane;\n"
"\n"
"varying vec2 var_TexDiffuse;\n"
"varying vec2 var_TexClip;\n"
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
GLSL_SHADER const char ZFILLCLIP_FRAG[] = 
"#version 100\n"
"//#pragma optimize(off)\n"
"\n"
"precision mediump float;\n"
"\n"
"varying vec2 var_TexDiffuse;\n"
"varying vec2 var_TexClip;\n"
"\n"
"uniform sampler2D u_fragmentMap0;\n"
"uniform sampler2D u_fragmentMap1;\n"
"uniform lowp float u_alphaTest;\n"
"uniform lowp vec4 u_glColor;\n"
"\n"
"void main(void)\n"
"{\n"
    "if (u_alphaTest > (texture2D(u_fragmentMap0, var_TexDiffuse).a * texture2D(u_fragmentMap1, var_TexClip).a) ) {\n"
      "discard;\n"
    "}\n"
	"\n"
  "gl_FragColor = u_glColor;\n"
"}\n"
;

// interaction(Blinn-phong)
GLSL_SHADER const char INTERACTION_BLINNPHONG_VERT[] = 
"#version 100\n"
"//#pragma optimize(off)\n"
"\n"
"precision mediump float;\n"
"\n"
"#define BLINN_PHONG\n"
"\n"
"varying vec2 var_TexDiffuse;\n"
"varying vec2 var_TexNormal;\n"
"varying vec2 var_TexSpecular;\n"
"varying vec4 var_TexLight;\n"
"varying lowp vec4 var_Color;\n"
"varying vec3 var_L;\n"
"#if defined(BLINN_PHONG)\n"
"varying vec3 var_H;\n"
"#else\n"
"varying vec3 var_V;\n"
"#endif\n"
"\n"
"attribute vec4 attr_TexCoord;\n"
"attribute vec3 attr_Tangent;\n"
"attribute vec3 attr_Bitangent;\n"
"attribute vec3 attr_Normal;\n"
"attribute highp vec4 attr_Vertex;\n"
"attribute lowp vec4 attr_Color;\n"
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
GLSL_SHADER const char INTERACTION_BLINNPHONG_FRAG[] = 
"#version 100\n"
"//#pragma optimize(off)\n"
"\n"
"precision mediump float;\n"
"\n"
"#define BLINN_PHONG\n"
"\n"
"//#define HALF_LAMBERT\n"
"\n"
"varying vec2 var_TexDiffuse;\n"
"varying vec2 var_TexNormal;\n"
"varying vec2 var_TexSpecular;\n"
"varying vec4 var_TexLight;\n"
"varying lowp vec4 var_Color;\n"
"varying vec3 var_L;\n"
"#if defined(BLINN_PHONG)\n"
"varying vec3 var_H;\n"
"#else\n"
"varying vec3 var_V;\n"
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
"\n"
"void main(void)\n"
"{\n"
	"//float u_specularExponent = 4.0;\n"
"\n"
	"vec3 L = normalize(var_L);\n"
"#if defined(BLINN_PHONG)\n"
	"vec3 H = normalize(var_H);\n"
	"vec3 N = 2.0 * texture2D(u_fragmentMap0, var_TexNormal.st).agb - 1.0;\n"
"#else\n"
	"vec3 V = normalize(var_V);\n"
	"vec3 N = normalize(2.0 * texture2D(u_fragmentMap0, var_TexNormal.st).agb - 1.0);\n"
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
	"vec3 lightProjection = texture2DProj(u_fragmentMap2, var_TexLight.xyw).rgb;\n"
	"vec3 lightFalloff = texture2D(u_fragmentMap1, vec2(var_TexLight.z, 0.5)).rgb;\n"
	"vec3 diffuseColor = texture2D(u_fragmentMap3, var_TexDiffuse).rgb * u_diffuseColor.rgb;\n"
	"vec3 specularColor = 2.0 * texture2D(u_fragmentMap4, var_TexSpecular).rgb * u_specularColor.rgb;\n"
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
	"gl_FragColor = vec4(color, 1.0) * var_Color;\n"
"}\n"
;

// diffuse dubemap(UNUSED in game)
GLSL_SHADER const char DIFFUSE_CUBEMAP_VERT[] = 
"#version 100\n"
"//#pragma optimize(off)\n"
"\n"
"precision mediump float;\n"
  "\n"
"// In\n"
"attribute highp vec4 attr_Vertex;\n"
"attribute lowp vec4 attr_Color;\n"
"attribute vec3 attr_TexCoord;\n"
  "\n"
"// Uniforms\n"
"uniform highp mat4 u_modelViewProjectionMatrix;\n"
"uniform mat4 u_textureMatrix;\n"
"uniform lowp float u_colorAdd;\n"
"uniform lowp float u_colorModulate;\n"
  "\n"
"// Out\n"
"// gl_Position\n"
"varying vec3 var_TexCoord;\n"
"varying lowp vec4 var_Color;\n"
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
GLSL_SHADER const char TEXGEN_VERT[] = 
"#version 100\n"
"//#pragma optimize(off)\n"
"\n"
"precision mediump float;\n"
"\n"
"attribute highp vec4 attr_Vertex;\n"
"attribute lowp vec4 attr_Color;\n"
"\n"
"uniform lowp vec4 u_colorAdd;\n"
"uniform lowp vec4 u_colorModulate;\n"
"uniform vec4 u_texgenS;\n"
"uniform vec4 u_texgenT;\n"
"uniform vec4 u_texgenQ;\n"
"uniform mat4 u_textureMatrix;\n"
"uniform highp mat4 u_modelViewProjectionMatrix;\n"
"\n"
"varying vec4 var_TexCoord;\n"
"varying lowp vec4 var_Color;\n"
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
GLSL_SHADER const char TEXGEN_FRAG[] = 
"#version 100\n"
"//#pragma optimize(off)\n"
"\n"
"precision mediump float;\n"
"\n"
"uniform sampler2D u_fragmentMap0;\n"
"uniform lowp vec4 u_glColor;\n"
"\n"
"varying vec4 var_TexCoord;\n"
"varying lowp vec4 var_Color;\n"
"\n"
"void main(void)\n"
"{\n"
	"// we always do a projective texture lookup so that we can support texgen\n"
	"// materials without a separate shader. Basic materials will have texture\n"
	"// coordinates with w = 1 which will result in a NOP projection when tex2Dproj\n"
	"// gets called.\n"
	"gl_FragColor = texture2DProj( u_fragmentMap0, var_TexCoord.xyw ) * u_glColor * var_Color;\n"
"}\n"
;



#ifdef _SHADOW_MAPPING
#define PACK_FLOAT_FUNC() \
"vec4 pack (highp float depth)\n" \
"{\n" \
"	const highp vec4 bitSh = vec4(256.0 * 256.0 * 256.0, 256.0 * 256.0, 256.0, 1.0);\n" \
"	const highp vec4 bitMsk = vec4(0.0, 1.0 / 256.0, 1.0 / 256.0, 1.0 / 256.0);\n" \
"	highp vec4 comp = fract(depth * bitSh);\n" \
"	comp -= comp.xxyz * bitMsk;\n" \
"	return depth < 1.0 ? comp : vec4(1.0, 1.0, 1.0, 1.0);\n" \
"}\n"
#define UNPACK_FLOAT_FUNC() \
"highp float unpack (vec4 colour)\n" \
"{\n" \
"	const highp vec4 bitShifts = vec4(1.0 / (256.0 * 256.0 * 256.0), 1.0 / (256.0 * 256.0), 1.0 / 256.0, 1.0);\n" \
"	return /*all(lessThan(colour, vec4(1.0, 1.0, 1.0, 1.0)))*/ colour.r < 1.0 ? dot(colour , bitShifts) : 1.0;\n" \
"}\n"

#define VECTOR_TO_DEPTH_FUNC(far, near) \
"float VectorToDepthValue(vec3 Vec)\n" \
"{\n" \
"	vec3 AbsVec = abs(Vec);\n" \
"	float LocalZcomp = max(AbsVec.x, max(AbsVec.y, AbsVec.z));\n" \
"	float NormZComp = (" #far " + " #near ") / (" #far " - " #near ") - (2.0 * " #far " * " #near ") / (" #far " - " #near ") / LocalZcomp;\n" \
"	return (NormZComp + 1.0) * 0.5;\n" \
"}\n"

// shadow map
GLSL_SHADER const char DEPTH_VERT[] =
"#version 100\n"
"//#pragma optimize(off)\n"
"\n"
"precision mediump float;\n"
"\n"
"attribute highp vec4 attr_Vertex;\n"
"\n"
"uniform highp mat4 u_modelViewProjectionMatrix;\n"
"uniform highp mat4 u_modelMatrix;\n"
"uniform highp vec4 u_lightOrigin;\n"
"\n"
"uniform highp vec4 globalLightOrigin;\n"
"//uniform lowp float u_uniformParm2; // .w 1.0 or 0.0\n"
"uniform highp float u_uniformParm0; // frustum z-far\n"
"uniform highp float u_uniformParm1; // frustum z-near\n"
"\n"
"void main(void)\n"
"{\n"
"	highp vec4 pos;\n"
"	//pos = attr_Vertex.w * u_lightOrigin + attr_Vertex - u_lightOrigin;\n"
"	//float w = max(attr_Vertex.w, u_uniformParm2);\n"
"	//pos = w * u_lightOrigin + vec4(attr_Vertex.xyz, w) - u_lightOrigin;\n"
"	//pos = attr_Vertex - u_lightOrigin; pos = (pos.wwww * u_lightOrigin) + pos;\n"
"	pos = vec4(attr_Vertex.xyz, 1.0);\n"
"	gl_Position = pos * u_modelViewProjectionMatrix;\n"
"}\n"
;
GLSL_SHADER const char DEPTH_FRAG[] =
"#version 100\n"
"//#pragma optimize(off)\n"
"\n"
"precision mediump float;\n"
"\n"
"uniform highp vec4 globalLightOrigin;\n"
"uniform highp float u_uniformParm0; // frustum z-far\n"
"uniform highp float u_uniformParm1; // frustum z-near\n"
"\n"
PACK_FLOAT_FUNC()
"\n"
"void main(void)\n"
"{\n"
"#ifdef _USING_DEPTH_TEXTURE\n"
"   #ifdef _DEBUG\n"
"       gl_FragColor = vec4((gl_FragCoord.z + 1.0) * 0.5, 0.0, 0.0, 1.0); // DEBUG\n"
"   #else\n"
"       gl_FragColor = vec4(1.0, 0.0, 0.0, 1.0);\n"
"   #endif\n"
"#else\n"
"	highp float depth;\n"
"	depth = gl_FragCoord.z;\n"
"   #ifdef _PACK_FLOAT\n"
"		gl_FragColor = gl_FragColor = pack(depth);\n"
"   #else\n"
"		gl_FragColor = vec4(depth, 0.0, 0.0, 1.0);\n"
"   #endif\n"
"#endif\n"
"}\n"
;

// interaction(shadow mapping)
GLSL_SHADER const char INTERACTION_SHADOW_MAPPING_VERT[] =
        "#version 100\n"
        "//#pragma optimize(off)\n"
        "\n"
        "precision mediump float;\n"
        "\n"
        "//#define BLINN_PHONG\n"
        "\n"
        "varying vec2 var_TexDiffuse;\n"
        "varying vec2 var_TexNormal;\n"
        "varying vec2 var_TexSpecular;\n"
        "varying vec4 var_TexLight;\n"
        "varying lowp vec4 var_Color;\n"
        "varying vec3 var_L;\n"
        "#if defined(BLINN_PHONG)\n"
        "varying vec3 var_H;\n"
		"#else\n"
		"varying vec3 var_V;\n"
        "#endif\n"
        "\n"
        "attribute vec4 attr_TexCoord;\n"
        "attribute vec3 attr_Tangent;\n"
        "attribute vec3 attr_Bitangent;\n"
        "attribute vec3 attr_Normal;\n"
        "attribute highp vec4 attr_Vertex;\n"
        "attribute lowp vec4 attr_Color;\n"
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
		"#ifdef _POINT_LIGHT\n"
		"	varying highp vec3 var_LightToVertex;\n"
        "	varying highp vec4 var_VertexPosition;\n"
		"#else\n"
		"	uniform highp mat4 shadowMVPMatrix;\n"
        "	varying highp vec4 var_ShadowCoord;\n"
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
		"#ifdef _POINT_LIGHT\n"
		"	highp vec4 posInLight = u_modelMatrix * attr_Vertex;\n"
		"	var_LightToVertex = posInLight.xyz - globalLightOrigin.xyz;\n"
        "	var_VertexPosition = attr_Vertex;\n"
		"#else\n"
        "	var_ShadowCoord = attr_Vertex * shadowMVPMatrix;\n"
		"#endif\n"
        "	gl_Position = u_modelViewProjectionMatrix * attr_Vertex;\n"
        "}\n"
;
GLSL_SHADER const char INTERACTION_SHADOW_MAPPING_FRAG[] =
        "#version 100\n"
        "//#pragma optimize(off)\n"
        "\n"
        "precision mediump float;\n"
        "\n"
        "//#define BLINN_PHONG\n"
        "\n"
        "//#define HALF_LAMBERT\n"
        "\n"
        "varying vec2 var_TexDiffuse;\n"
        "varying vec2 var_TexNormal;\n"
        "varying vec2 var_TexSpecular;\n"
        "varying vec4 var_TexLight;\n"
        "varying lowp vec4 var_Color;\n"
        "varying vec3 var_L;\n"
        "#if defined(BLINN_PHONG)\n"
        "varying vec3 var_H;\n"
        "#else\n"
        "varying vec3 var_V;\n"
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
		"#ifdef _POINT_LIGHT\n"
        "uniform highp samplerCube u_fragmentCubeMap6;	/* u_shadowMapTexture */\n"
		"#else\n"
		"uniform highp sampler2D u_fragmentMap6;	/* u_shadowMapTexture */\n"
		"#endif\n"
		"\n"
		"uniform highp vec4 globalLightOrigin;\n"
		"uniform highp float u_uniformParm0; // frustum z-far\n"
		"uniform highp float u_uniformParm1; // frustum z-near\n"
        "uniform lowp float u_uniformParm2; // sample size\n"
		"uniform lowp float u_uniformParm3; // shadow alpha\n"
		"uniform lowp float u_uniformParm4; // bias\n"
		"\n"
		"#ifdef _POINT_LIGHT\n"
		"	varying highp vec3 var_LightToVertex;\n"
        "	varying highp vec4 var_VertexPosition;\n"
		"	uniform highp mat4 shadowMVPMatrix[6];\n"
		"#else\n"
        "	varying highp vec4 var_ShadowCoord;\n"
		"#endif\n"
        "\n"
		"#ifdef _PACK_FLOAT\n"
		UNPACK_FLOAT_FUNC()
		"#define DC(x) (unpack(x))\n"
		"#else\n"
		"#define DC(x) ((x).r)\n"
		"#endif\n"
        "\n"
        "#ifdef _DYNAMIC_BIAS\n"
		"   #define BIAS_SCALE 1.0 // 0.999\n"
		"   #define BIAS(x) ((x) * BIAS_SCALE)\n"
        "#else\n"
		"	#define BIAS_OFFSET 0.0 // 0.001\n"
		"   #define BIAS(x) ((x) - BIAS_OFFSET)\n"
		"#endif\n"
		"\n"
        "void main(void)\n"
        "{\n"
        "	//float u_specularExponent = 4.0;\n"
        "\n"
        "	vec3 L = normalize(var_L);\n"
        "#if defined(BLINN_PHONG)\n"
        "	vec3 H = normalize(var_H);\n"
        "	vec3 N = 2.0 * texture2D(u_fragmentMap0, var_TexNormal.st).agb - 1.0;\n"
        "#else\n"
        "	vec3 V = normalize(var_V);\n"
        "	vec3 N = normalize(2.0 * texture2D(u_fragmentMap0, var_TexNormal.st).agb - 1.0);\n"
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
        "	vec3 lightProjection = texture2DProj(u_fragmentMap2, var_TexLight.xyw).rgb;\n"
        "	vec3 lightFalloff = texture2D(u_fragmentMap1, vec2(var_TexLight.z, 0.5)).rgb;\n"
        "	vec3 diffuseColor = texture2D(u_fragmentMap3, var_TexDiffuse).rgb * u_diffuseColor.rgb;\n"
        "	vec3 specularColor = 2.0 * texture2D(u_fragmentMap4, var_TexSpecular).rgb * u_specularColor.rgb;\n"
        "\n"
        "#if defined(BLINN_PHONG)\n"
        "	float specularFalloff = pow(NdotH, u_specularExponent);\n"
        "#else\n"
        "	vec3 R = -reflect(L, N);\n"
        "	float RdotV = clamp(dot(R, V), 0.0, 1.0);\n"
        "	float specularFalloff = pow(RdotV, u_specularExponent);\n"
        "#endif\n"
        "\n"
		"	float shadow = 0.0;\n"
		"	#define SAMPLES 9\n"
		"\n"
		"#ifdef _POINT_LIGHT\n"
		"	vec3 sampleOffsetTable[SAMPLES];\n"
		"	sampleOffsetTable[0] = vec3(0.0, 0.0, 0.0);\n"
		"	sampleOffsetTable[1] = vec3(1.0, 1.0, 1.0); sampleOffsetTable[2] = vec3(1.0, 1.0, -1.0); sampleOffsetTable[3] = vec3(1.0, -1.0, -1.0); sampleOffsetTable[4] = vec3(1.0, -1.0, 1.0);\n"
		"	sampleOffsetTable[5] = vec3(-1.0, 1.0, 1.0); sampleOffsetTable[6] = vec3(-1.0, -1.0, 1.0); sampleOffsetTable[7] = vec3(-1.0, 1.0, -1.0); sampleOffsetTable[8] = vec3(-1.0, -1.0, -1.0);\n"
		"	vec3 toLightGlobal = normalize( -var_LightToVertex );\n"
		"	int shadowIndex = 0;"
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
		"	highp vec4 shadowPosition = var_VertexPosition * shadowMVPMatrix[shadowIndex];\n"
		"	shadowPosition.xyz /= shadowPosition.w;\n"
		"	highp float currentDepth = BIAS(shadowPosition.z);\n"
        "   float distance = u_uniformParm2 + (length(var_LightToVertex) / 1000.0); // more far more large\n"
		"	for (int i = 0; i < SAMPLES; ++i) {\n"
		"		highp float shadowDepth = DC(textureCube(u_fragmentCubeMap6, normalize(var_LightToVertex + sampleOffsetTable[i] * distance)));\n"
		"		highp float visibility = currentDepth - shadowDepth;\n"
		"		shadow += 1.0 - step(0.0, visibility) * u_uniformParm3;\n"
		"		//shadow += visibility < 0.0 ? 1.0 : u_uniformParm3;\n"
		"	}\n"
		"#else\n"
		"	vec2 sampleOffsetTable[SAMPLES];\n"
		"	sampleOffsetTable[0] = vec2( 0.0, 0.0);\n"
		"	sampleOffsetTable[1] = vec2( 1.0, 1.0); sampleOffsetTable[2] = vec2( 1.0, -1.0); sampleOffsetTable[3] = vec2(-1.0, -1.0); sampleOffsetTable[4] = vec2(-1.0, 1.0);\n"
		"	sampleOffsetTable[5] = vec2( 1.0, 0.0); sampleOffsetTable[6] = vec2( -1.0, 0.0); sampleOffsetTable[7] = vec2(0.0, -1.0); sampleOffsetTable[8] = vec2(0.0, 1.0);\n"
		"	highp vec3 shadowCoord = var_ShadowCoord.xyz / var_ShadowCoord.w;\n"
		"	highp float currentDepth = BIAS(shadowCoord.z);\n"
		"	for (int i = 0; i < SAMPLES; ++i) {\n"
		"		highp float shadowDepth = DC(texture2D(u_fragmentMap6, shadowCoord.st + sampleOffsetTable[i] * u_uniformParm2));\n"
		"		highp float visibility = currentDepth - shadowDepth;\n"
		"		shadow += 1.0 - step(0.0, visibility) * u_uniformParm3;\n"
		"		//shadow += visibility < 0.0 ? 1.0 : u_uniformParm3;\n"
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
        "	gl_FragColor = vec4(color, 1.0) * var_Color;\n"
        "}\n"
;
#endif

#endif
