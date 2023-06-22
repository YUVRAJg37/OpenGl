#version 330 core
out vec4 FragColor;

in vec2 texCoord;
in vec4 outCol;

uniform sampler2D ourTex;

void main()
{
	FragColor = outCol;
}