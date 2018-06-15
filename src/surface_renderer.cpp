#include "surface_renderer.h"

surface_renderer::surface_renderer()
{
	initializeRenderer();
}

surface_renderer::~surface_renderer()
{

}

void surface_renderer::renderObj(glm::vec3 colour, float modelMat[16],glm::mat4 viewMat){
    //create model transforms
    float translation[16], sc[16], model[16];
    translate(-0.0, 0.0, -30.0, translation);
    scale(300, 300, 300, sc);
    multiply44(translation, sc, model);

    //use the currently loaded shader program
    glUseProgram(program);
    //bind the vertex array object
    glBindVertexArray(vao);

    //set the model, view and colour Uniforms and send to the shader
    setModelMatrix(model);
    setViewMatrix(viewMat);
    setColour(colour);

    glDrawElements(GL_TRIANGLES, buffer.size()*3, GL_UNSIGNED_INT, NULL);
}

void surface_renderer::initializeRenderer(){
	program = loadProgram("./shader/colour.vert.glsl", NULL, NULL, NULL, "./shader/colour.frag.glsl");
	initBuffers();
	createSurfaceObj();
	setProjectionMatrix();
}

void surface_renderer::createSurfaceObj(){
    createGround(buffer, indexes);
    glBufferData(GL_ARRAY_BUFFER, buffer.size() * sizeof(glm::vec4), buffer.data(), GL_STATIC_DRAW);
	// Load Element Data
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indexes.size() * sizeof(glm::ivec3), indexes.data(), GL_STATIC_DRAW);
}
