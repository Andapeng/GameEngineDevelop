#include "PostProcessingRenderer.h"
#include "glad/glad.h"
#include "../RHI/Shader.h"
#include "../Managers/ResourceManager.h"
#include "../Managers/WindowManager.h"
#include "../Log.h"
#include "../Misc/GameTimer.h"
GameTimer timer;
int PostProcessingRenderer::Initialize()
{
    g_pWindowManager->GetMainWindowSize(mWidth, mHeight);
    // initialize renderbuffer/framebuffer object
    glGenFramebuffers(1, &this->MSFBO);
    glGenFramebuffers(1, &this->FBO);
    glGenRenderbuffers(1, &this->RBO);
    // initialize renderbuffer storage with a multisampled color buffer (don't need a depth/stencil buffer)
    glBindFramebuffer(GL_FRAMEBUFFER, this->MSFBO);
    glBindRenderbuffer(GL_RENDERBUFFER, this->RBO);
    glRenderbufferStorageMultisample(GL_RENDERBUFFER, 4, GL_RGB, mWidth, mHeight); // allocate storage for render buffer object
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_RENDERBUFFER, this->RBO); // attach MS render buffer object to framebuffer
    if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
        Logger::LogError("ERROR::POSTPROCESSOR: Failed to initialize MSFBO");
    // also initialize the FBO/texture to blit multisampled color-buffer to; used for shader operations (for postprocessing effects)
    glBindFramebuffer(GL_FRAMEBUFFER, this->FBO);
    mTexture.Generate(mWidth, mHeight, NULL);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, mTexture.GetTextureID(), 0); // attach texture to framebuffer as its color attachment
    if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
        Logger::LogError("ERROR::POSTPROCESSOR: Failed to initialize FBO");
    glBindFramebuffer(GL_FRAMEBUFFER, 0);

    // configure VAO/VBO
    unsigned int VBO;
    float vertices[] = {
        // pos        // tex
        -1.0f, -1.0f, 0.0f, 0.0f,
         1.0f,  1.0f, 1.0f, 1.0f,
        -1.0f,  1.0f, 0.0f, 1.0f,

        -1.0f, -1.0f, 0.0f, 0.0f,
         1.0f, -1.0f, 1.0f, 0.0f,
         1.0f,  1.0f, 1.0f, 1.0f
    };
    glGenVertexArrays(1, &this->VAO);
    glGenBuffers(1, &VBO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindVertexArray(this->VAO);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
    g_pResourceManager->GetShader("postprocessing_shader").Use()->SetInt("scene", 0);
    // GLfloat offset = 1.0f / 300.0f;
    // GLfloat offsets[9][2] = {
    //     { -offset,  offset  },  // top-left
    //     {  0.0f,    offset  },  // top-center
    //     {  offset,  offset  },  // top-right
    //     { -offset,  0.0f    },  // center-left
    //     {  0.0f,    0.0f    },  // center-center
    //     {  offset,  0.0f    },  // center - right
    //     { -offset, -offset  },  // bottom-left
    //     {  0.0f,   -offset  },  // bottom-center
    //     {  offset, -offset  }   // bottom-right    
    // };
    // glUniform2fv(glGetUniformLocation(g_pResourceManager->GetShader("postprocessing_shader").GetID(), "offsets"), 9, (float*)offsets);
    // GLint edge_kernel[9] = {
    //     -1, -1, -1,
    //     -1,  8, -1,
    //     -1, -1, -1
    // };
    // glUniform1iv(glGetUniformLocation(g_pResourceManager->GetShader("postprocessing_shader").GetID(), "edge_kernel"), 9, edge_kernel);
    // GLfloat blur_kernel[9] = {
    //     1.0f / 16.0f, 2.0f / 16.0f, 1.0f / 16.0f,
    //     2.0f / 16.0f, 4.0f / 16.0f, 2.0f / 16.0f,
    //     1.0f / 16.0f, 2.0f / 16.0f, 1.0f / 16.0f
    // };
    // glUniform1fv(glGetUniformLocation(g_pResourceManager->GetShader("postprocessing_shader").GetID(), "blur_kernel"), 9, blur_kernel);
    timer.Start();
    return 0;
}

int PostProcessingRenderer::Release()
{
    return 0;
}

void PostProcessingRenderer::BeginRender()
{
    glBindFramebuffer(GL_FRAMEBUFFER, this->MSFBO);
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
}

void PostProcessingRenderer::EndRender()
{
    // now resolve multisampled color-buffer into intermediate FBO to store to texture
    glBindFramebuffer(GL_READ_FRAMEBUFFER, this->MSFBO);
    glBindFramebuffer(GL_DRAW_FRAMEBUFFER, this->FBO);
    glBlitFramebuffer(0, 0, this->mWidth, this->mHeight, 0, 0, this->mWidth, this->mHeight, GL_COLOR_BUFFER_BIT, GL_NEAREST);
    glBindFramebuffer(GL_FRAMEBUFFER, 0); // binds both READ and WRITE framebuffer to default framebuffer
}

void PostProcessingRenderer::OnRender()
{
    g_pResourceManager->GetShader("postprocessing_shader").Use();
    timer.GetElapsedTime();
    g_pResourceManager->GetShader("postprocessing_shader").SetFloat("time", timer.GetTotalTime());
    g_pResourceManager->GetShader("postprocessing_shader").SetInt("confuse", this->mConfuse);
    g_pResourceManager->GetShader("postprocessing_shader").SetInt("chaos", this->mChaos);
    g_pResourceManager->GetShader("postprocessing_shader").SetInt("shake", this->mShake);

    // render textured quad
    glActiveTexture(GL_TEXTURE0);
    mTexture.Bind();
    glBindVertexArray(this->VAO);
    glDrawArrays(GL_TRIANGLES, 0, 6);
    glBindVertexArray(0);
}

void PostProcessingRenderer::SetShake(bool bShake)
{
    mShake = bShake;
}