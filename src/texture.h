#ifndef MY_TEXTURE_H
#define MY_TEXTURE_H

#include <iostream>
#define STB_IMAGE_IMPLEMENTATION
#include "../Dependencies/stb_image.h"
#include "../Dependencies/glad.h"
#include <GLFW/glfw3.h>

using namespace std;

typedef struct {
  unsigned int tex1;
  unsigned int tex2;
} My_texture;
void createTexture(My_texture *texture, const char *p1, const char *p2,
                   unsigned int shaderProgram) {
  glGenTextures(1, &texture->tex1);
  glBindTexture(GL_TEXTURE_2D, texture->tex1);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  glPixelStorei(
      GL_UNPACK_ALIGNMENT,
      1); // whatever happens remember this one line for your whole life this
          // makes opengl read the bytes of a image byte by byte with no padding

  int width, height, nrChannels;
  stbi_set_flip_vertically_on_load(true);
  unsigned char *data = stbi_load(p1, &width, &height, &nrChannels, 0);

  if (data != NULL) {
    GLenum format = GL_RGBA;
    if (nrChannels == 3) {
      format = GL_RGB;
    }
    glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format,
                 GL_UNSIGNED_BYTE, data);
  } else {
    cerr << "image not loaded properly" << endl;
  }

  stbi_image_free(data);

  glGenTextures(1, &texture->tex2);
  glBindTexture(GL_TEXTURE_2D, texture->tex2);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  glPixelStorei(
      GL_UNPACK_ALIGNMENT,
      1); // whatever happens remember this one line for your whole life this
  //
  data = stbi_load(p2, &width, &height, &nrChannels, 0);
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB,
               GL_UNSIGNED_BYTE, data);

  stbi_image_free(data);

  glUniform1i(glGetUniformLocation(shaderProgram, "texture1"), 0);
  glUniform1i(glGetUniformLocation(shaderProgram, "texture2"), 1);
}
#endif
