#version 430 core

in vec2 vUV;
vec2 tile_num = vec2(8.0,4.0);
vec4 diffuseColor = vec4(1.2,1.2,1.2,1);  

uniform sampler2DArray stand;
uniform sampler2DArray stand_n;
uniform sampler2DArray walk;
uniform sampler2DArray jump;
uniform sampler2DArray attack;
uniform sampler2D Texture;
uniform int status;
uniform int spriteIndex;
uniform vec3 LightPos; 
uniform bool isFinish; 

out vec4 vFragColor;

void main()
{	
	vec2 uv = vUV;
	vec2 uv2 = floor(uv*tile_num)/tile_num;
	vec2 finaluv;

	vec3 uvNormal;
	vec4 textureColor;
	//vec3 LightDir = normalize(vec3(LightPos.xy - vUV.xy,LightPos.z ));
	if(status == 0){
		if(isFinish && (vUV.y >0.5)){			
			uv -= uv2;
			uv *= tile_num;
			finaluv = uv2 + vec2(step(1.0-uv.y,uv.x)/(2.0*tile_num.x),step(uv.x,uv.y)/(2.0*tile_num.y));
			uvNormal = normalize(texture(stand_n, vec3(vec2(1-finaluv.x,finaluv.y),spriteIndex)).bgr);
			textureColor = vec4(texture(stand,vec3(vec2(1-finaluv.x,finaluv.y),spriteIndex)).bgra);	
			vFragColor = vec4(vec4(textureColor *diffuseColor).rgb,textureColor.a);
		}
		else{		
			uvNormal = normalize(texture(stand_n, vec3(vec2(1-vUV.x,vUV.y),spriteIndex)).rgb);
			textureColor = vec4(texture(stand,vec3(vec2(1-vUV.x,vUV.y),spriteIndex)).bgra);
			vFragColor = vec4(vec4(textureColor *diffuseColor).rgb,textureColor.a);
		}
	}		
	if(status == 1){
		if(isFinish && (vUV.y >0.5)){			
			uv -= uv2;
			uv *= tile_num;
			finaluv = uv2 + vec2(step(1.0-uv.y,uv.x)/(2.0*tile_num.x),step(uv.x,uv.y)/(2.0*tile_num.y));
			uvNormal = normalize(texture(stand_n, vec3(vec2(finaluv.x,finaluv.y),spriteIndex)).rgb);
			textureColor = vec4(texture(stand,vec3(vec2(finaluv.x,finaluv.y),spriteIndex)).bgra);
			vFragColor = vec4(vec4(textureColor *diffuseColor).rgb,textureColor.a);
		}else{
			uvNormal = normalize(texture(stand_n, vec3(vec2(vUV.x,vUV.y),spriteIndex)).bgr);
			textureColor = vec4(texture(stand,vec3(vec2(vUV.x,vUV.y),spriteIndex)).bgra);
			vFragColor = vec4(vec4(textureColor *diffuseColor).rgb,textureColor.a);
		}		
	}				
	if(status == 2){
		if(isFinish && (vUV.y >0.5)){
			uv -= uv2;
			uv *= tile_num;
			finaluv = uv2 + vec2(step(1.0-uv.y,uv.x)/(2.0*tile_num.x),step(uv.x,uv.y)/(2.0*tile_num.y));			
			vFragColor = vec4(texture(walk,vec3(vec2(1-finaluv.x,finaluv.y),spriteIndex)).bgra);
		}else{
			vFragColor = vec4(texture(walk,vec3(vec2(1-vUV.x,vUV.y),spriteIndex)).bgra);
		}
	}		
	if(status == 3){
		if(isFinish && (vUV.y >0.5)){
			uv -= uv2;
			uv *= tile_num;
			finaluv = uv2 + vec2(step(1.0-uv.y,uv.x)/(2.0*tile_num.x),step(uv.x,uv.y)/(2.0*tile_num.y));			
			vFragColor = vec4(texture(walk,vec3(vec2(finaluv.x,finaluv.y),spriteIndex)).bgra);
		}else{
			vFragColor = vec4(texture(walk,vec3(vec2(vUV.x,vUV.y),spriteIndex)).bgra);
		}
	}
	if(status == 4){
		if(isFinish && (vUV.y >0.5)){
			uv -= uv2;
			uv *= tile_num;
			finaluv = uv2 + vec2(step(1.0-uv.y,uv.x)/(2.0*tile_num.x),step(uv.x,uv.y)/(2.0*tile_num.y));			
			vFragColor = vec4(texture(jump,vec3(vec2(1-finaluv.x,finaluv.y),spriteIndex)).bgra);
		}else{
			vFragColor = vec4(texture(jump,vec3(vec2(1-vUV.x,vUV.y),spriteIndex)).bgra);
		}
	}		
	if(status == 5){
		if(isFinish && (vUV.y >0.5)){
			uv -= uv2;
			uv *= tile_num;
			finaluv = uv2 + vec2(step(1.0-uv.y,uv.x)/(2.0*tile_num.x),step(uv.x,uv.y)/(2.0*tile_num.y));			
			vFragColor = vec4(texture(jump,vec3(vec2(finaluv.x,finaluv.y),spriteIndex)).bgra);
		}else{
			vFragColor = vec4(texture(jump,vec3(vec2(vUV.x,vUV.y),spriteIndex)).bgra);
		}
	}		
	if(status == 6){
		if(isFinish && (vUV.y >0.5)){
			uv -= uv2;
			uv *= tile_num;
			finaluv = uv2 + vec2(step(1.0-uv.y,uv.x)/(2.0*tile_num.x),step(uv.x,uv.y)/(2.0*tile_num.y));			
			vFragColor = vec4(texture(attack,vec3(vec2(1-finaluv.x,finaluv.y),spriteIndex)).bgra);
		}else{
			vFragColor = vec4(texture(attack,vec3(vec2(1-vUV.x,vUV.y),spriteIndex)).bgra);
		}
	}		
	if(status == 7){
		if(isFinish && (vUV.y >0.5)){
			uv -= uv2;
			uv *= tile_num;
			finaluv = uv2 + vec2(step(1.0-uv.y,uv.x)/(2.0*tile_num.x),step(uv.x,uv.y)/(2.0*tile_num.y));			
			vFragColor = vec4(texture(attack,vec3(vec2(finaluv.x,finaluv.y),spriteIndex)).bgra);
		}else{
			vFragColor = vec4(texture(attack,vec3(vec2(vUV.x,vUV.y),spriteIndex)).bgra);
		}
	}		
}
