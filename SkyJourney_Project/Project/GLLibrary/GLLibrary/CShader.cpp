#include <stdio.h>
#include <stdlib.h>
#include "CShader.h"

const char* mesh_vert = "#version 430\n\n"\
"uniform mat4 WorldMatrix;\n"\
"uniform mat4 ModelViewMatrix;\n"\
"uniform mat4 ProjectionMatrix;\n"\
"uniform mat4 ShadowTextureMatrix;\n"\
"layout(location = 0) in vec3	Vertex;\n"\
"layout(location = 1) in vec3	Normal;\n"\
"layout(location = 2) in vec2	TexCoord;\n"\
"layout(location = 6) in vec3	Tangent;\n"\
"//フラグメントシェーダーに渡す変数\n"\
"out vec3 V;//座標\n"\
"out vec3 N;//法線ベクトル\n"\
"out vec2 texCoord;\n"\
"out vec3 T;//接線ベクトル\n"\
"out vec3 B;//従法線ベクトル\n"\
"out vec4 vShadowCoord;    //!< シャドウデプスマップの参照用座標\n"\
"uniform int usenormalMap;\n"\
"void main(void)\n"\
"{\n"\
"	V = vec3(WorldMatrix * vec4(Vertex, 1));\n"\
"	gl_Position = ProjectionMatrix * ModelViewMatrix * vec4(Vertex, 1);\n"\
"	N = normalize(mat3(WorldMatrix) * Normal);\n"\
"	vShadowCoord = ShadowTextureMatrix * vec4(V, 1);    // 影用座標値(光源中心座標)\n"\
"\n"\
"	texCoord = TexCoord;\n"\
"	if(usenormalMap==1) {\n"\
"		T = normalize(mat3(WorldMatrix) * Tangent);\n"\
"		B = cross(N, T);//従法線ベクトル\n"\
"	}\n"
"}";
const char* skin_mesh_vert = "#version 430\n\n"\
"uniform mat4 Transforms[192];\n"\
"uniform mat4 WorldMatrix;\n"\
"uniform mat4 LocalMatrix;\n"\
"uniform mat4 ModelViewMatrix;\n"\
"uniform mat4 ProjectionMatrix;\n"\
"uniform mat4 ShadowTextureMatrix;\n"\
"uniform int useSkin = 0;\n"\
"layout(location = 0) in vec3 Vertex;\n"\
"layout(location = 1) in vec3 Normal;\n"\
"layout(location = 2) in vec2 TexCoord;\n"\
"layout(location = 3) in vec4 weights;\n"\
"layout(location = 4) in vec4 indices;\n"\
"//フラグメントシェーダーに渡す変数\n"\
"out vec3 V;//座標\n"\
"out vec3 N;//法線ベクトル\n"\
"out vec3 T;//接線ベクトル\n"\
"out vec3 B;//従法線ベクトル\n"\
"out vec2 texCoord;\n"\
"out vec4 vShadowCoord;    //!< シャドウデプスマップの参照用座標\n"\
"void main(void)\n"\
"{\n"\
"	if (useSkin==1) {\n"\
"		mat4 comb = mat4(0);\n"\
"		comb += Transforms[int(indices.x)] * weights.x;\n"\
"		comb += Transforms[int(indices.y)] * weights.y;\n"\
"		comb += Transforms[int(indices.z)] * weights.z;\n"\
"		comb += Transforms[int(indices.w)] * weights.w;\n"\
"		vec4 skinPosition = ModelViewMatrix * comb * LocalMatrix*vec4(Vertex, 1);\n"\
"		V = vec3(WorldMatrix * comb * LocalMatrix * vec4(Vertex, 1));\n"\
"		gl_Position = ProjectionMatrix * skinPosition;\n"\
"		N = normalize(mat3(WorldMatrix * comb*LocalMatrix) * Normal);\n"\
"	} else {\n"\
"		V = vec3(WorldMatrix * vec4(Vertex, 1));\n"\
"		gl_Position = ProjectionMatrix * ModelViewMatrix * LocalMatrix * vec4(Vertex, 1);\n"\
"		N = normalize(mat3(WorldMatrix) * Normal);\n"\
"	}\n"\
"	vShadowCoord = ShadowTextureMatrix * vec4(V, 1);    // 影用座標値(光源中心座標)\n"\
"	texCoord = TexCoord;\n"\
"}";
const char* mesh_frag = "#version 430\n\n"\
"uniform vec3 lightPos[5];\n"\
"uniform vec3 lightDir[5];\n"\
"uniform vec3 lightAmbientColor[5];\n"\
"uniform vec3 lightDiffuseColor[5];\n"\
"uniform float lightAttenuation[5];\n"\
"uniform int lightType[5];\n"\
"uniform float lightRadiationAngle[5];\n"\
"uniform vec2 stscroll;\n"\
"uniform vec3 eyeVec;\n"\
"uniform vec3 eyePos;\n"\
"uniform vec4 Ambient;\n"\
"uniform vec4 Diffuse;\n"\
"uniform vec3 Specular;\n"\
"uniform vec3 Emissive;\n"\
"uniform float Pow;\n"\
"uniform float alpha;\n"\
"uniform int lighting;\n"\
"uniform int uSetex;\n"\
"uniform int usenormalMap;"\
"uniform vec4 fogColor;\n"\
"uniform float fogNear;\n"\
"uniform float fogFar;\n"\
"//頂点シェーダーから受け取る変数\n"\
"in vec3 V;//位置\n"\
"in vec3 N;//法線ベクトル\n"\
"in vec3 T;//接線ベクトル\n"\
"in vec3 B;//従法線ベクトル\n"\
"in vec2 texCoord;\n"\
"uniform sampler2D sampler;\n"\
"uniform sampler2D normalMap;//法線マップ\n"\
"in vec4 vShadowCoord;    //!< シャドウデプスマップの参照用座標\n"\
"out vec4 out_color[2];\n"\
"uniform sampler2D depth_tex;    //!< デプス値テクスチャ\n"\
"uniform float shadow_ambient;    //!< 影の濃さ\n"\
"float restDepth(vec4 RGBA) {\n"\
"	const float rMask = 1.0;\n"\
"	const float gMask = 1.0 / 255.0;\n"\
"	const float bMask = 1.0 / (255.0 * 255.0);\n"\
"	const float aMask = 1.0 / (255.0 * 255.0 * 255.0);\n"\
"	float depth = dot(RGBA, vec4(rMask, gMask, bMask, aMask));\n"\
"	return depth;\n"\
"}\n"\
"void main(void)\n"\
"{\n"\
"	vec4 texColor = vec4(1, 1, 1, 1);\n"\
"	if (uSetex != 0) {\n"\
"		texColor = texture2D(sampler, texCoord + stscroll);\n"\
"	}\n"\
"	if(texColor.a * alpha <=0) discard;\n"
"	vec3 A = vec3(0, 0, 0);\n"\
"	vec3 D = vec3(0, 0, 0);\n"\
"	vec3 S = vec3(0, 0, 0);\n"\
"	vec3 color;\n"\
"	float visibility = 1.0;\n"\
"	vec3 E = normalize(eyePos - V);\n"\
"	vec3 Normal=N;\n"\
"	if (usenormalMap != 0) {\n"\
"		Normal = (texture2D(normalMap, texCoord + stscroll).xyz - 0.5) * 2.0;\n"\
"		Normal = T * Normal.x + B * Normal.y + N * Normal.z;\n"\
"		//Normal.xyz = (Normal / 2.0f) + 0.5f; //-1〜1から0〜1に補正\n"\
"		//Normal.w = texture2D(specurMap, texCoord + stscroll).r;\n"\
"		//Normal.w = 0;\n"\
"	}\n"\
"	if (lighting == 1) {\n"\
"		for (int i = 0; i < 5; i++) {\n"\
"			if (lightType[i] == 0) continue;\n"\
"			vec3 vec = vec3(0, 0, 0);\n"\
"			float p = 0;\n"\
"			if (lightType[i] == 1) {\n"\
"				vec = -lightDir[i];\n"\
"				p = 1;\n"\
"			}else\n"\
"			if (lightType[i] == 2 || lightType[i] == 3) {\n"\
"					vec = vec3(V - lightPos[i]);\n"\
"					float l = length(vec);\n"\
"					vec = normalize(vec);\n"\
"					if (l > 0)\n"\
"						p = clamp(1 / (pow(l * lightAttenuation[i], 2)), 0.0, 1.0);\n"\
"					else\n"\
"						p = 0;\n"\
"					if (lightType[i] == 3) {\n"\
"						float t = dot(vec, lightDir[i]);\n"\
"						if(t<cos(lightRadiationAngle[i])) p = 0;\n"\
"						else p = 1;\n"\
"						D+=lightDiffuseColor[i]*p;\n"\
"						continue;\n"\
"					}\n"\
"					vec = -vec;\n"\
"				}\n"\
"			vec3 L = vec; \n"\
"			float NL = max(0, dot(Normal, L)); \n"\
"			if(usenormalMap == 0)\n"\
"			//NL = (NL>0.0) ? ((NL>0.3) ? 1.0:0.95):0.80;\n"\
"			//NL = (NL>0.0) ? 1.0:0.8;\n"\
"			if(i==0) {\n"\
"				float bias = 0.000001;\n"\
/*シャドウマップ */
"				if ( vShadowCoord.z<1.0 && restDepth(texture2D( depth_tex, vShadowCoord.xy))  <  vShadowCoord.z-bias "\
"				&& abs(vShadowCoord.x)<1.0 && abs(vShadowCoord.y)<1.0)\n"\
"					NL*=0.8;\n"\
"           }\n"\
"			vec3 R = reflect(-E, Normal);\n"\
"			S += pow(max(0, dot(R, L)), Pow) * p;\n"\
"			D += lightDiffuseColor[i] * clamp(NL, 0.0, 1.0) * p;\n"\
"			A += lightAmbientColor[i] * p;\n"\
"		}\n"\
"		float l = length(eyePos - V);\n"\
"		float f = clamp((fogFar - l) / (fogFar - fogNear), 0.0, 1.0);\n"\
"		color = texColor.xyz * (visibility * Diffuse.xyz * clamp(D, 0.0, 1.0) + Ambient.xyz * clamp(A, 0.0, 1.0)) /*+ visibility * Specular * clamp(S, 0.0, 1.0) + Emissive*/;\n"\
"		out_color[0] = vec4(color + fogColor.xyz * (1.0 - f), clamp((texColor.w * Diffuse.w * alpha) - ((1.0 - fogColor.w) * (1.0 - f)), 0.0f, 1.0f));\n"\
"		out_color[1] = vec4(visibility * Specular * clamp(S, 0.0, 1.0)+ Emissive,1);\n"\
"	}\n"\
"	else {\n"\
"		color = Diffuse.xyz;\n"\
"		out_color[0] = (texColor * vec4(color, Diffuse.w * alpha));\n"\
"		out_color[1] = vec4(0,0,0,1);\n"\
"	}\n"\
"}";


