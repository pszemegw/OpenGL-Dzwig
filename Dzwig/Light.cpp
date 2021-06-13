#include "Light.h"


Light::Light(ShaderProgram * s, glm::vec3 dirl_dir, glm::vec3 dirl_amb, glm::vec3 dirl_dif, glm::vec3 dirl_spec, int m_dif, GLfloat m_shine, glm::vec3 m_spec)
{
	shader = s;
	dirLight_direction = dirl_dir; dirLight_ambient = dirl_amb; dirLight_diffuse = dirl_dif; dirLight_specular = dirl_spec;
	material_shininess = m_shine; material_specular = m_spec; material_diffuse = m_dif;


}

void Light::setShaderParams()
{
	shader->setVec3("dirLight.direction", dirLight_direction);
	shader->setVec3("dirLight.ambient", dirLight_ambient);
	shader->setVec3("dirLight.diffuse", dirLight_diffuse);
	shader->setVec3("dirLight.specular", dirLight_specular);

	shader->setInt("material.diffuse", material_diffuse);
	shader->setVec3("material.specular", material_specular);
	shader->setFloat("material.shininess", material_shininess);

	shader->setInt("numPointL", lights.size());
	for (int i = 0; i < lights.size(); ++i)
	{
		//std::cout << "X: " << i << std::endl;
		shader->setVec3("lights[" + to_string(i) + "].position", lights[i].position);
		shader->setFloat("lights[" + to_string(i) + "].constant", lights[i].constant);
		shader->setFloat("lights[" + to_string(i) + "].linear", lights[i].linear);
		shader->setFloat("lights[" + to_string(i) + "].quadratic", lights[i].quadratic);
		shader->setVec3("lights[" + to_string(i) + "].ambient", lights[i].ambient);
		shader->setVec3("lights[" + to_string(i) + "].diffuse", lights[i].diffuse);
		shader->setVec3("lights[" + to_string(i) + "].specular", lights[i].specular);
	}

	shader->setBool("isCamLight", isCameraLightEnabled);
	if (isCameraLightEnabled) 
	{
		shader->setVec3("cameraLight.position", cameraLight.position);
		shader->setFloat("cameraLight.constant", cameraLight.constant);
		shader->setFloat("cameraLight.linear", cameraLight.linear);
		shader->setFloat("cameraLight.quadratic", cameraLight.quadratic);
		shader->setVec3("cameraLight.ambient", cameraLight.ambient);
		shader->setVec3("cameraLight.diffuse", cameraLight.diffuse);
		shader->setVec3("cameraLight.specular", cameraLight.specular);
	}
}

void Light::addLight(glm::vec3 position, GLfloat constant, GLfloat linear, GLfloat quadratic, glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular)
{
	lights.push_back({ position,constant,linear,quadratic,ambient,diffuse,specular });
}

void Light::setCameraLight(glm::vec3 *position, GLfloat constant, GLfloat linear, GLfloat quadratic, glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular)
{
	cameraLight.position = *position;
	cameraLight.constant = constant;
	cameraLight.linear = linear;
	cameraLight.quadratic = quadratic;
	cameraLight.ambient = ambient;
	cameraLight.diffuse = diffuse;
	cameraLight.specular = specular;
}

void Light::cameraLightIntensityInc(GLfloat di)
{
	//cameraLight.constant -= di;
	//cameraLight.linear -= di;
	cameraLight.quadratic -= di;
	cameraLight.linear -= glm::sqrt(abs(di));
	//if (cameraLight.constant < 0.05f) cameraLight.constant = 0.05;
	if (cameraLight.quadratic < 0.0001f) cameraLight.quadratic = 0.0001f;
	if (cameraLight.quadratic > 200.0f) cameraLight.quadratic = 200.00f;

	if (cameraLight.linear < 0.0001f) cameraLight.linear = 0.0001f;
	if (cameraLight.linear > 200.0f) cameraLight.linear = 200.00f;
	//if (cameraLight.linear < 0.01f) cameraLight.linear = 0.01f;
}

void Light::updateCameraPosition(glm::vec3* pos)
{
	cameraLight.position = *pos;
}

void Light::toggleCameraLight()
{
	isCameraLightEnabled = !isCameraLightEnabled;
}

GLuint Light::getNumberOfPointLights()
{
	return lights.size();
}

glm::vec3 Light::getPointLightPos(GLuint index)
{
	if (index >= lights.size()) return glm::vec3(0.f);
	return lights[index].position;
}

void Light::updatePointLightPos(GLuint index, glm::vec3 pos)
{
	if (index >= lights.size()) return;
	lights[index].position.x = pos.x;
	lights[index].position.y = pos.y;
	lights[index].position.z = pos.z;
	setShaderParams();
}
