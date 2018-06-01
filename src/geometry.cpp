// Project Header
#include "geometry.h"

// --------------------------------------------------------------------------------
// Create Blade of Grass - Positions, Normals, Colours
void createBlade(std::vector<glm::vec4> &buffer, std::vector<glm::ivec3> &indexes) {
	// Top - 0
	buffer.push_back(glm::vec4( 0.0f,  1.0f,  0.0f,  1.0f));
	buffer.push_back(glm::vec4( 0.0f,  0.0f,  1.0f,  0.0f));
	buffer.push_back(glm::vec4( 0.0f,  0.48f, 0.05f, 0.0f));

	// Top - Left - 1
	buffer.push_back(glm::vec4(-0.03f, 0.9f,  0.01f, 1.0f));
	buffer.push_back(glm::vec4(-0.5f,  0.0f,  0.5f,  0.0f));
	buffer.push_back(glm::vec4( 0.0f,  0.48f, 0.05f, 0.0f));

	// Top - Right - 2
	buffer.push_back(glm::vec4( 0.03f, 0.9f,  0.01f, 1.0f));
	buffer.push_back(glm::vec4( 0.5f,  0.0f,  0.5f,  0.0f));
	buffer.push_back(glm::vec4( 0.0f,  0.48f, 0.05f, 0.0f));

	// Top - Back - 3
	buffer.push_back(glm::vec4( 0.0f,  0.9f, -0.01f, 1.0f));
	buffer.push_back(glm::vec4( 0.0f,  0.0f, -1.0f,  0.0f));
	buffer.push_back(glm::vec4( 0.0f,  0.48f, 0.05f, 0.0f));

	// Mid - Left - 4
	buffer.push_back(glm::vec4(-0.05f, 0.7f,  0.01f, 1.0f));
	buffer.push_back(glm::vec4(-0.5f,  0.0f,  0.5f,  0.0f));
	buffer.push_back(glm::vec4( 0.0f,  0.48f, 0.05f, 0.0f));

	// Mid - Right - 5
	buffer.push_back(glm::vec4( 0.05f, 0.7f,  0.01f, 1.0f));
	buffer.push_back(glm::vec4( 0.5f,  0.0f,  0.5f,  0.0f));
	buffer.push_back(glm::vec4( 0.0f,  0.48f, 0.05f, 0.0f));

	// Mid - Back - 6
	buffer.push_back(glm::vec4( 0.0f,  0.7f, -0.01f, 1.0f));
	buffer.push_back(glm::vec4( 0.0f,  0.0f, -1.0f,  0.0f));
	buffer.push_back(glm::vec4( 0.0f,  0.48f, 0.05f, 0.0f));

	// Bottom - Left - 7
	buffer.push_back(glm::vec4(-0.05f, 0.0f,  0.01f, 1.0f));
	buffer.push_back(glm::vec4(-0.5f,  0.0f,  0.5f,  0.0f));
	buffer.push_back(glm::vec4( 0.0f,  0.48f, 0.05f, 0.0f));

	// Bottom - Right - 8
	buffer.push_back(glm::vec4( 0.05f, 0.0f,  0.01f, 1.0f));
	buffer.push_back(glm::vec4( 0.5f,  0.0f,  0.5f,  0.0f));
	buffer.push_back(glm::vec4( 0.0f,  0.48f, 0.05f, 0.0f));

	// Bottom - Back - 9
	buffer.push_back(glm::vec4( 0.0f,  0.0f, -0.01f, 1.0f));
	buffer.push_back(glm::vec4( 0.0f,  0.0f, -1.0f,  0.0f));
	buffer.push_back(glm::vec4( 0.0f,  0.48f, 0.05f, 0.0f));

	// Indexes
	indexes.push_back(glm::ivec3(0, 1, 2));
	indexes.push_back(glm::ivec3(0, 2, 3));
	indexes.push_back(glm::ivec3(0, 3, 1));

	indexes.push_back(glm::ivec3(1, 4, 5));
	indexes.push_back(glm::ivec3(1, 5, 2));
	indexes.push_back(glm::ivec3(2, 5, 6));
	indexes.push_back(glm::ivec3(2, 6, 3));
	indexes.push_back(glm::ivec3(3, 6, 4));
	indexes.push_back(glm::ivec3(3, 4, 1));

	indexes.push_back(glm::ivec3(4, 7, 8));
	indexes.push_back(glm::ivec3(4, 8, 5));
	indexes.push_back(glm::ivec3(5, 8, 9));
	indexes.push_back(glm::ivec3(5, 9, 6));
	indexes.push_back(glm::ivec3(6, 9, 7));
	indexes.push_back(glm::ivec3(6, 7, 4));
}

