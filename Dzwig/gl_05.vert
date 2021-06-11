#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aTexCoord;
layout (location = 2) in vec3 aNormal;

const float density = 0.1;
const float grad = 1.5;

out vec2 TexCoord;
out vec3 Normal;
out vec3 FragPos;

out float visibility;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

uniform mat4 transform;

void main()
{
    gl_Position = projection * view * model * vec4(aPos, 1.0f);
	//transform*vec4(aPos,1.0f); //
    FragPos = vec3(model * vec4(aPos, 1.0));
	TexCoord = vec2(aTexCoord.x, 1.0 - aTexCoord.y);
	Normal = mat3(transpose(inverse(model))) * aNormal;  
	//Normal = aNormal;


	//float dist = length((view * model * vec4(aPos, 1.0f)).xyz);
	//visibility = exp(-pow((dist*density),grad));
	//visibility = clamp(visibility,0.0,1.0);

}