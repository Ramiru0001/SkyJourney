	#pragma once

//#include "GL.h"
#include <map>
#include <string>
class Shader {
public:
	//シェーダー側のlocationに対応
	enum {
		eVertexLocation,	//layout(location = 0) 
		eNormalLocation,	//layout(location = 1) 
		eTexcoordlLocation,	//layout(location = 2) 
	};

private:
	GLuint vertexShader;
	GLuint fragShader;

	GLuint program;
	GLint linked;
	static std::map<std::string, Shader*> m_instances;


	/*!
	@brief	コードからシェーダプログラムを作成
	@param program	[in]	シェーダープログラム
	@param shader	[in]	シェーダーオブジェクト　glCreateShader(GL_VERTEX_SHADER),glCreateShader(GL_FRAGMENT_SHADER)
	@param file		[in]	シェーダーファイル名
	@retval	成否
	**/
	bool Load(GLuint shader, const char* file);
	/*!
	@brief	コードからシェーダプログラムを作成
	@param program	[in]	シェーダープログラム
	@param shader	[in]	シェーダーオブジェクト　glCreateShader(GL_VERTEX_SHADER),glCreateShader(GL_FRAGMENT_SHADER)
	@param code		[in]	シェーダーソースコード
	@retval	成否
	**/
	bool ReadCode(GLuint shader, const char* code);

public:

	/*!
	@brief	コンパイル済みシェーダーの取得
	@param name [in] 名前
	@retval	シェーダーインスタンス
	**/
	static Shader* GetInstance(std::string name);

	/*!
	@brief	組み込み済みシェーダーの生成
	@param name [in] 名前
	@param vertex_shader_file	[in]	頂点シェーダのファイル名
	@param fragment_shader_file	[in]	フラグメントシェーダのファイル名
	@retval	シェーダーインスタンス
	**/
	static Shader* CreateInstance(std::string name,const char *vertex_shader_file, const char* fragment_shader_file);
	/*!
	@brief	コンストラクタ
			シェーダオブジェクトの生成のみ
	**/
	Shader();

	/*!
	@brief	コンストラクタ
			シェーダーファイルから生成
	@param vertex_shader_file	[in]	頂点シェーダのファイル名
	@param fragment_shader_file	[in]	フラグメントシェーダのファイル名
	**/
	Shader(const char* vertex_shader_file,const char* fragment_shader_file);
	/*!
	@brief	デストラクタ
	**/
	~Shader();

	/*!
	@brief	ファイルからシェーダプログラムを作成
	@param vertexPath	[in]	頂点シェーダのファイル名
	@param fragPath	[in]		フラグメントシェーダのファイル名
	@retval	成否
	**/
	bool Load(const char* vertexPath,const char*  fragPath);
	/*!
	@brief	ファイルからシェーダプログラムを個々に作成
	@param	path	[in]	シェーダーのファイル名
	@param	type	[in]	シェーダーオブジェクトの種類(GL_VERTEX_SHADER,GL_FRAGMENT_SHADER)
	@retval	成否
	**/
	bool Load(const char* path, GLuint type);
	/*!
	@brief	ソースコードからシェーダプログラムを個々に作成
	@param	code	[in]	シェーダーのソースコード
	@param	type	[in]	シェーダーオブジェクトの種類(GL_VERTEX_SHADER,GL_FRAGMENT_SHADER)
	@retval	成否
	**/
	bool ReadCode(const char* path,GLuint type);

	/*!
	@brief	ソースコードからシェーダプログラムを作成
	@param vertexcode	[in]	頂点シェーダのソースコード
	@param fragcode		[in]	フラグメントシェーダのソースコード
	@retval	成否
	**/
	bool ReadCode(const char* vertexcode, const char* fragcode);

	/*!
	@brief	シェーダー有効化
	@retval	無し
	**/
	void Enable();
	/*!
	@brief	シェーダー無効化
	@retval	無し
	**/
	void Disable();
	/*!
	@brief	シェーダープログラムの取得
	@retval	シェーダープログラム
	**/
	GLuint GetProgram() const{
		return program;
	}


};