// Create Cube with Positions and Normals
void createCube(std::vector<glm::vec4> &buffer, std::vector<glm::ivec3> &indexes) {
	// ---- Top ----
	// Left-Top-Back - 0
	buffer.push_back(glm::vec4(-1.0f,  1.0f, -1.0f,  1.0f)); // Position
	buffer.push_back(glm::vec4( 0.0f,  1.0f,  0.0f,  0.0f)); // Normal
	buffer.push_back(glm::vec4( 1.0f,  1.0f,  1.0f,  0.0f)); // Colour

	// Right-Top-Back - 1
	buffer.push_back(glm::vec4( 1.0f,  1.0f, -1.0f,  1.0f));
	buffer.push_back(glm::vec4( 0.0f,  1.0f,  0.0f,  0.0f));
	buffer.push_back(glm::vec4( 1.0f,  1.0f,  1.0f,  0.0f));

	// Left-Top-Front - 2
	buffer.push_back(glm::vec4(-1.0f,  1.0f,  1.0f,  1.0f));
	buffer.push_back(glm::vec4( 0.0f,  1.0f,  0.0f,  0.0f));
	buffer.push_back(glm::vec4( 1.0f,  1.0f,  1.0f,  0.0f));

	// Right-Top-Front - 3
	buffer.push_back(glm::vec4( 1.0f,  1.0f,  1.0f,  1.0f));
	buffer.push_back(glm::vec4( 0.0f,  1.0f,  0.0f,  0.0f));
	buffer.push_back(glm::vec4( 1.0f,  1.0f,  1.0f,  0.0f));

	// Top
	indexes.push_back(glm::ivec3(0, 2, 3));
	indexes.push_back(glm::ivec3(0, 3, 1));


	// ---- Bottom ----
	// Left-Bottom-Back - 4
	buffer.push_back(glm::vec4(-1.0f, -1.0f, -1.0f,  1.0f));
	buffer.push_back(glm::vec4( 0.0f, -1.0f,  0.0f,  0.0f));
	buffer.push_back(glm::vec4( 1.0f,  1.0f,  1.0f,  0.0f));

	// Right-Bottom-Back - 5
	buffer.push_back(glm::vec4( 1.0f, -1.0f, -1.0f,  1.0f));
	buffer.push_back(glm::vec4( 0.0f, -1.0f,  0.0f,  0.0f));
	buffer.push_back(glm::vec4( 1.0f,  1.0f,  1.0f,  0.0f));

	// Left-Bottom-Front - 6
	buffer.push_back(glm::vec4(-1.0f, -1.0f,  1.0f,  1.0f));
	buffer.push_back(glm::vec4( 0.0f, -1.0f,  0.0f,  0.0f));
	buffer.push_back(glm::vec4( 1.0f,  1.0f,  1.0f,  0.0f));

	// Right-Bottom-Front - 7
	buffer.push_back(glm::vec4( 1.0f, -1.0f,  1.0f,  1.0f));
	buffer.push_back(glm::vec4( 0.0f, -1.0f,  0.0f,  0.0f));
	buffer.push_back(glm::vec4( 1.0f,  1.0f,  1.0f,  0.0f));

	// Bottom
	indexes.push_back(glm::ivec3(4, 6, 7));
	indexes.push_back(glm::ivec3(4, 7, 5));

	// ---- Left ----
	// Left-Top-Back - 8
	buffer.push_back(glm::vec4(-1.0f,  1.0f, -1.0f,  1.0f));
	buffer.push_back(glm::vec4(-1.0f,  0.0f,  0.0f,  0.0f));
	buffer.push_back(glm::vec4( 1.0f,  1.0f,  1.0f,  0.0f));

	// Left-Bottom-Back - 9
	buffer.push_back(glm::vec4(-1.0f, -1.0f, -1.0f,  1.0f));
	buffer.push_back(glm::vec4(-1.0f,  0.0f,  0.0f,  0.0f));
	buffer.push_back(glm::vec4( 1.0f,  1.0f,  1.0f,  0.0f));

	// Left-Top-Front - 10
	buffer.push_back(glm::vec4(-1.0f,  1.0f,  1.0f,  1.0f));
	buffer.push_back(glm::vec4(-1.0f,  0.0f,  0.0f,  0.0f));
	buffer.push_back(glm::vec4( 1.0f,  1.0f,  1.0f,  0.0f));

	// Left-Bottom-Front - 11
	buffer.push_back(glm::vec4(-1.0f, -1.0f,  1.0f,  1.0f));
	buffer.push_back(glm::vec4(-1.0f,  0.0f,  0.0f,  0.0f));
	buffer.push_back(glm::vec4( 1.0f,  1.0f,  1.0f,  0.0f));

	// Left
	indexes.push_back(glm::ivec3(8,  9, 11));
	indexes.push_back(glm::ivec3(8, 11, 10));


	// ---- Right ----
	// Right-Top-Back - 12
	buffer.push_back(glm::vec4( 1.0f,  1.0f, -1.0f,  1.0f));
	buffer.push_back(glm::vec4( 1.0f,  0.0f,  0.0f,  0.0f));
	buffer.push_back(glm::vec4( 1.0f,  1.0f,  1.0f,  0.0f));

	// Right-Bottom-Back - 13
	buffer.push_back(glm::vec4( 1.0f, -1.0f, -1.0f,  1.0f));
	buffer.push_back(glm::vec4( 1.0f,  0.0f,  0.0f,  0.0f));
	buffer.push_back(glm::vec4( 1.0f,  1.0f,  1.0f,  0.0f));

	// Right-Top-Front - 14
	buffer.push_back(glm::vec4( 1.0f,  1.0f,  1.0f,  1.0f));
	buffer.push_back(glm::vec4( 1.0f,  0.0f,  0.0f,  0.0f));
	buffer.push_back(glm::vec4( 1.0f,  1.0f,  1.0f,  0.0f));

	// Right-Bottom-Front - 15
	buffer.push_back(glm::vec4( 1.0f, -1.0f,  1.0f,  1.0f));
	buffer.push_back(glm::vec4( 1.0f,  0.0f,  0.0f,  0.0f));
	buffer.push_back(glm::vec4( 1.0f,  1.0f,  1.0f,  0.0f));

	// Right
	indexes.push_back(glm::ivec3(14, 15, 13));
	indexes.push_back(glm::ivec3(14, 13, 12));


	// ---- Front ----
	// Left-Top-Front - 16
	buffer.push_back(glm::vec4(-1.0f,  1.0f,  1.0f,  1.0f));
	buffer.push_back(glm::vec4( 0.0f,  0.0f,  1.0f,  0.0f));
	buffer.push_back(glm::vec4( 1.0f,  1.0f,  1.0f,  0.0f));

	// Right-Top-Front - 17
	buffer.push_back(glm::vec4( 1.0f,  1.0f,  1.0f,  1.0f));
	buffer.push_back(glm::vec4( 0.0f,  0.0f,  1.0f,  0.0f));
	buffer.push_back(glm::vec4( 1.0f,  1.0f,  1.0f,  0.0f));

	// Left-Bottom-Front - 18
	buffer.push_back(glm::vec4(-1.0f, -1.0f,  1.0f,  1.0f));
	buffer.push_back(glm::vec4( 0.0f,  0.0f,  1.0f,  0.0f));
	buffer.push_back(glm::vec4( 1.0f,  1.0f,  1.0f,  0.0f));

	// Right-Bottom-Front - 19
	buffer.push_back(glm::vec4( 1.0f, -1.0f,  1.0f,  1.0f));
	buffer.push_back(glm::vec4( 0.0f,  0.0f,  1.0f,  0.0f));
	buffer.push_back(glm::vec4( 1.0f,  1.0f,  1.0f,  0.0f));

	// Front
	indexes.push_back(glm::ivec3(16, 18, 19));
	indexes.push_back(glm::ivec3(16, 19, 17));


	// ---- Back ----
	// Left-Top-Back - 20
	buffer.push_back(glm::vec4(-1.0f,  1.0f, -1.0f,  1.0f));
	buffer.push_back(glm::vec4( 0.0f,  0.0f, -1.0f,  0.0f));
	buffer.push_back(glm::vec4( 1.0f,  1.0f,  1.0f,  0.0f));

	// Right-Top-Back - 21
	buffer.push_back(glm::vec4( 1.0f,  1.0f, -1.0f,  1.0f));
	buffer.push_back(glm::vec4( 0.0f,  0.0f, -1.0f,  0.0f));
	buffer.push_back(glm::vec4( 1.0f,  1.0f,  1.0f,  0.0f));

	// Left-Bottom-Back - 22
	buffer.push_back(glm::vec4(-1.0f, -1.0f, -1.0f,  1.0f));
	buffer.push_back(glm::vec4( 0.0f,  0.0f, -1.0f,  0.0f));
	buffer.push_back(glm::vec4( 1.0f,  1.0f,  1.0f,  0.0f));

	// Right-Bottom-Back - 23
	buffer.push_back(glm::vec4( 1.0f, -1.0f, -1.0f,  1.0f));
	buffer.push_back(glm::vec4( 0.0f,  0.0f, -1.0f,  0.0f));
	buffer.push_back(glm::vec4( 1.0f,  1.0f,  1.0f,  0.0f));

	// Back
	indexes.push_back(glm::ivec3(21, 23, 22));
	indexes.push_back(glm::ivec3(21, 22, 20));
}

