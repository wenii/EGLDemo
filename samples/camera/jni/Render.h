//
// Created by Administrator on 2017/7/19.
//

#ifndef EGLTEST_RENDER_H
#define EGLTEST_RENDER_H
#include <GLES3/gl3.h>
#include <GLES3/gl3ext.h>
#include "Shader.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

class Render
{
public:
    Render();
    ~Render();
    void Draw();
    void Init(int width, int height);
    void SetYawPatch(float xpos, float ypos);

private:
    Shader m_shader;
    GLuint VAO;
    GLuint VBO;
    GLuint texture0;
    GLuint texture1;

    int ScreenWidth;
    int ScreenHeight;

    float Yaw;
    float Pitch;
    glm::vec3 cameraPos;
    glm::vec3 cameraFront;
    glm::vec3 cameraUp;

    static float Count;

};



#endif //EGLTEST_RENDER_H
