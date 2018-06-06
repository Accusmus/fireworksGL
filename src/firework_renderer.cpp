#include "firework_renderer.h"

firework_renderer::firework_renderer()
{
    //ctor
}

firework_renderer::~firework_renderer()
{
    //dtor
}


void firework_renderer::renderObj(){
    glUseProgram(program);
    glBindVertexArray(vao);
    glDrawElements(GL_TRIANGLES, buffer.size()*3, GL_UNSIGNED_INT, NULL);
}

void firework_renderer::setBufferObjData(std::vector<glm::vec4> data, std::vector<glm::ivec3> ind){
    buffer = data;
    indexes = ind;

    // Load Vertex Data
	glBufferData(GL_ARRAY_BUFFER, buffer.size() * sizeof(glm::vec4), buffer.data(), GL_STATIC_DRAW);

	// Load Element Data
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indexes.size() * sizeof(glm::ivec3), indexes.data(), GL_STATIC_DRAW);
}
