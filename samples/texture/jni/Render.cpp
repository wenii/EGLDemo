//
// Created by Administrator on 2017/7/19.
//

#include "Render.h"
#include "Log.h"
#include <unistd.h>
#include "Texture.h"
#include <math.h>
Render::Render() :
    m_VAO(0),
    m_VBO(0),
    m_EBO(0),
    m_texture0(0),
    m_texture1(0),
    m_screenWidth(0),
    m_screenHeight(0),
    m_Yaw(0.0f),
    m_Pitch(0.0f),
    m_Fov(45.0f),
    m_cameraPos(glm::vec3(0.0f, 0.0f, 1.0f)),
    m_cameraFront(glm::vec3(0.0f, 0.0f, -1.0f)),
    m_cameraUp(glm::vec3(0.0f, 1.0f, 0.0f)),
    m_scale(1.0f)
{

}

Render::~Render()
{
    glDeleteVertexArrays(1, &m_VAO);
    glDeleteBuffers(1, &m_VBO);

}

void Render::Init(int width, int height)
{
    m_screenWidth = width;
    m_screenHeight = height;
    m_scale = sqrt((float)m_screenWidth * m_screenWidth + (float)m_screenHeight * m_screenHeight);
    LOGD("Render::Init:glViewport:width:%d, height:%d", width, height);
    glViewport(0, 0, width, height);
    m_shader.CreateProgramFromFile("assets/vertex.glsl", "assets/fragment.glsl");
    LOGD("program:%d", m_shader.GetProgram());

    GLfloat vertices[] = {
        // Positions       // Texture Coords
        -1.0, -1.0, 0,     0.0, 0.0,   //左下
        1.0,  -1.0, 0,     1.0, 0.0,   //右下
        -1.0,  1.0, 0,     0.0, 1.0,   //左上
        1.0,   1.0, 0,     1.0, 1.0,   //右上
    };


    GLuint indices[] = {  // Note that we start from 0!
        0, 1, 2, // First Triangle
        1, 2, 3  // Second Triangle
    };

    glGenVertexArrays(1, &m_VAO);
    glBindVertexArray(m_VAO);

    glGenBuffers(1, &m_VBO);
    glBindBuffer(GL_ARRAY_BUFFER, m_VBO);

    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glGenBuffers(1, &m_EBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
    glEnableVertexAttribArray(1);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    m_texture0 = Texture::LoadTextureFromPackage("assets/container.jpg");
    m_texture1 = Texture::LoadTextureFromPackage("assets/awesomeface.png");
    LOGD("Render::Init:textID:%d, %d", m_texture0, m_texture1);

}

void Render::Draw()
{
	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
	m_shader.Use();

	glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, m_texture0);
    glUniform1i(glGetUniformLocation(m_shader.GetProgram(), "Texture0"), 0);

	glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, m_texture1);
    glUniform1i(glGetUniformLocation(m_shader.GetProgram(), "Texture1"), 1);


    float sum = sqrt((float)m_screenWidth * m_screenWidth + (float)m_screenHeight * m_screenHeight);
    float zoomScale = m_scale / sum;

    glm::mat4 model;
    model = glm::rotate(model, glm::radians(0.0f), glm::vec3(0.0f, 0.0f, 1.0f));

    // 缩放
    model = glm::scale(model, glm::vec3(zoomScale , zoomScale, 1.0f));

    // 移动
    float x = zoomScale * m_screenWidth;
    float y = zoomScale * m_screenHeight;
    glm::vec3 vec;
    vec.x = m_Yaw / x * 2;
    vec.y = m_Pitch / y * 2;
    vec.z = 1.0f;
    vec = glm::normalize(vec);
    model = glm::translate(model, vec);

     GLint transformLoc = glGetUniformLocation(m_shader.GetProgram(), "transform");
     glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(model));

    glBindVertexArray(m_VAO);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}


void Render::SetYawPatch(float xpos, float ypos)
{
    float sum = sqrt((float)m_screenWidth * m_screenWidth + (float)m_screenHeight * m_screenHeight);
    float zoomScale = m_scale / sum;

    float x = (zoomScale * m_screenWidth - m_screenWidth) / 2;
    float y = (zoomScale * m_screenHeight - m_screenHeight ) / 2;
     LOGD("Render::SetYawPatch:x:%f, y:%f, yaw:%f, pitch:%f", x, y, m_Yaw, m_Pitch);
      m_Yaw   -= xpos;
      if (abs(m_Yaw) > x){
          if(m_Yaw < 0){
            m_Yaw  = x * -1;
          }else{
            m_Yaw  = x;
          }
       }
       m_Pitch += ypos;
      if(abs(m_Pitch) > y){
        if(m_Pitch < 0){
            m_Pitch = y * -1;
        }else{
            m_Pitch = y;
        }
      }
}

void Render::SetZoomParam(float offset)
{
    m_scale += offset;
    float sum = sqrt((float)m_screenWidth * m_screenWidth + (float)m_screenHeight * m_screenHeight);
    if(m_scale < sum){
            m_scale = sum;
    }
}


