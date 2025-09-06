//Aquino Lozada Gabriela
//Practica 4
//Num.Cuenta: 319040012
//Fecha de entrega: 05 de septiembre del 2025
#include<iostream>

//#define GLEW_STATIC

#include <GL/glew.h>

#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>



// Shaders
#include "Shader.h"

void Inputs(GLFWwindow* window);


const GLint WIDTH = 800, HEIGHT = 600;
//Manipulan el entorno sin necesidad de compilar el programa
float movX = 0.0f;
float movY = 0.0f;
float movZ = -5.0f;
float rot = 0.0f;
int main() {
	glfwInit();
	//Verificación de compatibilidad 
	// Set all the required options for GLFW
	/*glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);*/

	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

	GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "Practica 4 Gabriela Aquino", nullptr, nullptr);

	int screenWidth, screenHeight;

	glfwGetFramebufferSize(window, &screenWidth, &screenHeight);

	//Verificación de errores de creacion  ventana
	if (nullptr == window)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();

		return EXIT_FAILURE;
	}

	glfwMakeContextCurrent(window);
	glewExperimental = GL_TRUE;

	//Verificación de errores de inicialización de glew

	if (GLEW_OK != glewInit()) {
		std::cout << "Failed to initialise GLEW" << std::endl;
		return EXIT_FAILURE;
	}


	// Define las dimensiones del viewport
	glViewport(0, 0, screenWidth, screenHeight);


	// Setup OpenGL options
	glEnable(GL_DEPTH_TEST);

	// enable alpha support
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);


	// Build and compile our shader program
	Shader ourShader("Shader/core.vs", "Shader/core.frag");


	// Set up vertex data (and buffer(s)) and attribute pointers



	// use with Perspective Projection
	float vertices[] = {
		-0.5f, -0.5f, 0.5f, 1.0f, 0.0f,0.0f,//Front
		0.5f, -0.5f, 0.5f,  1.0f, 0.0f,0.0f,
		0.5f,  0.5f, 0.5f,  1.0f, 0.0f,0.0f,
		0.5f,  0.5f, 0.5f,  1.0f, 0.0f,0.0f,
		-0.5f,  0.5f, 0.5f, 1.0f, 0.0f,0.0f,
		-0.5f, -0.5f, 0.5f, 1.0f, 0.0f,0.0f,

		-0.5f, -0.5f,-0.5f, 0.0f, 1.0f,0.0f,//Back
		 0.5f, -0.5f,-0.5f, 0.0f, 1.0f,0.0f,
		 0.5f,  0.5f,-0.5f, 0.0f, 1.0f,0.0f,
		 0.5f,  0.5f,-0.5f, 0.0f, 1.0f,0.0f,
		-0.5f,  0.5f,-0.5f, 0.0f, 1.0f,0.0f,
		-0.5f, -0.5f,-0.5f, 0.0f, 1.0f,0.0f,

		 0.5f, -0.5f,  0.5f,  0.0f, 0.0f,1.0f,
		 0.5f, -0.5f, -0.5f,  0.0f, 0.0f,1.0f,
		 0.5f,  0.5f, -0.5f,  0.0f, 0.0f,1.0f,
		 0.5f,  0.5f, -0.5f,  0.0f, 0.0f,1.0f,
		 0.5f,  0.5f,  0.5f,  0.0f, 0.0f,1.0f,
		 0.5f,  -0.5f, 0.5f, 0.0f, 0.0f,1.0f,

		-0.5f,  0.5f,  0.5f,  1.0f, 1.0f,0.0f,
		-0.5f,  0.5f, -0.5f,  1.0f, 1.0f,0.0f,
		-0.5f, -0.5f, -0.5f,  1.0f, 1.0f,0.0f,
		-0.5f, -0.5f, -0.5f,  1.0f, 1.0f,0.0f,
		-0.5f, -0.5f,  0.5f,  1.0f, 1.0f,0.0f,
		-0.5f,  0.5f,  0.5f,  1.0f, 1.0f,0.0f,

		-0.5f, -0.5f, -0.5f, 0.0f, 1.0f,1.0f,
		0.5f, -0.5f, -0.5f,  0.0f, 1.0f,1.0f,
		0.5f, -0.5f,  0.5f,  0.0f, 1.0f,1.0f,
		0.5f, -0.5f,  0.5f,  0.0f, 1.0f,1.0f,
		-0.5f, -0.5f,  0.5f, 0.0f, 1.0f,1.0f,
		-0.5f, -0.5f, -0.5f, 0.0f, 1.0f,1.0f,

		-0.5f,  0.5f, -0.5f, 1.0f, 0.2f,0.5f,
		0.5f,  0.5f, -0.5f,  1.0f, 0.2f,0.5f,
		0.5f,  0.5f,  0.5f,  1.0f, 0.2f,0.5f,
		0.5f,  0.5f,  0.5f,  1.0f, 0.2f,0.5f,
		-0.5f,  0.5f,  0.5f, 1.0f, 0.2f,0.5f,
		-0.5f,  0.5f, -0.5f, 1.0f, 0.2f,0.5f,
	};




	GLuint VBO, VAO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	//glGenBuffers(1, &EBO);

	// Enlazar  Vertex Array Object
	glBindVertexArray(VAO);

	//2.- Copiamos nuestros arreglo de vertices en un buffer de vertices para que OpenGL lo use
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	// 3.Copiamos nuestro arreglo de indices en  un elemento del buffer para que OpenGL lo use
	/*glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);*/

	// 4. Despues colocamos las caracteristicas de los vertices

	//Posicion
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);

	//Color
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);

	glBindBuffer(GL_ARRAY_BUFFER, 0);


	glBindVertexArray(0); // Unbind VAO (it's always a good thing to unbind any buffer/array to prevent strange bugs)


	glm::mat4 projection = glm::mat4(1);

	projection = glm::perspective(glm::radians(45.0f), (GLfloat)screenWidth / (GLfloat)screenHeight, 0.1f, 100.0f);//FOV, Radio de aspecto,znear,zfar
	//projection = glm::ortho(0.0f, (GLfloat)screenWidth, 0.0f, (GLfloat)screenHeight, 0.1f, 1000.0f);//Izq,Der,Fondo,Alto,Cercania,Lejania
	while (!glfwWindowShouldClose(window))
	{

		Inputs(window);
		// Check if any events have been activiated (key pressed, mouse moved etc.) and call corresponding response functions
		glfwPollEvents();

		// Render
		// Clear the colorbuffer
		glClearColor(0.549f, 0.710f, 0.827f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


		// Draw our first triangle
		ourShader.Use();
		glm::mat4 model = glm::mat4(1);
		glm::mat4 view = glm::mat4(1);


		view = glm::translate(view, glm::vec3(movX, movY, movZ));
		view = glm::rotate(view, glm::radians(rot), glm::vec3(0.0f, 1.0f, 0.0f));

		GLint modelLoc = glGetUniformLocation(ourShader.Program, "model");
		GLint viewLoc = glGetUniformLocation(ourShader.Program, "view");
		GLint projecLoc = glGetUniformLocation(ourShader.Program, "projection");
		GLint uUseSolidColor = glGetUniformLocation(ourShader.Program, "useSolidColor");
		GLint uSolidColor = glGetUniformLocation(ourShader.Program, "solidColor");

		glUniformMatrix4fv(projecLoc, 1, GL_FALSE, glm::value_ptr(projection));
		glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));


		glBindVertexArray(VAO);

		// Cuerpo completo COLOR BLANCO
		glUniform1i(uUseSolidColor, GL_TRUE);
		glUniform3f(uSolidColor, 1.0f, 1.0f, 1.0f);

		model = glm::mat4(1.0f); // Crea una matriz identidad para el cuerpo
		model = glm::scale(model, glm::vec3(2.0f, 1.0f, 1.0f)); // Escala el cuerpo para hacerlo más ancho
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f)); // Posición inicial del cuerpo
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		// Cuerpo del lado negro enfrente COLOR NEGRO
		glUniform1i(uUseSolidColor, GL_TRUE);
		glUniform3f(uSolidColor, 0.357f, 0.247f, 0.161f);

		model = glm::mat4(1.0f); // Crea una matriz identidad para el cuerpo
		model = glm::scale(model, glm::vec3(0.4f, 1.0f, 0.1f)); // Escala el cuerpo para hacerlo más ancho
		model = glm::translate(model, glm::vec3(-1.8f, 0.0f, 5.1f)); // Posición inicial del cuerpo
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		// Cuerpo del lado blanco enfrente COLOR BLANCO
		glUniform1i(uUseSolidColor, GL_TRUE);
		glUniform3f(uSolidColor, 1.0f, 1.0f, 1.0f);

		model = glm::mat4(1.0f); // Crea una matriz identidad para el cuerpo
		model = glm::scale(model, glm::vec3(-1.3f, 1.0f, 0.1f)); // Escala el cuerpo para hacerlo más ancho
		model = glm::translate(model, glm::vec3(-0.1f, 0.0f, 5.1f)); // Posición inicial del cuerpo
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		// Cuerpo del lado cafe enfrente trasera
		glUniform1i(uUseSolidColor, GL_TRUE);
		glUniform3f(uSolidColor, 0.357f, 0.247f, 0.161f);

		model = glm::mat4(1.0f); // Crea una matriz identidad para el cuerpo
		model = glm::scale(model, glm::vec3(0.222f, 0.5f, 0.1f)); // Escala el cuerpo para hacerlo más ancho
		model = glm::translate(model, glm::vec3(4.0f, -0.5f, 5.15f)); // Posición inicial del cuerpo
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		// Cuerpo del lado blanco enfrente trasera
		glUniform1i(uUseSolidColor, GL_TRUE);
		glUniform3f(uSolidColor, 1.0f, 1.0f, 1.0f);

		model = glm::mat4(1.0f); // Crea una matriz identidad para el cuerpo
		model = glm::scale(model, glm::vec3(0.222f, 0.5f, 0.1f)); // Escala el cuerpo para hacerlo más ancho
		model = glm::translate(model, glm::vec3(4.0f, 0.5f, 5.15f)); // Posición inicial del cuerpo
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		// Cuerpo del lado negro arriba (aplastado) COLOR CAFE
		glUniform1i(uUseSolidColor, GL_TRUE);
		glUniform3f(uSolidColor, 0.357f, 0.247f, 0.161f);

		model = glm::mat4(1.0f); // Crea una matriz identidad para el lado negro
		model = glm::scale(model, glm::vec3(0.4f, 0.1f, 1.0f)); // Escala para hacerlo más bajo (y largo)
		model = glm::translate(model, glm::vec3(-1.8f, 5.6f, 0.0f)); // Mueve el rectángulo encima del cuerpo, ajustado en Y
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36); // Dibuja el rectángulo

		// Cuerpo del lado blanco arriba (aplastado) COLOR BLANCO
		glUniform1i(uUseSolidColor, GL_TRUE);
		glUniform3f(uSolidColor, 1.0f, 1.0f, 1.0f);

		model = glm::mat4(1.0f); // Crea una matriz identidad para el lado blanco
		model = glm::scale(model, glm::vec3(1.5f, 0.1f, 1.0f)); // Escala para hacerlo más bajo (y largo)
		model = glm::translate(model, glm::vec3(0.15f, 5.6f, 0.0)); // Mueve el rectángulo encima del cuerpo, ajustado en Y
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36); // Dibuja el rectángulo

		// Cuerpo del lado negro atrás COLOR NEGRO
		glUniform1i(uUseSolidColor, GL_TRUE);
		glUniform3f(uSolidColor, 0.357f, 0.247f, 0.161f);

		model = glm::mat4(1.0f); // Crea una matriz identidad para el cuerpo
		model = glm::scale(model, glm::vec3(0.4f, 1.0f, 0.1f)); // Escala el cuerpo para hacerlo más ancho
		model = glm::translate(model, glm::vec3(-1.8f, 0.0f, -5.5f)); // Posición inicial del cuerpo
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		// Cuerpo del lado blanco atrás COLOR BLANCO
		glUniform1i(uUseSolidColor, GL_TRUE);
		glUniform3f(uSolidColor, 1.0f, 1.0f, 1.0f);

		model = glm::mat4(1.0f); // Crea una matriz identidad para el cuerpo
		model = glm::scale(model, glm::vec3(-1.3f, 1.0f, 0.1f)); // Escala el cuerpo para hacerlo más ancho
		model = glm::translate(model, glm::vec3(-0.1f, 0.0f, -5.1f)); // Posición inicial del cuerpo
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		// Cuerpo atras cafe enfrente trasera
		glUniform1i(uUseSolidColor, GL_TRUE);
		glUniform3f(uSolidColor, 0.357f, 0.247f, 0.161f);

		model = glm::mat4(1.0f); // Crea una matriz identidad para el cuerpo
		model = glm::scale(model, glm::vec3(0.222f, 0.5f, 0.1f)); // Escala el cuerpo para hacerlo más ancho
		model = glm::translate(model, glm::vec3(4.0f, -0.5f, -5.15f)); // Posición inicial del cuerpo
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		// Cuerpo del lado blanco enfrente trasera
		glUniform1i(uUseSolidColor, GL_TRUE);
		glUniform3f(uSolidColor, 1.0f, 1.0f, 1.0f);

		model = glm::mat4(1.0f); // Crea una matriz identidad para el cuerpo
		model = glm::scale(model, glm::vec3(0.222f, 0.5f, 0.1f)); // Escala el cuerpo para hacerlo más ancho
		model = glm::translate(model, glm::vec3(4.0f, 0.5f, -5.15f)); // Posición inicial del cuerpo
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		// Cola mitad cafe
		glUniform1i(uUseSolidColor, GL_TRUE);
		glUniform3f(uSolidColor, 0.357f, 0.247f, 0.161f);

		model = glm::mat4(1.0f); // Nueva matriz para la cabeza
		model = glm::scale(model, glm::vec3(0.1f, 0.5f, 1.0f)); // Escala la cabeza un poco más pequeña
		model = glm::translate(model, glm::vec3(10.55f, -0.5f, 0.0f)); // Posiciona la cabeza justo encima del cuerpo
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		// Cola mitad blanca
		glUniform1i(uUseSolidColor, GL_TRUE);
		glUniform3f(uSolidColor, 1.0f, 1.0f, 1.0f);

		model = glm::mat4(1.0f); // Nueva matriz para la cabeza
		model = glm::scale(model, glm::vec3(0.1f, 0.5f, 1.0f)); // Escala la cabeza un poco más pequeña
		model = glm::translate(model, glm::vec3(10.55f, 0.5f, 0.0f)); // Posiciona la cabeza justo encima del cuerpo
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		// Cola
		glUniform1i(uUseSolidColor, GL_TRUE);
		glUniform3f(uSolidColor, 0.545f, 0.412f, 0.325f);

		model = glm::mat4(1.0f); // Nueva matriz para la cabeza
		model = glm::scale(model, glm::vec3(0.1f, 0.2f, 0.2f)); // Escala la cabeza un poco más pequeña
		model = glm::translate(model, glm::vec3(11.6f, -0.1f, 0.0f)); // Posiciona la cabeza justo encima del cuerpo
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		// Cabeza COLOR BLANCO
		glUniform1i(uUseSolidColor, GL_TRUE);
		glUniform3f(uSolidColor, 1.0f, 1.0f, 1.0f);
		

		model = glm::mat4(1.0f); // Nueva matriz para la cabeza
		model = glm::scale(model, glm::vec3(0.6f, 0.8f, 0.8f)); // Escala la cabeza un poco más pequeña
		model = glm::translate(model, glm::vec3(-2.1f, -0.1f, 0.0f)); // Posiciona la cabeza justo encima del cuerpo
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		// Cabeza lado arriba (aplastado) COLOR blanco
		glUniform1i(uUseSolidColor, GL_TRUE);
		glUniform3f(uSolidColor, 1.0f, 1.0f, 1.0f);

		model = glm::mat4(1.0f); // Crea una matriz identidad para el lado negro
		model = glm::scale(model, glm::vec3(0.6f, 0.1f, 0.7f)); // Escala para hacerlo más bajo (y largo)
		model = glm::translate(model, glm::vec3(-2.1f, 3.8f, 0.0f)); // Mueve el rectángulo encima del cuerpo, ajustado en Y
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36); // Dibuja el rectángulo

		// Ojo izq
		glUniform1i(uUseSolidColor, GL_TRUE);
		glUniform3f(uSolidColor, 0.357f, 0.247f, 0.161f);

		model = glm::mat4(1.0f); // Nueva matriz para la cabeza
		model = glm::scale(model, glm::vec3(0.1f, 0.4f, 0.25f)); // Escala la cabeza un poco más pequeña
		model = glm::translate(model, glm::vec3(-16.2f, 0.25f, -1.0f)); // Posiciona la cabeza justo encima del cuerpo
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		// Ojo dere.
		glUniform1i(uUseSolidColor, GL_TRUE);
		glUniform3f(uSolidColor, 0.357f, 0.247f, 0.161f);

		model = glm::mat4(1.0f); // Nueva matriz para la cabeza
		model = glm::scale(model, glm::vec3(0.1f, 0.4f, 0.25f)); // Escala la cabeza un poco más pequeña
		model = glm::translate(model, glm::vec3(-16.2f, 0.25f, 1.0f)); // Posiciona la cabeza justo encima del cuerpo
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		// Ojo izq NEGRO
		glUniform1i(uUseSolidColor, GL_TRUE);
		glUniform3f(uSolidColor, 0.0f, 0.0f, 0.0f);

		model = glm::mat4(1.0f); // Nueva matriz para la cabeza
		model = glm::scale(model, glm::vec3(0.01f, 0.125f, 0.1f)); // Escala la cabeza un poco más pequeña
		model = glm::translate(model, glm::vec3(-167.2f, 0.3f, -1.74f)); // Posiciona la cabeza justo encima del cuerpo
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		// Ojo izq BLANCO
		glUniform1i(uUseSolidColor, GL_TRUE);
		glUniform3f(uSolidColor, 1.0f, 1.0f, 1.0f);

		model = glm::mat4(1.0f); // Nueva matriz para la cabeza
		model = glm::scale(model, glm::vec3(0.01f, 0.1f, 0.1f)); // Escala la cabeza un poco más pequeña
		model = glm::translate(model, glm::vec3(-167.2f, 0.5f, -2.74f)); // Posiciona la cabeza justo encima del cuerpo
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		// Ojo izq NEGRO
		glUniform1i(uUseSolidColor, GL_TRUE);
		glUniform3f(uSolidColor, 0.0f, 0.0f, 0.0f);

		model = glm::mat4(1.0f); // Nueva matriz para la cabeza
		model = glm::scale(model, glm::vec3(0.01f, 0.1f, 0.1f)); // Escala la cabeza un poco más pequeña
		model = glm::translate(model, glm::vec3(-167.2f, -0.5f, -2.74f)); // Posiciona la cabeza justo encima del cuerpo
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		// Ojo derecho NEGRO
		glUniform1i(uUseSolidColor, GL_TRUE);
		glUniform3f(uSolidColor, 0.0f, 0.0f, 0.0f);

		model = glm::mat4(1.0f); // Nueva matriz para la cabeza
		model = glm::scale(model, glm::vec3(0.01f, 0.125f, 0.1f)); // Escala la cabeza un poco más pequeña
		model = glm::translate(model, glm::vec3(-167.2f, 0.3f, 1.74f)); // Posiciona la cabeza justo encima del cuerpo
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		// Ojo izq BLANCO
		glUniform1i(uUseSolidColor, GL_TRUE);
		glUniform3f(uSolidColor, 1.0f, 1.0f, 1.0f);

		model = glm::mat4(1.0f); // Nueva matriz para la cabeza
		model = glm::scale(model, glm::vec3(0.01f, 0.1f, 0.1f)); // Escala la cabeza un poco más pequeña
		model = glm::translate(model, glm::vec3(-167.2f, 0.5f, 2.74f)); // Posiciona la cabeza justo encima del cuerpo
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		// Ojo izq NEGRO
		glUniform1i(uUseSolidColor, GL_TRUE);
		glUniform3f(uSolidColor, 0.0f, 0.0f, 0.0f);

		model = glm::mat4(1.0f); // Nueva matriz para la cabeza
		model = glm::scale(model, glm::vec3(0.01f, 0.1f, 0.1f)); // Escala la cabeza un poco más pequeña
		model = glm::translate(model, glm::vec3(-167.2f, -0.5f, 2.74f)); // Posiciona la cabeza justo encima del cuerpo
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);


		// frente de la cara.
		glUniform1i(uUseSolidColor, GL_TRUE);
		glUniform3f(uSolidColor, 1.0f, 1.0f, 1.0f);

		model = glm::mat4(1.0f); // Nueva matriz para la cabeza
		model = glm::scale(model, glm::vec3(0.1f, 0.4f, 0.25f)); // Escala la cabeza un poco más pequeña
		model = glm::translate(model, glm::vec3(-16.2f, 0.25f, 0.0f)); // Posiciona la cabeza justo encima del cuerpo
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		//Restante de la cara
		glUniform1i(uUseSolidColor, GL_TRUE);
		glUniform3f(uSolidColor, 1.0f, 1.0f, 1.0f);

		model = glm::mat4(1.0f); // Nueva matriz para la cabeza
		model = glm::scale(model, glm::vec3(0.1f, 0.3f, 0.75f)); // Escala la cabeza un poco más pequeña
		model = glm::translate(model, glm::vec3(-16.2f, -0.85f, 0.0f)); // Posiciona la cabeza justo encima del cuerpo
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		//Boca
		glUniform1i(uUseSolidColor, GL_TRUE);
		glUniform3f(uSolidColor, 0.941f, 0.941f, 0.941f);

		model = glm::mat4(1.0f); // Nueva matriz para la cabeza
		model = glm::scale(model, glm::vec3(0.05f, 0.4f, 0.45f)); // Escala la cabeza un poco más pequeña
		model = glm::translate(model, glm::vec3(-33.9f, -0.55f, 0.0f)); // Posiciona la cabeza justo encima del cuerpo
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		//Nariz
		glUniform1i(uUseSolidColor, GL_TRUE);
		glUniform3f(uSolidColor, 0.545f, 0.412f, 0.325f);

		model = glm::mat4(1.0f); // Nueva matriz para la cabeza
		model = glm::scale(model, glm::vec3(0.15f, 0.1f, 0.2f)); // Escala la cabeza un poco más pequeña
		model = glm::translate(model, glm::vec3(-12.0f, -0.7f, 0.0f)); // Posiciona la cabeza justo encima del cuerpo
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		//Nariz derecho
		glUniform1i(uUseSolidColor, GL_TRUE);
		glUniform3f(uSolidColor, 1.0f, 1.0f, 1.0f);

		model = glm::mat4(1.0f); // Nueva matriz para la cabeza
		model = glm::scale(model, glm::vec3(0.1f, 0.3f, 0.12f)); // Escala la cabeza un poco más pequeña
		model = glm::translate(model, glm::vec3(-17.5f, -0.55f, 1.32f)); // Posiciona la cabeza justo encima del cuerpo
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		//Nariz izquierdo
		glUniform1i(uUseSolidColor, GL_TRUE);
		glUniform3f(uSolidColor, 1.0f, 1.0f, 1.0f);

		model = glm::mat4(1.0f); // Nueva matriz para la cabeza
		model = glm::scale(model, glm::vec3(0.1f, 0.3f, 0.12f)); // Escala la cabeza un poco más pequeña
		model = glm::translate(model, glm::vec3(-17.5f, -0.55f, -1.32f)); // Posiciona la cabeza justo encima del cuerpo
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		//Nariz izquierdo oscuro
		glUniform1i(uUseSolidColor, GL_TRUE);
		glUniform3f(uSolidColor, 0.357f, 0.247f, 0.161f);;

		model = glm::mat4(1.0f); // Nueva matriz para la cabeza
		model = glm::scale(model, glm::vec3(0.1f, 0.08f, 0.08f)); // Escala la cabeza un poco más pequeña
		model = glm::translate(model, glm::vec3(-18.1f, -2.0f, -0.8f)); // Posiciona la cabeza justo encima del cuerpo
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		//Nariz derecho oscuro
		glUniform1i(uUseSolidColor, GL_TRUE);
		glUniform3f(uSolidColor, 0.357f, 0.247f, 0.161f);;

		model = glm::mat4(1.0f); // Nueva matriz para la cabeza
		model = glm::scale(model, glm::vec3(0.1f, 0.08f, 0.08f)); // Escala la cabeza un poco más pequeña
		model = glm::translate(model, glm::vec3(-18.1f, -2.0f, 0.8f)); // Posiciona la cabeza justo encima del cuerpo
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		//Nariz en medio claro
		glUniform1i(uUseSolidColor, GL_TRUE);
		glUniform3f(uSolidColor, 0.545f, 0.412f, 0.325f);

		model = glm::mat4(1.0f); // Nueva matriz para la cabeza
		model = glm::scale(model, glm::vec3(0.1f, 0.17f, 0.05f)); // Escala la cabeza un poco más pequeña
		model = glm::translate(model, glm::vec3(-18.1f, -1.0f, 0.0f)); // Posiciona la cabeza justo encima del cuerpo
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		//Nariz blanco
		glUniform1i(uUseSolidColor, GL_TRUE);
		glUniform3f(uSolidColor, 1.0f, 1.0f, 1.0f);

		model = glm::mat4(1.0f); // Nueva matriz para la cabeza
		model = glm::scale(model, glm::vec3(0.08f, 0.1f, 0.45f)); // Escala la cabeza un poco más pequeña
		model = glm::translate(model, glm::vec3(-22.0f, -3.7f, 0.0f)); // Posiciona la cabeza justo encima del cuerpo
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		//Oreja der
		glUniform1i(uUseSolidColor, GL_TRUE);
		glUniform3f(uSolidColor, 0.357f, 0.247f, 0.161f);

		model = glm::mat4(1.0f); // Nueva matriz para la cabeza
		model = glm::scale(model, glm::vec3(0.1f, 0.17f, 0.2f)); // Escala la cabeza un poco más pequeña
		model = glm::translate(model, glm::vec3(-15.2f, 3.0f, 1.2f)); // Posiciona la cabeza justo encima del cuerpo
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		//Oreja der
		glUniform1i(uUseSolidColor, GL_TRUE);
		glUniform3f(uSolidColor, 0.357f, 0.247f, 0.161f);

		model = glm::mat4(1.0f); // Nueva matriz para la cabeza
		model = glm::scale(model, glm::vec3(0.1f, 0.17f, 0.2f)); // Escala la cabeza un poco más pequeña
		model = glm::translate(model, glm::vec3(-15.2f, 2.3f, 2.2f)); // Posiciona la cabeza justo encima del cuerpo
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		//Oreja der
		glUniform1i(uUseSolidColor, GL_TRUE);
		glUniform3f(uSolidColor, 0.357f, 0.247f, 0.161f);

		model = glm::mat4(1.0f); // Nueva matriz para la cabeza
		model = glm::scale(model, glm::vec3(0.1f, 0.13f, 0.1f)); // Escala la cabeza un poco más pequeña
		model = glm::translate(model, glm::vec3(-15.2f, 4.1f, 3.8f)); // Posiciona la cabeza justo encima del cuerpo
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		//Oreja izq
		glUniform1i(uUseSolidColor, GL_TRUE);
		glUniform3f(uSolidColor, 0.357f, 0.247f, 0.161f);

		model = glm::mat4(1.0f); // Nueva matriz para la cabeza
		model = glm::scale(model, glm::vec3(0.1f, 0.17f, 0.2f)); // Escala la cabeza un poco más pequeña
		model = glm::translate(model, glm::vec3(-15.2f, 3.0f, -1.2f)); // Posiciona la cabeza justo encima del cuerpo
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		//Oreja izq
		glUniform1i(uUseSolidColor, GL_TRUE);
		glUniform3f(uSolidColor, 0.357f, 0.247f, 0.161f);

		model = glm::mat4(1.0f); // Nueva matriz para la cabeza
		model = glm::scale(model, glm::vec3(0.1f, 0.17f, 0.2f)); // Escala la cabeza un poco más pequeña
		model = glm::translate(model, glm::vec3(-15.2f, 2.3f, -2.2f)); // Posiciona la cabeza justo encima del cuerpo
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		//Oreja izq
		glUniform1i(uUseSolidColor, GL_TRUE);
		glUniform3f(uSolidColor, 0.357f, 0.247f, 0.161f);

		model = glm::mat4(1.0f); // Nueva matriz para la cabeza
		model = glm::scale(model, glm::vec3(0.1f, 0.13f, 0.1f)); // Escala la cabeza un poco más pequeña
		model = glm::translate(model, glm::vec3(-15.2f, 4.1f, -3.8f)); // Posiciona la cabeza justo encima del cuerpo
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		//Primera pata relieve
		glUniform1i(uUseSolidColor, GL_TRUE);
		glUniform3f(uSolidColor, 0.627f, 0.471f, 0.353f);

		model = glm::mat4(1.0f);
		model = glm::scale(model, glm::vec3(0.1f, 0.4f, 0.2f));//Tamaño de la pata
		model = glm::translate(model, glm::vec3(-9.5f, -1.75f, -1.6f));//Posición de la pata
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		//Primera pata
		glUniform1i(uUseSolidColor, GL_TRUE);
		glUniform3f(uSolidColor, 0.357f, 0.247f, 0.161f);

		model = glm::mat4(1.0f);
		model = glm::scale(model, glm::vec3(0.2f, 0.4f, 0.3f));//Tamaño de la pata
		model = glm::translate(model, glm::vec3(-4.0f, -1.75f, -1.2f));//Posición de la pata
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		//Segunda pata relieve
		glUniform1i(uUseSolidColor, GL_TRUE);
		glUniform3f(uSolidColor, 0.627f, 0.471f, 0.353f);

		model = glm::mat4(1.0f);
		model = glm::scale(model, glm::vec3(0.1f, 0.4f, 0.2f));//Tamaño de la pata
		model = glm::translate(model, glm::vec3(6.5f, -1.75f, -1.6f));//Posición de la pata
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		//Segunda pata
		glUniform1i(uUseSolidColor, GL_TRUE);
		glUniform3f(uSolidColor, 0.357f, 0.247f, 0.161f);

		model = glm::mat4(1.0f);
		model = glm::scale(model, glm::vec3(0.2f, 0.4f, 0.3f));//Tamaño de la pata
		model = glm::translate(model, glm::vec3(4.0f, -1.75f, -1.2f));//Posición de la pata
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		//Tercera pata relieve
		glUniform1i(uUseSolidColor, GL_TRUE);
		glUniform3f(uSolidColor, 0.627f, 0.471f, 0.353f);

		model = glm::mat4(1.0f);
		model = glm::scale(model, glm::vec3(0.1f, 0.4f, 0.2f));//Tamaño de la pata
		model = glm::translate(model, glm::vec3(-9.5f, -1.75f, 1.6f));//Posición de la pata
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		//Tercera pata
		glUniform1i(uUseSolidColor, GL_TRUE);
		glUniform3f(uSolidColor, 0.357f, 0.247f, 0.161f);

		model = glm::mat4(1.0f);
		model = glm::scale(model, glm::vec3(0.2f, 0.4f, 0.3f));//Tamaño de la pata
		model = glm::translate(model, glm::vec3(-4.0f, -1.75f, 1.2f));//Posición de la pata
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		//Cuarta pata relieve
		glUniform1i(uUseSolidColor, GL_TRUE);
		glUniform3f(uSolidColor, 0.627f, 0.471f, 0.353f);

		model = glm::mat4(1.0f);
		model = glm::scale(model, glm::vec3(0.1f, 0.4f, 0.2f));//Tamaño de la pata
		model = glm::translate(model, glm::vec3(6.5f, -1.75f, 1.6f));//Posición de la pata
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		//Cuarta pata
		glUniform1i(uUseSolidColor, GL_TRUE);
		glUniform3f(uSolidColor, 0.357f, 0.247f, 0.161f);

		model = glm::mat4(1.0f);
		model = glm::scale(model, glm::vec3(0.2f, 0.4f, 0.3f));//Tamaño de la pata
		model = glm::translate(model, glm::vec3(4.0f, -1.75f, 1.2f));//Posición de la pata
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		glBindVertexArray(0);


		// Swap the screen buffers
		glfwSwapBuffers(window);

	}
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);


	glfwTerminate();
	return EXIT_SUCCESS;
}
//Vamos a poder ir modificando los parametros cuando el programa se este ejecutando
//EStos valores son los que mueven la vista
void Inputs(GLFWwindow* window) {
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)  //GLFW_RELEASE
		glfwSetWindowShouldClose(window, true);
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		movX += 0.005f;
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		movX -= 0.005f;
	if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
		movY += 0.005f;
	if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
		movY -= 0.005f;
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		movZ -= 0.005f;
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		movZ += 0.005f;
	if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
		rot += 0.04f;
	if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
		rot -= 0.04f;
}