#version 430 core

in vec2 vUV;

uniform sampler2D Texture;
uniform float iTime;
uniform bool ishit;

out vec4 vFragColor;

void main()
{
	if(ishit){
		float t = iTime;
		vec4 c = texture2D(Texture,vUV);
		vFragColor = vec4(c.rgb,c.a-t);
	}
	else
		vFragColor = texture2D(Texture,vUV);
}
