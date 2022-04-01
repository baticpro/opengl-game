#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "source/Renderer/ShaderManager.h"
#include "source/Assets/AssetsManager.h"

int g_WindowWidth = 640;
int g_WindowHeight = 480;

void glfwWindowSizeCallback(GLFWwindow *window, int width, int height) {
    g_WindowWidth = width;
    g_WindowHeight = height;

    glViewport(0, 0, width, height);
};

void glfwSetKeyCallback(GLFWwindow *window, int key, int scancode, int action, int mods) {
    if (key == GLFW_KEY_ESCAPE) {
        glfwSetWindowShouldClose(window, GL_TRUE);
    }
}

GLfloat points[] = {
        0.0f, 0.5f, 0.0f,
        0.5f, -0.5, 0.0f,
        -0.5f, -0.5f, 0.0f
};

GLfloat colors[] = {
        1.0f, 0.0f, 0.0f,
        0.0f, 1.0f, 0.0f,
        0.0f, 0.0f, 1.0f
};

const char *vertex_shader = "#version 410\n"
                            "layout(location = 0) in vec3 ver_pos;"
                            "layout(location = 1) in vec3 ver_color;"
                            "out vec3 color;"
                            "void main() {"
                            "  color = ver_color;"
                            "  gl_Position = vec4(ver_pos, 1.0);"
                            "}"
        ;

const char *fragment_shader = "#version 410\n"
                            "in vec3 color;"
                            "out vec4 frag_color;"
                            "void main() {"
                            "  frag_color = vec4(color, 1.0);"
                            "}"
        ;

int main(int arg, char** argv) {
    GLFWwindow *window;
    AssetsManager assetsManager(argv[0]);
    assetsManager.loadTexture("tiles-forest.png");

    /* Initialize the library */
    if (!glfwInit())
        return -1;

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(g_WindowWidth, g_WindowHeight, "Hello World", NULL, NULL);
    if (!window) {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    if (!gladLoadGL()) {
        std::cout << "cant load glad" << std::endl;
        return -1;
    }

    glfwSetWindowSizeCallback(window, glfwWindowSizeCallback);
    glfwSetKeyCallback(window, glfwSetKeyCallback);

    std::cout << "Renderer:" << glGetString(GL_RENDERER) << std::endl;
    std::cout << "OpenGL:" << glGetString(GL_VERSION) << std::endl;

    glClearColor(1, 1, 0.5, 0);

    auto shaderManager = assetsManager.loadShader("default");

    if(!shaderManager->isReady()) {
        std::cerr << "program didn't compile" << std::endl;
        return -1;
    }

    GLuint p_vb = 0;
    glGenBuffers(1, &p_vb);
    glBindBuffer(GL_ARRAY_BUFFER, p_vb);
    glBufferData(GL_ARRAY_BUFFER, sizeof(points), points, GL_STATIC_DRAW);

    GLuint c_vb = 0;
    glGenBuffers(1, &c_vb);
    glBindBuffer(GL_ARRAY_BUFFER, c_vb);
    glBufferData(GL_ARRAY_BUFFER, sizeof(colors), colors, GL_STATIC_DRAW);

    GLuint vao = 0;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, p_vb);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, nullptr);

    glEnableVertexAttribArray(1);
    glBindBuffer(GL_ARRAY_BUFFER, c_vb);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, nullptr);

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window)) {
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);

        shaderManager->use();
        glBindVertexArray(vao);
        glDrawArrays(GL_TRIANGLES, 0, 3);

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}