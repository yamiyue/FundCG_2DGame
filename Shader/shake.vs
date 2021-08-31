#version 430 core

layout(location = 0) in vec3 vertex;
layout(location = 1) in vec3 normal;
layout(location = 2) in vec2 uv;

uniform mat4 ProjectionMatrix;
uniform mat4 ModelViewMatrix;
uniform vec3 Offset;
uniform vec3 Scale;

out vec2 vUV;

void main(void)
{
	vUV = uv;    
    vec4 pos = ProjectionMatrix * ModelViewMatrix *  vec4(vertex*Scale + Offset,1);
	//gl_Position = pos.xyww;
	gl_Position = pos;
}
