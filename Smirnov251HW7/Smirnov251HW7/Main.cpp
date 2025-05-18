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
// ГЛОБАЛЬНЫЕ ПЕРЕМЕННЫЕ
//=============================================================================
std::vector<model> models;
glm::mat4 T;       // матрица, в которой накапливаются все преобразования
glm::vec3 S, P, u; // координаты точки наблюдения
// точки, в которую направлен вектор наблюдения
// вектора направления вверх
float dist;         // вспомогательная переменная - расстояние между S и P
float fovy, aspect; // угол обзора и соотношение сторон окна наблюдения
float fovy_work, aspect_work; // рабочие переменные для fovy и aspect
float near_view, far_view;    // расстояния до окна наблюдения и до горизонта
float n, f;                   // рабочие переменные для near_view и far_view
float l, r, t, b;             // рабочие вспомогательные переменные
// для значений координат левой, правой,
// нижней и верхней координаты в СКН
enum projType { Ortho, Frustum, Perspective } pType; // тип трехмерной проекции
//=============================================================================
void initWorkPars() { // инициализация рабочих параметров камеры
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
void readFromFile(const char *fileName) { // чтение сцены из файла fileName
    // объявление и открытие файла
    // объявление и открытие файла
    std::ifstream in;
    in.open(fileName);
    if (in.is_open()) {
        // файл успешно открыт
        models.clear(); // очищаем имеющийся список рисунков
        // временные переменные для чтения из файла
        glm::mat4 M = glm::mat4(1.f); // матрица для получения модельной матрицы
        glm::mat4
            initM; // матрица для начального преобразования каждого рисунка
        std::vector<glm::mat4> transforms; // стек матриц преобразований
        std::vector<path> figure;          // список ломаных очередного рисунка
        float thickness = 2; // толщина со значением по умолчанию 2
        float r, g, b;       // составляющие цвета
        r = g = b = 0;   // значение составляющих цвета по умолчанию (черный)
        std::string cmd; // строка для считывания имени команды
        // непосредственно работа с файлом
        std::string str;       // строка, в которую считываем строки файла
        std::getline(in, str); // считываем из входного файла первую строку
        while (in) {           // если очередная строка считана успешно
            // обрабатываем строку
            if ((str.find_first_not_of(" \t\r\n") != std::string::npos) &&
                (str[0] != '#')) {
                // прочитанная строка не пуста и не комментарий
                std::stringstream s(str); // строковый поток из строки str
                s >> cmd;
                if (cmd == "camera") { // положение камеры
                    float x, y, z;
                    s >> x >> y >> z; // координаты точки наблюдения
                    S = glm::vec3(x, y, z);
                    s >> x >> y >>
                        z; // точка, в которую направлен вектор наблюдения
                    P = glm::vec3(x, y, z);
                    s >> x >> y >> z; // вектор направления вверх
                    u = glm::vec3(x, y, z);
                }
                else if (cmd == "screen") { // положение окна наблюдения
                    s >> fovy_work >> aspect >> near_view >>
                        far_view; // параметры команды
                    fovy = glm::radians(
                        fovy_work); // перевод угла из градусов в радианты
                }
                else if (cmd == "color") { // цвет линии
                    s >> r >> g >> b;      // считываем три составляющие цвета
                }
                else if (cmd == "thickness") { // толщина линии
                    s >> thickness;            // считываем значение толщины
                }
                else if (cmd == "path") {            // набор точек
                    std::vector<glm::vec3> vertices; // список точек ломаной
                    int N;                           // количество точек
                    s >> N;
                    std::string
                        str1;       // дополнительная строка для чтения из файла
                    while (N > 0) { // пока не все точки считали
                        std::getline(in, str1); // считываем в str1 из входного
                                                // файла очередную строку
                        // так как файл корректный, то на конец файла проверять
                        // не нужно
                        if ((str1.find_first_not_of(" \t\r\n") !=
                             std::string::npos) &&
                            (str1[0] != '#')) {
                            // прочитанная строка не пуста и не комментарий
                            // значит в ней пара координат
                            float x, y, z; // переменные для считывания
                            std::stringstream s1(str1); // еще один строковый
                                                        // поток из строки str1
                            s1 >> x >> y >> z;
                            vertices.push_back(
                                glm::vec3(x, y, z)); // добавляем точку в список
                            N--; // уменьшаем счетчик после успешного считывания
                                 // точки
                        }
                    }
                    // все точки считаны, генерируем ломаную (path) и кладем ее
                    // в список figure
                    figure.push_back(
                        path(vertices, glm::vec3(r, g, b) / 255.f, thickness));
                }
                else if (cmd == "model") { // начало описания нового рисунка
                    float mVcx, mVcy, mVcz, mVx, mVy,
                        mVz; // параметры команды model
                    s >> mVcx >> mVcy >> mVcz >> mVx >> mVy >>
                        mVz; // считываем значения переменных
                    float S = mVx / mVy < 1 ? 2.f / mVy : 2.f / mVx;
                    // сдвиг точки привязки из начала координат в нужную позицию
                    // после которого проводим масштабирование
                    initM = glm::scale(glm::vec3(S)) *
                            glm::translate(glm::vec3(-mVcx, -mVcy, -mVcz));
                    figure.clear();
                }
                else if (cmd == "figure") { // формирование новой модели
                    models.push_back(model(figure, M * initM));
                }
                else if (cmd == "translate") { // перенос
                    float Tx, Ty, Tz;    // параметры преобразования переноса
                    s >> Tx >> Ty >> Tz; // считываем параметры
                    M = glm::translate(glm::vec3(Tx, Ty, Tz)) *
                        M; // добавляем перенос к общему преобразованию
                }
                else if (cmd == "scale") { // масштабирование
                    float S;               // параметр масштабирования
                    s >> S;                // считываем параметр
                    M = glm::scale(glm::vec3(S)) *
                        M; // добавляем масштабирование к общему преобразованию
                }
                else if (cmd == "rotate") { // поворот
                    float theta;            // угол поворота в градусах
                    float nx, ny,
                        nz; // координаты направляющего вектора оси вращения
                    s >> theta >> nx >> ny >> nz; // считываем параметры
                    // добавляем вращение к общему преобразованию
                    M = glm::rotate(glm::radians(theta),
                                    glm::vec3(nx, ny, nz)) *
                        M;
                }
                else if (cmd == "pushTransform") { // сохранение матрицы в стек
                    transforms.push_back(M);       // сохраняем матрицу в стек
                }
                else if (cmd == "popTransform") { // откат к матрице из стека
                    M = transforms.back(); // получаем верхний элемент стека
                    transforms.pop_back(); // выкидываем матрицу из стека
                }
            }
            // считываем очередную строку
            std::getline(in, str);
        }
        initWorkPars();
    }
}
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
    // Назначение обработчика события Resize
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    // Назначение обработчика нажатия клавиш
    glfwSetKeyCallback(window, key_callback);

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

    readFromFile("Smirnov251HW7\\triangle.txt");
    // пока окно window не должно закрыться
    while (!glfwWindowShouldClose(window)) {
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f); // назначаем цвет заливки
        glClear(GL_COLOR_BUFFER_BIT);         // очищаем буфер заданным цветом
        // описание расположения параметра вершинного шейдера в вершинном буфере
        // шейдерную программу shaderProgram делаем активной
        glUseProgram(shaderProgram);
        glm::mat4 proj; // матрица перехода в пространство отсечения
        switch (pType) {
        case Ortho: // прямоугольная проекция
            proj = glm::ortho(l, r, b, t, n, f);
            break;
        case Frustum: // перспективная проекция с Frustum
            proj = glm::frustum(l, r, b, t, n, f);
            break;
        case Perspective: // перспективная проекция с Perspective
            proj = glm::perspective(fovy_work, aspect_work, n, f);
            break;
        }
        // матрица перехода от мировых координат в пространство отсечения
        glm::mat4 C = proj * T;
        for (int k = 0; k < models.size(); k++) { // цикл по моделям
            std::vector<path> figure =
                models[k].figure; // список ломаных очередной модели
            glm::mat4 TM =
                C * models[k].modelM; // матрица общего преобразования модели
            for (int i = 0; i < figure.size(); i++) {
                glBindVertexArray(
                    figure[i].vertexArray); // делаем активным вершинный массив
                                            // i-й ломаной
                glLineWidth(figure[i].thickness); // устанавливаем толщину линии
                glDrawArrays(GL_LINE_STRIP, 0,
                             figure[i].vertices.size()); // отрисовка ломаной
                glBindVertexArray(0); // отключаем вершинный массив
            }
        }
        glfwSwapBuffers(window); // поменять местами буферы изображения
        glfwPollEvents();        // проверить, произошли ли какие-то события
    }
    glfwTerminate(); // завершить работу GLFW
    return 0;
}
