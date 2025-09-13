//Aquino Lozada Gabriela
//Practica 5
// Num.Cuenta: 319040012
//Fecha de entrega: 12 septiembre del 2025
#include<iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

// Shaders
#include "Shader.h"

void Inputs(GLFWwindow* window);

const GLint WIDTH = 1200, HEIGHT = 800;

//For Keyboard
float	movX = 0.0f,
movY = 0.0f,
movZ = -5.0f,
rot = 0.0f;

//For model
float	hombro = 0.0f,
codo = 0.0f,
muneca = 0.0f,
dedo1 = 0.0f,
dedo2 = 0.0f,
dedo3 = 0.0f,
dedo4 = 0.0f,
dedo5 = 0.0f,
dedo6 = 0.0f,
dedo7 = 0.0f,
dedo8 = 0.0f,
dedo9 = 0.0f,
dedo10 = 0.0f;

int main() {
    glfwInit();
    //Verificación de compatibilidad
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

    GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "Practica 5 Gabriela Aquino", nullptr, nullptr);
    int screenWidth, screenHeight;
    glfwGetFramebufferSize(window, &screenWidth, &screenHeight);

    if (nullptr == window) {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return EXIT_FAILURE;
    }

    glfwMakeContextCurrent(window);
    glewExperimental = GL_TRUE;

    if (GLEW_OK != glewInit()) {
        std::cout << "Failed to initialise GLEW" << std::endl;
        return EXIT_FAILURE;
    }

    glViewport(0, 0, screenWidth, screenHeight);

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    Shader ourShader("Shader/core.vs", "Shader/core.frag");

    float vertices[] = {
        -0.5f, -0.5f, 0.5f,
        0.5f, -0.5f, 0.5f,
        0.5f,  0.5f, 0.5f,
        0.5f,  0.5f, 0.5f,
        -0.5f,  0.5f, 0.5f,
        -0.5f, -0.5f, 0.5f,

        -0.5f, -0.5f,-0.5f,
         0.5f, -0.5f,-0.5f,
         0.5f,  0.5f,-0.5f,
         0.5f,  0.5f,-0.5f,
        -0.5f,  0.5f,-0.5f,
        -0.5f, -0.5f,-0.5f,

         0.5f, -0.5f,  0.5f,
         0.5f, -0.5f, -0.5f,
         0.5f,  0.5f, -0.5f,
         0.5f,  0.5f, -0.5f,
         0.5f,  0.5f,  0.5f,
         0.5f,  -0.5f, 0.5f,

        -0.5f,  0.5f,  0.5f,
        -0.5f,  0.5f, -0.5f,
        -0.5f, -0.5f, -0.5f,
        -0.5f, -0.5f, -0.5f,
        -0.5f, -0.5f,  0.5f,
        -0.5f,  0.5f,  0.5f,

        -0.5f, -0.5f, -0.5f,
        0.5f, -0.5f, -0.5f,
        0.5f, -0.5f,  0.5f,
        0.5f, -0.5f,  0.5f,
        -0.5f, -0.5f,  0.5f,
        -0.5f, -0.5f, -0.5f,

        -0.5f,  0.5f, -0.5f,
        0.5f,  0.5f, -0.5f,
        0.5f,  0.5f,  0.5f,
        0.5f,  0.5f,  0.5f,
        -0.5f,  0.5f,  0.5f,
        -0.5f,  0.5f, -0.5f,
    };

    GLuint VBO, VAO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    glm::mat4 projection = glm::mat4(1);
    projection = glm::perspective(glm::radians(45.0f), (GLfloat)screenWidth / (GLfloat)screenHeight, 0.1f, 100.0f);

    glm::vec3 color = glm::vec3(0.0f, 0.0f, 1.0f);

    while (!glfwWindowShouldClose(window)) {
        Inputs(window);  // Llamada a la función Inputs
        glfwPollEvents();

        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        ourShader.Use();
        glm::mat4 model = glm::mat4(1);
        glm::mat4 view = glm::mat4(1);
        glm::mat4 modelTemp = glm::mat4(1.0f); //Temp
        glm::mat4 modelTemp2 = glm::mat4(1.0f); //Temp
        glm::mat4 modelTemp3 = glm::mat4(1.0f); //Temp
        glm::mat4 modelTemp4 = glm::mat4(1.0f); //Temp
        glm::mat4 modelTemp5 = glm::mat4(1.0f); //Temp
        glm::mat4 modelTemp6 = glm::mat4(1.0f); //Temp

        view = glm::translate(view, glm::vec3(movX, movY, movZ));
        view = glm::rotate(view, glm::radians(rot), glm::vec3(0.0f, 1.0f, 0.0f));

        GLint modelLoc = glGetUniformLocation(ourShader.Program, "model");
        GLint viewLoc = glGetUniformLocation(ourShader.Program, "view");
        GLint projecLoc = glGetUniformLocation(ourShader.Program, "projection");
        GLint uniformColor = ourShader.uniformColor;

        glUniformMatrix4fv(projecLoc, 1, GL_FALSE, glm::value_ptr(projection));
        glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
        glUniform3fv(uniformColor, 1, glm::value_ptr(color));

        glBindVertexArray(VAO);

        // Model Hombro
        model = glm::rotate(model, glm::radians(hombro), glm::vec3(0.0f, 0.0f, 1.0f)); // Hombro
        modelTemp = model = glm::translate(model, glm::vec3(1.5f, 0.0f, 0.0f));
        model = glm::scale(model, glm::vec3(3.0f, 1.0f, 1.0f));
        color = glm::vec3(0.0f, 1.0f, 0.0f);
        glUniform3fv(uniformColor, 1, glm::value_ptr(color));
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
        glDrawArrays(GL_TRIANGLES, 0, 36); // A

        // Model Antebrazo
        model = glm::translate(modelTemp, glm::vec3(1.5f, 0.0f, 0.0f));
        model = glm::rotate(model, glm::radians(codo), glm::vec3(0.0f, 1.0f, 0.0f));
        modelTemp = model = glm::translate(model, glm::vec3(1.0f, 0.0f, 0.0f));
        model = glm::scale(model, glm::vec3(2.0f, 1.0f, 1.0f));
        color = glm::vec3(1.0f, 0.0f, 0.0f);
        glUniform3fv(uniformColor, 1, glm::value_ptr(color));
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
        glDrawArrays(GL_TRIANGLES, 0, 36); // B

        // Model Palma (Rotación sobre el eje X)
        model = glm::translate(modelTemp, glm::vec3(1.0f, 0.0f, 0.0f));
        model = glm::rotate(model, glm::radians(muneca), glm::vec3(1.0f, 0.0f, 0.0f)); // Gira sobre el eje X
        modelTemp6 = modelTemp5 = modelTemp4 = modelTemp3 = modelTemp2 = modelTemp = model = glm::translate(model, glm::vec3(0.25f, 0.0f, 0.0f));
        model = glm::scale(model, glm::vec3(0.5f, 1.0f, 1.0f));
        color = glm::vec3(1.0f, 1.0f, 1.0f);
        glUniform3fv(uniformColor, 1, glm::value_ptr(color));
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
        glDrawArrays(GL_TRIANGLES, 0, 36); // C

        //Model Dedo1 A
        model = glm::translate(modelTemp, glm::vec3(0.25f, 0.35f, 0.375f));
        model = glm::rotate(model, glm::radians(dedo1), glm::vec3(0.0f, 0.0f, 1.0f));
        modelTemp = model = glm::translate(model, glm::vec3(0.5f, 0.0f, 0.0f));
        model = glm::scale(model, glm::vec3(1.0f, 0.3f, 0.25f));
        color = glm::vec3(0.0f, 1.0f, 1.0f);  // Color cyan
        glUniform3fv(uniformColor, 1, glm::value_ptr(color));
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
        glDrawArrays(GL_TRIANGLES, 0, 36); // D

        //Model Dedo1 B
        model = glm::translate(modelTemp, glm::vec3(0.5f, 0.0f, 0.0f));
        model = glm::rotate(model, glm::radians(dedo2), glm::vec3(0.0f, 0.0f, 1.0f));
        model = glm::translate(model, glm::vec3(0.5f, 0.0f, 0.0f));
        model = glm::scale(model, glm::vec3(1.0f, 0.3f, 0.25f));
        color = glm::vec3(1.0f, 0.0f, 0.0f);  // Color red
        glUniform3fv(uniformColor, 1, glm::value_ptr(color));
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
        glDrawArrays(GL_TRIANGLES, 0, 36); // E

        //Model Dedo2 A
        model = glm::translate(modelTemp3, glm::vec3(0.25f, 0.35f, 0.050f));
        model = glm::rotate(model, glm::radians(dedo3), glm::vec3(0.0f, 0.0f, 1.0f));
        modelTemp3 = model = glm::translate(model, glm::vec3(0.5f, 0.0f, 0.0f));
        model = glm::scale(model, glm::vec3(1.0f, 0.3f, 0.25f));
        color = glm::vec3(0.0f, 1.0f, 0.0f);  // Color green
        glUniform3fv(uniformColor, 1, glm::value_ptr(color));
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
        glDrawArrays(GL_TRIANGLES, 0, 36); // F

        //Model Dedo2 B
        model = glm::translate(modelTemp3, glm::vec3(0.5f, 0.0f, 0.0f));
        model = glm::rotate(model, glm::radians(dedo4), glm::vec3(0.0f, 0.0f, 1.0f));
        model = glm::translate(model, glm::vec3(0.5f, 0.0f, 0.0f));
        model = glm::scale(model, glm::vec3(1.0f, 0.3f, 0.25f));
        color = glm::vec3(0.0f, 0.0f, 1.0f);  // Color blue
        glUniform3fv(uniformColor, 1, glm::value_ptr(color));
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
        glDrawArrays(GL_TRIANGLES, 0, 36); // G

        //Model Dedo3 A
        model = glm::translate(modelTemp4, glm::vec3(0.25f, 0.35f, -0.375f));
        model = glm::rotate(model, glm::radians(dedo5), glm::vec3(0.0f, 0.0f, 1.0f));
        modelTemp4 = model = glm::translate(model, glm::vec3(0.5f, 0.0f, 0.0f));
        model = glm::scale(model, glm::vec3(1.0f, 0.3f, 0.25f));
        color = glm::vec3(1.0f, 1.0f, 0.0f);  // Color yellow
        glUniform3fv(uniformColor, 1, glm::value_ptr(color));
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
        glDrawArrays(GL_TRIANGLES, 0, 36); // H

        //Model Dedo3 B
        model = glm::translate(modelTemp4, glm::vec3(0.5f, 0.0f, 0.0f));
        model = glm::rotate(model, glm::radians(dedo6), glm::vec3(0.0f, 0.0f, 1.0f));
        model = glm::translate(model, glm::vec3(0.5f, 0.0f, 0.0f));
        model = glm::scale(model, glm::vec3(1.0f, 0.3f, 0.25f));
        color = glm::vec3(0.5f, 0.5f, 0.5f);  // Color gray
        glUniform3fv(uniformColor, 1, glm::value_ptr(color));
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
        glDrawArrays(GL_TRIANGLES, 0, 36); // I

        //Model Dedo4 A
        model = glm::translate(modelTemp5, glm::vec3(0.25f, -0.35f, -0.375f));
        model = glm::rotate(model, glm::radians(dedo7), glm::vec3(0.0f, 0.0f, 1.0f));
        modelTemp5 = model = glm::translate(model, glm::vec3(0.5f, 0.0f, 0.0f));
        model = glm::scale(model, glm::vec3(1.0f, 0.3f, 0.25f));
        color = glm::vec3(1.0f, 0.647f, 0.0f);  // Color orange
        glUniform3fv(uniformColor, 1, glm::value_ptr(color));
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
        glDrawArrays(GL_TRIANGLES, 0, 36); // J

        //Model Dedo4 B
        model = glm::translate(modelTemp5, glm::vec3(0.5f, 0.0f, 0.0f));
        model = glm::rotate(model, glm::radians(dedo8), glm::vec3(0.0f, 0.0f, 1.0f));
        model = glm::translate(model, glm::vec3(0.5f, 0.0f, 0.0f));
        model = glm::scale(model, glm::vec3(1.0f, 0.3f, 0.25f));
        color = glm::vec3(0.5f, 0.0f, 0.5f);  // Color purple
        glUniform3fv(uniformColor, 1, glm::value_ptr(color));
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
        glDrawArrays(GL_TRIANGLES, 0, 36); // K

        //Model Dedo5 A
        model = glm::translate(modelTemp6, glm::vec3(0.25f, -0.35f, 0.375f));
        model = glm::rotate(model, glm::radians(dedo9), glm::vec3(0.0f, 0.0f, 1.0f));
        modelTemp6 = model = glm::translate(model, glm::vec3(0.5f, 0.0f, 0.0f));
        model = glm::scale(model, glm::vec3(1.0f, 0.3f, 0.25f));
        color = glm::vec3(0.0f, 1.0f, 1.0f);  // Color cyan
        glUniform3fv(uniformColor, 1, glm::value_ptr(color));
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
        glDrawArrays(GL_TRIANGLES, 0, 36); // L

        //Model Dedo5 B
        model = glm::translate(modelTemp6, glm::vec3(0.5f, 0.0f, 0.0f));
        model = glm::rotate(model, glm::radians(dedo10), glm::vec3(0.0f, 0.0f, 1.0f));
        model = glm::translate(model, glm::vec3(0.5f, 0.0f, 0.0f));
        model = glm::scale(model, glm::vec3(1.0f, 0.3f, 0.25f));
        color = glm::vec3(0.0f, 0.5f, 0.5f);  // Color teal
        glUniform3fv(uniformColor, 1, glm::value_ptr(color));
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
        glDrawArrays(GL_TRIANGLES, 0, 36); // M



        glBindVertexArray(0);

        // Swap the screen buffers
        glfwSwapBuffers(window);
    }

    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);

    glfwTerminate();
    return EXIT_SUCCESS;
}

