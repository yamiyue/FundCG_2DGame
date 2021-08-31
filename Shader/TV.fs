#version 430 core

in vec2 vUV;

uniform sampler2D Texture;
uniform float iTime;
uniform bool ishit;

out vec4 vFragColor;

void main()
{
	vFragColor = texture2D(Texture,vUV);
}
