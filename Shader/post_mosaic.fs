#version 430 core

in vec2 vUV;
vec2 tile_num = vec2(40.0,20.0);
vec2 iResolution = vec2(800,600);
uniform sampler2D Texture;
out vec4 vFragColor;

void main( )
{
	vec2 uv = vUV;
	vec2 uv2 = floor(uv*tile_num)/tile_num;
    uv -= uv2;
    uv *= tile_num;
	vFragColor = texture2D( Texture, uv2 + vec2(step(1.0-uv.y,uv.x)/(2.0*tile_num.x),
        											                                            
        											step(uv.x,uv.y)/(2.0*tile_num.y)
                                                    
                                                   ) );										   
}