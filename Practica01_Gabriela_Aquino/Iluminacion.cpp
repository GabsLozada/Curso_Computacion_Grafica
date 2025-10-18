// Aquino Lozada Gabriela
// Practica 8
// 319040012
// Fecha: 12 de octubre del 2025

// Std. Includes
#include <string>

// GLEW
#include <GL/glew.h>

// GLFW
#include <GLFW/glfw3.h>

// GL includes
#include "Shader.h"
#include "Camera.h"
#include "Model.h"

// GLM Mathemtics
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/constants.hpp> // Para usar pi

// Other Libs
#include "SOIL2/SOIL2.h"
#include "stb_image.h"

// Properties
const GLuint WIDTH = 800, HEIGHT = 600;
int SCREEN_WIDTH, SCREEN_HEIGHT;

// Function prototypes
void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mode);
void MouseCallback(GLFWwindow* window, double xPos, double yPos);
void DoMovement();

// Camera
Camera camera(glm::vec3(0.0f, 0.0f, 15.0f));
bool keys[1024];
GLfloat lastX = 400, lastY = 300;
bool firstMouse = true;

// Light attributes for semicircular path
float lightAngle1 = glm::pi<float>(); 
float lightAngle2 = 0.0f;             
const float lightPathRadius = 10.0f;  
const float angleStep = 0.02f;        

// Variable de estado para controlar si es de día (true) o de noche (false)
bool isDay = true; 

GLfloat deltaTime = 0.0f;
GLfloat lastFrame = 0.0f;
float rot = 0.0f;
bool activanim = false;

