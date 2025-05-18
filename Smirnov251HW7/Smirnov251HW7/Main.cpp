#define GLM_ENABLE_EXPERIMENTAL
#include <glad\glad.h>

#include <GLFW\glfw3.h>
#include <glm\glm.hpp>
#include <glm\gtc\type_ptr.hpp>
#include <glm\gtx\transform.hpp>
#include <iostream>

// обработчик событи€ Resize
void framebuffer_size_callback(GLFWwindow *window, int width, int height) {
    glViewport(0, 0, width, height);
}
// ќбработчик нажати€ клавиш
void key_callback(GLFWwindow *window, int key, int scancode, int action,
                  int mode) {
    if (action != GLFW_RELEASE) { // если клавиша нажата
        switch (key) {            // анализируем обрабатываемую клавишу
        case GLFW_KEY_ESCAPE:     // если клавиша - Escape
            // устанавливаем, что окно window должно быть закрыто
            glfwSetWindowShouldClose(window, GL_TRUE);
            break;
        default:
            break;
        }
    }
}



int main() {
    setlocale(LC_ALL, "rus");
    glfwInit(); // »нициализаци€ GLFW
    // «адаетс€ минимальна€ требуема€ верси€ OpenGL.
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); // Ќомер до дес€тичной точки
    // Ќомер после дес€тичной точки
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    // »спользуем только средства указанной версии без совместимости с более
    // ранними
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    // —оздаем окно
    GLFWwindow *window =
        glfwCreateWindow(800, 600, "Task 7. Smirnov 251", NULL, NULL);
    if (window == NULL) { // если ссылка на окно не создана
        std::cout << "¬ызов glfwCreateWindow закончилс€ неудачей." << std::endl;
        glfwTerminate(); // завершить работу GLFW
        return -1;       // завершить программу
    }
    glfwMakeContextCurrent(window); // делаем окно window активным (текущим)

    // »нициализаци€ GLAD
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cout << "Ќе удалось загрузить GLAD" << std::endl;
        glfwTerminate(); // завершить работу GLFW
        return -1;       // завершить программу
    }

    // сообщаем диапазон координат в окне
    // (0, 0) - координаты левого нижнего угла, 800x600 - размеры окна в
    // пикселах
    glViewport(0, 0, 800, 600);
    glfwMakeContextCurrent(window); // делаем окно window активным (текущим)
    //
    // Ќазначение обработчика событи€ Resize
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    // Ќазначение обработчика нажати€ клавиш
    glfwSetKeyCallback(window, key_callback);

    glClearColor(0.2f, 0.3f, 0.3f, 1.0f); // назначаем цвет заливки
    glClear(GL_COLOR_BUFFER_BIT);         // очищаем буфер заданным цветом

    // пока окно window не должно закрытьс€
    while (!glfwWindowShouldClose(window)) {
        glfwSwapBuffers(window); // помен€ть местами буферы изображени€
        glfwPollEvents();        // проверить, произошли ли какие-то событи€
    }
    glfwTerminate(); // завершить работу GLFW
    return 0;
}