void Inputs(GLFWwindow* window) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        movX += 0.008f;
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        movX -= 0.008f;
    if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
        movY += 0.008f;
    if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
        movY -= 0.008f;
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        movZ -= 0.008f;
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        movZ += 0.008f;
    if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
        rot += 0.18f;
    if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
        rot -= 0.18f;

    // Restricciones para el hombro (solo movimiento arriba-abajo)
    if (glfwGetKey(window, GLFW_KEY_R) == GLFW_PRESS)
        hombro = glm::clamp(hombro + 0.018f, -90.0f, 90.0f);
    if (glfwGetKey(window, GLFW_KEY_F) == GLFW_PRESS)
        hombro = glm::clamp(hombro - 0.018f, -90.0f, 90.0f);

    // Restricciones para el codo (solo 0° a 90°)
    if (glfwGetKey(window, GLFW_KEY_G) == GLFW_PRESS)
        codo = glm::clamp(codo + 0.018f, 0.0f, 90.0f);
    if (glfwGetKey(window, GLFW_KEY_T) == GLFW_PRESS)
        codo = glm::clamp(codo - 0.018f, 0.0f, 90.0f);

    // Restricciones para la muñeca (giro sobre el eje X, solo 45° de movimiento)
    if (glfwGetKey(window, GLFW_KEY_H) == GLFW_PRESS)
        muneca = glm::clamp(muneca + 0.018f, -45.0f, 45.0f);
    if (glfwGetKey(window, GLFW_KEY_Y) == GLFW_PRESS)
        muneca = glm::clamp(muneca - 0.018f, -45.0f, 45.0f);

    // Restricciones para los dedos 1-6 (solo hacia abajo, rango 0° a -90°)
   // Movimiento para el dedo 1 (impar)
    if (glfwGetKey(window, GLFW_KEY_J) == GLFW_PRESS)
        dedo1 = glm::clamp(dedo1 + 0.018f, -90.0f, 0.0f);  // Aumenta el ángulo hacia 0
    if (glfwGetKey(window, GLFW_KEY_U) == GLFW_PRESS)
        dedo1 = glm::clamp(dedo1 - 0.018f, -90.0f, 0.0f);  // Disminuye el ángulo hacia -90

    // Movimiento para el dedo 2 (par)
    if (glfwGetKey(window, GLFW_KEY_K) == GLFW_PRESS)
        dedo2 = glm::clamp(dedo2 + 0.018f, -90.0f, 0.0f);  // Aumenta el ángulo hacia 0
    if (glfwGetKey(window, GLFW_KEY_I) == GLFW_PRESS)
        dedo2 = glm::clamp(dedo2 - 0.018f, -90.0f, 0.0f);  // Disminuye el ángulo hacia -90

    // Movimiento para el dedo 3 (impar)
    if (glfwGetKey(window, GLFW_KEY_J) == GLFW_PRESS)
        dedo3 = glm::clamp(dedo3 + 0.018f, -90.0f, 0.0f);  // Aumenta el ángulo hacia 0
    if (glfwGetKey(window, GLFW_KEY_U) == GLFW_PRESS)
        dedo3 = glm::clamp(dedo3 - 0.018f, -90.0f, 0.0f);  // Disminuye el ángulo hacia -90

    // Movimiento para el dedo 4 (par)
    if (glfwGetKey(window, GLFW_KEY_K) == GLFW_PRESS)
        dedo4 = glm::clamp(dedo4 + 0.018f, -90.0f, 0.0f);  // Aumenta el ángulo hacia 0
    if (glfwGetKey(window, GLFW_KEY_I) == GLFW_PRESS)
        dedo4 = glm::clamp(dedo4 - 0.018f, -90.0f, 0.0f);  // Disminuye el ángulo hacia -90

    // Movimiento para el dedo 5 (impar)
    if (glfwGetKey(window, GLFW_KEY_J) == GLFW_PRESS)
        dedo5 = glm::clamp(dedo5 + 0.018f, -90.0f, 0.0f);  // Aumenta el ángulo hacia 0
    if (glfwGetKey(window, GLFW_KEY_U) == GLFW_PRESS)
        dedo5 = glm::clamp(dedo5 - 0.018f, -90.0f, 0.0f);  // Disminuye el ángulo hacia -90

    // Movimiento para el dedo 6 (par)
    if (glfwGetKey(window, GLFW_KEY_K) == GLFW_PRESS)
        dedo6 = glm::clamp(dedo6 + 0.018f, -90.0f, 0.0f);  // Aumenta el ángulo hacia 0
    if (glfwGetKey(window, GLFW_KEY_I) == GLFW_PRESS)
        dedo6 = glm::clamp(dedo6 - 0.018f, -90.0f, 0.0f);  // Disminuye el ángulo hacia -90

    // Movimiento para el dedo 7
    if (glfwGetKey(window, GLFW_KEY_L) == GLFW_PRESS)
        dedo7 = glm::clamp(dedo7 + 0.018f, 0.0f, 90.0f);  // Aumenta el ángulo hacia 90

    if (glfwGetKey(window, GLFW_KEY_O) == GLFW_PRESS)
        dedo7 = glm::clamp(dedo7 - 0.018f, 0.0f, 90.0f);  // Disminuye el ángulo hacia 0

    // Movimiento para el dedo 8
    if (glfwGetKey(window, GLFW_KEY_N) == GLFW_PRESS)
        dedo8 = glm::clamp(dedo8 + 0.018f, 0.0f, 90.0f);  // Aumenta el ángulo hacia 90

    if (glfwGetKey(window, GLFW_KEY_P) == GLFW_PRESS)
        dedo8 = glm::clamp(dedo8 - 0.018f, 0.0f, 90.0f);  // Disminuye el ángulo hacia 0

    // Movimiento para el dedo 9
    if (glfwGetKey(window, GLFW_KEY_L) == GLFW_PRESS)
        dedo9 = glm::clamp(dedo9 + 0.018f, 0.0f, 90.0f);  // Aumenta el ángulo hacia 90

    if (glfwGetKey(window, GLFW_KEY_O) == GLFW_PRESS)
        dedo9 = glm::clamp(dedo9 - 0.018f, 0.0f, 90.0f);  // Disminuye el ángulo hacia 0

    // Movimiento para el dedo 10
    if (glfwGetKey(window, GLFW_KEY_N) == GLFW_PRESS)
        dedo10 = glm::clamp(dedo10 + 0.018f, 0.0f, 90.0f);  // Aumenta el ángulo hacia 90

    if (glfwGetKey(window, GLFW_KEY_P) == GLFW_PRESS)
        dedo10 = glm::clamp(dedo10 - 0.018f, 0.0f, 90.0f);  // Disminuye el ángulo hacia 0

}