int main()
{
    // Init GLFW
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

    GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "Practica 8 Gabriela Aquino", nullptr, nullptr);

    if (nullptr == window)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return EXIT_FAILURE;
    }

    glfwMakeContextCurrent(window);
    glfwGetFramebufferSize(window, &SCREEN_WIDTH, &SCREEN_HEIGHT);
    glfwSetKeyCallback(window, KeyCallback);
    glfwSetCursorPosCallback(window, MouseCallback);

    glewExperimental = GL_TRUE;
    if (GLEW_OK != glewInit())
    {
        std::cout << "Failed to initialize GLEW" << std::endl;
        return EXIT_FAILURE;
    }

    glViewport(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
    glEnable(GL_DEPTH_TEST);

    // Setup and compile our shaders
    Shader shader("Shader/modelLoading.vs", "Shader/modelLoading.frag");
    Shader lampshader("Shader/lamp.vs", "Shader/lamp.frag");
    Shader lightingShader("Shader/lighting.vs", "Shader/lighting.frag");

    // Load models
    Model red_dog((char*)"Models/RedDog.obj");
    Model beach_ball((char*)"Models/13517_Beach_Ball_v2_L3.obj");
    Model cars((char*)"Models/LowPolyCars.obj");
    Model fire((char*)"Models/Fire Hydrant 2 - WEB.obj"); // Corregido el error de tipeo aquí
    Model trash((char*)"Models/trash.obj");
    Model bush((char*)"Models/bush.obj");
    Model stop((char*)"Models/StopSign.obj");
    Model banca((char*)"Models/Banca.obj");
    Model street((char*)"Models/street.obj");
    Model grass((char*)"Models/grass.obj");
    Model sun((char*)"Models/13913_Sun_v2_l3.obj");
    Model moon((char*)"Models/Moon.obj");

    glm::mat4 projection = glm::perspective(camera.GetZoom(), (float)SCREEN_WIDTH / (float)SCREEN_HEIGHT, 0.1f, 100.0f);

    float vertices[] = {
      -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
       0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
       0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
       0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
      -0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
      -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
      -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
       0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
       0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
       0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
      -0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
      -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
      -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
      -0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
      -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
      -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
      -0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
      -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
       0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
       0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
       0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
       0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
       0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
       0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
      -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
       0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
       0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
       0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
      -0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
      -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
      -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
       0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
       0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
       0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
      -0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
      -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f
    };

    GLuint VBO, VAO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    // Game loop
    while (!glfwWindowShouldClose(window))
    {
        GLfloat currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        glfwPollEvents();
        DoMovement();
        
        // Color de fondo estático
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        lightingShader.Use();

        // Calcula la posición actual de cada luz basado en su ángulo
        glm::vec3 currentLightPos1;
        currentLightPos1.x = lightPathRadius * cos(lightAngle1);
        currentLightPos1.y = lightPathRadius * sin(lightAngle1);
        currentLightPos1.z = 0.0f;

        glm::vec3 currentLightPos2;
        currentLightPos2.x = lightPathRadius * cos(lightAngle2);
        currentLightPos2.y = lightPathRadius * sin(lightAngle2);
        currentLightPos2.z = 0.0f;

        GLint lightPosLoc = glGetUniformLocation(lightingShader.Program, "light.position");
        GLint lightPosLoc2 = glGetUniformLocation(lightingShader.Program, "light2.position");
        GLint viewPosLoc = glGetUniformLocation(lightingShader.Program, "viewPos");

        glUniform3f(lightPosLoc, currentLightPos1.x, currentLightPos1.y, currentLightPos1.z);
        glUniform3f(lightPosLoc2, currentLightPos2.x, currentLightPos2.y, currentLightPos2.z);
        glUniform3f(viewPosLoc, camera.GetPosition().x, camera.GetPosition().y, camera.GetPosition().z);

        if (isDay)
        {
            
            // Sol Encendido
            glUniform3f(glGetUniformLocation(lightingShader.Program, "light.ambient"), 0.7f, 0.7f, 0.5f);  // Luz ambiental más cálida, ligeramente amarilla
            glUniform3f(glGetUniformLocation(lightingShader.Program, "light.diffuse"), 1.0f, 1.0f, 0.6f);  // Luz difusa cálida, con un toque amarillo suave
            glUniform3f(glGetUniformLocation(lightingShader.Program, "light.specular"), 1.0f, 1.0f, 0.8f); // Especular cálido con un toque de amarillo

            // Luna APAGADA
            glUniform3f(glGetUniformLocation(lightingShader.Program, "light2.ambient"), 0.0f, 0.0f, 0.0f);
            glUniform3f(glGetUniformLocation(lightingShader.Program, "light2.diffuse"), 0.0f, 0.0f, 0.0f);
            glUniform3f(glGetUniformLocation(lightingShader.Program, "light2.specular"), 0.0f, 0.0f, 0.0f);

        }
        else // Es de noche
        {
            // Sol APAGADO
            glUniform3f(glGetUniformLocation(lightingShader.Program, "light.ambient"), 0.0f, 0.0f, 0.0f);
            glUniform3f(glGetUniformLocation(lightingShader.Program, "light.diffuse"), 0.0f, 0.0f, 0.0f);
            glUniform3f(glGetUniformLocation(lightingShader.Program, "light.specular"), 0.0f, 0.0f, 0.0f);

            // Luna ENCENDIDA 
            glUniform3f(glGetUniformLocation(lightingShader.Program, "light2.ambient"), 0.0f, 0.0f, 0.5f);  // Luz ambiental azul fría
            glUniform3f(glGetUniformLocation(lightingShader.Program, "light2.diffuse"), 0.3f, 0.5f, 1.0f);  // Luz difusa azul más brillante
            glUniform3f(glGetUniformLocation(lightingShader.Program, "light2.specular"), 0.5f, 0.6f, 1.0f); // Luz especular azul brillante
        }

        // Set material properties
        glUniform3f(glGetUniformLocation(lightingShader.Program, "material.ambient"), 0.3f, 0.3f, 0.3f); // Material con tono neutro
        glUniform3f(glGetUniformLocation(lightingShader.Program, "material.diffuse"), 0.5f, 0.5f, 0.5f); // Material neutro o gris
        glUniform3f(glGetUniformLocation(lightingShader.Program, "material.specular"), 0.7f, 0.7f, 0.7f); // Especular neutro para evitar el amarillo
        glUniform1f(glGetUniformLocation(lightingShader.Program, "material.shininess"), 0.5f); // Brillo moderado


        glm::mat4 view = camera.GetViewMatrix();
        glUniformMatrix4fv(glGetUniformLocation(lightingShader.Program, "projection"), 1, GL_FALSE, glm::value_ptr(projection));
        glUniformMatrix4fv(glGetUniformLocation(lightingShader.Program, "view"), 1, GL_FALSE, glm::value_ptr(view));
        
        // Draw scene models
        // Draw street
        glm::mat4 model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f));
        model = glm::scale(model, glm::vec3(0.005f, 0.005f, 0.005f));
        glUniformMatrix4fv(glGetUniformLocation(lightingShader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
        street.Draw(lightingShader);

        // Draw grass
        model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(0.0f, -0.3f, 1.0f));
        model = glm::scale(model, glm::vec3(0.08f, 0.05f, 0.085f));
        model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
        glUniformMatrix4fv(glGetUniformLocation(lightingShader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
        grass.Draw(lightingShader);

        // Draw cars
        model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(1.0f, 0.0f, 0.0f));
        model = glm::scale(model, glm::vec3(0.75f, 0.75f, 0.75f));
        model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
        glUniformMatrix4fv(glGetUniformLocation(lightingShader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
        cars.Draw(lightingShader);

        // Draw fire hydrant
        model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(-3.0f, 0.2f, 0.0f));
        model = glm::scale(model, glm::vec3(0.1f, 0.1f, 0.1f));
        glUniformMatrix4fv(glGetUniformLocation(lightingShader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
        fire.Draw(lightingShader);

        // Draw trash
        model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(4.0f, 0.0f, 3.0f));
        model = glm::scale(model, glm::vec3(0.05f, 0.05f, 0.05f));
        glUniformMatrix4fv(glGetUniformLocation(lightingShader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
        trash.Draw(lightingShader);

        // Draw bush
        model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(-3.0f, 0.0f, -3.0f));
        model = glm::scale(model, glm::vec3(0.02f, 0.02f, 0.02f));
        glUniformMatrix4fv(glGetUniformLocation(lightingShader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
        bush.Draw(lightingShader);

        // Draw stop sign
        model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(-2.0f, 1.1f, 2.0f));
        model = glm::scale(model, glm::vec3(0.5f, 0.5f, 0.5f));
        glUniformMatrix4fv(glGetUniformLocation(lightingShader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
        stop.Draw(lightingShader);

        // Draw banca
        model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(4.0f, 0.0f, 1.0f));
        model = glm::scale(model, glm::vec3(0.1f, 0.1f, 0.1f));
        model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
        glUniformMatrix4fv(glGetUniformLocation(lightingShader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
        banca.Draw(lightingShader);
        
        // Draw the lamps
        lampshader.Use();
        glUniformMatrix4fv(glGetUniformLocation(lampshader.Program, "projection"), 1, GL_FALSE, glm::value_ptr(projection));
        glUniformMatrix4fv(glGetUniformLocation(lampshader.Program, "view"), 1, GL_FALSE, glm::value_ptr(view));

        // Dibuja el Sol (Luz 1)
        model = glm::mat4(1.0f);
        model = glm::translate(model, currentLightPos1);
        model = glm::scale(model, glm::vec3(0.001f)); // Ajusta esta escala si es necesario
        glUniformMatrix4fv(glGetUniformLocation(lampshader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
        sun.Draw(lampshader); 

        // Dibuja la Luna (Luz 2)
        model = glm::mat4(1.0f);
        model = glm::translate(model, currentLightPos2);
        model = glm::scale(model, glm::vec3(0.3f)); // Ajusta esta escala si es necesario
        glUniformMatrix4fv(glGetUniformLocation(lampshader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
        moon.Draw(lampshader); 

        

        glfwSwapBuffers(window);
    }

    /*glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);*/
    glfwTerminate();
    return 0;
}

void DoMovement()
{
    // Camera controls
    if (keys[GLFW_KEY_W] || keys[GLFW_KEY_UP]) camera.ProcessKeyboard(FORWARD, deltaTime);
    if (keys[GLFW_KEY_S] || keys[GLFW_KEY_DOWN]) camera.ProcessKeyboard(BACKWARD, deltaTime);
    if (keys[GLFW_KEY_A] || keys[GLFW_KEY_LEFT]) camera.ProcessKeyboard(LEFT, deltaTime);
    if (keys[GLFW_KEY_D] || keys[GLFW_KEY_RIGHT]) camera.ProcessKeyboard(RIGHT, deltaTime);

    // Light controls
    if (keys[GLFW_KEY_O]) lightAngle1 -= angleStep;
    if (keys[GLFW_KEY_L]) lightAngle1 += angleStep;
    if (keys[GLFW_KEY_I]) lightAngle2 -= angleStep;
    if (keys[GLFW_KEY_K]) lightAngle2 += angleStep;

    // Limit angles to semicircle (0 to PI)
    if(lightAngle1 < 0.0f) lightAngle1 = 0.0f;
    if(lightAngle1 > glm::pi<float>()) lightAngle1 = glm::pi<float>();
    if(lightAngle2 < 0.0f) lightAngle2 = 0.0f;
    if(lightAngle2 > glm::pi<float>()) lightAngle2 = glm::pi<float>();
}

void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
    if (GLFW_KEY_ESCAPE == key && GLFW_PRESS == action)
    {
        glfwSetWindowShouldClose(window, GL_TRUE);
    }
    
    if (key == GLFW_KEY_B && action == GLFW_PRESS)
    {
        isDay = !isDay; // Invierte el estado de día/noche
    }

    if (key >= 0 && key < 1024)
    {
        if (action == GLFW_PRESS) keys[key] = true;
        else if (action == GLFW_RELEASE) keys[key] = false;
    }
}

void MouseCallback(GLFWwindow* window, double xPos, double yPos)
{
    if (firstMouse)
    {
        lastX = xPos;
        lastY = yPos;
        firstMouse = false;
    }

    GLfloat xOffset = xPos - lastX;
    GLfloat yOffset = lastY - yPos;

    lastX = xPos;
    lastY = yPos;

    camera.ProcessMouseMovement(xOffset, yOffset);
}