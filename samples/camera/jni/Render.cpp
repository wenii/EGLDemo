//
// Created by Administrator on 2017/7/19.
//
#include "Render.h"
#include "Log.h"
#include <unistd.h>
#include "Shader.h"
#include "Texture.h"


Render::Render() :
    m_VAO(0),
    m_VBO(0),
    m_texture0(0),
    m_texture1(0),
    m_screenWidth(0),
    m_screenHeight(0),
    m_Yaw(0.0f),
    m_Pitch(0.0f),
    m_Fov(45.0f),
    m_cameraPos(glm::vec3(0.0f, 0.0f, 3.0f)),
    m_cameraFront(glm::vec3(0.0f, 0.0f, -1.0f)),
    m_cameraUp(glm::vec3(0.0f, 1.0f, 0.0f))
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
    LOGD("Render::Init:glViewport:width:%d, height:%d", width, height);
    glViewport(0, 0, width, height);
    m_shader.CreateProgramFromFile("assets/vertex.glsl", "assets/fragment.glsl");
    LOGD("program:%d", m_shader.GetProgram());

    float vertices[] = {
        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
         0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
         0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
        -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

        -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
         0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
         0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
         0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
         0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
         0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
         0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f
    };


    glGenVertexArrays(1, &m_VAO);
    glBindVertexArray(m_VAO);

    glGenBuffers(1, &m_VBO);
    glBindBuffer(GL_ARRAY_BUFFER, m_VBO);

    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);


    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
    glEnableVertexAttribArray(1);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    m_texture0 = Texture::LoadTextureFromPackage("assets/container.jpg");
    m_texture1 = Texture::LoadTextureFromPackage("assets/awesomeface.png");
    LOGD("Render::Init:textID:%d, %d", m_texture0, m_texture1);

    glEnable(GL_DEPTH_TEST);

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

    glm::mat4 model;
    model = glm::rotate(model, glm::radians(0.0f), glm::vec3(0.0f, 0.0f, 1.0f));
    GLint modelLoc = glGetUniformLocation(m_shader.GetProgram(), "model");
    glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

    glm::mat4 view = glm::lookAt(m_cameraPos, glm::vec3(0.0f, 0.0f, 0.0f), m_cameraUp);
    GLint viewLoc = glGetUniformLocation(m_shader.GetProgram(), "view");
    glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));

    glm::mat4 projection;
    projection = glm::perspective(glm::radians(m_Fov), (float)m_screenWidth/m_screenHeight, 0.1f, 100.0f);
    GLint projectionLoc = glGetUniformLocation(m_shader.GetProgram(), "projection");
    glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(projection));

    glBindVertexArray(m_VAO);
    glDrawArrays(GL_TRIANGLES, 0, 36);
    glBindVertexArray(0);
}

void Render::SetYawPatch(float xpos, float ypos)
{
    m_Yaw   -= xpos * 0.1;
    m_Pitch -= ypos * 0.1;

	if (m_Pitch > 89.0f)
		m_Pitch = 89.0f;
	if (m_Pitch < -89.0f)
		m_Pitch = -89.0f;

    glm::vec3 front;
    front.x = cos(glm::radians(m_Yaw)) * cos(glm::radians(m_Pitch));
    front.y = sin(glm::radians(m_Pitch));
    front.z = sin(glm::radians(m_Yaw)) * cos(glm::radians(m_Pitch));
    m_cameraFront = glm::normalize(front);
    m_cameraPos = m_cameraFront * 3.0f;
}

void Render::SetZoomParam(float offset)
{
    int range = m_screenWidth > m_screenHeight ? m_screenWidth : m_screenHeight;
    float newOffset = 45.0 * offset / (float)range;

    if(m_Fov >= 1.0f && m_Fov <= 45.0f)
    {
        m_Fov -= newOffset;
    }
    if(m_Fov <= 1.0f)
    {
        m_Fov = 1.0f;
    }
    if(m_Fov >= 45.0f)
    {
        m_Fov = 45.0f;
    }
}

