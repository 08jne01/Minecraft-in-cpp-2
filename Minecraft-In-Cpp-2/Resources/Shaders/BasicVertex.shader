#version 460 core
layout(location = 0) in vec3 vertexPositions;
layout(location = 1) in vec2 texCoord;

out vec2 v_TexCoord;

uniform mat4 projMatrix;
uniform mat4 viewMatrix;
uniform mat4 modelMatrix;

void main()

{
	gl_Position = projMatrix*viewMatrix*modelMatrix*vec4(vertexPositions, 1.0);
	v_TexCoord = texCoord;
}