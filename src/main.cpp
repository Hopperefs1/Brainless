#include "dependencies.h"

float deltaTime = 0.0f;
float lastFrame = 0.0f;

My_window mywindow;
My_texture texture;
Camera cam1;
void render(unsigned int VAO, unsigned int texture1, unsigned int texture2,
            unsigned int shaderProgram, GLFWwindow *window);
// simple vertex shader source code store in constant char string
int main() {
  // INITIALIZING GLFWG

  cam1.cameraPos = glm::vec3(0.0f, 0.0f, 3.0f);
  //-------------------------------
  mywindow.width = 800;
  mywindow.height = 600;
  createWindow(&mywindow);
  // INITIALIZING GLAD
  if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
    std::cout << "FAILED TO INITIALIZE GLAD" << std::endl;
    return -1;
  }
  glViewport(0, 0, mywindow.width, mywindow.height);
  cout << "hello4" << endl;
  //----------------------------------

  // TRIANGLE
  // vertex input

  float vertices[] = {// positions                          // tex coords
                      -0.5f, -0.5f, -0.5f, 0.0f,  0.0f,  0.5f,  -0.5f, -0.5f,
                      1.0f,  0.0f,  0.5f,  0.5f,  -0.5f, 1.0f,  1.0f,  0.5f,
                      0.5f,  -0.5f, 1.0f,  1.0f,  -0.5f, 0.5f,  -0.5f, 0.0f,
                      1.0f,  -0.5f, -0.5f, -0.5f, 0.0f,  0.0f,

                      -0.5f, -0.5f, 0.5f,  0.0f,  0.0f,  0.5f,  -0.5f, 0.5f,
                      1.0f,  0.0f,  0.5f,  0.5f,  0.5f,  1.0f,  1.0f,  0.5f,
                      0.5f,  0.5f,  1.0f,  1.0f,  -0.5f, 0.5f,  0.5f,  0.0f,
                      1.0f,  -0.5f, -0.5f, 0.5f,  0.0f,  0.0f,

                      -0.5f, 0.5f,  0.5f,  1.0f,  0.0f,  -0.5f, 0.5f,  -0.5f,
                      1.0f,  1.0f,  -0.5f, -0.5f, -0.5f, 0.0f,  1.0f,  -0.5f,
                      -0.5f, -0.5f, 0.0f,  1.0f,  -0.5f, -0.5f, 0.5f,  0.0f,
                      0.0f,  -0.5f, 0.5f,  0.5f,  1.0f,  0.0f,

                      0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.5f,  0.5f,  -0.5f,
                      1.0f,  1.0f,  0.5f,  -0.5f, -0.5f, 0.0f,  1.0f,  0.5f,
                      -0.5f, -0.5f, 0.0f,  1.0f,  0.5f,  -0.5f, 0.5f,  0.0f,
                      0.0f,  0.5f,  0.5f,  0.5f,  1.0f,  0.0f,

                      -0.5f, -0.5f, -0.5f, 0.0f,  1.0f,  0.5f,  -0.5f, -0.5f,
                      1.0f,  1.0f,  0.5f,  -0.5f, 0.5f,  1.0f,  0.0f,  0.5f,
                      -0.5f, 0.5f,  1.0f,  0.0f,  -0.5f, -0.5f, 0.5f,  0.0f,
                      0.0f,  -0.5f, -0.5f, -0.5f, 0.0f,  1.0f,

                      -0.5f, 0.5f,  -0.5f, 0.0f,  1.0f,  0.5f,  0.5f,  -0.5f,
                      1.0f,  1.0f,  0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.5f,
                      0.5f,  0.5f,  1.0f,  0.0f,  -0.5f, 0.5f,  0.5f,  0.0f,
                      0.0f,  -0.5f, 0.5f,  -0.5f, 0.0f,  1.0f

  };
  glm::vec3 cubePositions[] = {
      glm::vec3(0.0f, 0.0f, 0.0f),    glm::vec3(2.0f, 5.0f, -15.0f),
      glm::vec3(-1.5f, -2.2f, -2.5f), glm::vec3(-3.8f, -2.0f, -12.3f),
      glm::vec3(2.4f, -0.4f, -3.5f),  glm::vec3(-1.7f, 3.0f, -7.5f),
      glm::vec3(1.3f, -2.0f, -2.5f),  glm::vec3(1.5f, 2.0f, -2.5f),
      glm::vec3(1.5f, 0.2f, -1.5f),   glm::vec3(-1.3f, 1.0f, -1.5f)};

  unsigned int VBO, VAO; // vertex buffer object(VBO) manages memory and
                         // vertices on gpu  vertex array object(VAO)....
  glGenVertexArrays(1, &VAO);
  glGenBuffers(1, &VBO); // generating 1 vertex buffer object

  glBindVertexArray(VAO);

  glBindBuffer(GL_ARRAY_BUFFER,
               VBO); // binding the buffer object with GL_ARRAY_BUFFER.
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

  // position attrib
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void *)0);
  glEnableVertexAttribArray(0);
  // texture coord attribute
  glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float),
                        (void *)(3 * sizeof(float)));
  glEnableVertexAttribArray(1);
  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glBindVertexArray(0);

  //----------------------------------

  unsigned int shaderProgram;
  shader *sobj = new shader("shaders/vertex.vert", "shaders/fragment.frag");
  sobj->shader_Compile(shaderProgram);
  glUseProgram(shaderProgram);
  createTexture(&texture, "textures/kitty.jpg", "textures/wall.jpg",
                shaderProgram);
  render(VAO, texture.tex1, texture.tex2, shaderProgram, mywindow.window);

  glDeleteProgram(shaderProgram);
  glDeleteBuffers(1, &VBO);
  glDeleteVertexArrays(1, &VAO);
  glDeleteTextures(1, &texture.tex1);
  glDeleteTextures(1, &texture.tex2);
  glfwTerminate();
  return 0;
}

// dont use now created problem fuck
// function which will be called each time the glfw window is resized
float angle = 0.0f;
void render(unsigned int VAO, unsigned int texture1, unsigned int texture2,
            unsigned int shaderProgram, GLFWwindow *window) {
  glEnable(GL_DEPTH_TEST);
  while (glfwWindowShouldClose(window) == false) {
    float currentFrame = (float)glfwGetTime();
    deltaTime = currentFrame - lastFrame;
    lastFrame = currentFrame;
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f); // this is the colour which is shown
                                          // when the colour buffer is cleared
    input(&cam1, deltaTime, window);

    glClear(GL_COLOR_BUFFER_BIT |
            GL_DEPTH_BUFFER_BIT); // this clears the colour buffer
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture1);

    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, texture2);
    glm::mat4 model = glm::mat4(1.0f);
    model = glm::rotate(model, (float)glfwGetTime() * glm::radians(angle),
                        glm::vec3(0.5f, 0.5f, 0.5f));
    viewMat(&cam1, shaderProgram);
    projectionMat(shaderProgram);

    int modelLoc = glGetUniformLocation(shaderProgram, "model");

    glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0, 36);
    glfwPollEvents(); // this processes events such as user input
    glfwSwapBuffers(
        window); // swaps the front buffer with the back buffer (image is
                 // rendered in the back buffer) this prevents flickering
  }
}
