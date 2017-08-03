//
// Created by Administrator on 2017/7/19.
//

#include "Render.h"
#include "Log.h"
#include <unistd.h>
#include "Texture.h"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

Render::Render() :
    m_VAO(0),
    m_VBO(0),
    m_LightVAO(0),
    m_ScreenWidth(0),
    m_ScreenHeight(0)
{
}

Render::~Render()
{
    glDeleteVertexArrays(1, &m_VAO);
    glDeleteBuffers(1, &m_VBO);

}

void Render::Init(int width, int height)
{
    m_ScreenWidth = width;
    m_ScreenHeight = height;
    LOGD("Render::Init:glViewport:width:%d, height:%d", width, height);
    glViewport(0, 0, width, height);
    m_shader.CreateProgramFromFile("assets/vertex.glsl", "assets/fragment.glsl");
    m_lampShader.CreateProgramFromFile("assets/lamp_vertex.glsl", "assets/lamp_fragment.glsl");
    LOGD("program:%d", m_shader.GetProgram());

float vertices[] = {
    -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
     0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
     0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
     0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
    -0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
    -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,

    -0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
     0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
     0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
     0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
    -0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
    -0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,

    -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
    -0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
    -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
    -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
    -0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
    -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,

     0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
     0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
     0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
     0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
     0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
     0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,

    -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
     0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
     0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
     0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,

    -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
     0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
     0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
     0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
    -0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
    -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f
};

    glGenVertexArrays(1, &m_VAO);
    glBindVertexArray(m_VAO);

    glGenBuffers(1, &m_VBO);
    glBindBuffer(GL_ARRAY_BUFFER, m_VBO);

    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
    glEnableVertexAttribArray(1);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    glGenVertexArrays(1, &m_LightVAO);
    glBindVertexArray(m_LightVAO);

    glBindBuffer(GL_ARRAY_BUFFER, m_VBO);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)0);
    glEnableVertexAttribArray(0);


    glEnable(GL_DEPTH_TEST);

}
glm::vec3 lightPos(0.8f, 0.8f, 1.4f);
void Render::Draw()
{
	glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
	m_shader.Use();

    //------DRAW CUBE-------
    GLint objectColorLoc = glGetUniformLocation(m_shader.GetProgram(), "objectColor");
    glUniform3f(objectColorLoc, 1.0f, 0.5f, 0.31f);

    GLint lightColorLoc = glGetUniformLocation(m_shader.GetProgram(), "lightColor");
    glUniform3f(lightColorLoc, 1.0f, 1.0f, 1.0f);

    m_shader.SetUniform3f("lightPos", lightPos.x, lightPos.y, lightPos.z);

    glm::mat4 model;
    GLint modelLoc = glGetUniformLocation(m_shader.GetProgram(), "model");
    glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

    glm::mat4 view = m_camera.GetViewMatrix();
    GLint viewLoc = glGetUniformLocation(m_shader.GetProgram(), "view");
    glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));

    glm::mat4 projection = glm::perspective(glm::radians(m_camera.GetFov()), (float)m_ScreenWidth/(float)m_ScreenHeight, 0.1f, 100.0f);
    GLint projectionLoc = glGetUniformLocation(m_shader.GetProgram(), "projection");
    glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(projection));

    glBindVertexArray(m_VAO);
    glDrawArrays(GL_TRIANGLES, 0, 36);

    //------DRAW LAMP----------
    m_lampShader.Use();
    glm::mat4 lampModel = glm::mat4();
    lampModel = glm::translate(lampModel, lightPos);
    lampModel = glm::scale(lampModel, glm::vec3(0.2f));
    GLint lampModelLoc = glGetUniformLocation(m_lampShader.GetProgram(), "model");
    glUniformMatrix4fv(lampModelLoc, 1, GL_FALSE, glm::value_ptr(lampModel));

    GLint lampViewLoc = glGetUniformLocation(m_lampShader.GetProgram(), "view");
    glUniformMatrix4fv(lampViewLoc, 1, GL_FALSE, value_ptr(view));

    GLint lampProjectionLoc = glGetUniformLocation(m_lampShader.GetProgram(), "projection");
    glUniformMatrix4fv(lampProjectionLoc, 1, GL_FALSE, value_ptr(projection));

    glBindVertexArray(m_LightVAO);
    glDrawArrays(GL_TRIANGLES, 0, 36);

    glBindVertexArray(0);
}


void Render::SetYawPatch(float xpos, float ypos)
{
    m_camera.SetPos(xpos, ypos);
}

void Render::SetZoomParam(float offset)
{
    m_camera.SetFov(offset);
}

