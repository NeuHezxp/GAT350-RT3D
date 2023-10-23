#version 430

// Input variables from vertex shader. These are interpolated values for each fragment.
in vec3 fposition;  // Fragment position in view space
in vec3 fnormal;    // Fragment normal in view space
in vec2 ftexcoord;  // Texture coordinates for the fragment

// Output color to the framebuffer
out vec4 ocolor;

// Material properties, defined in a struct for organization
uniform struct Material {
    vec3 diffuse;    // Base color of the material
    vec3 specular;   // Highlight color of the material
    float shininess; // Shininess factor, higher values give smaller, sharper highlights
} material;

// Light properties, also defined in a struct
uniform struct Light {
    vec3 position; // Position of the light source in view space
    vec3 color;    // Color of the light
} light;

// Ambient light color. This light is uniform and comes from all directions.
uniform vec3 ambientLight;

// Camera position in view space. Needed for specular reflection calculations.
uniform vec3 cameraPosition;

// Texture sampler for applying textures to the material
layout(binding = 0) uniform sampler2D tex;

void main()
{
    // Normalize the interpolated normal vector. Important for accurate lighting.
    vec3 normal = normalize(fnormal);

    // Calculate the direction vector from the fragment to the light source.
    vec3 lightDir = normalize(light.position - fposition);

    // Ambient Lighting: Constant color added to the fragment.
    // Affects the whole fragment uniformly.
    vec3 ambient = ambientLight;

    // Diffuse Lighting: Dependent on the angle between the light direction and fragment normal.
    // Affects how "bright" the fragment appears.
    float intensity = max(dot(lightDir, normal), 0.0);
    vec3 diffuse = material.diffuse * light.color * intensity;

    // Specular Lighting: Creates highlights on the fragment.
    // Dependent on the angle between the reflection of the light direction and the view direction.
    vec3 viewDir = normalize(cameraPosition - fposition);
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    vec3 specular = material.specular * spec;

    // Combine all lighting components to get the final color for this fragment.
    // Each component (ambient, diffuse, specular) contributes to the final color.
    vec3 result = ambient + diffuse + specular;

    // Sample the color from the texture at the given texture coordinates.
    // This allows us to map images onto geometry.
    vec4 texcolor = texture(tex, ftexcoord);

    // Multiply the texture color with the calculated lighting to get the final color.
    // This is the color that will be written to the framebuffer.
    ocolor = texcolor * vec4(result, 1.0);
}
