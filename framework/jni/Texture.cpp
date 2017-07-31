//
// Created by Administrator on 2017/7/21.
//

#include "Texture.h"
#include "../../thirdparty/stb/stb_image.h"
#include <GLES3/gl3.h>
#include <GLES3/gl3ext.h>
#include <unistd.h>
#include "PackageFiles.h"


unsigned int Texture::LoadTextureFromBuffer(void* buffer, int length)
{

    GLuint textID = 0;
    int comp , width, height;
    stbi_uc * image = stbi_load_from_memory( (unsigned char *)buffer, length, &width, &height, &comp, 4 );
    if(image != NULL)
    {
        glGenTextures(1, &textID);
        glBindTexture( GL_TEXTURE_2D, textID );

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        glTexImage2D( GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, (const unsigned char*)image );
        glGenerateMipmap(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, 0);
    }
    stbi_image_free(image);
    return textID;
}

unsigned int  Texture::LoadTextureFromPackage(const char* filename)
{
    int length = 0;
    void* buffer = NULL;
    unsigned int textID = 0;
    if(PackageFiles::ReadFileFromApplicationPackage(filename, length, buffer) && buffer != NULL)
    {
        textID = LoadTextureFromBuffer(buffer, length);
    }

    free(buffer);
    return textID;
}