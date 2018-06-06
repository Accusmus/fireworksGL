#include "renderer.h"

renderer::renderer()
{
    //Set the perspective matrix this will be consistant throughout application
	projectionMatrix = glm::perspective(glm::radians(67.0f), 1.0f, 0.01f, 300.0f);
}

renderer::~renderer()
{
    //dtor
}

void renderer::initBuffers(){

    glUseProgram(program);

    glGenVertexArrays(1, &vao);
	glGenBuffers(1, &vbo);
	glGenBuffers(1, &ebo);

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
}

void renderer::deleteObjects(){
    glDeleteVertexArrays(1, &vao);
	glDeleteBuffers(1, &vbo);
	glDeleteBuffers(1, &ebo);

	// Delete Program
	glDeleteProgram(program);
}

void renderer::setViewMatrix(glm::mat4 vMatrix){
    glUniformMatrix4fv(glGetUniformLocation(program, "u_View"),  1, GL_FALSE, glm::value_ptr(vMatrix));
}

void renderer::setModelMatrix(const float mMatrix[16]){
    glUniformMatrix4fv(glGetUniformLocation(program, "u_Model"), 1, GL_FALSE, mMatrix);
}

void renderer::setProjectionMatrix(){
    glUniformMatrix4fv(glGetUniformLocation(program, "u_Projection"), 1, GL_FALSE, glm::value_ptr(projectionMatrix));
}

void renderer::setColour(glm::vec3 col){
    glUniform3f(glGetUniformLocation(program, "u_Colour"), col.x, col.y, col.z);
}
