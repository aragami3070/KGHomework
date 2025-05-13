#define GLM_ENABLE_EXPERIMENTAL
#include <glad\glad.h>
#include <GLFW\glfw3.h>
#include <glm\glm.hpp>
#include <glm\gtx\transform.hpp>
#include <glm\gtc\type_ptr.hpp>

int main() {
    glfwInit();      // Инициализация GLFW
    glfwTerminate(); // завершить работу GLFW
    return 0;
}