const char *solid_vert = "#version 430\n\n"\
"uniform mat4 PVWMatrix;\n"\
"layout(location = 0) in vec3	Vertex;\n"\
"void main(void)\n"\
"{\n"\
"	gl_Position = PVWMatrix * vec4(Vertex, 1);\n"\
"}";

const char* solid_frag = "#version 430\n\n"\
"uniform vec4 Color;\n"\
"out vec4 out_color;\n"\
"void main() {\n"\
"	out_color = Color;\n"\
"}";

const char* trail_vert ="#version 430\n"\
"uniform mat4 PVWMatrix;\n"\
"layout(location = 0) in vec3	Vertex;\n"\
"layout(location = 2) in vec2	TexCoord;\n"\
"layout(location = 5) in vec4	VertexColor;\n"\
"out vec2 texCoord;\n"\
"out vec4 vertex_color;\n"\
"void main(void)\n"\
"{\n"\
"	gl_Position = PVWMatrix * vec4(Vertex, 1);\n"\
"	vertex_color = VertexColor;\n"\
"	texCoord = TexCoord;\n"\
"}\n";
const char* trail_frag = "#version 430\n"\
"uniform sampler2D sampler;\n"\
"in vec2 texCoord;\n"\
"in vec4 vertex_color;\n"\
"out vec4 out_color;\n"\
"void main() {\n"\
"	vec4 texColor = vec4(1, 1, 1, 1);\n"\
"	texColor = texture2D(sampler, texCoord);\n"\
"	out_color = vertex_color * texColor;\n"\
"};\n";

