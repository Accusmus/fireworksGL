#ifndef FIREWORK_MANAGER_H
#define FIREWORK_MANAGER_H

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



class firework_manager
{
    public:
        firework_manager();
        virtual ~firework_manager();

    protected:

    private:
};

#endif // FIREWORK_MANAGER_H
