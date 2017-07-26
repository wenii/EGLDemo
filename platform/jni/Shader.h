//
// Created by Administrator on 2017/7/20.
//

#ifndef EGLDEMO_SHADER_H
#define EGLDEMO_SHADER_H



class Shader
{
public:
    static const bool CHECK_GL_ERROR = true;

    void CreateProgramFromString(const char* vertexString, const char* fragmentSting);
    void CreateProgramFromFile(const char* vertexFile, const char* fragmentFile);

    unsigned int GetProgram(){return m_program;}
    void Use();

private:
    void checkGlError(const char* op);
    unsigned int loadShader(int shaderType, const char* pSource);
    unsigned int createProgram(const char*, const char*);


private:
    unsigned int  m_program;

};



#endif //EGLDEMO_SHADER_H
