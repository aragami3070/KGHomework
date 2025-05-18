#define GLM_ENABLE_EXPERIMENTAL
#include <glad\glad.h>

#include <GLFW\glfw3.h>
#include <glm\glm.hpp>
#include <glm\gtc\type_ptr.hpp>
#include <glm\gtx\transform.hpp>
#include <iostream>

// ���������� ������� Resize
void framebuffer_size_callback(GLFWwindow *window, int width, int height) {
    glViewport(0, 0, width, height);
}
// ���������� ������� ������
void key_callback(GLFWwindow *window, int key, int scancode, int action,
                  int mode) {
    if (action != GLFW_RELEASE) { // ���� ������� ������
        switch (key) {            // ����������� �������������� �������
        case GLFW_KEY_ESCAPE:     // ���� ������� - Escape
            // �������������, ��� ���� window ������ ���� �������
            glfwSetWindowShouldClose(window, GL_TRUE);
            break;
        default:
            break;
        }
    }
}



int main() {
    setlocale(LC_ALL, "rus");
    glfwInit(); // ������������� GLFW
    // �������� ����������� ��������� ������ OpenGL.
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); // ����� �� ���������� �����
    // ����� ����� ���������� �����
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    // ���������� ������ �������� ��������� ������ ��� ������������� � �����
    // �������
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    // ������� ����
    GLFWwindow *window =
        glfwCreateWindow(800, 600, "Task 7. Smirnov 251", NULL, NULL);
    if (window == NULL) { // ���� ������ �� ���� �� �������
        std::cout << "����� glfwCreateWindow ���������� ��������." << std::endl;
        glfwTerminate(); // ��������� ������ GLFW
        return -1;       // ��������� ���������
    }
    glfwMakeContextCurrent(window); // ������ ���� window �������� (�������)

    // ������������� GLAD
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cout << "�� ������� ��������� GLAD" << std::endl;
        glfwTerminate(); // ��������� ������ GLFW
        return -1;       // ��������� ���������
    }

    // �������� �������� ��������� � ����
    // (0, 0) - ���������� ������ ������� ����, 800x600 - ������� ���� �
    // ��������
    glViewport(0, 0, 800, 600);
    glfwMakeContextCurrent(window); // ������ ���� window �������� (�������)
    //
    // ���������� ����������� ������� Resize
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    // ���������� ����������� ������� ������
    glfwSetKeyCallback(window, key_callback);

    glClearColor(0.2f, 0.3f, 0.3f, 1.0f); // ��������� ���� �������
    glClear(GL_COLOR_BUFFER_BIT);         // ������� ����� �������� ������

    // ���� ���� window �� ������ ���������
    while (!glfwWindowShouldClose(window)) {
        glfwSwapBuffers(window); // �������� ������� ������ �����������
        glfwPollEvents();        // ���������, ��������� �� �����-�� �������
    }
    glfwTerminate(); // ��������� ������ GLFW
    return 0;
}
