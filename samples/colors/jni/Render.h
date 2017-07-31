//
// Created by Administrator on 2017/7/19.
//

#ifndef EGLTEST_RENDER_H
#define EGLTEST_RENDER_H
#include <GLES3/gl3.h>
#include <GLES3/gl3ext.h>
#include "Shader.h"
#include "Camera.h"

class Render
{
public:
    Render();
    ~Render();
    void Draw();
    void Init(int width, int height);
    void SetYawPatch(float xpos, float ypos);
    void SetZoomParam(float offset);

private:
    Shader      m_shader;
    Shader      m_lampShader;
    GLuint      m_VAO;
    GLuint      m_VBO;
    GLuint      m_LightVAO;
    int         m_ScreenWidth;
    int         m_ScreenHeight;
    Camera      m_camera;


};



#endif //EGLTEST_RENDER_H