const char* image_vert = "#version 430\n\n"\
"uniform mat4 PVWMatrix;\n"\
"layout(location = 0) in vec3	Vertex;\n"\
"layout(location = 2) in vec2	TexCoord;\n"\
"out vec2 texCoord;\n"\
"void main(void)\n"\
"{\n"\
"	gl_Position = PVWMatrix * vec4(Vertex, 1);\n"\
"	texCoord = TexCoord;\n"\
"}";
const char* image_frag = "#version 430\n\n"\
"uniform vec4 Color;\n"\
"in vec2 texCoord;\n"\
"uniform sampler2D sampler;\n"\
"out vec4 out_color;\n"\
"void main() {\n"\
"	vec4 texColor = vec4(1, 1, 1, 1);\n"\
"	texColor = texture2D(sampler, texCoord);\n"\
"	out_color = texColor * Color;\n"\
"}";

const char* effect_vert = "#version 430\n"\
"layout(location = 0) in vec3 Vertex;\n"\
"out vec2 texCoord;\n"\
"void main(void)\n"\
"{\n"\
"	texCoord = Vertex.xy;\n"\
"	gl_Position = vec4(Vertex.xy * 2.0 - 1.0, 0.0, 1.0);\n"\
"}\n";


const char* effect_frag = "#version 430\n"\
"float rand(vec2 co) { \n"\
"	float t = fract(co.x * 43758.5453);\n"\
"	return t;\n"\
"}\n"\
"uniform sampler2D tDiffuse;\n"\
"uniform vec2 vScreenSize;\n"\
"in vec2 texCoord;\n"\
"out vec4 out_color;\n"\
"void main() {\n"\
"	float radius = 5.0;\n"\
"	float x = (texCoord.x * vScreenSize.x) + rand(vec2(texCoord.x, texCoord.y)) * radius * 2.0 - radius;\n"\
"	float y = (texCoord.y * vScreenSize.y) + rand(vec2(texCoord.y, texCoord.x)) * radius * 2.0 - radius;\n"\
"	vec4 textureColor = texture2D(tDiffuse, vec2(texCoord.x + rand(vec2(texCoord.x, texCoord.y)) * 0.01, texCoord.y + rand(vec2(texCoord.y, texCoord.x)) * 0.01));\n"\
"	out_color = textureColor;\n"\
"}\n";

