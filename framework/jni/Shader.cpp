//
// Created by Administrator on 2017/7/20.
//

#include "Shader.h"
#include "Log.h"
#include <unistd.h>
#include <GLES3/gl3.h>
#include <GLES3/gl3ext.h>
#include "PackageFiles.h"

Shader::Shader() :
    m_program(0)
{

}

void Shader::CreateProgramFromString(const char* vertexString, const char* fragmentSting)
{
    m_program = createProgram(vertexString, fragmentSting);
}
void Shader::CreateProgramFromFile(const char* vertexFile, const char* fragmentFile)
{
    int length = 0;
    void* vertexBuffer = NULL;
    void* fragmentBuffer = NULL;

    PackageFiles::ReadFileFromApplicationPackage(vertexFile, length, vertexBuffer);
    LOGD("Shader::CreateProgramFromFile:vertexFile:%s, length:%d, vertexBuffer:%s", vertexFile, length, (char*)vertexBuffer);

    PackageFiles::ReadFileFromApplicationPackage(fragmentFile, length, fragmentBuffer);
    LOGD("Shader::CreateProgramFromFile:vertexFile:%s, length:%d, vertexBuffer:%s", fragmentFile, length, (char*)fragmentBuffer);

    if(vertexBuffer != NULL || fragmentBuffer != NULL)
    {
        m_program = createProgram((char*)vertexBuffer, (char*)fragmentBuffer);
    }

    free(vertexBuffer);
    free(fragmentBuffer);
}

void Shader::Use()
{
    glUseProgram(m_program);
}

void Shader::checkGlError(const char* op)
{
	if (CHECK_GL_ERROR) {
		GLint error = glGetError();
		while (error) {
			LOGD("after %s glError (0x%x)\n", op, error);
			error = glGetError();
		}
	}
}

unsigned int Shader::loadShader(int shaderType, const char* pSource)
{
    GLuint shader = glCreateShader((GLenum) shaderType);
	checkGlError("glCreateShader");
	if (shader) {
		glShaderSource(shader, 1, &pSource, NULL);
		glCompileShader(shader);
		GLint compiled = 0;
		glGetShaderiv(shader, GL_COMPILE_STATUS, &compiled);
		if (!compiled) {
			GLint infoLen = 0;
			glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &infoLen);
			if (infoLen) {
				char* buf = (char*) malloc(infoLen);
				if (buf) {
					glGetShaderInfoLog(shader, infoLen, NULL, buf);
					LOGD("Could not compile shader %d:\n%s\n", shaderType, buf);
					free(buf);
				}
				glDeleteShader(shader);
				shader = 0;
			}
		}
	}
	return shader;
}
unsigned int Shader::createProgram(const char* vertex, const char* fragment)
{
    GLuint vertexShader = loadShader(GL_VERTEX_SHADER, vertex);
	if (!vertexShader) {
		return 0;
	}

	GLuint pixelShader = loadShader(GL_FRAGMENT_SHADER, fragment);
	if (!pixelShader) {
		return 0;
	}

	GLuint program = glCreateProgram();
	if (program) {
		glAttachShader(program, vertexShader);
		checkGlError("glAttachVertexShader");

		glAttachShader(program, pixelShader);
		checkGlError("glAttachFragmentShader");

		glLinkProgram(program);
		GLint linkStatus = GL_FALSE;
		glGetProgramiv(program, GL_LINK_STATUS, &linkStatus);
		if (linkStatus != GL_TRUE) {
			GLint bufLength = 0;
			glGetProgramiv(program, GL_INFO_LOG_LENGTH, &bufLength);
			if (bufLength) {
				char* buf = (char*) malloc(bufLength);
				if (buf) {
					glGetProgramInfoLog(program, bufLength, NULL, buf);
					LOGD("Could not link program:%s", buf);
					free(buf);
				}
			}
			glDeleteProgram(program);
			program = 0;
		}
	}
	return program;
}



