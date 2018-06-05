#ifndef GEOMETRY_H
#define GEOMETRY_H

// System Headers
#include <iostream>
#include <vector>

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
#define GLM_ENABLE_EXPERIMENTAL
#include "glm/glm.hpp"
#include "glm/gtx/string_cast.hpp"

void createCube(std::vector<glm::vec4> &buffer, std::vector<glm::ivec3> &indexes);

// --------------------------------------------------------------------------------
// Create Blade of Grass - Positions, Normals, Colours
void createBlade(std::vector<glm::vec4> &buffer, std::vector<glm::ivec3> &indexes);

// --------------------------------------------------------------------------------
// Create Ground - Positions, Normals, Colours
void createGround(std::vector<glm::vec4> &buffer, std::vector<glm::ivec3> &indexes);

// --------------------------------------------------------------------------------
// Create Sphere with Positions and Normals
void createSphereData(std::vector<glm::vec4> &buffer, std::vector<glm::ivec3> &indexes, float r, int sub1, int sub2, glm::vec3 colour);

// --------------------------------------------------------------------------------
#endif // GEOMETRY_H