const char* no_effect_frag = "#version 430\n"\
"uniform sampler2D tDiffuse;\n"\
"in vec2 texCoord;\n"\
"out vec4 out_color;\n"\
"void main() {\n"\
"	vec4 textureColor = texture2D(tDiffuse, vec2(texCoord.x, texCoord.y));\n"\
"	out_color = textureColor;\n"\
"}\n";


const char* edge_vert = "#version 430\n"\
"layout(location = 0) in vec3 Vertex;\n"\
"out vec2 texCoord;\n"\
"void main(void)\n"\
"{\n"\
"	texCoord = Vertex.xy;\n"\
"	gl_Position = vec4(Vertex.xy * 2.0 - 1.0, 0.0, 1.0);\n"\
"}\n";


const char* edge_frag = "#version 430\n"\
"uniform sampler2D depth;\n"\
"const float dx = 1.0f/1920.0f;\n"\
"const float dy = 1.0f/1080.0f;\n"\
"in vec2 texCoord;\n"\
"out vec4 out_color;\n"\
"float peek(const in float x, const in float y)\n"\
"{\n"\
"	return texture2D(depth, vec2(x, y)).r;\n"\
"}\n"\
"void main(void)\n"\
"{\n"\
"	float x = texCoord.x;\n"\
"	float y = texCoord.y;\n"\
"	mat3 m = mat3(\n"\
"		peek(x - dx, y - dy), peek(x, y - dy), peek(x + dx, y - dy),\n"\
"		peek(x - dx, y), peek(x, y), peek(x + dx, y),\n"\
"		peek(x - dx, y + dy), peek(x, y + dy), peek(x + dx, y + dy)\n"\
"	);\n"\
"	vec2 h = vec2(\n"\
"		m[0][0] - m[0][2] + (m[1][0] - m[1][2]) * 2.0 + m[2][0] - m[2][2],\n"\
"		m[0][0] - m[2][0] + (m[0][1] - m[2][1]) * 2.0 + m[0][2] - m[2][2]\n"\
"	);\n"\
"	float d = step(0.99, 1.0 - length(h));\n"\
"	out_color = vec4(vec3(0,0,0), 1.0 - d);\n"\
"}\n";



