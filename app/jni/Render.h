//
// Created by Administrator on 2017/7/19.
//

#ifndef EGLTEST_RENDER_H
#define EGLTEST_RENDER_H
#include <GLES3/gl3.h>
#include <GLES3/gl3ext.h>

class Shader;
class Render
{
public:
    Render();
    ~Render();
    void Draw();
    void Init(int width, int height);

private:
    Shader* m_shader;
    GLuint VAO;
    GLuint VBO;
    GLuint EBO;
    GLuint texture;


};



#endif //EGLTEST_RENDER_H
