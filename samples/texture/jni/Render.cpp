//
// Created by Administrator on 2017/7/19.
//

#include "Render.h"
#include "Log.h"
#include <unistd.h>
#include "Shader.h"
#include "Texture.h"

/*
static const char* vertex =
	"attribute vec4 Position;\n"
	"void main()\n"
	"{\n"
	"   gl_Position = Position;\n"
	"}\n";

static const char* fragment =
	"void main()\n"
	"{\n"
	"	gl_FragColor = vec4(0.0, 1.0, 0.0, 1.0);\n"
	"}\n";
*/
static const char* cubeVertex =
    "layout(location = 0) attribute vec4 Position;\n"
    "layout(location = 1) attribute vec2 texcoord;\n"
    "varying  vec2 otexcoord;\n"
    "void main()\n"
    "{\n"
    "   otexcoord = vec2(texcoord.x, 1.0 - texcoord.y);\n"
    "   gl_Position = Position;\n"
    "}\n";

static const char* cubeFragment =
    "varying vec2 otexcoord;\n"
    "uniform sampler2D Texture0;\n"
    "uniform sampler2D Texture1;\n"
	"void main()\n"
	"{\n"
	"	gl_FragColor = mix(texture2D( Texture0, otexcoord ) , texture2D(Texture1, otexcoord), 0.2);\n"
	"}\n";


Render::Render() :
    m_shader(NULL),
    VAO(0),
    VBO(0)
{
}

Render::~Render()
{
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);

    delete m_shader;
    m_shader = NULL;
}

void Render::Init(int width, int height)
{
    LOGD("Render::Init:glViewport:width:%d, height:%d", width, height);
    glViewport(0, 0, width, height);
    m_shader = new Shader(cubeVertex, cubeFragment);
    LOGD("program:%d", m_shader->GetProgram());

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

    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glGenBuffers(1, &EBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
    glEnableVertexAttribArray(1);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    texture0 = Texture::LoadTextureFromPackage("assets/container.jpg");
    texture1 = Texture::LoadTextureFromPackage("assets/awesomeface.png");
    LOGD("Render::Init:textID:%d, %d", texture0, texture1);

}

void Render::Draw()
{
	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
	m_shader->Use();

	glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture0);
    glUniform1i(glGetUniformLocation(m_shader->GetProgram(), "Texture0"), 0);

	glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, texture1);
    glUniform1i(glGetUniformLocation(m_shader->GetProgram(), "Texture1"), 1);

    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}

