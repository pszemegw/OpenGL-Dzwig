#version 330 core

#define MAX_POINT_LIGHTS 128

out vec4 FragColor;

in vec2 TexCoord;
in vec3 Normal;
in vec3 FragPos;

in float visibility;

uniform vec3 lightPos;
uniform vec3 lightColor;
uniform vec3 ambientColor;
uniform sampler2D texture1;
uniform sampler2D texture2;
uniform vec3 fogColor;
uniform vec3 viewPos;

struct Material {
    sampler2D diffuse;
    vec3 specular;    
    float shininess;
}; 

struct Light {
    vec3 position;  
    vec3 direction;
    float cutOff;
    float outerCutOff;
  
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
	
    float constant;
    float linear;
    float quadratic;
};

struct DirLight {
    vec3 direction;
  
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};  

struct PointLight {
    vec3 position;
    
    float constant;
    float linear;
    float quadratic;
	
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

uniform DirLight dirLight;

uniform int numPointL;
uniform PointLight lights[MAX_POINT_LIGHTS];
uniform PointLight cameraLight;


uniform Material material;
uniform Light light;

uniform bool isCamLight;


vec3 CalcPointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir);
vec3 CalcDirLight(DirLight light, vec3 normal, vec3 viewDir);


void main()
{
	//float specularStrength = 0.5;

	vec3 norm = normalize(Normal);
	vec3 viewDir = normalize(viewPos - FragPos);
	vec3 result;

	result = CalcDirLight(dirLight,norm,viewDir);

	for(int i = 0; i < numPointL; i++)
        result += CalcPointLight(lights[i], norm, FragPos, viewDir);  

	if(isCamLight)
		result += CalcPointLight(cameraLight, norm, FragPos, viewDir);

	//float distance    = length(light.position - FragPos); 
	//float attenuation = 1.0 / (
	//light.constant + 
	//light.linear * distance + 
	//light.quadratic * (distance * distance)); 

	
	//vec3 lightDir = normalize(lightPos - FragPos);  
	//float diff = max(dot(norm, lightDir), 0.0);
	//vec3 diffuse = diff * lightColor;

	
	//vec3 reflectDir = reflect(-lightDir, norm); 

	//float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
	//vec3 specular = light.specular * (spec * material.specular);  

	
    //vec3 ambient = ambientStrength * ambientColor;
	//vec3 ambient = light.ambient * texture(material.diffuse, TexCoord).rgb;

	//directionalLight *= attenuation;
	//diffuse   *= attenuation;
    //specular *= attenuation;  

    FragColor = vec4(result ,1.0f);//mix(texture(texture1, TexCoord), texture(texture2, TexCoord), 0);
	//texture(texture1,TexCoord) * (diffuse+specular+directionalLight)

	// FOG

	//FragColor = mix(vec4(fogColor,1.0), FragColor, visibility);
}



vec3 CalcDirLight(DirLight light, vec3 normal, vec3 viewDir)
{
    vec3 lightDir = normalize(-light.direction);
    // diffuse shading
    float diff = max(dot(normal, lightDir), 0.0);
    // specular shading
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    // combine results
    vec3 ambient  = light.ambient  * vec3(texture(material.diffuse, TexCoord));
    vec3 diffuse  = light.diffuse  * diff * vec3(texture(material.diffuse, TexCoord));
    vec3 specular = light.specular * spec * material.specular;
    return (ambient + diffuse + specular);
} 




vec3 CalcPointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir)
{
    vec3 lightDir = normalize(light.position - fragPos);
    // diffuse shading
    float diff = max(dot(normal, lightDir), 0.0);
    // specular shading
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    // attenuation
    float distance = length(light.position - fragPos);
    float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * (distance * distance));    
    // combine results
    vec3 ambient = light.ambient * vec3(texture(material.diffuse, TexCoord));
    vec3 diffuse = light.diffuse * diff * vec3(texture(material.diffuse, TexCoord));
    vec3 specular = light.specular * spec * material.specular;
    ambient *= attenuation;
    diffuse *= attenuation;
    specular *= attenuation;
    return (ambient + diffuse + specular);
}