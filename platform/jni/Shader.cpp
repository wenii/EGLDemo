//
// Created by Administrator on 2017/7/20.
//

#include "Shader.h"
#include "Log.h"
#include <unistd.h>


Shader::Shader(const char* vertex, const char* fragment)
{
    m_program = createProgram(vertex, fragment);
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

GLuint Shader::loadShader(GLenum shaderType, const char* pSource)
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
GLuint Shader::createProgram(const char* vertex, const char* fragment)
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