// --------------------------------------------------------------------------------
// Create Ground - Positions, Normals, Colours
void createGround(std::vector<glm::vec4> &buffer, std::vector<glm::ivec3> &indexes) {
	// Left-Front - 0
	buffer.push_back(glm::vec4(-1.0f,  0.0f,  1.0f,  1.0f));
	buffer.push_back(glm::vec4( 0.0f,  1.0f,  0.0f,  0.0f));
	buffer.push_back(glm::vec4( 0.38f, 0.25f, 0.06f, 0.0f));

	// Right-Front - 1
	buffer.push_back(glm::vec4( 1.0f,  0.0f,  1.0f,  1.0f));
	buffer.push_back(glm::vec4( 0.0f,  1.0f,  0.0f,  0.0f));
	buffer.push_back(glm::vec4( 0.38f, 0.25f, 0.06f, 0.0f));

	// Right-Back - 2
	buffer.push_back(glm::vec4( 1.0f,  0.0f, -1.0f,  1.0f));
	buffer.push_back(glm::vec4( 0.0f,  1.0f,  0.0f,  0.0f));
	buffer.push_back(glm::vec4( 0.38f, 0.25f, 0.06f, 0.0f));

	// Left-Back - 3
	buffer.push_back(glm::vec4(-1.0f,  0.0f, -1.0f,  1.0f));
	buffer.push_back(glm::vec4( 0.0f,  1.0f,  0.0f,  0.0f));
	buffer.push_back(glm::vec4( 0.38f, 0.25f, 0.06f, 0.0f));

	// Front
	indexes.push_back(glm::ivec3(0, 1, 2));
	indexes.push_back(glm::ivec3(0, 2, 3));
}
