#include "Box.h"

Box::Box()
{
}
void Box::DimensionTransformation(GLfloat source[],GLfloat target[][4])
{
	//for uniform value, transfer 1 dimension to 2 dimension
	int i = 0;
	for(int j=0;j<4;j++)
		for(int k=0;k<4;k++)
		{
			target[j][k] = source[i];
			i++;
		}
}
void Box::Begin(int programIndex)
{
	shaderProgram = shaderPrograms[programIndex];
	shaderProgram->bind();
	vao.bind();
}
void Box::Paint(GLfloat* ProjectionMatrix, GLfloat* ModelViewMatrix)
{
	GLfloat P[4][4];
	GLfloat MV[4][4];

	DimensionTransformation(ProjectionMatrix,P);
	DimensionTransformation(ModelViewMatrix,MV);

	//pass projection matrix to shader
	shaderProgram->setUniformValue("ProjectionMatrix",P);
	//pass modelview matrix to shader
	shaderProgram->setUniformValue("ModelViewMatrix",MV);

	vvbo.bind();
	shaderProgram->enableAttributeArray(0);
	shaderProgram->setAttributeArray(0, GL_FLOAT, 0, 3, NULL);
	vvbo.release();

	nvbo.bind();
	shaderProgram->enableAttributeArray(1);
	shaderProgram->setAttributeArray(1, GL_FLOAT, 0, 3, NULL);
	nvbo.release();

	uvbo.bind();
	shaderProgram->enableAttributeArray(2);
	shaderProgram->setAttributeArray(2, GL_FLOAT, 0, 2, NULL);
	uvbo.release();

	//Draw triangles with 4 indices starting from the 0th index
	glDrawArrays(GL_TRIANGLE_FAN,0,vertices.size());
}
void Box::End()
{
	shaderProgram->disableAttributeArray(0);
	shaderProgram->disableAttributeArray(1);
	shaderProgram->disableAttributeArray(2);

	vao.release();
	shaderProgram->release();
}

void Box::Init()
{
	InitShader("./Shader/box.vs", "./Shader/box.fs");	
	InitVAO();
	InitVBO();
}
void Box::InitVAO()
{
	vao.create();
	vao.bind();
}
void Box::InitVBO()
{
	//Set each vertex's position
	vertices <<QVector3D(1.0f, -1.0f, 0.0f)
			<<QVector3D(1.0f, 1.0f, 0.0f)
			<<QVector3D(-1.0f, 1.0f, 0.0f)
			<<QVector3D(-1.0f, -1.0f, 0.0f);

	vvbo.create();
	vvbo.bind();
	vvbo.setUsagePattern(QOpenGLBuffer::StaticDraw);
	vvbo.allocate(vertices.constData(),vertices.size() * sizeof(QVector3D));

	nvbo.create();
	nvbo.bind();
	nvbo.setUsagePattern(QOpenGLBuffer::StaticDraw);
	nvbo.allocate(normals.constData(), normals.size() * sizeof(QVector3D));

	//Set each vertex's uv
	uvs<<QVector2D(1.0f, 0.0f)
		<<QVector2D(1.0f, 1.0f)
		<<QVector2D(0.0f, 1.0f)
		<<QVector2D(0.0f, 0.0f);

	uvbo.create();
	uvbo.bind();
	uvbo.setUsagePattern(QOpenGLBuffer::StaticDraw);
	uvbo.allocate(uvs.constData(),uvs.size() * sizeof(QVector2D));

}
void Box::InitShader(QString vertexShaderPath,QString fragmentShaderPath)
{
	// Create Shader
	shaderProgram = new QOpenGLShaderProgram();
	QFileInfo  vertexShaderFile(vertexShaderPath);
	if(vertexShaderFile.exists())
	{
		vertexShader = new QOpenGLShader(QOpenGLShader::Vertex);
		if(vertexShader->compileSourceFile(vertexShaderPath))
			shaderProgram->addShader(vertexShader);
		else
			qWarning() << "Vertex Shader Error " << vertexShader->log();
	}
	else
		qDebug()<<vertexShaderFile.filePath()<<" can't be found";

	QFileInfo  fragmentShaderFile(fragmentShaderPath);
	if(fragmentShaderFile.exists())
	{
		fragmentShader = new QOpenGLShader(QOpenGLShader::Fragment);
		if(fragmentShader->compileSourceFile(fragmentShaderPath))
			shaderProgram->addShader(fragmentShader);
		else
			qWarning() << "fragment Shader Error " << fragmentShader->log();
	}
	else
		qDebug()<<fragmentShaderFile.filePath()<<" can't be found";
	shaderProgram->link();
	shaderPrograms.push_back(shaderProgram);
	shaderProgram = NULL;
}