void Shader::SetUniform1f( 	const char* name,
      	float v0)
{
    GLint location = glGetUniformLocation(m_program, name);
    glUniform1f(location, v0);
}


void Shader::SetUniform2f( 	const char* name,
        float v0,
        float v1)
{
    GLint location = glGetUniformLocation(m_program, name);
    glUniform2f(location, v0, v1);
}

void Shader::SetUniform3f( 	const char* name,
        float v0,
      	float v1,
      	float v2)
{
    GLint location = glGetUniformLocation(m_program, name);
    glUniform3f(location, v0, v1, v2);
}

void Shader::SetUniform4f( 	const char* name,
      	float v0,
      	float v1,
      	float v2,
      	float v3)
{
    GLint location = glGetUniformLocation(m_program, name);
    glUniform4f(location, v0, v1, v2, v3);
}

void Shader::SetUniform1i( 	const char* name,
      	GLint v0)
{
    GLint location = glGetUniformLocation(m_program, name);
    glUniform1i(location, v0);
}

void Shader::SetUniform2i( 	const char* name,
      	int v0,
      	int v1)
{
    GLint location = glGetUniformLocation(m_program, name);
    glUniform2i(location, v0, v1);
}

void Shader::SetUniform3i( 	const char* name,
      	int v0,
      	int v1,
      	int v2)
{
    GLint location = glGetUniformLocation(m_program, name);
    glUniform3i(location, v0, v1, v2);
}

void Shader::SetUniform4i( 	const char* name,
      	int v0,
      	int v1,
      	int v2,
      	int v3)
{
    GLint location = glGetUniformLocation(m_program, name);
    glUniform4i(location, v0, v1, v2, v3);
}

void Shader::SetUniform1ui( 	const char* name,
      	unsigned int v0)
{
    GLint location = glGetUniformLocation(m_program, name);
    glUniform1ui(location, v0);
}

void Shader::SetUniform2ui( 	const char* name,
      	unsigned int v0,
      	unsigned int v1)
{
    GLint location = glGetUniformLocation(m_program, name);
    glUniform2ui(location, v0, v1);
}

void Shader::SetUniform3ui( 	const char* name,
      	unsigned int v0,
      	unsigned int v1,
      	unsigned int v2)
{
    GLint location = glGetUniformLocation(m_program, name);
    glUniform3ui(location, v0, v1, v2);
}

void Shader::SetUniform4ui( 	const char* name,
      	unsigned int v0,
      	unsigned int v1,
      	unsigned int v2,
      	unsigned int v3)
{
    GLint location = glGetUniformLocation(m_program, name);
    glUniform4ui(location, v0, v1, v2, v3);
}

void Shader::SetUniform1fv( 	const char* name,
      	unsigned int count,
      	const float *value)
{
    GLint location = glGetUniformLocation(m_program, name);
    glUniform1fv(location, count, value);
}

void Shader::SetUniform2fv( 	const char* name,
      	unsigned int count,
      	const float *value)
{
    GLint location = glGetUniformLocation(m_program, name);
    glUniform2fv(location, count, value);
}

void Shader::SetUniform3fv( 	const char* name,
      	unsigned int count,
      	const float *value)
{
    GLint location = glGetUniformLocation(m_program, name);
    glUniform3fv(location, count, value);
}

void Shader::SetUniform4fv( 	const char* name,
      	unsigned int count,
      	const float *value)
{
    GLint location = glGetUniformLocation(m_program, name);
    glUniform4fv(location, count, value);
}

void Shader::SetUniform1iv( 	const char* name,
      	unsigned int count,
      	const int *value)
{
    GLint location = glGetUniformLocation(m_program, name);
    glUniform1iv(location, count, value);
}

void Shader::SetUniform2iv( 	const char* name,
      	unsigned int count,
      	const int *value)
{
    GLint location = glGetUniformLocation(m_program, name);
    glUniform2iv(location, count, value);
}