const char* gaussian_blur_vert = "#version 430\n"\
"layout(location = 0) in vec3 Vertex; \n"\
"out vec2 texCoord;\n"\
"void main(void) {\n"\
"	texCoord = Vertex.xy;\n"\
"		gl_Position = vec4(Vertex.xy * 2.0 - 1.0, 0.0, 1.0); \n"\
"}\n";


const char* gaussian_blur_frag = "#version 430\n"\
"uniform sampler2D texture;\n"\
"uniform float     weight[10];\n"\
"uniform int      horizontal;\n"\
"uniform vec2    scale;\n"\
"in vec2 texCoord;\n"\
"out vec4 out_color;\n"\
"void main(void) {\n"\
"	vec2  fc;\n"\
"	vec4  destColor = vec4(0.0);\n"\
"	if (horizontal == 1) {\n"\
"		float tFrag = scale.x;\n"\
"		fc = texCoord;\n"\
"		for (int i = 1; i <= 9; i++) {"\
"			destColor += texture2D(texture, fc + vec2(float(i),0.0) * tFrag) * weight[i]; \n"\
"			destColor += texture2D(texture, fc + vec2(-float(i),0.0) * tFrag) * weight[i]; \n"\
"		}\n"\
"		destColor += texture2D(texture, fc) * weight[0];\n"\
"	} else {\n"\
"		float tFrag = scale.y;\n"\
"		fc = texCoord;\n"\
"		for (int i = 1; i <= 9; i++) {"\
"			destColor += texture2D(texture, fc + vec2(0.0, float(i)) * tFrag) * weight[i]; \n"\
"			destColor += texture2D(texture, fc + vec2(0.0, -float(i)) * tFrag) * weight[i]; \n"\
"		}\n"\
"		destColor += texture2D(texture, fc) * weight[0];\n"\
"	}\n"\
"	out_color = destColor;\n"\
"}\n";



const char* depth_of_field_vert = "#version 430\n"\
"layout(location = 0) in vec3 Vertex; \n"\
"out vec2 texCoord;\n"\
"void main(void) {\n"\
"	texCoord = Vertex.xy;\n"\
"		gl_Position = vec4(Vertex.xy * 2.0 - 1.0, 0.0, 1.0); \n"\
"}\n";


const char* depth_of_field_frag = "#version 430\n"\
"uniform sampler2D depthTexture;\n"\
"uniform sampler2D sceneTexture;\n"\
"uniform sampler2D blurTexture1;\n"\
"uniform sampler2D blurTexture2;\n"\
"uniform float     offset;\n"\
"in vec2 texCoord;\n"\
"out vec4 out_color;\n"\
"float restDepth(vec4 RGBA) {\n"\
"	const float rMask = 1.0;\n"\
"	const float gMask = 1.0 / 255.0;\n"\
"	const float bMask = 1.0 / (255.0 * 255.0);\n"\
"	const float aMask = 1.0 / (255.0 * 255.0 * 255.0);\n"\
"	float depth = dot(RGBA, vec4(rMask, gMask, bMask, aMask));\n"\
"	return depth;\n"\
"}\n"\
"float convCoord(float depth, float offset) {\n"\
"	float d = clamp(depth + offset, 0.0, 1.0);\n"\
"	if (d > 0.85) {\n"\
"		d = 6.6 * (1.0 - d);\n"\
"	} else if (d >= 0.4) {\n"\
"		d = 1.0;\n"\
"	} else {\n"\
"		d = pow(d/0.4,3);\n"\
"	}\n"\
"	return d;\n"\
"}\n"\
"void main(void) {\n"\
"	float d = restDepth(texture2D(depthTexture, texCoord));\n"\
"	d = convCoord(d, offset);\n"\
"	float coef = 1.0 - d;\n"\
"	float blur1Coef = coef * d;\n"\
"	float blur2Coef = coef * coef;\n"\
"	vec4 sceneColor = texture2D(sceneTexture, texCoord);\n"\
"	vec4 blur1Color = texture2D(blurTexture1, texCoord);\n"\
"	vec4 blur2Color = texture2D(blurTexture2, texCoord);\n"\
"	vec4 destColor = sceneColor * d + blur1Color * blur1Coef + blur2Color * blur2Coef;\n"\
"	out_color = destColor;\n"\
"}\n";

