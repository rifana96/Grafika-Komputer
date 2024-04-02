#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stb/stb_image.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include"shaderClass.h"

const int windowWidth = 800;
const int windowHeight = 800;

const int jumlahObjek = 6;
const int jumlahIndices = 3;

void binding(GLuint& VAO, GLuint& VBO, GLuint& EBO, GLsizei vboSize ,GLfloat* vboName, GLsizei eboSize,GLuint* eboName)
{
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, vboSize, vboName, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, eboSize, eboName, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

int main()
{
	glfwInit();

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* window = glfwCreateWindow(windowWidth, windowHeight, "Dinning_Table", 0, 0);
	if (window == NULL)
	{
		std::cout << "window gagal dibuka";
		glfwTerminate();
		return 1;
	}
	glfwMakeContextCurrent(window);

	gladLoadGL();
	glViewport(0, 0, windowWidth, windowHeight);

	Shader shaderProgram("default.vert", "default.frag");

	GLfloat permukaanMeja[] =
	{
		// Koordinat simpul		// Warna
		// Front face
		-0.5f, -0.1f,  0.5f,	1.0f, 0.0f, 0.0f, //kiri bawah 0
		 0.5f, -0.1f,  0.5f,	0.0f, 1.0f, 0.0f, //kanan bawah 1
		 0.5f,  0.1f,  0.5f,	0.0f, 0.0f, 1.0f, //kanan atas 2
		-0.5f,  0.1f,  0.5f,	1.0f, 1.0f, 1.0f, //kiri atas 3

		// Back face
		-0.5f, -0.1f, -0.5f,	1.0f, 0.0f, 0.0f, //kiri bawah 4
		 0.5f, -0.1f, -0.5f,	0.0f, 1.0f, 0.0f, //kanan bawah 5
		 0.5f,  0.1f, -0.5f,	0.0f, 0.0f, 1.0f, //kanan atas 6
		-0.5f,  0.1f, -0.5f,	1.0f, 1.0f, 1.0f, //kiri atas 7

		// Top face
		-0.5f,  0.1f,  0.5f,	1.0f, 0.0f, 0.0f, //kiri bawah 8
		 0.5f,  0.1f,  0.5f,	0.0f, 1.0f, 0.0f, //kanan bawah 9
		 0.5f,  0.1f, -0.5f,	0.0f, 0.0f, 1.0f, //kanan atas 10
		-0.5f,  0.1f, -0.5f,	1.0f, 1.0f, 1.0f, //kiri atas 11

		// Bottom face
		-0.5f, -0.1f,  0.5f,	1.0f, 0.0f, 0.0f, //kiri bawah 12
		 0.5f, -0.1f,  0.5f,	0.0f, 1.0f, 0.0f, //kanan bawah 13
		 0.5f, -0.1f, -0.5f,	0.0f, 0.0f, 1.0f, //kanan atas 14
		-0.5f, -0.1f, -0.5f,	1.0f, 1.0f, 1.0f  //kiri atas 15
	};

	GLfloat kakiKiriMeja[] =
	{
		//front face
		-0.5f, -0.5f,  0.5f,	1.0f, 0.0f, 0.0f,  //0
		-0.3f, -0.5f,  0.5f,	0.0f, 1.0f, 0.0f,  //1
		-0.3f, -0.1f,  0.5f,	0.0f, 0.0f, 1.0f,  //2
		-0.5f, -0.1f,  0.5f,	1.0f, 1.0f, 1.0f,  //3
													  
		//back face						  
		-0.5f, -0.5f,  0.3f,	1.0f, 0.0f, 0.0f,  //4
		-0.3f, -0.5f,  0.3f,	0.0f, 1.0f, 0.0f,  //5
		-0.3f, -0.1f,  0.3f,	0.0f, 0.0f, 1.0f,  //6
		-0.5f, -0.1f,  0.3f,	1.0f, 1.0f, 1.0f,  //7
													  
		//bottom face						  
		-0.5f, -0.5f,  0.5f,	1.0f, 0.0f, 0.0f,  //8
		-0.3f, -0.5f,  0.5f,	0.0f, 1.0f, 0.0f,  //9
		-0.3f, -0.5f,  0.3f,	0.0f, 0.0f, 1.0f,  //10
		-0.5f, -0.5f,  0.3f,	1.0f, 1.0f, 1.0f   //11	
	};												  
													  
	GLfloat kakiKananMeja[] =						  
	{												  
		//front face						  
		0.3f, -0.5f,  0.5f,		1.0f, 0.0f, 0.0f,   
		0.5f, -0.5f,  0.5f,		0.0f, 1.0f, 0.0f,   
		0.5f, -0.1f,  0.5f,		0.0f, 0.0f, 1.0f,   
		0.3f, -0.1f,  0.5f,		1.0f, 1.0f, 1.0f,   
													  
		//back face							  
		0.3f, -0.5f,  0.3f,     1.0f, 0.0f, 0.0f,   
		0.5f, -0.5f,  0.3f,     0.0f, 1.0f, 0.0f,   
		0.5f, -0.1f,  0.3f,     0.0f, 0.0f, 1.0f,   
		0.3f, -0.1f,  0.3f,     1.0f, 1.0f, 1.0f,   
													  
		//bottom face						  
		0.3f, -0.5f,  0.5f,		1.0f, 0.0f, 0.0f,   
		0.5f, -0.5f,  0.5f,		0.0f, 1.0f, 0.0f,   
		0.5f, -0.5f,  0.3f,		0.0f, 0.0f, 1.0f,   
		0.3f, -0.5f,  0.3f,		1.0f, 1.0f, 1.0f   
	};												  
													  
	GLfloat backKakiKananMeja[] =					  
	{												  
		//front face							  
		0.3f, -0.5f,  -0.3f,    1.0f, 0.0f, 0.0f,  
		0.5f, -0.5f,  -0.3f,    0.0f, 1.0f, 0.0f,  
		0.5f, -0.1f,  -0.3f,    0.0f, 0.0f, 1.0f,  
		0.3f, -0.1f,  -0.3f,    1.0f, 1.0f, 1.0f,  
													  
		//back face							  
		0.3f, -0.5f,  -0.5f,    1.0f, 0.0f, 0.0f,  
		0.5f, -0.5f,  -0.5f,    0.0f, 1.0f, 0.0f,  
		0.5f, -0.1f,  -0.5f,    0.0f, 0.0f, 1.0f,  
		0.3f, -0.1f,  -0.5f,    1.0f, 1.0f, 1.0f,  
													  
		//bottom face							  
		0.3f, -0.5f,  -0.3f,    1.0f, 0.0f, 0.0f,  
		0.5f, -0.5f,  -0.3f,    0.0f, 1.0f, 0.0f,  
		0.5f, -0.5f,  -0.5f,    0.0f, 0.0f, 1.0f,  
		0.3f, -0.5f,  -0.5f,    1.0f, 1.0f, 1.0f  
	};												  
													  
	GLfloat backKakiKiriMeja[] =					  
	{												  
		//front face							  
		-0.5f, -0.5f,  -0.3f,   1.0f, 0.0f, 0.0f, 
		-0.3f, -0.5f,  -0.3f,   0.0f, 1.0f, 0.0f, 
		-0.3f, -0.1f,  -0.3f,   0.0f, 0.0f, 1.0f, 
		-0.5f, -0.1f,  -0.3f,   1.0f, 1.0f, 1.0f, 
													  
		//back face							  
		-0.5f, -0.5f,  -0.5f,   1.0f, 0.0f, 0.0f, 
		-0.3f, -0.5f,  -0.5f,   0.0f, 1.0f, 0.0f, 
		-0.3f, -0.1f,  -0.5f,   0.0f, 0.0f, 1.0f, 
		-0.5f, -0.1f,  -0.5f,   1.0f, 1.0f, 1.0f, 
													  
		//bottom face						  
		-0.5f, -0.5f,  -0.3f,   1.0f, 0.0f, 0.0f, 
		-0.3f, -0.5f,  -0.3f,   0.0f, 1.0f, 0.0f, 
		-0.3f, -0.5f,  -0.5f,   0.0f, 0.0f, 1.0f, 
		-0.5f, -0.5f,  -0.5f,   1.0f, 1.0f, 1.0f 
	};

	GLfloat taplakMeja[] =
	{
		// Koordinat simpul		// Warna
		// Top face
		-0.5f,  0.1001f,  0.2f,		1.0f, 1.0f, 1.0f, //kiri bawah 0
		 0.5f,  0.1001f,  0.2f,		1.0f, 1.0f, 1.0f, //kanan bawah 1
		 0.5f,  0.1001f,  -0.2f,	1.0f, 1.0f, 1.0f, //kanan atas 2
		-0.5f,  0.1001f,  -0.2f,	1.0f, 1.0f, 1.0f,  //kiri atas 3

		//right face
		0.50015f, -0.25f, 0.2f,		1.0f, 1.0f, 1.0f,	//kanan bawah depan 4
		0.50015f, -0.25f, -0.2f,	1.0f, 1.0f, 1.0f,	//kanan bawah belakang 5

		//left face
		-0.50015f, -0.25f, 0.2f,	1.0f, 1.0f, 1.0f,	//kiri bawah depan 6
		-0.50015f, -0.25f, -0.2f,	1.0f, 1.0f, 1.0f,	//kiri bawah belakang 7
	};

	GLuint permukaanMejaIndices[] =
	{
		0, 1, 2, 2, 3, 0,		// Front face
		4, 5, 6, 6, 7, 4,		// Back face
		8, 9, 10, 10, 11, 8,	// top face
		12, 13, 14, 14, 15, 12,	// bottom face
		0, 3, 7, 7, 4, 0,		// left face
		1, 2, 6, 6, 5, 1		// right face
	};

	GLuint kakiMejaIndices[] =
	{
		0, 1, 2, 2, 3, 0,		// Front face
		4, 5, 6, 6, 7, 4,		// back face
		8, 9, 10, 10, 11, 8,	// bottom face
		0, 3, 7, 7, 4, 0,		// left face
		1, 2, 6, 6, 5, 1		// right face
	};

	GLuint taplakMejaIndices[] =
	{
		0, 1, 2, 2, 3, 0,
		1, 4, 5, 5, 2, 1,
		0, 6, 7, 7, 3, 0
	};

	GLuint VAO[jumlahObjek], VBO[jumlahObjek], EBO[jumlahIndices];
	glGenVertexArrays(jumlahObjek, VAO);
	glGenBuffers(jumlahObjek, VBO);
	glGenBuffers(jumlahIndices, EBO);

	//Meja
	binding(VAO[0], VBO[0], EBO[0], sizeof(permukaanMeja), permukaanMeja, sizeof(permukaanMejaIndices), permukaanMejaIndices);
	binding(VAO[1], VBO[1], EBO[1], sizeof(kakiKiriMeja), kakiKiriMeja, sizeof(kakiMejaIndices), kakiMejaIndices);
	binding(VAO[2], VBO[2], EBO[1], sizeof(kakiKananMeja), kakiKananMeja, sizeof(kakiMejaIndices), kakiMejaIndices);
	binding(VAO[3], VBO[3], EBO[1], sizeof(backKakiKiriMeja), backKakiKiriMeja, sizeof(kakiMejaIndices), kakiMejaIndices);
	binding(VAO[4], VBO[4], EBO[1], sizeof(backKakiKananMeja), backKakiKananMeja, sizeof(kakiMejaIndices), kakiMejaIndices);

	//Taplak Meja
	binding(VAO[5], VBO[5], EBO[2], sizeof(taplakMeja), taplakMeja, sizeof(taplakMejaIndices), taplakMejaIndices);

	float rotation = 0.0f;
	double prevTime = glfwGetTime();

	glEnable(GL_DEPTH_TEST);

	while (!glfwWindowShouldClose(window))
	{
		glClearColor(0.212f, 0.228f, 0.255f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		shaderProgram.Activate();

		glm::mat4 model = glm::mat4(1.0f);
		glm::mat4 view = glm::mat4(1.0f);
		glm::mat4 projection = glm::mat4(1.0f);

		double currentTime = glfwGetTime();
		if (currentTime - prevTime >= 1 / 60)
		{
			rotation += 0.01f;
			prevTime = currentTime;
		}

		model = glm::rotate(model, glm::radians(rotation), glm::vec3(1.0f, 1.0f, 0.0f));
		view = glm::translate(view, glm::vec3(0.0f, 0.0f, -2.0f));
		projection = glm::perspective(glm::radians(45.0f), (float)(windowWidth / windowHeight), 0.1f, 100.0f);

		int modelLocation = glGetUniformLocation(shaderProgram.ID, "model");
		glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(model));
		int viewLocation = glGetUniformLocation(shaderProgram.ID, "view");
		glUniformMatrix4fv(viewLocation, 1, GL_FALSE, glm::value_ptr(view));
		int projectionLocation = glGetUniformLocation(shaderProgram.ID, "projection");
		glUniformMatrix4fv(projectionLocation, 1, GL_FALSE, glm::value_ptr(projection));

		//Meja
		glBindVertexArray(VAO[0]);
		glDrawElements(GL_TRIANGLES, sizeof(permukaanMejaIndices) / sizeof(int), GL_UNSIGNED_INT, 0);
		glBindVertexArray(VAO[1]);
		glDrawElements(GL_TRIANGLES, sizeof(kakiMejaIndices)/sizeof(int), GL_UNSIGNED_INT, 0);
		glBindVertexArray(VAO[2]);
		glDrawElements(GL_TRIANGLES, sizeof(kakiMejaIndices) / sizeof(int), GL_UNSIGNED_INT, 0);
		glBindVertexArray(VAO[3]);
		glDrawElements(GL_TRIANGLES, sizeof(kakiMejaIndices) / sizeof(int), GL_UNSIGNED_INT, 0);
		glBindVertexArray(VAO[4]);
		glDrawElements(GL_TRIANGLES, sizeof(kakiMejaIndices) / sizeof(int), GL_UNSIGNED_INT, 0);

		//Taplak meja
		glBindVertexArray(VAO[5]);
		glDrawElements(GL_TRIANGLES, sizeof(taplakMejaIndices) / sizeof(int), GL_UNSIGNED_INT, 0);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glDeleteVertexArrays(jumlahObjek, VAO);
	glDeleteBuffers(jumlahObjek, VBO);
	glDeleteBuffers(jumlahIndices, EBO);
	shaderProgram.Delete();
	glfwTerminate();
	return 0;
}