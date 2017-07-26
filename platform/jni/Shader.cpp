//
// Created by Administrator on 2017/7/20.
//

#include "Shader.h"
#include "Log.h"
#include <unistd.h>
#include <GLES3/gl3.h>
#include <GLES3/gl3ext.h>
#include "PackageFiles.h"

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
