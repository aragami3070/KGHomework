#pragma once
#include <glad\glad.h>
#include <glm\glm.hpp>
#include <vector>

class path {
  public:
    std::vector<glm::vec3> vertices; // последовательность точек
    glm::vec3 color;                 // цвет, разбитый на составляющие RGB
    float thickness;                 // толщина линии
    GLuint vertexArray;              // вершинный массив (объект OpenGL)
    path(std::vector<glm::vec3> verts, glm::vec3 col, float thickn) {
        vertices = verts;
        color = col;
        thickness = thickn;
        setupPath();
    }
  private:
    GLuint vertexBuffer; // вершинный буфер (объект OpenGL)
    void setupPath() {
        // создаем вершинный массив и вершинный буфер
        glGenVertexArrays(1, &vertexArray); // создаем вершинный массив
        glGenBuffers(1, &vertexBuffer);     // создаем вершинный буфер
        glBindVertexArray(vertexArray);     // делаем вершинный массив активным
        // связываем vertexBuffer c GL_ARRAY_BUFFER
        glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
        // копируем содержимое vertices в вершинный буфер vertexBuffer
        glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(glm::vec3),
                     &vertices[0], GL_STATIC_DRAW);
        // описание расположения параметра вершинного шейдера в вершинном буфере
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(glm::vec3),
                              (GLvoid *)0);
        glEnableVertexAttribArray(0);     // включение параметра 0 для шейдера
        glBindBuffer(GL_ARRAY_BUFFER, 0); // отвязка буферного объекта
        glBindVertexArray(0);             // отключение вершинного массива
    }
};

class model {
  public:
    std::vector<path> figure; // составляющие рисунка
    glm::mat4 modelM;         // модельная матрица
    model(std::vector<path> fig, glm::mat4 mat) {
        figure = fig;
        modelM = mat;
    }
};
