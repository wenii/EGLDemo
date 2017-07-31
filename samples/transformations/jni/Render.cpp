//
// Created by Administrator on 2017/7/19.
//
#include "Render.h"
#include "Log.h"
#include <unistd.h>
#include "Shader.h"
#include "Texture.h"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"


float Render::frameCount = 0.0f;
Render::Render() :
    m_VAO(0),
    m_VBO(0),
    m_EBO(0),
    m_texture0(0),
    m_texture1(0)
{
}

Render::~Render()
{
    glDeleteVertexArrays(1, &m_VAO);
    glDeleteBuffers(1, &m_VBO);
}

void Render::Init(int width, int height)
{
    LOGD("Render::Init:glViewport:width:%d, height:%d", width, height);
    glViewport(0, 0, width, height);
    m_shader.CreateProgramFromFile("assets/vertex.glsl", "assets/fragment.glsl");
    LOGD("program:%d", m_shader.GetProgram());

    GLfloat vertices[] = {
        // Positions       // Texture Coords
        -0.5, -0.5, 0,     0.0, 0.0,   //左下
        0.5,  -0.5, 0,     1.0, 0.0,   //右下
        -0.5,  0.5, 0,     0.0, 1.0,   //左上
        0.5,   0.5, 0,     1.0, 1.0,   //右上
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
    frameCount += 0.05f;

	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
	m_shader.Use();

	glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, m_texture0);
    glUniform1i(glGetUniformLocation(m_shader.GetProgram(), "Texture0"), 0);

	glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, m_texture1);
    glUniform1i(glGetUniformLocation(m_shader.GetProgram(), "Texture1"), 1);


    glm::mat4 transform;
    transform = glm::translate(transform, glm::vec3(0.5f, -0.5f, 0.0f));
    transform = glm::rotate(transform, (GLfloat)frameCount, glm::vec3(0.0f, 0.0f, 1.0f));

    GLint transformLoc = glGetUniformLocation(m_shader.GetProgram(), "transform");
    glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(transform));

    glBindVertexArray(m_VAO);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}