void Shader::SetUniform3iv( 	const char* name,
      	unsigned int count,
      	const int *value)
{
    GLint location = glGetUniformLocation(m_program, name);
    glUniform3iv(location, count, value);
}

void Shader::SetUniform4iv( 	const char* name,
      	unsigned int count,
      	const int *value)
{
    GLint location = glGetUniformLocation(m_program, name);
    glUniform4iv(location, count, value);
}

void Shader::SetUniform1uiv( 	const char* name,
      	unsigned int count,
      	const unsigned int *value)
{
    GLint location = glGetUniformLocation(m_program, name);
    glUniform1uiv(location, count, value);
}

void Shader::SetUniform2uiv( 	const char* name,
      	unsigned int count,
      	const unsigned int *value)
{
    GLint location = glGetUniformLocation(m_program, name);
    glUniform2uiv(location, count, value);
}

void Shader::SetUniform3uiv( 	const char* name,
      	unsigned int count,
      	const unsigned int *value)
{
    GLint location = glGetUniformLocation(m_program, name);
    glUniform3uiv(location, count, value);
}

void Shader::SetUniform4uiv( 	const char* name,
      	unsigned int count,
      	const unsigned int *value)
{
    GLint location = glGetUniformLocation(m_program, name);
    glUniform4uiv(location, count, value);
}

void Shader::SetUniformMatrix2fv( 	const char* name,
      	unsigned int count,
      	bool transpose,
      	const float *value)
{
    GLint location = glGetUniformLocation(m_program, name);
    glUniformMatrix2fv(location, count, GL_FALSE, value);
}

void Shader::SetUniformMatrix3fv( 	const char* name,
      	unsigned int count,
      	bool transpose,
      	const float *value)
{
    GLint location = glGetUniformLocation(m_program, name);
    glUniformMatrix3fv(location, count, GL_FALSE, value);
}

void Shader::SetUniformMatrix4fv( 	const char* name,
      	unsigned int count,
      	bool transpose,
      	const float *value)
{
    GLint location = glGetUniformLocation(m_program, name);
    glUniformMatrix4fv(location, count, GL_FALSE, value);
}

void Shader::SetUniformMatrix2x3fv( 	const char* name,
      	unsigned int count,
      	bool transpose,
      	const float *value)
{
    GLint location = glGetUniformLocation(m_program, name);
    glUniformMatrix2x3fv(location, count, GL_FALSE, value);
}

void Shader::SetUniformMatrix3x2fv( 	const char* name,
      	unsigned int count,
      	bool transpose,
      	const float *value)
{
    GLint location = glGetUniformLocation(m_program, name);
    glUniformMatrix3x2fv(location, count, GL_FALSE, value);
}

void Shader::SetUniformMatrix2x4fv( 	const char* name,
      	unsigned int count,
      	bool transpose,
      	const float *value)
{
    GLint location = glGetUniformLocation(m_program, name);
    glUniformMatrix2x4fv(location, count, GL_FALSE, value);
}

void Shader::SetUniformMatrix4x2fv( 	const char* name,
      	unsigned int count,
      	bool transpose,
      	const float *value)
{
    GLint location = glGetUniformLocation(m_program, name);
    glUniformMatrix4x2fv(location, count, GL_FALSE, value);
}

void Shader::SetUniformMatrix3x4fv( 	const char* name,
      	unsigned int count,
      	bool transpose,
      	const float *value)
{
    GLint location = glGetUniformLocation(m_program, name);
    glUniformMatrix3x4fv(location, count, GL_FALSE, value);
}

void Shader::SetUniformMatrix4x3fv( 	const char* name,
      	unsigned int count,
      	bool transpose,
      	const float *value)
{
    GLint location = glGetUniformLocation(m_program, name);
    glUniformMatrix4x3fv(location, count, GL_FALSE, value);
}
