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

#include "firework.h"
#include "firework_renderer.h"


class firework_manager
{
    public:
        firework_manager();
        virtual ~firework_manager();

        void update();
        void createFirework(glm::vec3 pos, glm::vec3 acc, float size);
        void createFirework(float size);
        void createNumFireworks(int num, float size);

        int getNumOfFireworks();
        glm::vec3 getFireworkPos(int id);
        glm::vec3 getFireworkColour(int id);
        float getFireworkSize(int id);
        void setFireworkSize(int id, float s);

        void initRenderer();
        void render(int id, float modelMat[16], glm::mat4 viewMat);
        void deleteRenderObj();

    protected:

    private:
        std::vector<firework> fireworks;
        firework_renderer renderer;

        glm::vec3 createRandomColour();
};

#endif // FIREWORK_MANAGER_H
