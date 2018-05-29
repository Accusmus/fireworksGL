// System Headers
#include <iostream>
#include <fstream>
#include <cmath>
#include <cstdlib>

// OpenGL Headers
// OpenGL Headers
#if defined(_WIN32)
	#include <GL/glew.h>
	#if defined(GLEW_EGL)
		#include <GL/eglew.h>
	#elif defined(GLEW_OSMESA)
		#define GLAPI extern
		#include <GL/osmesa.h>
	#elif defined(_WIN32)
		#include <GL/wglew.h>
	#elif !defined(__APPLE__) && !defined(__HAIKU__) || defined(GLEW_APPLE_GLX)
		#include <GL/glxew.h>
	#endif

	// OpenGL Headers
	#define GLFW_INCLUDE_GLCOREARB
	#include <GLFW/glfw3.h>
#elif defined(__APPLE__)
	#define GLFW_INCLUDE_GLCOREARB
	#include <GLFW/glfw3.h>
	#include <OpenGL/gl3.h>
	#include <OpenGL/gl3ext.h>
		// OpenGL Headers
	#include <OpenGL/gl3.h>
#elif defined(__LINUX__)
    #include <GL/glew.h>
    #include <GL/glut.h>
    #include <GLFW/glfw3.h>

#elif defined(__unix__)
    #include <GL/glew.h>
    #include <GL/glut.h>
    #include <GLFW/glfw3.h>
#endif

// GLM Headers
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

// Project Headers
#include "shader.h"
#include "utils.h"
#include "geometry.h"
#include "image.h"
#include "camera.h"

// Camera
Camera *camera;

// Update Framebuffer
bool update_framebuffer = false;
bool pause = false;
bool mode = false;

float uniform() {
	return rand()/(float)RAND_MAX;
}

// --------------------------------------------------------------------------------
// GLFW Callbacks
// --------------------------------------------------------------------------------

// Called on Error Event
void onError(int error, const char *description) {
	// Print Error message
	std::cerr << "Error: " << error << " : " << description << std::endl;
}

// Called on Window Close Event
void onWindowClose(GLFWwindow *window) {
	// Nothing to do right now
	// Do not call glfwDestroyWindow from here
}

// Called on Window Size Event
void onFramebufferSize(GLFWwindow *window, int width, int height) {
	// Set-up the window/screen coordinates
	glfwMakeContextCurrent(window);
	glViewport(0, 0, width, height);
	glfwMakeContextCurrent(NULL);
}

// --------------------------------------------------------------------------------
// Keyboard Input
// --------------------------------------------------------------------------------
void onKey(GLFWwindow *window, int key, int scancode, int action, int mods) {
	// If user presses 'F'
	if((key == GLFW_KEY_F) && (action == GLFW_PRESS)) {
		// Set framebuffer to update
		update_framebuffer = true;
	}

	// If user presses 'P'
	if((key == GLFW_KEY_P) && (action == GLFW_PRESS)) {
		// Pause / unpause
		pause = !pause;
	}

	// If user presses 'M'
	if((key == GLFW_KEY_M) && (action == GLFW_PRESS)) {
		// Switch Mode
		mode = !mode;
	}
}

// --------------------------------------------------------------------------------
// Mouse Input
// --------------------------------------------------------------------------------
void onMouseButton(GLFWwindow *window, int button, int action, int mods) {
	// Update Camera
	camera->onMouseButton(window, button, action, mods);
}

void onCursorPosition(GLFWwindow *window, double x, double y) {
	// Update Camera
	camera->onCursorPosition(window, x, y);
}

