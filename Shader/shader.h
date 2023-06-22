#ifndef SHADER_H
#define SHADER_H

#include <glad/glad.h>

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <glm/fwd.hpp>

class Shader
{
public:

	//Program ID
	unsigned int ID;

	//Constructor reads and builds the shader
	Shader(const char* vertexPath, const char* fragmentPath);
	~Shader();
	//use/activate the shader
	void use();
	//Utilities
	void setBool(const std::string& name, bool value) const;
	void setInt(const std::string& name, int value) const;
	void setFloat(const std::string& name, float value) const;
	//void setMat4(const std::string& name, glm::mat4 value) const;

private:

	void checkCompileErrors(unsigned int shader, std::string type);
};

#endif
