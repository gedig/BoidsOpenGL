#include <ShaderProgram.hpp>
ShaderProgram::ShaderProgram() : currentShaders(0), matrixIDSet(false)
{
}

ShaderProgram::ShaderProgram(std::string shaderName, bool & failure, bool geometry) : currentShaders(0), matrixIDSet(false)
{
	failure = !Init(shaderName, geometry);
}

ShaderProgram::~ShaderProgram() {
	glUseProgram(0);

	for (int i = 0; i < currentShaders; i++)
		glDetachShader(programID, shaderIDs[i]);

	glDeleteProgram(programID);

	for (int i = 0; i < currentShaders; i++)
		glDeleteShader(shaderIDs[i]);
}

int ShaderProgram::Init(std::string shaderName, bool geometry) {
	programID = glCreateProgram();

	std::string shaderPath = generated::ShaderPaths::getShaderDirectory();
	if (!LoadShader(shaderPath + shaderName + ".vs.glsl", GL_VERTEX_SHADER))
		return -1;

	if (!LoadShader(shaderPath + shaderName + ".fs.glsl", GL_FRAGMENT_SHADER))
		return -1;

	// Geometry shader is optional
	if (geometry) {
		if (!LoadShader(shaderPath + shaderName + ".gs.glsl", GL_GEOMETRY_SHADER))
			 return -1;
	}

	return LinkShaders();
}

bool ShaderProgram::LoadShader(const std::string &filename, GLenum shaderType) {
	std::cout << "Loading Shader: " << filename << std::endl;

	int shaderID = CreateShader(filename, shaderType);

	if (TryCompileShader(shaderID)) {
		glAttachShader(programID, shaderID);
		shaderIDs[currentShaders++] = shaderID;

		return true;
	}

	return false;
}

void ShaderProgram::SetMatrix(const glm::mat4 mat) {
	if (!matrixIDSet) {
		matrixID = glGetUniformLocation(programID, "mvp");
		matrixIDSet = true;
	}

	glUniformMatrix4fv(matrixID, 1, GL_FALSE, &mat[0][0]);
}

bool ShaderProgram::TryCompileShader(int shaderID) {
	glCompileShader(shaderID);

	int compiled = 0;
	glGetShaderiv(shaderID, GL_COMPILE_STATUS, &compiled);

	if (compiled == false)
		PrintShaderCompilationErrorInfo(shaderID);

	return (compiled != 0);
}

int ShaderProgram::CreateShader(const std::string &filename, GLenum shaderType) {

	std::string str = ReadFile(filename.c_str());

	char* src = const_cast<char*>(str.c_str());
	int32_t size = str.length();

	int shaderID = glCreateShader(shaderType);

	glShaderSource(shaderID, 1, &src, &size);

	return shaderID;
}

bool ShaderProgram::LinkShaders() {
	glLinkProgram(programID);

	int linked = 0;
	glGetProgramiv(programID, GL_LINK_STATUS, (int *)&linked);
	if (linked == false)
		PrintShaderLinkingError(programID);

	return linked != 0;
}

void ShaderProgram::PrintShaderLinkingError(int32_t shaderID) {
	std::cout << "===============================\n";
	std::cout << "Shader linking failed: " << std::endl;

	int maxLength = 0;
	glGetProgramiv(shaderID, GL_INFO_LOG_LENGTH, &maxLength);

	std::cout << "Info Length : " << maxLength << std::endl;

	char* shaderProgramInfoLog = new char[maxLength];
	glGetProgramInfoLog(programID, maxLength, &maxLength, shaderProgramInfoLog);

	std::cout << "Linker error message: " << shaderProgramInfoLog << std::endl;

	// Can handle the error differently here, like printing to a file or displaying a message."
	delete shaderProgramInfoLog;
	return;
}

void ShaderProgram::PrintShaderCompilationErrorInfo(int32_t shaderID) {
	std::cout << "===============================\n";
	std::cout << "Shader compilation failed: " << std::endl;

	int maxLength = 0;
	glGetShaderiv(shaderID, GL_INFO_LOG_LENGTH, &maxLength);

	char* shaderInfoLog = new char[maxLength];
	glGetShaderInfoLog(shaderID, maxLength, &maxLength, shaderInfoLog);

	std::cout << "\tError Info: " << shaderInfoLog << std::endl;

	std::cout << "===============================\n\n";
	delete shaderInfoLog;
}

std::string ShaderProgram::ReadFile(const char * file) {
	std::ifstream t(file);
	std::stringstream buffer;
	buffer << t.rdbuf();

	std::string fileContent = buffer.str();

	return fileContent;
}