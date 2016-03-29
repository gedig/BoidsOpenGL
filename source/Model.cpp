#include "Model.hpp"

#include "AssetPaths.hpp"

Model::Model() : positionAttributeIndex(0), colourAttributeIndex(1)
{
}

Model::~Model() {
	glDeleteBuffers(2, vbo);
	glDeleteVertexArrays(1, vao);
}

int Model::Init(std::string modelName) {
	if (SetupBufferObjects(modelName) && shader.Init(modelName))
		return 1;
	else
		return -1;
}

void Model::SetMatrix(glm::mat4 mvp) {
	shader.UseProgram();
	shader.SetMatrix(mvp);
}

void Model::Update() {
	// TODO-DG: Any updates that have to go in here.
}

void Model::Render() const {
	// Enable and bind our positions
	glEnableVertexAttribArray(positionAttributeIndex);
	glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
	glVertexAttribPointer(positionAttributeIndex, 3, GL_FLOAT, GL_FALSE, 0, 0);

	// Enable and bind our colours
	glEnableVertexAttribArray(colourAttributeIndex);
	glBindBuffer(GL_ARRAY_BUFFER, vbo[1]);
	glVertexAttribPointer(colourAttributeIndex, 4, GL_FLOAT, GL_FALSE, 0, 0);

	glDrawArrays(GL_TRIANGLES, 0, positions.size() / 3);
	glDisableVertexAttribArray(positionAttributeIndex);
	glDisableVertexAttribArray(colourAttributeIndex);
}

bool Model::SetupBufferObjects(std::string modelName) {
	std::string assetPath = generated::AssetPaths::getAssetDirectory();
	positions = ReadFile((assetPath + modelName + ".mdl").c_str());
	colours = ReadFile((assetPath + modelName+".col").c_str());

	glGenBuffers(2, vbo);
	glGenVertexArrays(1, vao);
	glBindVertexArray(vao[0]);

	// Bind the points of the model.
	glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
	glBufferData(GL_ARRAY_BUFFER, positions.size() * sizeof(GLfloat), &positions[0], GL_STATIC_DRAW);
	glVertexAttribPointer(positionAttributeIndex, 3, GL_FLOAT, GL_FALSE, 0, 0);

	// Bind colors
	glBindBuffer(GL_ARRAY_BUFFER, vbo[1]);
	glBufferData(GL_ARRAY_BUFFER, colours.size() * sizeof(GLfloat), &colours[0], GL_STATIC_DRAW);
	glVertexAttribPointer(colourAttributeIndex, 4, GL_FLOAT, GL_FALSE, 0, 0);

	return true;
}