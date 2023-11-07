#version 430


in layout(location = 0) vec2 ftexcoord;
out layout(location = 0) vec4 ocolor;


uniform struct Material
{

	vec3 albedo;
	vec2 offset;
	vec2 tiling;
} material;

layout(binding = 0) uniform sampler2D tex; //add multiple for more textures

void main()
{
	vec4 texcolor = texture(tex, ftexcoord);//can make it whatever color u want EX: bbb
	//if (texcolor.a < 0.8) discard;
	if(texcolor.a < 0.5) discard;
	ocolor = texcolor * vec4(material.albedo,1);
}
