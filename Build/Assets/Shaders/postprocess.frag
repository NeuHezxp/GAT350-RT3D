#version 430

		#define  INVERT_MASK     (1<<0)
		#define  GRAYSCALE_MASK  (1<<1)
		#define  COLORTINT_MASK  (1<<2)

//in layout(location = 0) vec3 color;
in layout(location = 0) vec2 ftexcoord;
out layout(location = 0) vec4 ocolor;

uniform float blend = 1;
uniform uint params = 0;

layout(binding = 0) uniform sampler2D screenTexture; //add multiple for more textures

vec4 invert(in vec4 color)
{
	
	return vec4(vec3(1)-color.rgb,color.a);
}
vec4 grayscale(in vec4 color)
{
return vec4(vec3((0.2126 * color.r + 0.7152 * color.g + 0.0722 * color.b) / 3),color.a);
}

void main()
{
	vec4 basecolor = texture(screenTexture,ftexcoord );//can make it whatever color u want EX: bbb
	vec4 postprocess = basecolor;
	//vec4 postprocess = invert(basecolor);
	if (bool(params & INVERT_MASK)) postprocess = invert(postprocess);
	if (bool(params & GRAYSCALE_MASK)) postprocess = grayscale(postprocess);
	//if (bool(params & COLORTINT_MASK)) postprocess = colortint(postprocess);
	 postprocess = grayscale(postprocess);
	//if (texcolor.a < 0.8) discard;
	ocolor = mix(basecolor, postprocess, blend);
}