const char* glare_mix_vert = "#version 430\n"\
"layout(location = 0) in vec3 Vertex; \n"\
"out vec2 texCoord;\n"\
"void main(void) {\n"\
"	texCoord = Vertex.xy;\n"\
"		gl_Position = vec4(Vertex.xy * 2.0 - 1.0, 0.0, 1.0); \n"\
"}\n";


const char* glare_mix_frag = "#version 430"\
"uniform sampler2D texture1;"\
"uniform sampler2D texture2;"\
"in vec2 texCoord;"\
"out vec4 out_color;"\
"void main(void) {"\
"	vec4  destColor = texture2D(texture1, texCoord);"\
"	vec4  smpColor = texture2D(texture2, texCoord);"\
"	destColor += smpColor * 1.0;"\
"	out_color = destColor;"\
"}";
const char* lighting_vert = "#version 430\n"\
"layout(location = 0) in vec3 Vertex; \n"\
"out vec2 texCoord;\n"\
"void main(void) {\n"\
"	texCoord = Vertex.xy;\n"\
"		gl_Position = vec4(Vertex.xy * 2.0 - 1.0, 0.0, 1.0); \n"\
"}\n";


const char* lighting_frag = "#version 430\n"\
"uniform sampler2D color_texture;\n"\
"uniform sampler2D normal_texture;\n"\
"uniform sampler2D worldpos_texture;\n"\
"uniform sampler2D shadowmap_texture;\n"\
"uniform sampler2D extra_texture;\n"\
"#define LIGHT_MAX 5\n"\
"uniform vec3 lightPos[LIGHT_MAX];\n"\
"uniform vec3 lightDir[LIGHT_MAX];\n"\
"uniform vec3 lightAmbientColor[LIGHT_MAX];\n"\
"uniform vec3 lightDiffuseColor[LIGHT_MAX];\n"\
"uniform float lightAttenuation[LIGHT_MAX];\n"\
"uniform int lightType[LIGHT_MAX];\n"\
"uniform float lightRadiationAngle[LIGHT_MAX];\n"\
"uniform vec3 eyeVec;\n"\
"uniform vec3 eyePos;\n"\
"in vec2 texCoord;\n"\
"out vec4 out_color[2];\n"\
"void main(void) {\n"\
"	vec4 BaseColor = texture2D(color_texture, texCoord);\n"\
"	vec3 NormalColor = texture2D(normal_texture, texCoord).xyz;\n"\
"	float isNormal = texture2D(normal_texture, texCoord).w;\n"\
"	float SpecPower = 5.0;\n"\
"	vec4 WorldPos = texture2D(worldpos_texture, texCoord);\n"\
"	vec4 excolor = texture2D(shadowmap_texture, texCoord);\n"\
"	float emissive = excolor.x;\n"\
"	float metalic = excolor.y;\n"\
"	float roughNess = excolor.y;\n"\
"	float Shadow = excolor.z;\n"\
"	vec4 ext = texture2D(extra_texture, texCoord);\n"\
"	//NormalColor = (NormalColor * 2.0) - 1.0f;\n"\
"	vec3 diffuse = vec3(0, 0, 0);\n"\
"	float spec = 0;\n"\
"	vec3 EyeVec = normalize(eyePos - WorldPos.xyz);\n"\
"	//法線無しはライティングしない\n"\
"	if (isNormal == 0) {\n"\
"		out_color[0] = BaseColor;\n"\
"		out_color[1] = vec4(BaseColor.xyz, 0);\n"\
"	} else {\n"\
"		for (int i = 0; i < LIGHT_MAX; i++) {\n"\
"			if (lightType[i] == 0) continue;\n"\
"			vec3 L = vec3(0, 0, 0);\n"\
"			float p = 0;\n"\
"			if (lightType[i] == 1) {\n"\
"				L = -lightDir[i];\n"\
"				p = 1;\n"\
"			} else\n"\
"			if (lightType[i] == 2 || lightType[i] == 3) {\n"\
"					L = WorldPos.xyz - lightPos[i];\n"\
"					float l = length(L);\n"\
"					L = normalize(L);\n"\
"					if (l > 0)\n"\
"						p = clamp(1 / (pow(l * lightAttenuation[i], 2)), 0.0, 1.0);\n"\
"					else\n"\
"						continue;\n"\
"					if (lightType[i] == 3) {\n"\
"						float t = dot(L, lightDir[i]);\n"\
"						t = clamp(t + sin(lightRadiationAngle[i]), 0.0, 1.0);\n"\
"						//if(t<1) p = 0;\n"\
"						p *= pow(t, 20);\n"\
"					}\n"\
"					L = -L;\n"\
"				}\n"\
"			float NL = dot(NormalColor, L);\n"\
"			vec3 R = reflect(-EyeVec, NormalColor);\n"\
"			spec += metalic * pow(max(0, dot(R, L)), SpecPower) * p;\n"\
"			if (ext.x < 1.0)\n"\
"				NL = NL > 0 ? 1.0 : 0.9;\n"\
"			else\n"\
"				NL = clamp(NL, 0.0, 1.0);\n"\
"			if (i == 0) NL = Shadow;\n"\
"			diffuse += BaseColor.xyz * lightDiffuseColor[i] * NL * p;\n"\
"			diffuse += lightAmbientColor[i].xyz * BaseColor.xyz;\n"\
"		}\n"\
"		out_color[0] = vec4(diffuse, BaseColor.w);\n"\
"		out_color[1] = vec4(BaseColor.xyz * spec + BaseColor.xyz * emissive, BaseColor.w);\n"\
"	}\n"\
"}\n";