// --------------------------------------------------------------------------------
// Example 21 - Instanced-Rendering Grass
// --------------------------------------------------------------------------------
int main() {
	// Set Error Callback
	glfwSetErrorCallback(onError);

	// Initialise GLFW
	if (!glfwInit()) {
		// Return Error
		return 1;
	}

	// Window Size
	int window_width = 600;
	int window_height = 600;

	// Create Window
	GLFWwindow *window = createWindow(600, 600, "Example 21 - Instanced Rendering", 3, 2);

	// Check Window
	if (window == NULL) {
		// Print Error Message
		std::cerr << "Error: create window or context failed." << std::endl;

		// Return Error
		return 1;
	}

	#if defined(_WIN32)
		// Initialise GLEW
		if (glewInit() != GLEW_OK) {
			// Return Error
			return 1;
		}
    #endif // defined
    #if defined(__linux__)
        glewExperimental = true;
        if(glewInit() != GLEW_OK){
            return 1;
        }
	#endif

	// Set window callback functions
	glfwSetFramebufferSizeCallback(window, onFramebufferSize);
	glfwSetWindowCloseCallback(window, onWindowClose);

	// Set mouse input callback functions
	glfwSetMouseButtonCallback(window, onMouseButton);
	glfwSetCursorPosCallback(window, onCursorPosition);

	// Set keyboard input callback functions
	glfwSetKeyCallback(window, onKey);

	// ----------------------------------------
	// Initialise OpenGL
	// ----------------------------------------
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);

	glFrontFace(GL_CCW);
	glEnable(GL_CULL_FACE);

	// Get Maximum Anistropic level
	GLfloat maxAnistropy = 0.0f;
	glGetFloatv(GL_MAX_TEXTURE_MAX_ANISOTROPY_EXT, &maxAnistropy);

	// Enable Anistropic Filtering
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAX_ANISOTROPY_EXT, maxAnistropy);

	int maxVertexUniformComponents;
	glGetIntegerv(GL_MAX_VERTEX_UNIFORM_COMPONENTS, &maxVertexUniformComponents);

	std::cout << "Max Vertex Uniform Components: " << maxVertexUniformComponents << std::endl;

	// ----------------------------------------
	// Camera
	// ----------------------------------------
	camera = new GimbalFreeLookCamera(window, glm::vec3(0.0f, 0.2f, 1.4f));

	// ----------------------------------------
	// Create GLSL Program and VAOs, VBOs
	// ----------------------------------------

	// Load GLSL Program
	GLuint program = loadProgram("./shader/colour.vert.glsl",
								 NULL, NULL, NULL,
								 "./shader/colour.frag.glsl");

	// Use Program
	glUseProgram(program);

	// ----------------------------------------
	// Vertex Array Objects
	// ----------------------------------------
	// Vertex Array Objects (VAO)
	GLuint vao[2];

	// Vertex Buffer Objects (VBO)
	GLuint vbo[2];

	// Element Buffer Objects (EBO)
	GLuint ebo[2];

	// Number of indexes
	GLuint numIndexes[2];

	// Create VAO, VBO & EBO
	glGenVertexArrays(2, vao);
	glGenBuffers(2, vbo);
	glGenBuffers(2, ebo);

	// ----------------------------------------
	// Vertex Stream - Ground
	// ----------------------------------------

	// Bind VAO, VBO & EBO
	glBindVertexArray(vao[0]);
	glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo[0]);

	// Use Program
	glUseProgram(program);

	// Set Vertex Attribute Pointers
	glVertexAttribPointer(glGetAttribLocation(program, "vert_Position"), 4, GL_FLOAT, GL_FALSE, 12 * sizeof(GLfloat), NULL);
	glVertexAttribPointer(glGetAttribLocation(program, "vert_Normal"),   4, GL_FLOAT, GL_FALSE, 12 * sizeof(GLfloat), (GLvoid*)(4*sizeof(float)));
	glVertexAttribPointer(glGetAttribLocation(program, "vert_Colour"),   4, GL_FLOAT, GL_FALSE, 12 * sizeof(GLfloat), (GLvoid*)(8*sizeof(float)));

	// Enable Vertex Attribute Arrays
	glEnableVertexAttribArray(glGetAttribLocation(program, "vert_Position"));
	glEnableVertexAttribArray(glGetAttribLocation(program, "vert_Normal"));
	glEnableVertexAttribArray(glGetAttribLocation(program, "vert_Colour"));

	// ----------------------------------------
	// Object
	// ----------------------------------------

	// Vertex and Index buffers (host)
	std::vector<glm::vec4> buffer;
	std::vector<glm::ivec3> indexes;

	// Create Ground
	createGround(buffer, indexes);

	// Load Vertex Data
	glBufferData(GL_ARRAY_BUFFER, buffer.size() * sizeof(glm::vec4), buffer.data(), GL_STATIC_DRAW);

	// Load Element Data
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indexes.size() * sizeof(glm::ivec3), indexes.data(), GL_STATIC_DRAW);

	// Set number of indexes
	numIndexes[0] = indexes.size();

	// ----------------------------------------
	// Vertex Stream - Grass
	// ----------------------------------------

	// Bind VAO, VBO & EBO
	glBindVertexArray(vao[1]);
	glBindBuffer(GL_ARRAY_BUFFER, vbo[1]);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo[1]);

	// Use Program
	glUseProgram(program);

	// Set Vertex Attribute Pointers
	glVertexAttribPointer(glGetAttribLocation(program, "vert_Position"), 4, GL_FLOAT, GL_FALSE, 12 * sizeof(GLfloat), NULL);
	glVertexAttribPointer(glGetAttribLocation(program, "vert_Normal"),   4, GL_FLOAT, GL_FALSE, 12 * sizeof(GLfloat), (GLvoid*)(4*sizeof(float)));
	glVertexAttribPointer(glGetAttribLocation(program, "vert_Colour"),   4, GL_FLOAT, GL_FALSE, 12 * sizeof(GLfloat), (GLvoid*)(8*sizeof(float)));

	// Enable Vertex Attribute Arrays
	glEnableVertexAttribArray(glGetAttribLocation(program, "vert_Position"));
	glEnableVertexAttribArray(glGetAttribLocation(program, "vert_Normal"));
	glEnableVertexAttribArray(glGetAttribLocation(program, "vert_Colour"));

	// ----------------------------------------
	// Object - Grass
	// ----------------------------------------

	// Vertex and Index buffers (host)
	buffer.clear();
	indexes.clear();

	// Create Blade of Grass
	createBlade(buffer, indexes);

	// Load Vertex Data
	glBufferData(GL_ARRAY_BUFFER, buffer.size() * sizeof(glm::vec4), buffer.data(), GL_STATIC_DRAW);

	// Load Element Data
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indexes.size() * sizeof(glm::ivec3), indexes.data(), GL_STATIC_DRAW);

	// Set number of indexes
	numIndexes[1] = indexes.size();

	// ----------------------------------------
	// Grass - Transforms
	// ----------------------------------------

	// Grass Parameters
	int grassX = 100;
	int grassZ = 100;
	int halfX = grassX / 2;
	int halfZ = grassZ / 2;
	float sX = 2.0 / grassX;
	float sZ = 2.0 / grassZ;
	int numObjects = grassX * grassZ;


	// Model Matrix
	std::vector<glm::mat4> modelMatrix;

	// Grid
	for(int iz = -halfZ; iz < halfZ; iz++) {
		for(int ix = -halfX; ix < halfX; ix++) {
			// Random Angle
			// float theta = uniform() * glm::pi<float>() / 4.0f;
			float theta = 0.0f;

			// Random Scale
			// float scale = (uniform() * 0.5 + 0.5) * 0.1;
			float scale = 0.1;

			// Random Axis
			glm::vec3 axis = glm::normalize(glm::vec3(uniform() * 2.0 - 1.0f, uniform() * 2.0 - 1.0f, uniform() * 2.0 - 1.0f));

			// Individual Blade Transform
			modelMatrix.push_back(glm::translate(glm::mat4(), glm::vec3((ix + 0.5f) * sX, 0.0f, (iz + 0.5f) * sZ)) *
								  glm::rotate(glm::mat4(), theta, axis) *
								  glm::scale(glm::mat4(), glm::vec3(scale, scale, scale)));
		}
	}

	// // ----------------------------------------
	// // Instance Attributes
	// // ----------------------------------------

	// // Create buffer object
