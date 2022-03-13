#include "Texture.h"
#include <GLAD/glad.h>

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>
#include <iostream>
Texture2D::Texture2D()
    :mTextureID(0)
{
  
}

Texture2D::~Texture2D()
{
}

int Texture2D::LoadTexture(std::string path, std::string textureName)
{
    glGenTextures(1, &mTextureID);
    std::cout << "texture id : " << mTextureID << std::endl;
    glBindTexture(GL_TEXTURE_2D, mTextureID);
    // set the texture wrapping parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// set texture wrapping to GL_REPEAT (default wrapping method)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    // set texture filtering parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    int width, height, nrChannels;
    //stbi_set_flip_vertically_on_load(true); // tell stb_image.h to flip loaded texture's on the y-axis.
    // The FileSystem::getPath(...) is part of the GitHub repository so we can find files on any IDE/platform; replace it with your own image path.
    unsigned char* data = stbi_load(path.c_str() , &width, &height, &nrChannels, 0);
    if (data)
    {
        if (nrChannels == 3)
        {
            std::cout << "channel: " << nrChannels << std::endl;
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        }
        else if (nrChannels == 4)
        {
            std::cout << "channel: " << nrChannels << std::endl;
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
        }
        else if (nrChannels == 1)
        {
            std::cout << "channel: " << nrChannels << std::endl;
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RED, GL_UNSIGNED_BYTE, data);
        }
        
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        std::cout << "Failed to load texture" << std::endl;
    }
    stbi_image_free(data);
    return 0;
}

void Texture2D::Bind()
{
    glBindTexture(GL_TEXTURE_2D, mTextureID);
}
