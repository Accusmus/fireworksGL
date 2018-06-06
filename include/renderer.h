#ifndef RENDERER_H
#define RENDERER_H

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

// GLM Headers
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>



class renderer
{
    public:
        renderer();
        virtual ~renderer();

        virtual void renderObj(glm::vec3 colour, float modelMat[16], glm::mat4 viewMat) = 0;
        virtual void setUpProgram(const char *vert_file, const char *ctrl_file, const char *eval_file, const char *geom_file, const char *frag_file) = 0;
        virtual void initializeRenderer() = 0;
        void initBuffers();
        void deleteObjects();

        void setViewMatrix(glm::mat4 vMatrix);
        void setModelMatrix(const float mMatrix[16]);
        void setProjectionMatrix();
        void setColour(glm::vec3 col);


    protected:
        GLuint program;
        GLuint vao, vbo, ebo;

        std::vector<glm::vec4> buffer;
        std::vector<glm::ivec3> indexes;


    private:
        glm::mat4 projectionMatrix;
};

#endif // RENDERER_H
