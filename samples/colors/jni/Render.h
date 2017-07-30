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
    Shader m_shader;
    Shader m_lampShader;
    GLuint VAO;
    GLuint VBO;
    GLuint LightVAO;
    int ScreenWidth;
    int ScreenHeight;
    Camera camera;


};



#endif //EGLTEST_RENDER_H
