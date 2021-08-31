
#include <QtGui/QOpenGLFunctions_4_3_Core>
#include <QtGui/QOpenGLVertexArrayObject>
#include <QtGui/QOpenGLBuffer>
#include <QtGui/QOpenGLShader>
#include <QtGui/QOpenGLShaderProgram>
#include <QtOpenGL/QtOpenGL> 
#include <QVector>
#include <QVector3D>
#include <QVector2D>
#include <QFileInfo>
#include <QOpenGLTexture>
#include <QImage>
#include <QDebug>
#include <QString>


class Character 
{
public:
	QOpenGLShaderProgram* shaderProgram;
	QVector<QOpenGLShaderProgram*> shaderPrograms;
	QOpenGLShader* vertexShader;
	QOpenGLShader* fragmentShader;
	QVector<QVector3D> vertices;
	QVector<QVector3D> normals;
	QVector<QVector2D> uvs;
	QOpenGLVertexArrayObject vao;
	QOpenGLBuffer vvbo;
	QOpenGLBuffer nvbo;
	QOpenGLBuffer uvbo;

	enum status {
		stand_R,stand_L,walk_R,walk_L,jump_R,jump_L,attack_R,attack_L
	}m_status;
	
	float jump_offset = 0;
	QVector2D center = QVector2D(-1.0f, -1.0f);

public:
	Character();
	void Init();
	void InitVAO();
	void InitVBO();
	void InitShader(QString vertexShaderPath,QString fragmentShaderPath);
	void DimensionTransformation(GLfloat source[],GLfloat target[][4]);
	void Begin(int programIndex);
	void Paint(GLfloat* ProjectionMatrix, GLfloat* ModelViewMatrix);
	void End();

};