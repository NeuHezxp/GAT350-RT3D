#version 430


in layout(location = 0) vec3 fposition;
in layout(location = 1) vec3 fnormal;
in layout(location = 2) vec2 ftexcoord;
in layout(location = 3) vec4 fcolor;

out layout(location = 0) vec4 ocolor;

layout(binding = 0) uniform sampler2D tex; //add multiple for more textures

void main()
{
	vec4 texcolor = texture(tex, ftexcoord);//can make it whatever color u want EX: bbb
	ocolor = texcolor * fcolor; // casted to vec4 with alpha 1
}
