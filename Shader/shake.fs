#version 430 core

in vec2 vUV;
uniform float iTime;
uniform sampler2D Texture;
uniform sampler2D finishTexture;
uniform bool isFinish;

float redShift = 100.0;
float greenShift = 50.0;
float blueShift = 15.0;
float aberrationStrength = 0.001;
vec2 iResolution = vec2(800,600);

out vec4 vFragColor;

void main()
{
	vec4 textureColor = texture2D(Texture,vUV);
	const mat3 p = mat3(13.323122,23.5112,21.71123,21.1212,28.7312,11.9312,21.8112,14.7212,61.3934);
	//vec2 uv = vec2(1.,iResolution.y/iResolution.x)*fragCoord.xy / iResolution.xy;
	vec2 uv = vUV;
	vec3 acc = vec3(0.0);
	float dof = 5.*sin(iTime*.1);
	for (int i=0;i<LAYERS;i++) {
		float fi = float(i);
		vec2 q = uv*(1.+fi*DEPTH);
		q += vec2(q.y*(WIDTH*mod(fi*7.238917,1.)-WIDTH*.5),SPEED*iTime/(1.+fi*DEPTH*.03));
		vec3 n = vec3(floor(q),31.189+fi);
		vec3 m = floor(n)*.00001 + fract(n);
		vec3 mp = (31415.9+m)/fract(p*m);
		vec3 r = fract(mp);
		vec2 s = abs(mod(q,1.)-.5+.9*r.xy-.45);
		s += .01*abs(2.*fract(10.*q.yx)-1.); 
		float d = .6*max(s.x-s.y,s.x+s.y)+max(s.x,s.y)-.01;
		float edge = .005+.05*min(.5*abs(fi-5.-dof),1.);
		acc += vec3(smoothstep(edge,-edge,d)*(r.x/(1.+.02*fi*DEPTH)));
	}
	vec4 finalColor = mix(textureColor*2,vec4(vec3(acc),1.0),0.5);
	if(!isFinish)
		vFragColor = finalColor;
	else{
		vec4 c = texture2D(finishTexture,vUV);
		if(c.a==0)
			vFragColor = finalColor;
		else
			vFragColor = c;
	}
	//vFragColor = textureColor;
	//vFragColor = vec4(vec3(acc),1.0);
}


float random (in vec2 st)
{
    return fract(sin(dot(st.xy, vec2(12.9898,78.233)))* 43758.5453123);
}

float noise(in vec2 st)
{
    vec2 i = floor(st);
    vec2 f = fract(st);
    float a = random(i);
    float b = random(i + vec2(1.0, 0.0));
    float c = random(i + vec2(0.0, 1.0));
    float d = random(i + vec2(1.0, 1.0));
    vec2 u = f * f * (3.0 - 2.0 * f);
    return mix(a, b, u.x) + (c - a)* u.y * (1.0 - u.x) + (d - b) * u.x * u.y;
}

#define octaves 3
float fbm(in vec2 p)
{
    float value = 0.0;
    float freq = 1.13;
    float amp = 0.57;    
    for (int i = 0; i < octaves; i++)
    {
        value += amp * (noise((p - vec2(1.0)) * freq));
        freq *= 1.61;
        amp *= 0.47;
    }
    return value;
}

float pat(in vec2 p)
{
    float time = iTime*0.75;
    vec2 aPos = vec2(sin(time * 0.035), sin(time * 0.05)) * 3.;
    vec2 aScale = vec2(3.25);
    float a = fbm(p * aScale + aPos);
    vec2 bPos = vec2(sin(time * 0.09), sin(time * 0.11)) * 1.2;
    vec2 bScale = vec2(0.75);
    float b = fbm((p + a) * bScale + bPos);
    vec2 cPos = vec2(-0.6, -0.5) + vec2(sin(-time * 0.01), sin(time * 0.1)) * 1.9;
    vec2 cScale = vec2(1.25);
    float c = fbm((p + b) * cScale + cPos);
    return c;
}

vec2 Shake(float maxshake, float mag)
{
    float speed = 20.0*mag;
    float shakescale = maxshake * mag;
    
    float time = iTime*speed;			// speed of shake
    
    vec2 p1 = vec2(0.25,0.25);
    vec2 p2 = vec2(0.75,0.75);
    p1 += time;
    p2 += time;
    
    // random shake is just too violent...
    //float val1 = random(p1);
    //float val2 = random(p2);
    
    float val1 = pat(p1);
    float val2 = pat(p2);
    val1 = clamp(val1,0.0,1.0);
    val2 = clamp(val2,0.0,1.0);
    
    return vec2(val1*shakescale,val2*shakescale);
}

void main()
{
	// aber
	vec2 texelSize = vec2(0.01, 0.01) / iResolution.xy;
    
    float uvXOffset = bx2(vUV.x);
    
    float uvXFromCenter = uvXOffset - 5;
    float finalUVX = uvXFromCenter * abs(uvXFromCenter) * aberrationStrength;
    
    float redChannel = texture2D(Texture, vec2(vUV.x + (finalUVX * (redShift * texelSize.x)), vUV.y)).r;
    float greenChannel = texture2D(Texture, vec2(vUV.x + (finalUVX * (greenShift * texelSize.x)), vUV.y)).g;
    float blueChannel = texture2D(Texture, vec2(vUV.x + (finalUVX * (blueShift * texelSize.x)), vUV.y)).b;
        
	vFragColor = vec4(redChannel, greenChannel, blueChannel, 1.0);


    float maxshake = 0.05;				// max shake amount
    float mag = 0.5+sin(iTime)*0.5;		// shake magnitude...

    // *temp* , We will calc shakexy once in the vertex shader...
    vec2 shakexy = Shake(maxshake,mag);
    
	vec2 uv = vUV;
    uv *= 1.0-(maxshake*mag);
    vec3 col = texture(Texture, uv + shakexy).xyz;
    
    vFragColor = vec4(col, 1.0);
}
