#include "Shader.h"

/*
	Load shader code from a file
*/
std::string get_all_string(const std::string & path) {
	std::string result;
	std::ifstream file;
	try {
		// Open the file
		file.open(path);

		// Read the string
		std::stringstream fileSS;
		fileSS << file.rdbuf();

		// Close file handle
		file.close();

		// Get the result string
		result = fileSS.str();
	}
	catch (std::ifstream::failure e) {
		std::cerr << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ > " << path 
			<< std::endl << e.what() << std::endl;
	}

	return result;
}

/*
	Compile shaders
	@return The id of the shader program
*/
void Shader::load_shader(const std::string& vShaderCode, const std::string& fShaderCode) {

	GLuint vertex, fragment;
	GLint success;
	GLchar infoLog[512];
	const GLchar * vShaderText = vShaderCode.c_str();
	const GLchar * fShaderText = fShaderCode.c_str();


	// Creaate and compile vertex shader
	vertex = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertex, 1, &vShaderText, nullptr);
	glCompileShader(vertex);

	// print compile errors if any
	glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(vertex, 512, NULL, infoLog);
		std::cerr << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
	};

	// Creaate and compile fragment shader
	fragment = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragment, 1, &fShaderText, nullptr);
	glCompileShader(fragment);

	// print compile errors if any
	glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(fragment, 512, NULL, infoLog);
		std::cerr << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
	};

	// Create and link shader Program
	this->ID = glCreateProgram();
	glAttachShader(this->ID, vertex);
	glAttachShader(this->ID, fragment);
	glLinkProgram(this->ID);

	// Print linking errors if any
	glGetProgramiv(this->ID, GL_LINK_STATUS, &success);
	if (!success)
	{
		glGetProgramInfoLog(this->ID, 512, NULL, infoLog);
		std::cerr << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
	}

	// Delete the shaders as they're linked into our program now and no longer necessery
	glDeleteShader(vertex);
	glDeleteShader(fragment);
}


Shader::Shader(const std::string & vertexPath, const std::string & fragmentPath)
{
	std::string vShaderCode = get_all_string(vertexPath);
	std::string fShaderCode = get_all_string(fragmentPath);

	load_shader(vShaderCode, fShaderCode);

}


void Shader::setBool(const std::string & name, GLboolean value) const
{
	glUniform1i(glGetUniformLocation(this->ID, name.c_str()), (int)value);
}

void Shader::setInt(const std::string & name, GLint value) const
{
	glUniform1i(glGetUniformLocation(this->ID, name.c_str()), value);
}

void Shader::setFloat(const std::string & name, GLfloat value) const
{
	glUniform1f(glGetUniformLocation(this->ID, name.c_str()), value);
}
