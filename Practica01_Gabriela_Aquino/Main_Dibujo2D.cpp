//Nombre: Aquino Lozada Gabriela
//Practica 2
//Fecha de entrega: 22 de agosto del 2025
//Numero de Cuenta: 319040012

#include<iostream>

//#define GLEW_STATIC

#include <GL/glew.h>

#include <GLFW/glfw3.h>

// Shaders
#include "Shader.h"

void resize(GLFWwindow* window, int width, int height);

const GLint WIDTH = 800, HEIGHT = 600;


int main() {
	glfwInit();
	//Verificaci�n de compatibilidad 
	/*glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_COMPAT_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);*/

	GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "Practica 2 Gabriela Aquino", NULL, NULL);
	glfwSetFramebufferSizeCallback(window, resize);

	//Verificaci�n de errores de creacion  ventana
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();

		return EXIT_FAILURE;
	}

	glfwMakeContextCurrent(window);
	glewExperimental = GL_TRUE;

	//Verificaci�n de errores de inicializaci�n de glew

	if (GLEW_OK != glewInit()) {
		std::cout << "Failed to initialise GLEW" << std::endl;
		return EXIT_FAILURE;
	}

	// Imprimimos informacin de OpenGL del sistema
	std::cout << "> Version: " << glGetString(GL_VERSION) << std::endl;
	std::cout << "> Vendor: " << glGetString(GL_VENDOR) << std::endl;
	std::cout << "> Renderer: " << glGetString(GL_RENDERER) << std::endl;
	std::cout << "> SL Version: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << std::endl;


	// Define las dimensiones del viewport
	//glViewport(0, 0, screenWidth, screenHeight);

	Shader ourShader("Shader/core.vs", "Shader/core.frag");

	// Set up vertex data (and buffer(s)) and attribute pointers
	float vertices[] = {
		//Fondo
		-0.297f, 0.370f, 0.0f, 0.439f, 0.663f, 1.000f,
		0.297f, 0.370f, 0.0f ,0.439f, 0.663f, 1.000f,
		0.297f, -0.222f, 0.0f, 0.439f, 0.663f, 1.000f,

		-0.297f, -0.222f, 0.0f, 0.439f, 0.663f, 1.000f,
		0.297f, -0.222f, 0.0f,0.439f, 0.663f, 1.000f,
		-0.297f, 0.370f, 0.0f,0.439f, 0.663f, 1.000f,

		-0.297f, -0.074f, 0.0f,0.678f, 0.812f, 1.000f,
		-0.297f, 0.222f, 0.0f,  0.678f, 0.812f, 1.000f,
		0.297f, 0.222f, 0.0f, 0.678f, 0.812f, 1.000f,

		-0.297f, -0.074f, 0.0f, 0.678f, 0.812f, 1.000f,
		0.297f, 0.222f, 0.0f, 0.678f, 0.812f, 1.000f,
		0.297f, -0.074f, 0.0f, 0.678f, 0.812f, 1.000f,

		//Cuerpo del Capibara
		0.186f, 0.038f, 0.0f, 0.690f, 0.412f, 0.310f,
		0.186f, -0.184f, 0.0f, 0.690f, 0.412f, 0.310f,
		-0.075f, 0.038f, 0.0f, 0.690f, 0.412f, 0.310f,

		-0.075f, 0.038f, 0.0f, 0.690f, 0.412f, 0.310f,//F2
		0.186f, -0.184f, 0.0f, 0.690f, 0.412f, 0.310f,//I1
		-0.075f, -0.184f, 0.0f, 0.690f, 0.412f, 0.310f,

		-0.149f, -0.184f, 0.0f, 0.690f, 0.412f, 0.310f,//J1
		-0.149f, -0.149f, 0.0f, 0.690f, 0.412f, 0.310f,
		-0.075f, -0.184f, 0.0f, 0.690f, 0.412f, 0.310f,//I2

		-0.150f, -0.148f, 0.0f, 0.690f, 0.412f, 0.310f,//E1
		-0.075f, -0.148f, 0.0f, 0.690f, 0.412f, 0.310f,//I2
		-0.075f, -0.185f, 0.0f, 0.690f, 0.412f, 0.310f,

		0.036f, 0.185f, 0.0f, 0.690f, 0.412f, 0.310f,
		-0.223f, 0.185f, 0.0f, 0.690f, 0.412f, 0.310f,
		-0.223f, 0.036f, 0.0f, 0.690f, 0.412f, 0.310f,

		0.036f, 0.185f, 0.0f, 0.690f, 0.412f, 0.310f,
		-0.223f, 0.036f, 0.0f, 0.690f, 0.412f, 0.310f,
		0.036f, 0.036f, 0.0f, 0.690f, 0.412f, 0.310f,

		0.073f, 0.222f, 0.0f, 0.690f, 0.412f, 0.310f,
		-0.00062f, 0.222f, 0.0f, 0.690f, 0.412f, 0.310f,
		0.073f, 0.150f, 0.0f, 0.690f, 0.412f, 0.310f,

		-0.00062f, 0.222f, 0.0f, 0.690f, 0.412f, 0.310f,
		0.073f, 0.150f, 0.0f, 0.690f, 0.412f, 0.310f,
		-0.00062f, 0.150f, 0.0f, 0.690f, 0.412f, 0.310f,

		0.036f, 0.075f, 0.0f, 0.690f, 0.412f, 0.310f,
		0.110f, 0.075f, 0.0f, 0.690f, 0.412f, 0.310f,
		0.110f, 0.036f, 0.0f, 0.690f, 0.412f, 0.310f,

		0.036f, 0.075f, 0.0f, 0.690f, 0.412f, 0.310f,
		0.110f, 0.036f, 0.0f, 0.690f, 0.412f, 0.310f,
		0.036f, 0.036f, 0.0f, 0.690f, 0.412f, 0.310f,

		// Silueta del capibara en negro
		-0.260f, 0.0368f, 0.0f,    0.0f, 0.0f, 0.0f,  // bottom right
		-0.260f, 0.186f, 0.0f,     0.0f, 0.0f, 0.0f,  // bottom left
		-0.223f, 0.185f, 0.0f,     0.0f, 0.0f, 0.0f,

		-0.223f,  0.0372f, 0.0f,   0.0f, 0.0f, 0.0f,
		-0.260f,  0.0368f, 0.0f,   0.0f, 0.0f, 0.0f,
		-0.223f,  0.185f, 0.0f,    0.0f, 0.0f, 0.0f,

		-0.223f,  0.0372f, 0.0f,   0.0f, 0.0f, 0.0f,
		-0.223f,  0.00034f, 0.0f,  0.0f, 0.0f, 0.0f,
		-0.112f,  0.0381f, 0.0f,   0.0f, 0.0f, 0.0f,

		-0.223f,  0.00034f, 0.0f,  0.0f, 0.0f, 0.0f,
		-0.112f,  0.0381f, 0.0f,   0.0f, 0.0f, 0.0f,
		-0.112f, -0.000609f, 0.0f, 0.0f, 0.0f, 0.0f,

		-0.112f, -0.000609f, 0.0f, 0.0f, 0.0f, 0.0f,
		-0.075f, -0.0012f, 0.0f,   0.0f, 0.0f, 0.0f,
		-0.112f, -0.109f, 0.0f,    0.0f, 0.0f, 0.0f,

		-0.075f, -0.0012f, 0.0f,   0.0f, 0.0f, 0.0f,
		-0.112f, -0.109f, 0.0f,    0.0f, 0.0f, 0.0f,
		-0.075f, -0.110f, 0.0f,    0.0f, 0.0f, 0.0f,

		-0.112f, -0.109f, 0.0f,    0.0f, 0.0f, 0.0f,
		-0.150f, -0.111f, 0.0f,    0.0f, 0.0f, 0.0f,
		-0.150f, -0.148f, 0.0f,    0.0f, 0.0f, 0.0f,

		-0.112f, -0.109f, 0.0f,    0.0f, 0.0f, 0.0f,
		-0.150f, -0.148f, 0.0f,    0.0f, 0.0f, 0.0f,
		-0.112f, -0.148f, 0.0f,    0.0f, 0.0f, 0.0f,

		-0.150f, -0.148f, 0.0f,    0.0f, 0.0f, 0.0f,
		-0.186f, -0.148f, 0.0f,    0.0f, 0.0f, 0.0f,
		-0.185f, -0.222f, 0.0f,    0.0f, 0.0f, 0.0f,

		-0.150f, -0.148f, 0.0f,    0.0f, 0.0f, 0.0f,
		-0.185f, -0.222f, 0.0f,    0.0f, 0.0f, 0.0f,
		-0.150f, -0.222f, 0.0f,    0.0f, 0.0f, 0.0f,

		-0.150f, -0.185f, 0.0f,    0.0f, 0.0f, 0.0f,
		-0.150f, -0.222f, 0.0f,    0.0f, 0.0f, 0.0f,
		0.186f,  -0.222f, 0.0f,    0.0f, 0.0f, 0.0f,

		-0.150f, -0.185f, 0.0f,    0.0f, 0.0f, 0.0f,
		0.186f,  -0.185f, 0.0f,    0.0f, 0.0f, 0.0f,
		0.186f,  -0.222f, 0.0f,    0.0f, 0.0f, 0.0f,

		0.186f,  -0.222f, 0.0f,    0.0f, 0.0f, 0.0f,
		0.220f,  -0.222f, 0.0f,    0.0f, 0.0f, 0.0f,
		0.220f,   0.036f, 0.0f,    0.0f, 0.0f, 0.0f,

		0.186f,  -0.222f, 0.0f,    0.0f, 0.0f, 0.0f,
		0.220f,   0.036f, 0.0f,    0.0f, 0.0f, 0.0f,
		0.186f,   0.036f, 0.0f,    0.0f, 0.0f, 0.0f,

		0.186f,   0.036f, 0.0f,    0.0f, 0.0f, 0.0f,
		0.186f,   0.074f, 0.0f,    0.0f, 0.0f, 0.0f,
		0.110f,   0.036f, 0.0f,    0.0f, 0.0f, 0.0f,

		0.186f,   0.074f, 0.0f,    0.0f, 0.0f, 0.0f,
		0.110f,   0.036f, 0.0f,    0.0f, 0.0f, 0.0f,
		0.110f,   0.074f, 0.0f,    0.0f, 0.0f, 0.0f,

		0.110f,   0.074f, 0.0f,    0.0f, 0.0f, 0.0f,
		0.110f,   0.111f, 0.0f,    0.0f, 0.0f, 0.0f,
		0.036f,   0.074f, 0.0f,    0.0f, 0.0f, 0.0f,

		0.110f,   0.111f, 0.0f,    0.0f, 0.0f, 0.0f,
		0.036f,   0.074f, 0.0f,    0.0f, 0.0f, 0.0f,
		0.036f,   0.111f, 0.0f,    0.0f, 0.0f, 0.0f,

		0.073f,   0.111f, 0.0f,    0.0f, 0.0f, 0.0f,
		0.036f,   0.111f, 0.0f,    0.0f, 0.0f, 0.0f,
		0.073f,   0.150f, 0.0f,    0.0f, 0.0f, 0.0f,

		0.073f,   0.150f, 0.0f,    0.0f, 0.0f, 0.0f,
		0.036f,   0.111f, 0.0f,    0.0f, 0.0f, 0.0f,
		0.036f,   0.150f, 0.0f,    0.0f, 0.0f, 0.0f,

		0.073f,   0.150f, 0.0f,    0.0f, 0.0f, 0.0f,
		0.111f,   0.150f, 0.0f,    0.0f, 0.0f, 0.0f,
		0.111f,   0.222f, 0.0f,    0.0f, 0.0f, 0.0f,

		0.073f,   0.150f, 0.0f,    0.0f, 0.0f, 0.0f,
		0.111f,   0.222f, 0.0f,    0.0f, 0.0f, 0.0f,
		0.073f,   0.222f, 0.0f,    0.0f, 0.0f, 0.0f,

		0.073f,   0.222f, 0.0f,    0.0f, 0.0f, 0.0f,
		0.073f,   0.260f, 0.0f,    0.0f, 0.0f, 0.0f,
		-0.00062f,0.222f, 0.0f,    0.0f, 0.0f, 0.0f,

		-0.00062f,0.222f, 0.0f,    0.0f, 0.0f, 0.0f,
		-0.00062f,0.260f, 0.0f,    0.0f, 0.0f, 0.0f,
		0.072f,   0.260f, 0.0f,    0.0f, 0.0f, 0.0f,

		-0.00062f,0.222f, 0.0f,    0.0f, 0.0f, 0.0f,
		-0.223f,  0.222f, 0.0f,    0.0f, 0.0f, 0.0f,
		-0.223f,  0.185f, 0.0f,    0.0f, 0.0f, 0.0f,

		-0.00062f,0.185f, 0.0f,    0.0f, 0.0f, 0.0f,
		-0.00062f,0.222f, 0.0f,    0.0f, 0.0f, 0.0f,
		-0.222f,  0.185f, 0.0f,    0.0f, 0.0f, 0.0f,

		-0.111f,  0.147f, 0.0f,    0.0f, 0.0f, 0.0f,
		-0.038f,  0.147f, 0.0f,    0.0f, 0.0f, 0.0f,
		-0.038f,  0.111f, 0.0f,    0.0f, 0.0f, 0.0f,

		-0.111f,  0.147f, 0.0f,    0.0f, 0.0f, 0.0f,
		-0.111f,  0.111f, 0.0f,    0.0f, 0.0f, 0.0f,
		-0.038f,  0.111f, 0.0f,    0.0f, 0.0f, 0.0f,


		//Sombra del capibara marron rojo
			0.073f, 0.222f, 0.0f, 0.541f, 0.251f, 0.157f,
			0.036f, 0.222f, 0.0f, 0.541f, 0.251f, 0.157f,
			0.036f, 0.185f, 0.0f, 0.541f, 0.251f, 0.157f,

			0.036f, 0.185f, 0.0f, 0.541f, 0.251f, 0.157f,
			0.073f, 0.185f, 0.0f, 0.541f, 0.251f, 0.157f,
			0.073f, 0.222f, 0.0f, 0.541f, 0.251f, 0.157f,

			-0.112f, 0.038f, 0.0f, 0.541f, 0.251f, 0.157f,
			-0.112f, -0.0006f, 0.0f, 0.541f, 0.251f, 0.157f,
			-0.075f, -0.0012f, 0.0f, 0.541f, 0.251f, 0.157f,

			-0.075f, -0.0012f, 0.0f, 0.541f, 0.251f, 0.157f,
			-0.112f, 0.038f, 0.0f, 0.541f, 0.251f, 0.157f,
			-0.075f, 0.038f, 0.0f, 0.541f, 0.251f, 0.157f,

			-0.075f, -0.0012f, 0.0f, 0.541f, 0.251f, 0.157f,
			-0.038f, -0.0012f, 0.0f, 0.541f, 0.251f, 0.157f,
			-0.038f, -0.110f, 0.0f, 0.541f, 0.251f, 0.157f,

			-0.075, -0.0012f, 0.0f, 0.541f, 0.251f, 0.157f,
			-0.075, -0.110f, 0.0f, 0.541f, 0.251f, 0.157f,
			-0.038f, -0.110f, 0.0f, 0.541f, 0.251f, 0.157f,

			-0.112f, -0.110f, 0.0f, 0.541f, 0.251f, 0.157f,
			-0.075f, -0.110f, 0.0f, 0.541f, 0.251f, 0.157f,
			-0.112f, -0.148f, 0.0f, 0.541f, 0.251f, 0.157f,

			-0.075f, -0.110f, 0.0f, 0.541f, 0.251f, 0.157f,
			-0.112f, -0.148f, 0.0f, 0.541f, 0.251f, 0.157f,
			-0.075f, -0.148f, 0.0f, 0.541f, 0.251f, 0.157f,

			0.110f, -0.148f, 0.0f, 0.541f, 0.251f, 0.157f,
			0.110f, -0.185f, 0.0f, 0.541f, 0.251f, 0.157f,
			0.185f, -0.185f, 0.0f, 0.541f, 0.251f, 0.157f,

			0.185f, -0.185f, 0.0f, 0.541f, 0.251f, 0.157f,
			0.185f, -0.148f, 0.0f, 0.541f, 0.251f, 0.157f,
			0.110f, -0.148f, 0.0f, 0.541f, 0.251f, 0.157f,

			0.185f, -0.148f, 0.0f, 0.541f, 0.251f, 0.157f,
			0.148f, -0.148f, 0.0f, 0.541f, 0.251f, 0.157f,
			0.148f, -0.111f, 0.0f, 0.541f, 0.251f, 0.157f,

			0.185f, -0.148f, 0.0f, 0.541f, 0.251f, 0.157f,
			0.148f, -0.111f, 0.0f, 0.541f, 0.251f, 0.157f,
			0.185f, -0.111f, 0.0f, 0.541f, 0.251f, 0.157f,

			//Nariz dle capabibara
				-0.223f, 0.185f, 0.0f, 0.525f, 0.384f, 0.290f,
				-0.149f, 0.185f, 0.0f, 0.525f, 0.384f, 0.290f,
				-0.149f, 0.149f, 0.0f, 0.525f, 0.384f, 0.290f,

				-0.223f, 0.185f, 0.0f, 0.525f, 0.384f, 0.290f,
				-0.149f, 0.149f, 0.0f, 0.525f, 0.384f, 0.290f,
				-0.223f, 0.149f, 0.0f, 0.525f, 0.384f, 0.290f,

				-0.223f, 0.149f, 0.0f, 0.525f, 0.384f, 0.290f,
				-0.223f, 0.111f, 0.0f, 0.525f, 0.384f, 0.290f,
				-0.186f, 0.111f, 0.0f, 0.525f, 0.384f, 0.290f,

				-0.223f, 0.149f, 0.0f, 0.525f, 0.384f, 0.290f,
				-0.186f, 0.149f, 0.0f, 0.525f, 0.384f, 0.290f,
				-0.186f, 0.111f, 0.0f, 0.525f, 0.384f, 0.290f,




	};
	unsigned int indices[] = {  // note that we start from 0!
		3,2,1,// second Triangle
		0,1,3,

	};



	GLuint VBO, VAO, EBO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	// Enlazar  Vertex Array Object
	glBindVertexArray(VAO);

	//2.- Copiamos nuestros arreglo de vertices en un buffer de vertices para que OpenGL lo use
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	// 3.Copiamos nuestro arreglo de indices en  un elemento del buffer para que OpenGL lo use
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// 4. Despues colocamos las caracteristicas de los vertices

	//Posicion
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);

	//Color
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);

	glBindBuffer(GL_ARRAY_BUFFER, 0);


	glBindVertexArray(0); // Unbind VAO (it's always a good thing to unbind any buffer/array to prevent strange bugs)



	while (!glfwWindowShouldClose(window))
	{
		// Check if any events have been activiated (key pressed, mouse moved etc.) and call corresponding response functions
		glfwPollEvents();

		// Render
		// Clear the colorbuffer
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);


		// Draw our first triangle
		ourShader.Use();
		glBindVertexArray(VAO);


		glPointSize(1);
		glDrawArrays(GL_POINTS, 0, 25);
		// glDrawArrays(GL_LINES,0,5);
		 //glDrawArrays(GL_LINE_LOOP,0,4);

		glDrawArrays(GL_TRIANGLES, 0, 180);
		//glDrawElements(GL_TRIANGLES, 6,GL_UNSIGNED_INT,0);



		glBindVertexArray(0);

		// Swap the screen buffers
		glfwSwapBuffers(window);
	}



	glfwTerminate();
	return EXIT_SUCCESS;
}

void resize(GLFWwindow* window, int width, int height)
{
	// Set the Viewport to the size of the created window
	glViewport(0, 0, width, height);
	//glViewport(0, 0, screenWidth, screenHeight);
}