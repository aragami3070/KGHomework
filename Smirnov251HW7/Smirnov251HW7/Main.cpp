#define GLM_ENABLE_EXPERIMENTAL
#include <Windows.h>
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
double lastX, lastY; // ��������� ������� �������
bool mouseBtnPressed = false;
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

// ������� �������� ������������ ���, �������� �������� n,
// ���������� ����� ����� P
glm::mat4 rotateP(float theta, glm::vec3 n, glm::vec3 P) {
    return glm::translate(P) * glm::rotate(theta, n) * glm::translate(-P);
}

// ���������� ��������� �������
void cursorPos_callback(GLFWwindow *window, double xpos, double ypos) {
    if (mouseBtnPressed) {
        // ������� �������� ������������ ����� P
        glm::mat4 M = rotateP(0.05, glm::vec3(lastY - ypos, lastX - xpos, 0),
                              glm::vec3(0, 0, -dist));
        glm::vec3 u_new =
            glm::mat3(M) * glm::vec3(0, 1, 0); // �������� ����������� �����
        glm::vec3 S_new =
            glm::vec3(M * glm::vec4(0, 0, 0, 1)); // �������� ������ ���������
        // ������� � ��� � ������� ������ ��������� � ����� �����, � �����������
        // ���������� - � ����� P
        T = glm::lookAt(S_new, glm::vec3(0, 0, -dist), u_new) * T;

        lastX = xpos;
        lastY = ypos;
    }
    else {
        // ��������� ������, �������� ��� ��������
        glm::vec3 n = glm::vec3(lastY - ypos, lastX - xpos, 0);
        // ������� ������� ��������
        glm::mat4 M = glm::rotate(glm::length(n) * 0.002f, n);
        // ������� ���� (0, 0, -1), �� ������� ������� �����������
        glm::vec3 P = M * glm::vec4(0, 0, -1, 1);
        // ��������� � ��������������� ������� � ����� ������� ���������
        // �����������
        T = glm::lookAt(glm::vec3(0), P, u) * T;
        lastX = xpos;
        lastY = ypos;
    }
}

// ���������� ������� ������� ��� ���������� �������
void cursorPosSave_callback(GLFWwindow *window, double xpos, double ypos) {
    lastX = xpos;
    lastY = ypos;
}

// ���������� ������� ���������
void scroll_callback(GLFWwindow *window, double xoffset, double yoffset) {
    dist += yoffset;
}
// ���������� ������� ������ ����
void mouse_button_callback(GLFWwindow *window, int button, int action,
                           int mods) {
    if (action == GLFW_PRESS && button == GLFW_MOUSE_BUTTON_LEFT) {
        mouseBtnPressed = true;
    }
    else if (action == GLFW_RELEASE && button == GLFW_MOUSE_BUTTON_LEFT) {
        mouseBtnPressed = false;
    }
}

