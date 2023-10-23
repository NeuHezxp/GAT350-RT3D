#version 430

in layout(location = 0) vec3 vposition;
in layout(location = 1) vec2 vtexcoord;
in layout(location = 2) vec3 vnormal;

out vec3 fposition;
out vec3 fnormal;
out vec2 ftexcoord;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

uniform vec2 tiling;
uniform vec2 offset;

void main()
{
    mat4 modelView = view * model;
    fposition = vec3(modelView * vec4(vposition, 1));
    fnormal = normalize(mat3(modelView) * vnormal);
    ftexcoord = (vtexcoord * tiling) + offset;

    mat4 mvp = projection * view * model;
    gl_Position = mvp * vec4(vposition, 1.0);
}
