// OpenGL 4.0
#version 400

// Input to Vertex Shader
in vec4 vert_Position;
in vec4 vert_Normal;
in vec4 vert_Colour;

//----------------------------------------------
// Transform Matrices
uniform mat4 u_Model;
uniform mat4 u_View;
uniform mat4 u_Projection;

uniform vec3 u_Colour;

// Output to Fragment Shader
out vec4 frag_Position;
out vec4 frag_Colour;

//----------------------------------------------
// Instanced - Vertex Buffer Object
//----------------------------------------------
void main() {
	// Vertex Colour
	frag_Colour = vec4(u_Colour, 0.0f);
	//----------------------------------------------
	// Fragment Position
	//----------------------------------------------
	gl_Position = u_Projection * u_View * u_Model * vert_Position;
}
