#include "Shader.h"

/*
	Load shader code from a file
*/

void check_compile_Error(GLuint object, GLboolean compile, const GLchar * name) {
	static GLchar infoLog[512];
	GLint success;
	if (compile) {
		glGetShaderiv(object, GL_COMPILE_STATUS, &success);
		if (!success)
		{
			glGetShaderInfoLog(object, 512, NULL, infoLog);
			fprintf(stderr, "ERROR::VERTEX::COMPILATION_FAILED Name: %s\n", name);
		};
	}
	else {
		glGetProgramiv(object, GL_LINK_STATUS, &success);
		if (!success)
		{
			glGetProgramInfoLog(object, 1024, NULL, infoLog);
			fprintf(stderr, "ERROR::Shader: LINK_TIME ERROR Name: %s\n-----------------------------------------\n",
				name);
		}
	}
}

GLchar * get_all_string(const GLchar * path) {

	FILE * file = fopen(path, "r");
	size_t buf_size = 4096;
	GLchar * buffer = (GLchar *)malloc(sizeof(GLchar) * buf_size);
	if (!buffer)
	{
		fprintf(stderr, "out of memory\n");
		return nullptr;
	}
	int c;
	int counter = 0;
	while ((c = fgetc(file)) != EOF) {
		if (counter >= buf_size - 1) {
			// ¶¯Ì¬À©Õ¹»º³åÇø
			buf_size *= 2;
			buffer = (GLchar *)realloc(buffer, sizeof(GLchar) * buf_size);
			if (!buffer)
			{
				fprintf(stderr, "out of memory\n");
				return nullptr;
			}
		}
		buffer[counter++] = c;
	}
	// ×Ö·û´®½áÎ²
	buffer[counter++] = '\0';
	fclose(file);

	return buffer;
}

/*
	Compile shaders
	@return The id of the shader program
*/
void Shader::load_shader(const GLchar * vShaderCode, const GLchar * fShaderCode) {

	GLuint vertex, fragment;
	GLint success;
	GLchar infoLog[512];
	const GLchar * vShaderText = vShaderCode;
	const GLchar * fShaderText = fShaderCode;


	// Creaate and compile vertex shader
	vertex = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertex, 1, &vShaderText, nullptr);
	glCompileShader(vertex);

	// print compile errors if any
	check_compile_Error(vertex, true, "Vertex Shader");

	// Creaate and compile fragment shader
	fragment = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragment, 1, &fShaderText, nullptr);
	glCompileShader(fragment);

	// print compile errors if any
	glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);
	check_compile_Error(vertex, true, "Fragment Shader");

	// Create and link shader Program
	this->ID = glCreateProgram();
	glAttachShader(this->ID, vertex);
	glAttachShader(this->ID, fragment);
	glLinkProgram(this->ID);

	// Print linking errors if any
	check_compile_Error(this->ID, false, "LINKING");

	// Delete the shaders as they're linked into our program now and no longer necessery
	glDeleteShader(vertex);
	glDeleteShader(fragment);
}


Shader::Shader(const GLchar * vertexPath, const GLchar * fragmentPath)
{
	load_shader(get_all_string(vertexPath), get_all_string(fragmentPath));
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

void Shader::setVec3(const std::string & name, glm::vec3 value) const
{
	glUniform3f(glGetUniformLocation(this->ID, name.c_str()), value.x, value.y, value.z);
}

void Shader::setMat4(const std::string & name, glm::mat4 mat) const
{
	glUniformMatrix4fv(glGetUniformLocation(this->ID, name.c_str()), 1, GL_FALSE, glm::value_ptr(mat));
}

