#version 430 core

layout(location = 0) in vec3 vertex;
layout(location = 1) in vec3 normal;
layout(location = 2) in vec2 uv;

uniform mat4 ProjectionMatrix;
uniform mat4 ModelViewMatrix;
uniform vec3 offset;
uniform vec2 sizelife;

out vec2 vUV;
out float life;

void main(void)
{
	vUV = uv;  	
	float scale = sizelife.x;
	life = sizelife.y;
    gl_Position = ProjectionMatrix * ModelViewMatrix * vec4((vertex + offset)*scale, 1.0f);
    //gl_Position = ProjectionMatrix * vec4((vertex + offset)*scale, 1.0f);
	//gl_Position = vec4(vertex, 1.0f);
}