// ���������� ������� ������
void key_callback(GLFWwindow *window, int key, int scancode, int action,
                  int mode) {
    if (action != GLFW_RELEASE) { // ���� ������� ������
        switch (key) {            // ����������� �������������� �������
        case GLFW_KEY_ESCAPE:     // ���� ������� - Escape
            initWorkPars();
            break;
        case GLFW_KEY_W:
            if (mode == GLFW_MOD_SHIFT) {
                T = glm::lookAt(glm::vec3(0, 0, -0.1), glm::vec3(0, 0, -1.1),
                                glm::vec3(0, 1, 0)) *
                    T;
            }
            else {
                T = glm::lookAt(glm::vec3(0, 0, -1), glm::vec3(0, 0, -2),
                                glm::vec3(0, 1, 0)) *
                    T;
            }
            break;
        case GLFW_KEY_S:
            if (mode == GLFW_MOD_SHIFT) {
                T = glm::lookAt(glm::vec3(0, 0, 0.1), glm::vec3(0, 0, -0.9),
                                glm::vec3(0, 1, 0)) *
                    T;
            }
            else {
                T = glm::lookAt(glm::vec3(0, 0, 1), glm::vec3(0, 0, 0),
                                glm::vec3(0, 1, 0)) *
                    T;
            }
            break;
        case GLFW_KEY_A:
            if (mode == GLFW_MOD_SHIFT) {
                T = glm::lookAt(glm::vec3(-0.1, 0, 0), glm::vec3(-0.1, 0, -1),
                                glm::vec3(0, 1, 0)) *
                    T;
            }
            else {
                T = glm::lookAt(glm::vec3(-1, 0, 0), glm::vec3(-1, 0, -1),
                                glm::vec3(0, 1, 0)) *
                    T;
            }
            break;
        case GLFW_KEY_D:
            if (mode == GLFW_MOD_SHIFT) {
                T = glm::lookAt(glm::vec3(0.1, 0, 0), glm::vec3(0.1, 0, -1),
                                glm::vec3(0, 1, 0)) *
                    T;
            }
            else {
                T = glm::lookAt(glm::vec3(1, 0, 0), glm::vec3(1, 0, -1),
                                glm::vec3(0, 1, 0)) *
                    T;
            }
            break;
        case GLFW_KEY_R: {
            glm::vec3 u_new = glm::mat3(glm::rotate(0.1f, glm::vec3(0, 0, 1))) *
                              glm::vec3(0, 1, 0);
            T = glm::lookAt(glm::vec3(0, 0, 0), glm::vec3(0, 0, -1), u_new) * T;
            break;
        }
        case GLFW_KEY_Y: {
            glm::vec3 u_new =
                glm::mat3(glm::rotate(-0.1f, glm::vec3(0, 0, 1))) *
                glm::vec3(0, 1, 0);
            T = glm::lookAt(glm::vec3(0, 0, 0), glm::vec3(0, 0, -1), u_new) * T;
            break;
        }
        case GLFW_KEY_T: {
            if (mode == GLFW_MOD_SHIFT) {
                // ������� �������� ������������ ����� P
                glm::mat4 M =
                    rotateP(0.1, glm::vec3(1, 0, 0), glm::vec3(0, 0, -dist));
                glm::vec3 u_new =
                    glm::mat3(M) *
                    glm::vec3(0, 1, 0); // �������� ����������� �����
                glm::vec3 S_new = glm::vec3(
                    M * glm::vec4(0, 0, 0, 1)); // �������� ������ ���������
                // ������� � ��� � ������� ������ ��������� � ����� �����, �
                // ����������� ���������� - � ����� P
                T = glm::lookAt(S_new, glm::vec3(0, 0, -dist), u_new) * T;
            }
            else {
                glm::mat4 M = glm::rotate(
                    0.1f,
                    glm::vec3(1, 0, 0)); // ������� �������� ������������ Ox
                glm::vec3 u_new =
                    glm::mat3(M) *
                    glm::vec3(0, 1, 0); // �������� ����������� �����
                // �������� �����, � ������� ������� �����������
                glm::vec3 P_new = glm::vec3(M * glm::vec4(0, 0, -1, 1));
                T = glm::lookAt(glm::vec3(0, 0, 0), P_new, u_new) * T;
            }
            break;
        }
        case GLFW_KEY_G: {
            if (mode == GLFW_MOD_SHIFT) {
                // ������� �������� ������������ ����� P
                glm::mat4 M =
                    rotateP(-0.1, glm::vec3(1, 0, 0), glm::vec3(0, 0, -dist));
                glm::vec3 u_new =
                    glm::mat3(M) *
                    glm::vec3(0, 1, 0); // �������� ����������� �����
                glm::vec3 S_new = glm::vec3(
                    M * glm::vec4(0, 0, 0, 1)); // �������� ������ ���������
                // ������� � ��� � ������� ������ ��������� � ����� �����, �
                // ����������� ���������� - � ����� P
                T = glm::lookAt(S_new, glm::vec3(0, 0, -dist), u_new) * T;
            }
            else {
                glm::mat4 M = glm::rotate(
                    -0.1f,
                    glm::vec3(1, 0, 0)); // ������� �������� ������������ Ox
                glm::vec3 u_new =
                    glm::mat3(M) *
                    glm::vec3(0, 1, 0); // �������� ����������� �����
                // �������� �����, � ������� ������� �����������
                glm::vec3 P_new = glm::vec3(M * glm::vec4(0, 0, -1, 1));
                T = glm::lookAt(glm::vec3(0, 0, 0), P_new, u_new) * T;
            }
            break;
        }
        case GLFW_KEY_F: {
            if (mode == GLFW_MOD_SHIFT) {
                // ������� �������� ������������ ����� P
                glm::mat4 M =
                    rotateP(-0.1, glm::vec3(0, 1, 0), glm::vec3(0, 0, -dist));
                glm::vec3 u_new =
                    glm::mat3(M) *
                    glm::vec3(0, 1, 0); // �������� ����������� �����
                glm::vec3 S_new = glm::vec3(
                    M * glm::vec4(0, 0, 0, 1)); // �������� ������ ���������
                // ������� � ��� � ������� ������ ��������� � ����� �����, �
                // ����������� ���������� - � ����� P
                T = glm::lookAt(S_new, glm::vec3(0, 0, -dist), u_new) * T;
            }
            else {
                glm::mat4 M = glm::rotate(
                    -0.1f,
                    glm::vec3(0, 1, 0)); // ������� �������� ������������ Ox
                glm::vec3 u_new =
                    glm::mat3(M) *
                    glm::vec3(0, 1, 0); // �������� ����������� �����
                // �������� �����, � ������� ������� �����������
                glm::vec3 P_new = glm::vec3(M * glm::vec4(0, 0, -1, 1));
                T = glm::lookAt(glm::vec3(0, 0, 0), P_new, u_new) * T;
            }
            break;
        }
        case GLFW_KEY_H: {
            if (mode == GLFW_MOD_SHIFT) {
                // ������� �������� ������������ ����� P
                glm::mat4 M =
                    rotateP(0.1, glm::vec3(0, 1, 0), glm::vec3(0, 0, -dist));
                glm::vec3 u_new =
                    glm::mat3(M) *
                    glm::vec3(0, 1, 0); // �������� ����������� �����
                glm::vec3 S_new = glm::vec3(
                    M * glm::vec4(0, 0, 0, 1)); // �������� ������ ���������
                // ������� � ��� � ������� ������ ��������� � ����� �����, �
                // ����������� ���������� - � ����� P
                T = glm::lookAt(S_new, glm::vec3(0, 0, -dist), u_new) * T;
            }
            else {
                glm::mat4 M = glm::rotate(
                    0.1f,
                    glm::vec3(0, 1, 0)); // ������� �������� ������������ Ox
                glm::vec3 u_new =
                    glm::mat3(M) *
                    glm::vec3(0, 1, 0); // �������� ����������� �����
                // �������� �����, � ������� ������� �����������
                glm::vec3 P_new = glm::vec3(M * glm::vec4(0, 0, -1, 1));
                T = glm::lookAt(glm::vec3(0, 0, 0), P_new, u_new) * T;
            }
            break;
        }
        case GLFW_KEY_I:
            if (mode == GLFW_MOD_SHIFT) {
                t -= 1;
            }
            else {
                t += 1;
            }
            break;
        case GLFW_KEY_J:
            if (mode == GLFW_MOD_SHIFT) {
                l += 1;
            }
            else {
                l -= 1;
            }
            break;
        case GLFW_KEY_K:
            if (mode == GLFW_MOD_SHIFT) {
                b -= 1;
            }
            else {
                b += 1;
            }
            break;
        case GLFW_KEY_L:
            if (mode == GLFW_MOD_SHIFT) {
                r -= 1;
            }
            else {
                r += 1;
            }
            break;
        case GLFW_KEY_U:
            if (mode == GLFW_MOD_SHIFT) {
                n = std::min(f - 0.1, n + 0.2);
            }
            else {
                n = std::max(0.1, n - 0.2);
            }
            break;
        case GLFW_KEY_O:
            if (mode == GLFW_MOD_SHIFT) {
                f += 0.2;
            }
            else {
                f = std::max(n + 0.1, f - 0.2);
            }
            break;
        case GLFW_KEY_B:
            if (mode == GLFW_MOD_SHIFT) {
                dist += 0.2;
            }
            else {
                dist = std::max(dist - 0.2, 0.1);
            }
            break;
        case GLFW_KEY_Z:
            if (mode == GLFW_MOD_SHIFT) {
                fovy_work = std::min(fovy_work + 0.2, 3.);
            }
            else {
                fovy_work = std::max(fovy_work - 0.2, 0.3);
            }
            break;
        case GLFW_KEY_X:
            if (mode == GLFW_MOD_SHIFT) {
                aspect_work += 0.05;
            }
            else {
                aspect_work = std::max(aspect_work - 0.05, 0.01);
            }
            break;
        case GLFW_KEY_1:
            pType = Ortho;
            break;
        case GLFW_KEY_2:
            pType = Frustum;
            break;
        case GLFW_KEY_3:
            pType = Perspective;
            break;
        case GLFW_KEY_F3: {
            OPENFILENAMEW openFileDialog = {
                0}; // ���� ���������� W-������ (Unicode)
            wchar_t fileName[MAX_PATH] = {0}; // wchar_t ������ char
            // ������������� ��������� �������
            ZeroMemory(&openFileDialog, sizeof(openFileDialog));
            openFileDialog.lStructSize = sizeof(openFileDialog);
            openFileDialog.hwndOwner = NULL;
            openFileDialog.lpstrFile = fileName;
            openFileDialog.lpstrFile[0] = '\0';
            openFileDialog.nMaxFile = sizeof(fileName);
            openFileDialog.lpstrFilter =
                L"Text files (*.txt)\0*.txt\0All files 2007\0*.*\0";
            openFileDialog.nFilterIndex = 1;
            openFileDialog.lpstrFileTitle = NULL;
            openFileDialog.nMaxFileTitle = 0;
            openFileDialog.lpstrInitialDir = NULL;
            openFileDialog.Flags =
                OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST | OFN_HIDEREADONLY;
            // ������ ��������� ������� � ��������� ����������
            if (GetOpenFileName(&openFileDialog)) {
                char narrowFileName[MAX_PATH];
                WideCharToMultiByte(CP_UTF8, 0, fileName, -1, narrowFileName,
                                    MAX_PATH, NULL, NULL);
                readFromFile(narrowFileName);
            }
            break;
        }
        case GLFW_KEY_F5:
            if (glfwGetInputMode(window, GLFW_CURSOR) == GLFW_CURSOR_DISABLED) {
                // ���������� ������
                glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
                // ����������� ���������� ��������� �������
                glfwSetCursorPosCallback(window, cursorPosSave_callback);
            }
            else {
                // ����������� ������
                glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
                // ���������� ���������� ��������� �������
                glfwSetCursorPosCallback(window, cursorPos_callback);
            }
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
    // ���������� ����������� ��������� �������
    glfwSetCursorPosCallback(window, cursorPosSave_callback);
    glfwSetScrollCallback(window, scroll_callback);
    glfwSetMouseButtonCallback(window, mouse_button_callback);

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
        "uniform mat4 clipView;\n"
        "void main() {\n"
        " gl_Position = clipView * vec4(position, 1.0);\n"
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
    const char *fragmentShaderSource = "#version 330 core\n"
                                       "out vec4 color;\n"
                                       "uniform vec3 pathColor;\n"
                                       "void main() {\n"
                                       " color = vec4(pathColor, 1.0f);\n"
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
    // ����������� � ��������� shaderProgram ������������ ���������� pathColor
    GLint pathColorLocation = glGetUniformLocation(shaderProgram, "pathColor");
    // ����������� � ��������� shaderProgram ������������ ���������� clipView
    GLint clipViewLocation = glGetUniformLocation(shaderProgram, "clipView");

    readFromFile("Smirnov251HW7\\Geometric.txt");
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
            // ��������� ��������� ������� TM � ���������� clipView ���������
            // ���������
            glUniformMatrix4fv(clipViewLocation, 1, GL_FALSE,
                               glm::value_ptr(TM));
            for (int i = 0; i < figure.size(); i++) {
                // ��������� ����� ����� � ���������� pathColor ���������
                // ���������
                glUniform3fv(pathColorLocation, 1,
                             glm::value_ptr(figure[i].color));
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
