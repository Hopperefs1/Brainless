#ifndef MY_WINDOW_H
#define MY_WINDOW_H

#include <GLFW/glfw3.h>
#include <iostream>
using namespace std;
typedef struct {
  GLFWwindow *window;
  int width;
  int height;
} My_window;
void framebuffer_size_callback(GLFWwindow *window1, int width, int height);
void createWindow(My_window *window1) {
  glfwInit();
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  cout << "hello" << endl;
  int this_width = window1->width;
  int this_height = window1->height;
  // CREATING WINDOW
  window1->window =
      glfwCreateWindow(this_width, this_height, "hello", NULL, NULL);

  if (window1->window == NULL) {
    std::cout << "FAILED TO CREATE GLFW WINDOW" << std::endl;
    glfwTerminate();
    return;
  }
  cout << "hello2" << endl;
  glfwMakeContextCurrent(window1->window);
  glfwSetFramebufferSizeCallback(window1->window, framebuffer_size_callback);

  cout << "hello3" << endl;
}

void framebuffer_size_callback(GLFWwindow *window1, int width, int height) {
  glViewport(0, 0, width, height);
}
#endif // ! MY_WINDOW_H
