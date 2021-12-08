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
    void SetZoomParam(float offset);

private:
    Shader m_shader;
    GLuint m_VAO;
    GLuint m_VBO;
    GLuint m_EBO;
    GLuint m_texture0;
    GLuint m_texture1;

    int             m_screenWidth;
    int             m_screenHeight;

    float           m_Yaw;
    float           m_Pitch;
    float           m_Fov;
    glm::vec3       m_cameraPos;
    glm::vec3       m_cameraFront;
    glm::vec3       m_cameraUp;
    float           m_scale;

};



#endif //EGLTEST_RENDER_H