//	 GLuint ibo;
//	 glGenBuffers(1, &ibo);
//
//	 // Bind buffer object
//	 glBindBuffer(GL_ARRAY_BUFFER, ibo);
//
//	 // Buffer Model Matrix Data
//	 glBufferData(GL_ARRAY_BUFFER, numObjects * sizeof(glm::mat4), glm::value_ptr(modelMatrix[0]), GL_STATIC_DRAW);
//
//	 // Set Attribute Pointers
//	 glVertexAttribPointer(6, 4, GL_FLOAT, GL_FALSE, 16 * sizeof(GLfloat), (GLvoid*)( 0*sizeof(float)));
//	 glVertexAttribPointer(7, 4, GL_FLOAT, GL_FALSE, 16 * sizeof(GLfloat), (GLvoid*)( 4*sizeof(float)));
//	 glVertexAttribPointer(8, 4, GL_FLOAT, GL_FALSE, 16 * sizeof(GLfloat), (GLvoid*)( 8*sizeof(float)));
//	 glVertexAttribPointer(9, 4, GL_FLOAT, GL_FALSE, 16 * sizeof(GLfloat), (GLvoid*)(12*sizeof(float)));
//
//	 // Enable Attribute Arrays
//	 glEnableVertexAttribArray(6);
//	 glEnableVertexAttribArray(7);
//	 glEnableVertexAttribArray(8);
//	 glEnableVertexAttribArray(9);
//
//	 // Set Attribute Divisors (one per instance)
//	 glVertexAttribDivisor(6, 1);
//	 glVertexAttribDivisor(7, 1);
//	 glVertexAttribDivisor(8, 1);
//	 glVertexAttribDivisor(9, 1);

	// ----------------------------------------
	// Vertex Array Object
	// ----------------------------------------

	// Unbind VAO, VBO & EBO
	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	// ----------------------------------------
	// View Matrix
	// ----------------------------------------
	// Copy to program
	glUseProgram(program);

	// Copy View Matrix to Shader
	glUniformMatrix4fv(glGetUniformLocation(program, "u_View"),  1, GL_FALSE, glm::value_ptr(camera->getViewMatrix()));

	// ----------------------------------------
	// Projection Matrix
	// ----------------------------------------
	glm::mat4 projectionMatrix;

	// Calculate Perspective Projection
	projectionMatrix = glm::perspective(glm::radians(67.0f), 1.0f, 0.2f, 50.0f);

	// Copy Projection Matrix to Shader
	glUniformMatrix4fv(glGetUniformLocation(program, "u_Projection"), 1, GL_FALSE, glm::value_ptr(projectionMatrix));

	// ----------------------------------------
	// Main Render loop
	// ----------------------------------------
	float time = glfwGetTime();
	float total = 0.0f;
	int frame_count = 0;

	// Main Loop
	while (!glfwWindowShouldClose(window)) {
		// Make the context of the given window current on the calling thread
		glfwMakeContextCurrent(window);

		// Set clear (background) colour to black
		glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

		// Clear Screen
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// Update Time
		float current_time = glfwGetTime();
		float dt = current_time - time;
		time = current_time;

		// Frames Per Second Counter
		total += dt;
		frame_count++;
		if(total >= 1.0f) {
			total = 0.0f;
			std::cout << "fps: " << frame_count << std::endl;
			frame_count = 0;
		}

		// ----------------------------------------
		// Update Camera
		camera->update(dt);

		// Use Program
		glUseProgram(program);

		// Copy View Matrix to Shader
		glUniformMatrix4fv(glGetUniformLocation(program, "u_View"),  1, GL_FALSE, glm::value_ptr(camera->getViewMatrix()));
		// ----------------------------------------

		// ----------------------------------------
		// Draw Ground
		// ----------------------------------------
		// Use Program
		glUseProgram(program);

		// Copy Model Matrix to Shader
		glUniformMatrix4fv(glGetUniformLocation(program, "u_Model"), 1, GL_FALSE, glm::value_ptr(glm::mat4()));

		// Copy Grass Flag to Shader
		glUniform1i(glGetUniformLocation(program, "u_Grass"), 0);

		// Bind Vertex Array Object
		glBindVertexArray(vao[0]);

		// Draw Elements (Triangles)
		glDrawElements(GL_TRIANGLES, numIndexes[0] * 3, GL_UNSIGNED_INT, NULL);

		// Unbind Vertex Array Object
		glBindVertexArray(0);


		// ----------------------------------------
		// Grass - Individual Rendering
		// ----------------------------------------
		// Bind Vertex Array Object
		glBindVertexArray(vao[1]);

		// Copy Grass Flag to Shader
		glUniform1i(glGetUniformLocation(program, "u_Grass"), 1);

		for(int i = 0; i < numObjects; i++) {
			// Copy Model Matrix to Shader
			glUniformMatrix4fv(glGetUniformLocation(program, "u_Model"), 1, GL_FALSE, glm::value_ptr(modelMatrix[i]));

			// Draw Elements (Triangles)
			glDrawElements(GL_TRIANGLES, numIndexes[1] * 3, GL_UNSIGNED_INT, NULL);
		}

		// Unbind Vertex Array Object
		glBindVertexArray(0);

		// // ----------------------------------------
		// // Grass - Instanced - Calculate Position
		// // ----------------------------------------
		// // Copy Grass Flag to Shader
		// glUniform1i(glGetUniformLocation(program, "u_Grass"), 1);

		// // Copy Grass Parameters into Shader
		// glUniform1i(glGetUniformLocation(program, "u_GrassX"), grassX);
		// glUniform1i(glGetUniformLocation(program, "u_GrassZ"), grassZ);

		// // Bind Vertex Array Object
		// glBindVertexArray(vao[1]);

		// // Draw Elements (Triangles)
		// glDrawElementsInstanced(GL_TRIANGLES, numIndexes[1] * 3, GL_UNSIGNED_INT, NULL, numObjects);

		// // Unbind Vertex Array Object
		// glBindVertexArray(0);

		// // ----------------------------------------
		// // Grass - Instanced - Uniforms
		// // ----------------------------------------
		// // Bind Vertex Array Object
		// glBindVertexArray(vao[1]);

		// // Copy Grass Flag to Shader
		// glUniform1i(glGetUniformLocation(program, "u_Grass"), 1);

		// // Render instances
		// for(int i = 0; i < numObjects; i += 200) {
		// 	// Calculate number of instances
		// 	int numInstances = glm::min(200, numObjects - i);

		// 	// Copy Model Matrix to Shader
		// 	glUniformMatrix4fv(glGetUniformLocation(program, "u_Model"), numInstances, GL_FALSE, glm::value_ptr(modelMatrix[i]));

		// 	// Draw Elements (Triangles)
		// 	glDrawElementsInstanced(GL_TRIANGLES, numIndexes[1] * 3, GL_UNSIGNED_INT, NULL, numInstances);
		// }

		// // Unbind Vertex Array Object
		// glBindVertexArray(0);

		// // ----------------------------------------
		// // Grass - Instanced - Instance Attributes
		// // ----------------------------------------

		// // Bind Vertex Array Object
		// glBindVertexArray(vao[1]);

		// // Copy Grass Flag to Shader
		// glUniform1i(glGetUniformLocation(program, "u_Grass"), 1);

		// // Draw Elements (Triangles)
		// glDrawElementsInstanced(GL_TRIANGLES, numIndexes[1] * 3, GL_UNSIGNED_INT, NULL, numObjects);

		// // Unbind Vertex Array Object
		// glBindVertexArray(0);

		// ----------------------------------------
		// Swap the back and front buffers
		glfwSwapBuffers(window);

		// Poll window events
		glfwPollEvents();
	}

	// Delete VAO, VBO & EBO
	glDeleteVertexArrays(2, vao);
	glDeleteBuffers(2, vbo);
	glDeleteBuffers(2, ebo);

	// Delete Program
	glDeleteProgram(program);

	// Stop receiving events for the window and free resources; this must be
	// called from the main thread and should not be invoked from a callback
	glfwDestroyWindow(window);

	// Terminate GLFW
	glfwTerminate();

	return 0;
}


