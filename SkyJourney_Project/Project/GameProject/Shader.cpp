#include "Shader.h"

std::map<std::string, Shader*> Shader::m_instances;
Shader* Shader::GetInstance(std::string name)
{
	if (!m_instances[name]) m_instances[name] = new Shader();
	return m_instances[name];
}
Shader* Shader::CreateInstance(std::string name, const char* vertex_shader_file, const char* fragment_shader_file)
{

	if (!m_instances[name]) m_instances[name] = new Shader(vertex_shader_file, fragment_shader_file);
	return m_instances[name];
}
Shader::Shader():program(0){
}

Shader::Shader(const char* vertex_shader_file, const char* fragment_shader_file) {
	Load(vertex_shader_file, fragment_shader_file);
}

bool Shader::ReadCode(GLuint shader, const char* code) {
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
			printf("%s\n", log);
			delete log;
		}
	}
	glAttachShader(program, shader);
	glLinkProgram(program);

	glGetProgramiv(program, GL_LINK_STATUS, &linked);

	if (linked) {
		//	glUseProgram(program);
	} else {
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

	return true;

}
bool Shader::Load(GLuint shader, const char *file) {
	FILE *fp;
	fopen_s(&fp,file, "rb");
	if(!fp) {
		printf("ファイルが開けません[%s]\n",file);
		return false;
	}
	//ファイルの末尾まで移動
	fseek( fp, 0, SEEK_END );
	//現在の位置からファイルのサイズを取得
	int size = ftell( fp );
	fseek( fp, 0, SEEK_SET );
	//コード読み込み先領域を確保
	GLchar *code = new char[size+1];
	//コード読み込み
	fread(code,size,1,fp);
	fclose(fp);
	code[size] = '\0';
	//読み込んだコードをコンパイル
	bool r = ReadCode(shader, code);
	delete code;
	return r;
 
}
bool Shader::ReadCode(const char* vertexcode, const char* fragcode) {

	program = glCreateProgram();
	if (vertexcode) {
		//頂点シェーダーの作成
		bool ret = ReadCode(glCreateShader(GL_VERTEX_SHADER), vertexcode);
		if (!ret) return false;
	}
	if (fragcode) {
		//フラグメントシェーダーの作成
		bool ret = ReadCode(glCreateShader(GL_FRAGMENT_SHADER), fragcode);
		if (!ret) return false;
	}
	return true;
}
bool Shader::Load(const char* vertexPath,const char* fragPath){

	program = glCreateProgram();
	if(vertexPath) {
		//頂点シェーダーの作成
		bool ret = Load(glCreateShader(GL_VERTEX_SHADER),vertexPath);
		if(!ret) return false;
	}
	if(fragPath) {
		//フラグメントシェーダーの作成
		bool ret = Load(glCreateShader(GL_FRAGMENT_SHADER),fragPath);
		if(!ret) return false;
	}
	return true;
}
bool Shader::Load(const char* path, GLuint type){
	if (!program) program = glCreateProgram();
	if (path) {
		bool ret = Load(glCreateShader(type), path);
		if (!ret) return false;
	}
	return true;
}
bool Shader::ReadCode(const char* path, GLuint type) {
	if (!program) program = glCreateProgram();
	if (path) {
		bool ret = ReadCode(glCreateShader(type), path);
		if (!ret) return false;
	}
	return true;
}
Shader::~Shader(){
	if (program>0) glDeleteProgram(program);

}
void Shader::Enable(){
	glUseProgram(program);
}
void Shader::Disable(){
	glUseProgram(0);
}