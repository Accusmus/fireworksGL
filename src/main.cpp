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
#include "transforms.h"
#include "firework_manager.h"

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

void update(firework_manager &fManager, int update_num);

// --------------------------------------------------------------------------------

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
	GLFWwindow *window = createWindow(window_width, window_height, "Assignment 4 - Fireworks", 3, 2);

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
	//glEnable(GL_CULL_FACE);
	glCullFace(GL_FRONT);

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
	GLuint vao;

	// Vertex Buffer Objects (VBO)
	GLuint vbo;

	// Element Buffer Objects (EBO)
	GLuint ebo;

	// Create VAO, VBO & EBO
	glGenVertexArrays(1, &vao);
	glGenBuffers(1, &vbo);
	glGenBuffers(1, &ebo);

	// Copy View Matrix to Shader
	glUniformMatrix4fv(glGetUniformLocation(program, "u_View"),  1, GL_FALSE, glm::value_ptr(camera->getViewMatrix()));

	glBindVertexArray(vao);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);

    	// Set Vertex Attribute Pointers
	glVertexAttribPointer(glGetAttribLocation(program, "vert_Position"), 4, GL_FLOAT, GL_FALSE, 12 * sizeof(GLfloat), NULL);
	glVertexAttribPointer(glGetAttribLocation(program, "vert_Normal"),   4, GL_FLOAT, GL_FALSE, 12 * sizeof(GLfloat), (GLvoid*)(4*sizeof(float)));
	glVertexAttribPointer(glGetAttribLocation(program, "vert_Colour"),   4, GL_FLOAT, GL_FALSE, 12 * sizeof(GLfloat), (GLvoid*)(8*sizeof(float)));

	// Enable Vertex Attribute Arrays
	glEnableVertexAttribArray(glGetAttribLocation(program, "vert_Position"));
	glEnableVertexAttribArray(glGetAttribLocation(program, "vert_Normal"));
	glEnableVertexAttribArray(glGetAttribLocation(program, "vert_Colour"));

	// Vertex and Index buffers (host)
	std::vector<glm::vec4> buffer;
	std::vector<glm::ivec3> indexes;

	// Create Ground
	//createBlade(buffer, indexes);
	//createGround(buffer, indexes);
	//createCube(buffer, indexes);
	createSphereData(buffer, indexes, 0.1, 5, 5);
	std::cout << indexes.size() << std::endl;

	// Load Vertex Data
	glBufferData(GL_ARRAY_BUFFER, buffer.size() * sizeof(glm::vec4), buffer.data(), GL_STATIC_DRAW);

	// Load Element Data
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indexes.size() * sizeof(glm::ivec3), indexes.data(), GL_STATIC_DRAW);

	// ----------------------------------------
	// Projection Matrix
	// ----------------------------------------
	glm::mat4 projectionMatrix;

	// Calculate Perspective Projection
	projectionMatrix = glm::perspective(glm::radians(67.0f), 1.0f, 0.01f, 300.0f);

	// Copy Projection Matrix to Shader
	glUniformMatrix4fv(glGetUniformLocation(program, "u_Projection"), 1, GL_FALSE, glm::value_ptr(projectionMatrix));

	srand(glfwGetTime());

	firework_manager fManager = firework_manager();
	// ----------------------------------------
	// Main Render loop
	// ----------------------------------------
	float time = glfwGetTime();
	float total = 0.0f, updates = 0.0f;
	int frame_count = 0, update_count = 0;


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

		updates += dt;

        //this will update roughly 60 times a second
		if(updates >= 0.0166f){
            //reset update
            update_count++;
            updates = 0.0f;

            update(fManager, update_count);

            fManager.update();
		}



		if(total >= 1.0f) {
			total = 0.0f;
			std::cout << "fps: " << frame_count << std::endl;
			frame_count = 0;
			update_count = 0;

		}

		// ----------------------------------------
		// Update Camera
		camera->update(dt);

		// Use Program
		glUseProgram(program);

		glUniformMatrix4fv(glGetUniformLocation(program, "u_View"),  1, GL_FALSE, glm::value_ptr(camera->getViewMatrix()));


		// Bind Vertex Array Object
		glBindVertexArray(vao);

		for(size_t i = 0; i < fManager.getNumOfFireworks(); i++){
            float sc[16];
            glm::vec3 fwPos = fManager.getFireworkPos(i);

            translate(fwPos.x, fwPos.y, fwPos.z, sc);

            glUniformMatrix4fv(glGetUniformLocation(program, "u_Model"), 1, GL_FALSE, sc);

            // Draw Elements (Triangles)
            glDrawElements(GL_TRIANGLES, indexes.size()*3, GL_UNSIGNED_INT, NULL);
		}

		// Unbind Vertex Array Object
		glBindVertexArray(0);

		// ----------------------------------------
		// Swap the back and front buffers
		glfwSwapBuffers(window);

		// Poll window events
		glfwPollEvents();
	}
	// Delete VAO, VBO & EBO
	glDeleteVertexArrays(1, &vao);
	glDeleteBuffers(1, &vbo);
	glDeleteBuffers(1, &ebo);

	// Delete Program
	glDeleteProgram(program);

	// Stop receiving events for the window and free resources; this must be
	// called from the main thread and should not be invoked from a callback
	glfwDestroyWindow(window);

	// Terminate GLFW
	glfwTerminate();

	return 0;
}

void update(firework_manager &fManager, int update_num){
    if(update_num == 1 || update_num == 15 || update_num == 30 || update_num == 45){
        fManager.createNumFireworks(1);
    }
    fManager.update();
}


