#include <QtGui/QtGui>  
#pragma comment(lib,"opengl32.lib")
#pragma comment(lib,"glu32.lib") 
#include <BackGround.h>
#include <Character.h>
#include <FrameBuffer.h>
#include <MiniMap.h>
#include <Box.h>
#include <TV.h>
#include <CRT.h>
#include <Apple.h>
#include <GL/gl.h>
#include <GL/glu.h>

class MainView : public QGLWidget , protected QOpenGLFunctions_4_3_Core
{  
public:  
	explicit MainView(QWidget *parent = 0);
	~MainView();

public:
	virtual void paintGL();
	void initializeGL();
	void initializeTexture();
	void addframe();
	void addoffset(bool left);
	void addjump();
	void addattack();
	void addy(int sign);
	void CheckCollision();
	void CheckAttack();
	void CheckApple();
	void addGravaty();
	void MoveLight();
	
public:
	uint frame = 0;
	uint attack_frame = 0;

	GLuint frameBuffer;
	GLuint depthrenderBuffer;
	GLuint renderedTexture;
	
	GLuint smallmapframeBuffer;
	GLuint smallmapdepthrenderBuffer;
	GLuint smallmaprenderedTexture;

	QOpenGLTexture* background1;
	QOpenGLTexture* background2;

	QOpenGLTexture* box0;
	QOpenGLTexture* box1;

	QOpenGLTexture* tv;
	QOpenGLTexture* crt_content;
	QOpenGLTexture* crt;

	QOpenGLTexture* apple;

	QOpenGLTexture* finishTexture;

	//	For Character Texture
	//	stand
	GLuint tex_stand;
	QVector<QImage> stands;
	//	stand normal
	GLuint tex_stand_n;
	QVector<QImage> stands_n;
	//	walk
	GLuint tex_walk;
	QVector<QImage> walks;	
	//	jump
	GLuint tex_jump;
	QImage jumps;
	//	attack
	GLuint tex_attack;
	QVector<QImage> attacks;


	GLfloat ProjectionMatrix[16];
	GLfloat ModelViewMatrix[16];
	
	BackGround *backGround1;
	BackGround *backGround2;
	Box *m_box0;
	Box *m_box1;
	Box *m_box2;
	Apple *m_apple0;
	Apple *m_apple1;
	Apple *m_apple2;
	TV *m_tv;
	CRT *m_crt;
	Character *character;
	FrameBuffer *frameBufferObject;
	MiniMap *minimap;
	bool isJump = false;
	bool isAttack = false;
	bool isCharInit = false;
	bool isContactDown = false;
	bool isContactRight = false;
	bool isContactLeft = false;

	bool isbox0_hit = false;
	bool isbox1_hit = false;
	bool isbox2_hit = false;
	bool box0_hit_start = false;
	bool box1_hit_start = false;
	bool box2_hit_start = false;
	bool box0_distroy = false;
	bool box1_distroy = false;
	bool box2_distroy = false;
	float box0_hit_time = 0;
	float box1_hit_time = 0;
	float box2_hit_time = 0;

	bool isapple0_col = false;
	bool isapple1_col = false;
	bool isapple2_col = false;
	bool apple0_col_start = false;
	bool apple1_col_start = false;
	bool apple2_col_start = false;
	bool apple0_distroy = false;
	bool apple1_distroy = false;
	bool apple2_distroy = false;
	float apple0_col_time = 0;
	float apple1_col_time = 0;
	float apple2_col_time = 0;

	float lightx = 0;
	float lighty = 0;
	float lightz = 1.0f;
	bool light_reverse = false;

	bool isFinish = false;
};  