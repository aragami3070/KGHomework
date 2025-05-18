#define GLM_ENABLE_EXPERIMENTAL
#include <glad\glad.h>

#include "Figure.h"

#include <GLFW\glfw3.h>
#include <glm\glm.hpp>
#include <glm\gtc\type_ptr.hpp>
#include <glm\gtx\transform.hpp>

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

//=============================================================================
// ���������� ����������
//=============================================================================
std::vector<model> models;
glm::mat4 T;       // �������, � ������� ������������� ��� ��������������
glm::vec3 S, P, u; // ���������� ����� ����������
// �����, � ������� ��������� ������ ����������
// ������� ����������� �����
float dist;         // ��������������� ���������� - ���������� ����� S � P
float fovy, aspect; // ���� ������ � ����������� ������ ���� ����������
float fovy_work, aspect_work; // ������� ���������� ��� fovy � aspect
float near_view, far_view;    // ���������� �� ���� ���������� � �� ���������
float n, f;                   // ������� ���������� ��� near_view � far_view
float l, r, t, b;             // ������� ��������������� ����������
// ��� �������� ��������� �����, ������,
// ������ � ������� ���������� � ���
enum projType { Ortho, Frustum, Perspective } pType; // ��� ���������� ��������
//=============================================================================
void initWorkPars() { // ������������� ������� ���������� ������
    n = near_view;
    f = far_view;
    fovy_work = fovy;
    aspect_work = aspect;
    float Vy = 2 * near_view * glm::tan(fovy / 2);
    float Vx = aspect * Vy;
    l = -Vx / 2;
    r = -l;
    b = -Vy / 2;
    t = -b;
    dist = glm::length(P - S);
    T = glm::lookAt(S, P, u);
}
void readFromFile(const char *fileName) { // ������ ����� �� ����� fileName
    // ���������� � �������� �����
    // ���������� � �������� �����
    std::ifstream in;
    in.open(fileName);
    if (in.is_open()) {
        // ���� ������� ������
        models.clear(); // ������� ��������� ������ ��������
        // ��������� ���������� ��� ������ �� �����
        glm::mat4 M = glm::mat4(1.f); // ������� ��� ��������� ��������� �������
        glm::mat4
            initM; // ������� ��� ���������� �������������� ������� �������
        std::vector<glm::mat4> transforms; // ���� ������ ��������������
        std::vector<path> figure;          // ������ ������� ���������� �������
        float thickness = 2; // ������� �� ��������� �� ��������� 2
        float r, g, b;       // ������������ �����
        r = g = b = 0;   // �������� ������������ ����� �� ��������� (������)
        std::string cmd; // ������ ��� ���������� ����� �������
        // ��������������� ������ � ������
        std::string str;       // ������, � ������� ��������� ������ �����
        std::getline(in, str); // ��������� �� �������� ����� ������ ������
        while (in) {           // ���� ��������� ������ ������� �������
            // ������������ ������
            if ((str.find_first_not_of(" \t\r\n") != std::string::npos) &&
                (str[0] != '#')) {
                // ����������� ������ �� ����� � �� �����������
                std::stringstream s(str); // ��������� ����� �� ������ str
                s >> cmd;
                if (cmd == "camera") { // ��������� ������
                    float x, y, z;
                    s >> x >> y >> z; // ���������� ����� ����������
                    S = glm::vec3(x, y, z);
                    s >> x >> y >>
                        z; // �����, � ������� ��������� ������ ����������
                    P = glm::vec3(x, y, z);
                    s >> x >> y >> z; // ������ ����������� �����
                    u = glm::vec3(x, y, z);
                }
                else if (cmd == "screen") { // ��������� ���� ����������
                    s >> fovy_work >> aspect >> near_view >>
                        far_view; // ��������� �������
                    fovy = glm::radians(
                        fovy_work); // ������� ���� �� �������� � ��������
                }
                else if (cmd == "color") { // ���� �����
                    s >> r >> g >> b;      // ��������� ��� ������������ �����
                }
                else if (cmd == "thickness") { // ������� �����
                    s >> thickness;            // ��������� �������� �������
                }
                else if (cmd == "path") {            // ����� �����
                    std::vector<glm::vec3> vertices; // ������ ����� �������
                    int N;                           // ���������� �����
                    s >> N;
                    std::string
                        str1;       // �������������� ������ ��� ������ �� �����
                    while (N > 0) { // ���� �� ��� ����� �������
                        std::getline(in, str1); // ��������� � str1 �� ��������
                                                // ����� ��������� ������
                        // ��� ��� ���� ����������, �� �� ����� ����� ���������
                        // �� �����
                        if ((str1.find_first_not_of(" \t\r\n") !=
                             std::string::npos) &&
                            (str1[0] != '#')) {
                            // ����������� ������ �� ����� � �� �����������
                            // ������ � ��� ���� ���������
                            float x, y, z; // ���������� ��� ����������
                            std::stringstream s1(str1); // ��� ���� ���������
                                                        // ����� �� ������ str1
                            s1 >> x >> y >> z;
                            vertices.push_back(
                                glm::vec3(x, y, z)); // ��������� ����� � ������
                            N--; // ��������� ������� ����� ��������� ����������
                                 // �����
                        }
                    }
                    // ��� ����� �������, ���������� ������� (path) � ������ ��
                    // � ������ figure
                    figure.push_back(
                        path(vertices, glm::vec3(r, g, b) / 255.f, thickness));
                }
                else if (cmd == "model") { // ������ �������� ������ �������
                    float mVcx, mVcy, mVcz, mVx, mVy,
                        mVz; // ��������� ������� model
                    s >> mVcx >> mVcy >> mVcz >> mVx >> mVy >>
                        mVz; // ��������� �������� ����������
                    float S = mVx / mVy < 1 ? 2.f / mVy : 2.f / mVx;
                    // ����� ����� �������� �� ������ ��������� � ������ �������
                    // ����� �������� �������� ���������������
                    initM = glm::scale(glm::vec3(S)) *
                            glm::translate(glm::vec3(-mVcx, -mVcy, -mVcz));
                    figure.clear();
                }
                else if (cmd == "figure") { // ������������ ����� ������
                    models.push_back(model(figure, M * initM));
                }
                else if (cmd == "translate") { // �������
                    float Tx, Ty, Tz;    // ��������� �������������� ��������
                    s >> Tx >> Ty >> Tz; // ��������� ���������
                    M = glm::translate(glm::vec3(Tx, Ty, Tz)) *
                        M; // ��������� ������� � ������ ��������������
                }
                else if (cmd == "scale") { // ���������������
                    float S;               // �������� ���������������
                    s >> S;                // ��������� ��������
                    M = glm::scale(glm::vec3(S)) *
                        M; // ��������� ��������������� � ������ ��������������
                }
                else if (cmd == "rotate") { // �������
                    float theta;            // ���� �������� � ��������
                    float nx, ny,
                        nz; // ���������� ������������� ������� ��� ��������
                    s >> theta >> nx >> ny >> nz; // ��������� ���������
                    // ��������� �������� � ������ ��������������
                    M = glm::rotate(glm::radians(theta),
                                    glm::vec3(nx, ny, nz)) *
                        M;
                }
                else if (cmd == "pushTransform") { // ���������� ������� � ����
                    transforms.push_back(M);       // ��������� ������� � ����
                }
                else if (cmd == "popTransform") { // ����� � ������� �� �����
                    M = transforms.back(); // �������� ������� ������� �����
                    transforms.pop_back(); // ���������� ������� �� �����
                }
            }
            // ��������� ��������� ������
            std::getline(in, str);
        }
        initWorkPars();
    }
}
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
    // ���������� ����������� ������� Resize
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    // ���������� ����������� ������� ������
    glfwSetKeyCallback(window, key_callback);

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

    //=====================================================================
    // ��������� ������
    //=====================================================================
    const char *vertexShaderSource =
        "#version 330 core\n"
        "layout (location = 0) in vec3 position;\n"
        "void main() {\n"
        " gl_Position = vec4(position.x, position.y, position.z, 1.0);\n"
        "}\0";
    //=====================================================================
    GLuint vertexShader; // ��������� ������ - ��������� ������
    vertexShader = glCreateShader(GL_VERTEX_SHADER); // ������� ������

    // ����������� �������� ��� � ���������� �������
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader); // ����������� ������

    GLint success; // ��������� ����������
    // ����������� ������ ���������� ������� � ���������� success
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (!success) {          // ���� ���������� ������ � �������
        GLchar infoLog[512]; // ������� ��������� ��� ��������� �� ������
        // ����������� ���������
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        // ������� ��������� �� ������ �� �����
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n"
                  << infoLog << std::endl;
    }

    //======================================================
    // ����������� ������
    //======================================================
    const char *fragmentShaderSource =
        "#version 330 core\n"
        "out vec4 color;\n"
        "void main() {\n"
        " color = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
        "}\n\0";
    //=======================================================
    GLuint fragmentShader; // ��������� ������ - ����������� ������
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER); // ������� ������
    // ����������� �������� ��� � ���������� �������
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader); // ����������� ������
    // ����������� ������ ���������� ������� � ��������� ����� ����������
    // success
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if (!success) {          // ���� ���������� ������ � �������
        GLchar infoLog[512]; // ������� ��������� ��� ��������� �� ������
        glGetShaderInfoLog(fragmentShader, 512, NULL,
                           infoLog); // ����������� ���������
        // ������� ��������� �� ������ �� �����
        std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n"
                  << infoLog << std::endl;
    }
    // ��������� ���������
    GLuint shaderProgram;              // ������������� ��������� ���������
    shaderProgram = glCreateProgram(); // ������� ����������� ������
    glAttachShader(shaderProgram,
                   vertexShader); // ������������ ��������� ������
    glAttachShader(shaderProgram, fragmentShader); // ����������� ������
    glLinkProgram(shaderProgram);                  // ���������� ���������
    // ����������� ������ ���������� ��������� ��������� � ���������� success
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if (!success) {          // ���� ���������� ������ � �������
        GLchar infoLog[512]; // ������� ��������� ��� ��������� �� ������
        glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
        // ������� ��������� �� ������ �� �����
        std::cout << "ERROR::SHADER::PROGRAM::LINK_FAILED\n"
                  << infoLog << std::endl;
    }
    // �������� ��������� ��������
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    readFromFile("Smirnov251HW7\\triangle.txt");
    // ���� ���� window �� ������ ���������
    while (!glfwWindowShouldClose(window)) {
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f); // ��������� ���� �������
        glClear(GL_COLOR_BUFFER_BIT);         // ������� ����� �������� ������
        // �������� ������������ ��������� ���������� ������� � ��������� ������
        // ��������� ��������� shaderProgram ������ ��������
        glUseProgram(shaderProgram);
        glm::mat4 proj; // ������� �������� � ������������ ���������
        switch (pType) {
        case Ortho: // ������������� ��������
            proj = glm::ortho(l, r, b, t, n, f);
            break;
        case Frustum: // ������������� �������� � Frustum
            proj = glm::frustum(l, r, b, t, n, f);
            break;
        case Perspective: // ������������� �������� � Perspective
            proj = glm::perspective(fovy_work, aspect_work, n, f);
            break;
        }
        // ������� �������� �� ������� ��������� � ������������ ���������
        glm::mat4 C = proj * T;
        for (int k = 0; k < models.size(); k++) { // ���� �� �������
            std::vector<path> figure =
                models[k].figure; // ������ ������� ��������� ������
            glm::mat4 TM =
                C * models[k].modelM; // ������� ������ �������������� ������
            for (int i = 0; i < figure.size(); i++) {
                glBindVertexArray(
                    figure[i].vertexArray); // ������ �������� ��������� ������
                                            // i-� �������
                glLineWidth(figure[i].thickness); // ������������� ������� �����
                glDrawArrays(GL_LINE_STRIP, 0,
                             figure[i].vertices.size()); // ��������� �������
                glBindVertexArray(0); // ��������� ��������� ������
            }
        }
        glfwSwapBuffers(window); // �������� ������� ������ �����������
        glfwPollEvents();        // ���������, ��������� �� �����-�� �������
    }
    glfwTerminate(); // ��������� ������ GLFW
    return 0;
}
