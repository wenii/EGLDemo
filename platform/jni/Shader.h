//
// Created by Administrator on 2017/7/20.
//

#ifndef EGLDEMO_SHADER_H
#define EGLDEMO_SHADER_H
#include <GLES3/gl3.h>
#include <GLES3/gl3ext.h>


class Shader
{
public:
    static const bool CHECK_GL_ERROR = true;
    Shader(const char* vertex, const char* fragment);
    GLuint GetProgram(){return m_program;}
    void Use();

private:
    void checkGlError(const char* op);
    GLuint loadShader(GLenum shaderType, const char* pSource);
    GLuint createProgram(const char*, const char*);

private:
    GLuint  m_program;

};



#endif //EGLDEMO_SHADER_H
