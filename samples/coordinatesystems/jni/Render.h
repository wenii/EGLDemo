//
// Created by Administrator on 2017/7/19.
//

#ifndef EGLTEST_RENDER_H
#define EGLTEST_RENDER_H
#include <GLES3/gl3.h>
#include <GLES3/gl3ext.h>
#include "Shader.h"
class Render
{
public:
    Render();
    ~Render();
    void Draw();
    void Init(int width, int height);

private:
    Shader      m_shader;
    GLuint      m_VAO;
    GLuint      m_VBO;
    GLuint      m_texture0;
    GLuint      m_texture1;

    int         m_screenWidth;
    int         m_screenHeight;

    static float Count;

};



#endif //EGLTEST_RENDER_H
