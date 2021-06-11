#version 330 core
out vec4 FragColor;

in vec2 TexCoord;
in vec3 Normal;
in vec3 FragPos;

uniform vec3 lightPos;
uniform vec3 lightColor;
uniform sampler2D texture1;
uniform sampler2D texture2;

void main()
{

	vec3 norm = normalize(Normal);
	vec3 lightDir = normalize(lightPos - FragPos);  
	float diff = max(dot(norm, lightDir), 0.0);
	vec3 diffuse = diff * lightColor;

	float ambientStrength = 0.1;
    vec3 ambient = ambientStrength * lightColor;
	vec3 test = vec3(.1f,.1f,.1f);

    FragColor = vec4(texture(texture1,TexCoord) * (ambient+diffuse) ,1.0f);//mix(texture(texture1, TexCoord), texture(texture2, TexCoord), 0);
}