std::map<std::string, CShader*> CShader::m_instances;
CShader* CShader::GetInstance(std::string type)
{
	if (!m_instances[type]) m_instances[type] = new CShader(type);
	return m_instances[type];
}
void CShader::ClearInstance()
{
	for (auto& s : m_instances)
		delete s.second;
	m_instances.clear();
}
CShader* CShader::CreateInstance(std::string type)
{
	return new CShader(type);
}
CShader::CShader():program(0){

}

CShader::CShader(std::string type) {
	if (type == "SkinMesh") {
		ReadCode(skin_mesh_vert, mesh_frag);
	} else
	if (type == "StaticMesh") {
		ReadCode(mesh_vert, mesh_frag);
	} else
	if (type == "Effect") {
		ReadCode(effect_vert, effect_frag);
	}else
	if (type == "NoEffect") {
		ReadCode(effect_vert, no_effect_frag);
	}else
	if (type == "Edge") {
		ReadCode(edge_vert, edge_frag);
	}else
	if (type == "Image") {
		ReadCode(image_vert, image_frag);
	}else
	if (type == "Solid") {
		ReadCode(solid_vert, solid_frag);
	}else
	if (type == "Trail") {
		ReadCode(trail_vert, trail_frag);
	//	load("shader\\trail.vert", "shader\\trail.frag");
	}else
	if (type == "GaussianBlur") {
			ReadCode(gaussian_blur_vert, gaussian_blur_frag);
	}else
	if (type == "DepthOfField") {
			ReadCode(depth_of_field_vert, depth_of_field_frag);
	}else
	if (type == "GlareMix") {
		ReadCode(depth_of_field_vert, depth_of_field_frag);
	}else
	if (type == "Lighting") {
		ReadCode(lighting_vert, lighting_frag);
	} else {
		printf("\nシェーダー無し\n");
	}

}
CShader::CShader(const char* vertexPath,const char* pixelPath){
	Load(vertexPath,pixelPath);
}

