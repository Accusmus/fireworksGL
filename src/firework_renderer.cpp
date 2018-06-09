#include "firework_renderer.h"

firework_renderer::firework_renderer()
{
    //do all of the set up ready to draw
    initializeRenderer();
}

firework_renderer::~firework_renderer()
{
    //dtor
}

void firework_renderer::initializeRenderer(){
    //Load the shader programs
    program = loadProgram("./shader/colour.vert.glsl", NULL, NULL, NULL, "./shader/colour.frag.glsl");
    initBuffers();
    createFireworkObject(1.0f, 10, 10);
    setProjectionMatrix();
}


void firework_renderer::renderObj(glm::vec3 colour, float modelMat[16], glm::mat4 viewMat){
    //use the currently loaded shader program
    glUseProgram(program);
    //bind the vertex array object
    glBindVertexArray(vao);

    //set the model, view and colour Uniforms and send to the shader
    setModelMatrix(modelMat);
    setViewMatrix(viewMat);
    setColour(colour);

    glDrawElements(GL_TRIANGLES, buffer.size()*3, GL_UNSIGNED_INT, NULL);
}

void firework_renderer::createFireworkObject(float size, int horRes, int vertRes){
    //Create the object data which we are going to draw
    createSphereData(buffer, indexes, size, horRes, vertRes);
    // Load Vertex Data
	glBufferData(GL_ARRAY_BUFFER, buffer.size() * sizeof(glm::vec4), buffer.data(), GL_STATIC_DRAW);
	// Load Element Data
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indexes.size() * sizeof(glm::ivec3), indexes.data(), GL_STATIC_DRAW);
}
