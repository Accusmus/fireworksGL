#ifndef FIREWORK_H
#define FIREWORK_H

// System Headers
#include <iostream>
#include <vector>
#include <glm/glm.hpp>
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


class firework
{
    public:
        firework();
        virtual ~firework();

        void setPosition(glm::vec3 pos);
        void setAcceleration(glm::vec3 acc);
        void update();

        void setColour(glm::vec3 col);
        glm::vec3 getPosition();
        glm::vec3 getColour();
        bool isAlive();

    protected:

    private:
        glm::vec3 position;
        glm::vec3 acceleration;
        glm::vec3 velocity;

        glm::vec3 colour;

        glm::vec3 gravity;

        bool alive;
};

#endif // FIREWORK_H