bool CShader::ReadCode(GLuint shader, const char* code) {
	GLint compiled;
	
	int size = strlen(code);
	glShaderSource(shader, 1, (const GLchar * *)& code, &size);
	glCompileShader(shader);
	glGetShaderiv(shader, GL_COMPILE_STATUS, &compiled);
	if (!compiled) {
		GLint length;
		GLchar* log;
		glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &length);
		if (length > 0) {
			log = new GLchar[length];
			glGetShaderInfoLog(shader, length, &length, log);
			MessageBox(GL::hWnd, log, "エラー", MB_OK);
			delete log;
		}
	}
	//delete[] code;

	glAttachShader(program, shader);
	glLinkProgram(program);

	glGetProgramiv(program, GL_LINK_STATUS, &linked);

	if (linked) {
		//	glUseProgram(program);
	}
	else {
		GLint length;
		GLchar* log;
		glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &length);
		if (length > 0) {
			log = new GLchar[length];
			glGetShaderInfoLog(shader, length, &length, log);
			fprintf(stderr, "compile log='%s'\n", log);
			delete log;
		}
	}


	glDeleteShader(shader);
	//glDeleteShader(fragShader);

	return true;

}
bool CShader::Load(GLuint shader, const char *file) {
	FILE *fp;
	fopen_s(&fp,file, "rb");
	if(!fp) {
		printf("ファイルが開けません[%s]\n",file);
		return false;
	}
	fseek( fp, 0, SEEK_END );
	int size = ftell( fp );
	fseek( fp, 0, SEEK_SET );
	GLchar *code = new char[size+1];
	fread(code,size,1,fp);
	fclose(fp);
	code[size] = 0;
	bool r = ReadCode(shader, code);
	delete code;
	return r;
 
}
bool CShader::ReadCode(const char* vertexcode, const char* fragcode) {

	program = glCreateProgram();
	if (vertexcode) {

		bool ret = ReadCode(glCreateShader(GL_VERTEX_SHADER), vertexcode);
		if (!ret) return false;
	}
	if (fragcode) {

		bool ret = ReadCode(glCreateShader(GL_FRAGMENT_SHADER), fragcode);
		if (!ret) return false;
	}


	return true;

}
bool CShader::Load(const char* vertexPath,const char* fragPath){

	program = glCreateProgram();
	if(vertexPath) {

		bool ret = Load(glCreateShader(GL_VERTEX_SHADER),vertexPath);
		if(!ret) return false;
	}
	if(fragPath) {
		
		bool ret = Load(glCreateShader(GL_FRAGMENT_SHADER),fragPath);
		if(!ret) return false;
	}
	

	return true;
	
}
bool CShader::Load(const char* path, GLuint type){
	if (!program) program = glCreateProgram();
	if (path) {
		bool ret = Load(glCreateShader(type), path);
		if (!ret) return false;
	}
	return true;
}
bool CShader::ReadCode(const char* path, GLuint type) {
	if (!program) program = glCreateProgram();
	if (path) {
		bool ret = ReadCode(glCreateShader(type), path);
		if (!ret) return false;
	}
	return true;
}
CShader::~CShader(){
	if (program>0) glDeleteProgram(program);

}
void CShader::ReadVertexShader(std::string type)
{
	if (type == "SkinMesh") {
		ReadCode(skin_mesh_vert, GL_VERTEX_SHADER);
	} else
	if (type == "StaticMesh") {
		ReadCode(mesh_vert, GL_VERTEX_SHADER);
	} else
	if (type == "Effect") {
	//	load("shader\\effect.vert", "shader\\effect.frag");
	}else
	if (type == "NoEffect") {
	//	load("shader\\effect.vert", "shader\\noeffect.frag");
	}else
	if (type == "Depth") {
	//	load("shader\\showdepth.vert", "shader\\showdepth.frag");
	}else
	if (type == "Image") {
		ReadCode(image_vert, GL_VERTEX_SHADER);
	}else
	if (type == "Solid") {
		ReadCode(solid_vert, GL_VERTEX_SHADER);
	}else
	if (type == "Trail") {
		ReadCode(trail_vert, GL_VERTEX_SHADER);
	//	load("shader\\trail.vert", "shader\\trail.frag");
	}
	else {
		printf("\nシェーダー無し\n");
	}

}
void CShader::Enable(){
	glUseProgram(program);
}
void CShader::Disable(){
	glUseProgram(0);
}