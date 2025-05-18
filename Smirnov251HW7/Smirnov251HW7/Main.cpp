#define GLM_ENABLE_EXPERIMENTAL
#include <glad\glad.h>

#include <GLFW\glfw3.h>
#include <glm\glm.hpp>
#include <glm\gtc\type_ptr.hpp>
#include <glm\gtx\transform.hpp>
#include <iostream>

// обработчик события Resize
void framebuffer_size_callback(GLFWwindow *window, int width, int height) {
    glViewport(0, 0, width, height);
}
// Обработчик нажатия клавиш
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
    glfwInit(); // Инициализация GLFW
    // Задается минимальная требуемая версия OpenGL.
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); // Номер до десятичной точки
    // Номер после десятичной точки
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    // Используем только средства указанной версии без совместимости с более
    // ранними
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    // Создаем окно
    GLFWwindow *window =
        glfwCreateWindow(800, 600, "Task 7. Smirnov 251", NULL, NULL);
    if (window == NULL) { // если ссылка на окно не создана
        std::cout << "Вызов glfwCreateWindow закончился неудачей." << std::endl;
        glfwTerminate(); // завершить работу GLFW
        return -1;       // завершить программу
    }
    glfwMakeContextCurrent(window); // делаем окно window активным (текущим)

    // Инициализация GLAD
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cout << "Не удалось загрузить GLAD" << std::endl;
        glfwTerminate(); // завершить работу GLFW
        return -1;       // завершить программу
    }

    // сообщаем диапазон координат в окне
    // (0, 0) - координаты левого нижнего угла, 800x600 - размеры окна в
    // пикселах
    glViewport(0, 0, 800, 600);
    glfwMakeContextCurrent(window); // делаем окно window активным (текущим)
    //
    // Назначение обработчика события Resize
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    // Назначение обработчика нажатия клавиш
    glfwSetKeyCallback(window, key_callback);

    glClearColor(0.2f, 0.3f, 0.3f, 1.0f); // назначаем цвет заливки
    glClear(GL_COLOR_BUFFER_BIT);         // очищаем буфер заданным цветом

    //=====================================================================
    // ВЕРШИННЫЙ ШЕЙДЕР
    //=====================================================================
    const char *vertexShaderSource =
        "#version 330 core\n"
        "layout (location = 0) in vec3 position;\n"
        "void main() {\n"
        " gl_Position = vec4(position.x, position.y, position.z, 1.0);\n"
        "}\0";
    //=====================================================================
    GLuint vertexShader; // шейдерный объект - вершинный шейдер
    vertexShader = glCreateShader(GL_VERTEX_SHADER); // создаем объект

    // привязываем исходный код к шейдерному объекту
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader); // компилируем шейдер

    GLint success; // результат компиляции
    // запрашиваем статус компиляции шейдера в переменную success
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (!success) {          // если компиляция прошла с ошибкой
        GLchar infoLog[512]; // объявим контейнер для сообщения об ошибке
        // запрашиваем сообщение
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        // выводим сообщение об ошибке на экран
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n"
                  << infoLog << std::endl;
    }

    //======================================================
    // ФРАГМЕНТНЫЙ ШЕЙДЕР
    //======================================================
    const char *fragmentShaderSource =
        "#version 330 core\n"
        "out vec4 color;\n"
        "void main() {\n"
        " color = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
        "}\n\0";
    //=======================================================
    GLuint fragmentShader; // шейдерный объект - фрагментный шейдер
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER); // создаем объект
    // привязываем исходный код к шейдерному объекту
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader); // компилируем шейдер
    // запрашиваем статус компиляции шейдера в описанную ранее переменную
    // success
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if (!success) {          // если компиляция прошла с ошибкой
        GLchar infoLog[512]; // объявим контейнер для сообщения об ошибке
        glGetShaderInfoLog(fragmentShader, 512, NULL,
                           infoLog); // запрашиваем сообщение
        // выводим сообщение об ошибке на экран
        std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n"
                  << infoLog << std::endl;
    }
    // Шейдерная программа
    GLuint shaderProgram;              // идентификатор шейдерной программы
    shaderProgram = glCreateProgram(); // создаем программный объект
    glAttachShader(shaderProgram,
                   vertexShader); // присоединяем вершинный шейдер
    glAttachShader(shaderProgram, fragmentShader); // фрагментный шейдер
    glLinkProgram(shaderProgram);                  // компоновка программы
    // запрашиваем статус компоновки шейдерной программы в переменную success
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if (!success) {          // если компоновка прошла с ошибкой
        GLchar infoLog[512]; // объявим контейнер для сообщения об ошибке
        glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
        // выводим сообщение об ошибке на экран
        std::cout << "ERROR::SHADER::PROGRAM::LINK_FAILED\n"
                  << infoLog << std::endl;
    }
    // удаление шейдерных объектов
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    //==============================================
    // НАБОР ИСХОДНЫХ ДАННЫХ ДЛЯ ОТРИСОВКИ
    //==============================================
    GLfloat vertices[] = {-0.5f, -0.5f, 0.0f, 0.5f, -0.5f,
                          0.0f,  0.0f,  0.5f, 0.0f};

    GLuint vertexArray; // объект вершинного массива
    // создаем вершинный массив, идентификатор которого присваиваем vertexArray
    glGenVertexArrays(1, &vertexArray);
    glBindVertexArray(vertexArray); // делаем активным вершинный массив

    GLuint vertexBuffer; // идентификатор буферного объекта
    // создаем буферный объект, идентификатор которого присваиваем vertexBuffer
    glGenBuffers(1, &vertexBuffer);
    // привязка vertexBuffer к GL_ARRAY_BUFFER
    glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
    // в буфер, привязанный к GL_ARRAY_BUFFER копируем содержимое vertices
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    // описание расположения параметра вершинного шейдера в вершинном буфере
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat),
                          (GLvoid *)0);
    glEnableVertexAttribArray(0);     // включение параметра 0 для шейдера
    glBindBuffer(GL_ARRAY_BUFFER, 0); // отвязка буферного объекта
    glBindVertexArray(0);             // отключение вершинного массива

    // описание расположения параметра вершинного шейдера в вершинном буфере
    // шейдерную программу shaderProgram делаем активной
    glUseProgram(shaderProgram);
    glBindVertexArray(vertexArray);    // делаем активным вершинный массив
    glLineWidth(6);                    // устанавливаем толщину линии - 6
    glDrawArrays(GL_LINE_STRIP, 0, 3); // отрисовка одного треугольника
    glBindVertexArray(0);              // отключаем вершинный массив

    // пока окно window не должно закрыться
    while (!glfwWindowShouldClose(window)) {
        glfwSwapBuffers(window); // поменять местами буферы изображения
        glfwPollEvents();        // проверить, произошли ли какие-то события
    }
    glfwTerminate(); // завершить работу GLFW
    return 0;
}
