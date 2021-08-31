#include "MainView.h"  

MainView::MainView(QWidget *parent) : QGLWidget(parent) 
{  
	
}  
MainView::~MainView()
{}  
void MainView::initializeGL()
{
	initializeOpenGLFunctions();

#pragma region FrameBuffer Init
	//	FrameBuffer
	glGenFramebuffers(1, &frameBuffer);
	//glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, renderedTexture, 0);

	//	Generate the texture which framebuffer render to 
	glGenTextures(1, &renderedTexture);

	//	Generate the depth render buffer
	glGenRenderbuffers(1, &depthrenderBuffer);
#pragma endregion

#pragma region Small Map FrameBuffer Init
	//	FrameBuffer
	glGenFramebuffers(1, &smallmapframeBuffer);
	//glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, smallmaprenderedTexture, 0);

	//	Generate the texture which framebuffer render to 
	glGenTextures(1, &smallmaprenderedTexture);

	//	Generate the depth render buffer
	glGenRenderbuffers(1, &smallmapdepthrenderBuffer);
#pragma endregion


	backGround1 = new BackGround;
	backGround1->Init();

	backGround2 = new BackGround;
	backGround2->Init();

	m_box0 = new Box;
	m_box0->Init();

	m_box1 = new Box;
	m_box1->Init();

	m_box2 = new Box;
	m_box2->Init();

	m_apple0 = new Apple;
	m_apple0->Init();

	m_apple1 = new Apple;
	m_apple1->Init();

	m_apple2 = new Apple;
	m_apple2->Init();

	m_tv = new TV;
	m_tv->Init();

	m_crt = new CRT;
	m_crt->Init();

	character = new Character;
	character->Init();
	isCharInit = true;

	minimap = new MiniMap;
	minimap->Init();

	frameBufferObject = new FrameBuffer;
	frameBufferObject->Init();

	initializeTexture();
}
void MainView::initializeTexture()
{
#pragma region Load BackGround Texture
	QImage background1_img("./Textures/background1.png");
	background1 = new QOpenGLTexture(background1_img.mirrored());
	background1->setWrapMode(QOpenGLTexture::DirectionS, QOpenGLTexture::Repeat);
	background1->setWrapMode(QOpenGLTexture::DirectionT, QOpenGLTexture::Repeat);
	background1->setMagnificationFilter(QOpenGLTexture::Filter::LinearMipMapLinear);
	background1->setMinificationFilter(QOpenGLTexture::Filter::LinearMipMapLinear);

	QImage background2_img("./Textures/background2.png");
	background2 = new QOpenGLTexture(background2_img.mirrored());
	background2->setWrapMode(QOpenGLTexture::DirectionS, QOpenGLTexture::Repeat);
	background2->setWrapMode(QOpenGLTexture::DirectionT, QOpenGLTexture::Repeat);
	background2->setMagnificationFilter(QOpenGLTexture::Filter::LinearMipMapLinear);
	background2->setMinificationFilter(QOpenGLTexture::Filter::LinearMipMapLinear);
#pragma endregion

#pragma region Load Box Texture
	QImage box0_img("./Textures/box/box0.png");
	box0 = new QOpenGLTexture(box0_img.mirrored());
	box0->setWrapMode(QOpenGLTexture::DirectionS, QOpenGLTexture::Repeat);
	box0->setWrapMode(QOpenGLTexture::DirectionT, QOpenGLTexture::Repeat);
	box0->setMagnificationFilter(QOpenGLTexture::Filter::LinearMipMapLinear);
	box0->setMinificationFilter(QOpenGLTexture::Filter::LinearMipMapLinear);

	QImage box1_img("./Textures/box/box1.png");
	box1 = new QOpenGLTexture(box1_img.mirrored());
	box1->setWrapMode(QOpenGLTexture::DirectionS, QOpenGLTexture::Repeat);
	box1->setWrapMode(QOpenGLTexture::DirectionT, QOpenGLTexture::Repeat);
	box1->setMagnificationFilter(QOpenGLTexture::Filter::LinearMipMapLinear);
	box1->setMinificationFilter(QOpenGLTexture::Filter::LinearMipMapLinear);
#pragma endregion

#pragma region Load Apple Texture
	QImage apple_img("./Textures/apple.png");
	apple = new QOpenGLTexture(apple_img.mirrored());
	apple->setWrapMode(QOpenGLTexture::DirectionS, QOpenGLTexture::Repeat);
	apple->setWrapMode(QOpenGLTexture::DirectionT, QOpenGLTexture::Repeat);
	apple->setMagnificationFilter(QOpenGLTexture::Filter::LinearMipMapLinear);
	apple->setMinificationFilter(QOpenGLTexture::Filter::LinearMipMapLinear);
#pragma endregion

#pragma region Load Finish Texture
	
	QImage finish_img("./Textures/finish.png");
	finishTexture = new QOpenGLTexture(finish_img.mirrored());
	finishTexture->setWrapMode(QOpenGLTexture::DirectionS, QOpenGLTexture::Repeat);
	finishTexture->setWrapMode(QOpenGLTexture::DirectionT, QOpenGLTexture::Repeat);
	finishTexture->setMagnificationFilter(QOpenGLTexture::Filter::LinearMipMapLinear);
	finishTexture->setMinificationFilter(QOpenGLTexture::Filter::LinearMipMapLinear);
#pragma endregion

#pragma region Load Stand Texture
	//	stand
	QImage stand_img;
	stand_img = QImage("./Textures/stand/stand1_0.png");
	stand_img = stand_img.mirrored();
	stands.push_back(stand_img);

	stand_img = QImage("./Textures/stand/stand1_1.png");
	stand_img = stand_img.mirrored();
	stands.push_back(stand_img);

	stand_img = QImage("./Textures/stand/stand1_2.png");
	stand_img = stand_img.mirrored();
	stands.push_back(stand_img);

	stand_img = QImage("./Textures/stand/stand1_3.png");
	stand_img = stand_img.mirrored();
	stands.push_back(stand_img);

	glGenTextures(1, &tex_stand);
	glBindTexture(GL_TEXTURE_2D_ARRAY, tex_stand);
	glTexStorage3D(GL_TEXTURE_2D_ARRAY, 1, GL_RGBA4, 100, 100, 4);

	glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	for (int i = 0; i < 4; i++) {
		GLubyte *data = stands[i].bits();
		glTexSubImage3D(GL_TEXTURE_2D_ARRAY, 0, 0, 0, i, 100, 100, 1, GL_RGBA,
			GL_UNSIGNED_BYTE, data);
	}
	glBindTexture(GL_TEXTURE_2D_ARRAY, 0);
#pragma endregion

#pragma region Load Stand Texture
	//	stand
	QImage stand_n_img;
	stand_n_img = QImage("./Textures/stand/stand1_0.png");
	stand_n_img = stand_n_img.mirrored();
	stands_n.push_back(stand_n_img);

	stand_n_img = QImage("./Textures/stand/stand1_1.png");
	stand_n_img = stand_n_img.mirrored();
	stands_n.push_back(stand_n_img);

	stand_n_img = QImage("./Textures/stand/stand1_2.png");
	stand_n_img = stand_n_img.mirrored();
	stands_n.push_back(stand_n_img);

	stand_n_img = QImage("./Textures/stand/stand1_3.png");
	stand_n_img = stand_n_img.mirrored();
	stands_n.push_back(stand_n_img);

	glGenTextures(1, &tex_stand_n);
	glBindTexture(GL_TEXTURE_2D_ARRAY, tex_stand_n);
	glTexStorage3D(GL_TEXTURE_2D_ARRAY, 1, GL_RGBA4, 100, 100, 4);

	glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	for (int i = 0; i < 4; i++) {
		GLubyte *data = stands_n[i].bits();
		glTexSubImage3D(GL_TEXTURE_2D_ARRAY, 0, 0, 0, i, 100, 100, 1, GL_RGBA,
			GL_UNSIGNED_BYTE, data);
	}
	glBindTexture(GL_TEXTURE_2D_ARRAY, 0);
#pragma endregion

#pragma region Load Walk Texture
	//	walk
	QImage walk_img;
	walk_img = QImage("./Textures/walk/walk1_0.png");
	walk_img = walk_img.mirrored();
	walks.push_back(walk_img);

	walk_img = QImage("./Textures/walk/walk1_1.png");
	walk_img = walk_img.mirrored();
	walks.push_back(walk_img);

	walk_img = QImage("./Textures/walk/walk1_2.png");
	walk_img = walk_img.mirrored();
	walks.push_back(walk_img);

	walk_img = QImage("./Textures/walk/walk1_3.png");
	walk_img = walk_img.mirrored();
	walks.push_back(walk_img);

	glGenTextures(1, &tex_walk);
	glBindTexture(GL_TEXTURE_2D_ARRAY, tex_walk);
	glTexStorage3D(GL_TEXTURE_2D_ARRAY, 1, GL_RGBA4, 100, 100, 4);

	glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	for (int i = 0; i < 4; i++) {
		GLubyte *data = walks[i].bits();
		glTexSubImage3D(GL_TEXTURE_2D_ARRAY, 0, 0, 0, i, 100, 100, 1, GL_RGBA,
			GL_UNSIGNED_BYTE, data);
	}
	glBindTexture(GL_TEXTURE_2D_ARRAY, 0);
#pragma endregion

#pragma region Load Jump Texture
	//	jump
	jumps = QImage("./Textures/jump/jump_0.png");
	jumps = jumps.mirrored();
	glGenTextures(1, &tex_jump);
	glBindTexture(GL_TEXTURE_2D_ARRAY, tex_jump);
	glTexStorage3D(GL_TEXTURE_2D_ARRAY, 1, GL_RGBA4, 100, 100, 4);

	glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	for (int i = 0; i < 1; i++) {
		GLubyte *data = jumps.bits();
		glTexSubImage3D(GL_TEXTURE_2D_ARRAY, 0, 0, 0, i, 100, 100, 1, GL_RGBA,
			GL_UNSIGNED_BYTE, data);
	}
	glBindTexture(GL_TEXTURE_2D_ARRAY, 0);
#pragma endregion

#pragma region Load Attack Texture
	//	attack
	QImage attack_img;
	attack_img = QImage("./Textures/attack/swing0.png");
	attack_img = attack_img.mirrored();
	attacks.push_back(attack_img);

	attack_img = QImage("./Textures/attack/swing1.png");
	attack_img = attack_img.mirrored();
	attacks.push_back(attack_img);

	attack_img = QImage("./Textures/attack/swing2.png");
	attack_img = attack_img.mirrored();
	attacks.push_back(attack_img);

	glGenTextures(1, &tex_attack);
	glBindTexture(GL_TEXTURE_2D_ARRAY, tex_attack);
	glTexStorage3D(GL_TEXTURE_2D_ARRAY, 1, GL_RGBA4, 100, 100, 3);

	glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	for (int i = 0; i < 3; i++) {
		GLubyte *data = attacks[i].bits();
		glTexSubImage3D(GL_TEXTURE_2D_ARRAY, 0, 0, 0, i, 100, 100, 1, GL_RGBA,
			GL_UNSIGNED_BYTE, data);
	}
	glBindTexture(GL_TEXTURE_2D_ARRAY, 0);
#pragma endregion

#pragma region Load Climb Texture

#pragma endregion

#pragma region Load TV Texture
	QImage tv_img("./Textures/tv.png");
	tv = new QOpenGLTexture(tv_img.mirrored());
	tv->setWrapMode(QOpenGLTexture::DirectionS, QOpenGLTexture::Repeat);
	tv->setWrapMode(QOpenGLTexture::DirectionT, QOpenGLTexture::Repeat);
	tv->setMagnificationFilter(QOpenGLTexture::Filter::LinearMipMapLinear);
	tv->setMinificationFilter(QOpenGLTexture::Filter::LinearMipMapLinear);
#pragma endregion

#pragma region Load CRT Texture
	QImage content_img("./Textures/adele.png");
	crt_content = new QOpenGLTexture(content_img.mirrored());
	crt_content->setWrapMode(QOpenGLTexture::DirectionS, QOpenGLTexture::Repeat);
	crt_content->setWrapMode(QOpenGLTexture::DirectionT, QOpenGLTexture::Repeat);
	crt_content->setMagnificationFilter(QOpenGLTexture::Filter::LinearMipMapLinear);
	crt_content->setMinificationFilter(QOpenGLTexture::Filter::LinearMipMapLinear);

	QImage crt_img("./Textures/post_CRT_noise.png");
	crt = new QOpenGLTexture(crt_img.mirrored());
	crt->setWrapMode(QOpenGLTexture::DirectionS, QOpenGLTexture::Repeat);
	crt->setWrapMode(QOpenGLTexture::DirectionT, QOpenGLTexture::Repeat);
	crt->setMagnificationFilter(QOpenGLTexture::Filter::LinearMipMapLinear);
	crt->setMinificationFilter(QOpenGLTexture::Filter::LinearMipMapLinear);
#pragma endregion


}

void MainView::paintGL()
{
    glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
	float time = (float)QTime::currentTime().msec() / 1000 + QTime::currentTime().second();

#pragma region FrameBuffer Setting
	//	統一畫到framebuffer
	glBindFramebuffer(GL_FRAMEBUFFER, frameBuffer);

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(1, 1, 1, 0);
	glViewport(0, 0, width(), height());
	//	bind texture framebuffer render to
	glBindTexture(GL_TEXTURE_2D, renderedTexture);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width(), height(), 0, GL_RGB, GL_UNSIGNED_BYTE, 0);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

	//	bind depthbuffer
	glBindRenderbuffer(GL_RENDERBUFFER, depthrenderBuffer);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, width(), height());
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, depthrenderBuffer);

	glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, renderedTexture, 0);

	GLenum DrawBuffers[2] = { GL_COLOR_ATTACHMENT0,GL_DEPTH_ATTACHMENT };
	glDrawBuffers(2, DrawBuffers);
#pragma endregion

#pragma region Camera Control
	glPushMatrix();
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	if (character->center.x() > -0.5f && character->center.x() < 3.5f) {
		if (character->center.y() < -0.5f)
			gluLookAt(character->center.x(), -0.5f, 1, character->center.x(), -0.5f, 0, 0, 1, 0);
		else if (character->center.y() > 0.5f)
			gluLookAt(character->center.x(), 0.5, 1, character->center.x(), 0.5, 0, 0, 1, 0);
		else
			gluLookAt(character->center.x(), character->center.y(), 1, character->center.x(), character->center.y(), 0, 0, 1, 0);
	}
	else if (character->center.x() <= -0.5f) {
		if (character->center.y() < -0.5f)
			gluLookAt(-0.5f, -0.5f, 1, -0.5f, -0.5f, 0, 0, 1, 0);
		else if (character->center.y() > 0.5f)
			gluLookAt(-0.5f, 0.5, 1, -0.5f, 0.5, 0, 0, 1, 0);
		else
			gluLookAt(-0.5f, character->center.y(), 1, -0.5f, character->center.y(), 0, 0, 1, 0);
	}
	else {
		if (character->center.y() < -0.5f)
			gluLookAt(3.5f, -0.5f, 1, 3.5f, -0.5f, 0, 0, 1, 0);
		else if (character->center.y() > 0.5f)
			gluLookAt(3.5f, 0.5f, 1, 3.5f, 0.5f, 0, 0, 1, 0);
		else
			gluLookAt(3.5f, character->center.y(), 1, 3.5f, character->center.y(), 0, 0, 1, 0);
	}
#pragma endregion

#pragma region BackGround
	//	BackGround
	backGround1->Begin(0);
	//	Texture
	glActiveTexture(GL_TEXTURE0 + background1->textureId());
	glBindTexture(GL_TEXTURE_2D, background1->textureId());
	backGround1->shaderProgram->setUniformValue("Texture", background1->textureId());
	backGround1->shaderProgram->setUniformValue("Offset", QVector3D(0, 0, 0));
	backGround1->shaderProgram->setUniformValue("Scale", QVector3D(1.5, 1.5, 0));		
	glGetFloatv(GL_MODELVIEW_MATRIX, ModelViewMatrix);
	glGetFloatv(GL_PROJECTION_MATRIX, ProjectionMatrix);
	backGround1->Paint(ProjectionMatrix, ModelViewMatrix);
	backGround1->End();

	//	BackGround2
	backGround2->Begin(0);
	//	Texture
	glActiveTexture(GL_TEXTURE0 + background2->textureId());
	glBindTexture(GL_TEXTURE_2D, background2->textureId());
	backGround2->shaderProgram->setUniformValue("Texture", background2->textureId());
	backGround2->shaderProgram->setUniformValue("Offset", QVector3D(3,0,0));
	backGround2->shaderProgram->setUniformValue("Scale", QVector3D(1.5, 1.5, 0));
	glGetFloatv(GL_MODELVIEW_MATRIX, ModelViewMatrix);
	glGetFloatv(GL_PROJECTION_MATRIX, ProjectionMatrix);
	backGround2->Paint(ProjectionMatrix, ModelViewMatrix);
	backGround2->End();
#pragma endregion

#pragma region Boxs
	glEnable(GL_BLEND);
	if (!box0_distroy) {
		m_box0->Begin(0);
		//	Texture
		if (isbox0_hit) {
			glActiveTexture(GL_TEXTURE0 + box1->textureId());
			glBindTexture(GL_TEXTURE_2D, box1->textureId());
			m_box0->shaderProgram->setUniformValue("Texture", box1->textureId());
			if (!box0_hit_start) {
				box0_hit_time = time;
				box0_hit_start = true;
			}
			if (time - box0_hit_time < 1)
				m_box0->shaderProgram->setUniformValue("iTime", time - box0_hit_time);
			else
				box0_distroy = true;
			m_box0->shaderProgram->setUniformValue("ishit", true);
		}
		else {
			glActiveTexture(GL_TEXTURE0 + box0->textureId());
			glBindTexture(GL_TEXTURE_2D, box0->textureId());
			m_box0->shaderProgram->setUniformValue("Texture", box0->textureId());
		}

		m_box0->shaderProgram->setUniformValue("Offset", QVector3D(0.3, -1.04, 0));
		m_box0->shaderProgram->setUniformValue("Scale", QVector3D(0.2, 0.2, 0));
		glGetFloatv(GL_MODELVIEW_MATRIX, ModelViewMatrix);
		glGetFloatv(GL_PROJECTION_MATRIX, ProjectionMatrix);

		m_box0->Paint(ProjectionMatrix, ModelViewMatrix);
		m_box0->End();
	}

	if (!box1_distroy) {
		m_box1->Begin(0);
		//	Texture

		if (isbox1_hit) {
			glActiveTexture(GL_TEXTURE0 + box1->textureId());
			glBindTexture(GL_TEXTURE_2D, box1->textureId());
			m_box1->shaderProgram->setUniformValue("Texture", box1->textureId());
			if (!box1_hit_start) {
				box1_hit_time = time;
				box1_hit_start = true;
			}
			if (time - box1_hit_time < 1)
				m_box1->shaderProgram->setUniformValue("iTime", time - box1_hit_time);
			else
				box1_distroy = true;
			m_box1->shaderProgram->setUniformValue("ishit", true);
		}
		else {
			glActiveTexture(GL_TEXTURE0 + box0->textureId());
			glBindTexture(GL_TEXTURE_2D, box0->textureId());
			m_box1->shaderProgram->setUniformValue("Texture", box0->textureId());
		}

		m_box1->shaderProgram->setUniformValue("Offset", QVector3D(1.9, -0.875, 0));
		m_box1->shaderProgram->setUniformValue("Scale", QVector3D(0.2, 0.2, 0));
		glGetFloatv(GL_MODELVIEW_MATRIX, ModelViewMatrix);
		glGetFloatv(GL_PROJECTION_MATRIX, ProjectionMatrix);

		m_box1->Paint(ProjectionMatrix, ModelViewMatrix);
		m_box1->End();
	}

	if (!box2_distroy) {
		m_box2->Begin(0);
		if (isbox2_hit) {
			glActiveTexture(GL_TEXTURE0 + box1->textureId());
			glBindTexture(GL_TEXTURE_2D, box1->textureId());
			m_box2->shaderProgram->setUniformValue("Texture", box1->textureId());
			if (!box2_hit_start) {
				box2_hit_time = time;
				box2_hit_start = true;
			}
			if (time - box2_hit_time < 1)
				m_box2->shaderProgram->setUniformValue("iTime", time - box2_hit_time);
			else
				box2_distroy = true;
			m_box2->shaderProgram->setUniformValue("ishit", true);
		}
		else {
			glActiveTexture(GL_TEXTURE0 + box0->textureId());
			glBindTexture(GL_TEXTURE_2D, box0->textureId());
			m_box2->shaderProgram->setUniformValue("Texture", box0->textureId());
		}

		m_box2->shaderProgram->setUniformValue("Offset", QVector3D(3, -0.7, 0));
		m_box2->shaderProgram->setUniformValue("Scale", QVector3D(0.2, 0.2, 0));
		glGetFloatv(GL_MODELVIEW_MATRIX, ModelViewMatrix);
		glGetFloatv(GL_PROJECTION_MATRIX, ProjectionMatrix);
		m_box2->Paint(ProjectionMatrix, ModelViewMatrix);
		m_box2->End();
	}	
	glDisable(GL_BLEND);
#pragma endregion

#pragma region TV
	glEnable(GL_BLEND);
	m_tv->Begin(0);
	//	Texture
	glActiveTexture(GL_TEXTURE0 + tv->textureId());
	glBindTexture(GL_TEXTURE_2D, tv->textureId());
	m_tv->shaderProgram->setUniformValue("Texture", tv->textureId());	

	m_tv->shaderProgram->setUniformValue("Offset", QVector3D(-0.7, -0.5, 0));
	m_tv->shaderProgram->setUniformValue("Scale", QVector3D(1.0, 1.0, 1.0));
	glGetFloatv(GL_MODELVIEW_MATRIX, ModelViewMatrix);
	glGetFloatv(GL_PROJECTION_MATRIX, ProjectionMatrix);
	m_tv->Paint(ProjectionMatrix, ModelViewMatrix);
	m_tv->End();
	glDisable(GL_BLEND);
#pragma endregion
	
	CheckCollision();

#pragma region Apples
	glEnable(GL_BLEND);
	if (box0_distroy) {
		if (!apple0_distroy) {
			m_apple0->Begin(0);
			glActiveTexture(GL_TEXTURE0 + apple->textureId());
			glBindTexture(GL_TEXTURE_2D, apple->textureId());
			m_apple0->shaderProgram->setUniformValue("Texture", apple->textureId());
			m_apple0->shaderProgram->setUniformValue("Offset", QVector3D(0.3, -1.04, 0));
			m_apple0->shaderProgram->setUniformValue("Scale", QVector3D(0.1, 0.1, 0));
			if (isapple0_col) {
				if (!apple0_col_start) {
					apple0_col_time = time;
					apple0_col_start = true;
				}
				if (time - apple0_col_time < 1)
					m_apple0->shaderProgram->setUniformValue("iTime", time - apple0_col_time);
				else
					apple0_distroy = true;
				m_apple0->shaderProgram->setUniformValue("ishit", true);
			}
			glGetFloatv(GL_MODELVIEW_MATRIX, ModelViewMatrix);
			glGetFloatv(GL_PROJECTION_MATRIX, ProjectionMatrix);
			m_apple0->Paint(ProjectionMatrix, ModelViewMatrix);
			m_apple0->End();
		}
	}

	if (box1_distroy) {
		if (!apple1_distroy) {
			m_apple1->Begin(0);
			glActiveTexture(GL_TEXTURE0 + apple->textureId());
			glBindTexture(GL_TEXTURE_2D, apple->textureId());
			m_apple1->shaderProgram->setUniformValue("Texture", apple->textureId());
			m_apple1->shaderProgram->setUniformValue("Offset", QVector3D(1.9, -0.875, 0));
			m_apple1->shaderProgram->setUniformValue("Scale", QVector3D(0.1, 0.1, 0));
			if (isapple1_col) {
				if (!apple1_col_start) {
					apple1_col_time = time;
					apple1_col_start = true;
				}
				if (time - apple1_col_time < 1)
					m_apple1->shaderProgram->setUniformValue("iTime", time - apple1_col_time);
				else
					apple1_distroy = true;
				m_apple1->shaderProgram->setUniformValue("ishit", true);
			}
			glGetFloatv(GL_MODELVIEW_MATRIX, ModelViewMatrix);
			glGetFloatv(GL_PROJECTION_MATRIX, ProjectionMatrix);
			m_apple1->Paint(ProjectionMatrix, ModelViewMatrix);
			m_apple1->End();
		}
	}

	if (box2_distroy) {
		if (!apple2_distroy) {
			m_apple2->Begin(0);
			glActiveTexture(GL_TEXTURE0 + apple->textureId());
			glBindTexture(GL_TEXTURE_2D, apple->textureId());
			m_apple2->shaderProgram->setUniformValue("Texture", apple->textureId());
			m_apple2->shaderProgram->setUniformValue("Offset", QVector3D(3, -0.7, 0));
			m_apple2->shaderProgram->setUniformValue("Scale", QVector3D(0.1, 0.1, 0));
			if (isapple2_col) {
				if (!apple2_col_start) {
					apple2_col_time = time;
					apple2_col_start = true;
				}
				if (time - apple2_col_time < 1)
					m_apple2->shaderProgram->setUniformValue("iTime", time - apple2_col_time);
				else
					apple2_distroy = true;
				m_apple2->shaderProgram->setUniformValue("ishit", true);
			}
			glGetFloatv(GL_MODELVIEW_MATRIX, ModelViewMatrix);
			glGetFloatv(GL_PROJECTION_MATRIX, ProjectionMatrix);
			m_apple2->Paint(ProjectionMatrix, ModelViewMatrix);
			m_apple2->End();
		}
	}

	glDisable(GL_BLEND);
#pragma endregion

#pragma region CRT
	m_crt->Begin(0);
	glGetFloatv(GL_MODELVIEW_MATRIX, ModelViewMatrix);
	glGetFloatv(GL_PROJECTION_MATRIX, ProjectionMatrix);
	//	Texture
	glActiveTexture(GL_TEXTURE0 + crt_content->textureId());
	glBindTexture(GL_TEXTURE_2D, crt_content->textureId());
	m_crt->shaderProgram->setUniformValue("Texture0", crt_content->textureId());
	glActiveTexture(GL_TEXTURE0 + crt->textureId());
	glBindTexture(GL_TEXTURE_2D, crt->textureId());
	m_crt->shaderProgram->setUniformValue("Texture1", crt->textureId());
	m_crt->shaderProgram->setUniformValue("iTime", time);
	m_crt->shaderProgram->setUniformValue("Offset", QVector3D(-0.85, -0.54, 0));
	m_crt->shaderProgram->setUniformValue("Scale", QVector3D(0.35, 0.27, 1.0));	
	m_crt->Paint(ProjectionMatrix, ModelViewMatrix);
	m_crt->End();
#pragma endregion

#pragma region Character
	//	Character
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glPushMatrix();
	character->Begin(0);
	glMatrixMode(GL_MODELVIEW);
	glTranslatef(character->center.x(), character->center.y(), 0);
	glScalef(1, 1, 0);
	glScalef(0.2, 0.2, 0);

	glGetFloatv(GL_MODELVIEW_MATRIX, ModelViewMatrix);
	glGetFloatv(GL_PROJECTION_MATRIX, ProjectionMatrix);

	//	stand
	glActiveTexture(GL_TEXTURE0 + tex_stand);
	glBindTexture(GL_TEXTURE_2D_ARRAY, tex_stand);
	character->shaderProgram->setUniformValue("stand", tex_stand);

	//	stand_n
	glActiveTexture(GL_TEXTURE0 + tex_stand_n);
	glBindTexture(GL_TEXTURE_2D_ARRAY, tex_stand_n);
	character->shaderProgram->setUniformValue("stand_n", tex_stand_n);

	//	walk
	glActiveTexture(GL_TEXTURE0 + tex_walk);
	glBindTexture(GL_TEXTURE_2D_ARRAY, tex_walk);
	character->shaderProgram->setUniformValue("walk", tex_walk);

	//	jump
	glActiveTexture(GL_TEXTURE0 + tex_jump);
	glBindTexture(GL_TEXTURE_2D_ARRAY, tex_jump);
	character->shaderProgram->setUniformValue("jump", tex_jump);

	//	jump
	glActiveTexture(GL_TEXTURE0 + tex_attack);
	glBindTexture(GL_TEXTURE_2D_ARRAY, tex_attack);
	character->shaderProgram->setUniformValue("attack", tex_attack);

	if (character->m_status == character->stand_R) {

		character->shaderProgram->setUniformValue("status", character->stand_R);
		character->shaderProgram->setUniformValue("spriteIndex", frame % 5);
		character->shaderProgram->setUniformValue("LightPos", QVector3D(lightx, lighty, lightz).normalized());
	}
	if (character->m_status == character->stand_L) {
		character->shaderProgram->setUniformValue("status", character->stand_L);
		character->shaderProgram->setUniformValue("spriteIndex", frame % 5);
		character->shaderProgram->setUniformValue("LightPos", QVector3D(lightx, lightx, lightz).normalized());
	}
	if (character->m_status == character->walk_R) {
		character->shaderProgram->setUniformValue("status", character->walk_R);
		character->shaderProgram->setUniformValue("spriteIndex", frame % 4);
	}
	if (character->m_status == character->walk_L) {
		character->shaderProgram->setUniformValue("status", character->walk_L);
		character->shaderProgram->setUniformValue("spriteIndex", frame % 4);
	}
	if (character->m_status == character->jump_R) {
		character->shaderProgram->setUniformValue("status", character->jump_R);
		character->shaderProgram->setUniformValue("spriteIndex", 0);
	}
	if (character->m_status == character->jump_L) {
		character->shaderProgram->setUniformValue("status", character->jump_L);
		character->shaderProgram->setUniformValue("spriteIndex", 0);
	}
	if (character->m_status == character->attack_R) {
		character->shaderProgram->setUniformValue("status", character->attack_R);
		character->shaderProgram->setUniformValue("spriteIndex", attack_frame % 3);
	}
	if (character->m_status == character->attack_L) {
		character->shaderProgram->setUniformValue("status", character->attack_L);
		character->shaderProgram->setUniformValue("spriteIndex", attack_frame % 3);
	}
	character->shaderProgram->setUniformValue("isFinish", isFinish);
	character->Paint(ProjectionMatrix, ModelViewMatrix);
	character->End();
	glPopMatrix();
	glDisable(GL_BLEND);
	glPopMatrix();
#pragma endregion

#pragma region Small Map FrameBuffer Setting
	//	統一畫到framebuffer
	glBindFramebuffer(GL_FRAMEBUFFER, smallmapframeBuffer);

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(1, 1, 1, 0);
	glViewport(0, 0, width(), height());

	//	bind texture framebuffer render to
	glBindTexture(GL_TEXTURE_2D, smallmaprenderedTexture);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width(), height(), 0, GL_RGB, GL_UNSIGNED_BYTE, 0);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

	//	bind depthbuffer
	glBindRenderbuffer(GL_RENDERBUFFER, smallmapdepthrenderBuffer);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, width(), height());
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, smallmapdepthrenderBuffer);

	glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, smallmaprenderedTexture, 0);

	GLenum smallmapDrawBuffers[2] = { GL_COLOR_ATTACHMENT0,GL_DEPTH_ATTACHMENT };
	glDrawBuffers(2, smallmapDrawBuffers);
#pragma endregion

#pragma region MiniMap View Setting
	glPushMatrix();
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-1.5f, 4.5f, -1.5, 1.5f, -1, 100);
#pragma endregion

#pragma region MiniMapBackGround
	//	BackGround
	backGround1->Begin(0);
	//	Texture
	glActiveTexture(GL_TEXTURE0 + background1->textureId());
	glBindTexture(GL_TEXTURE_2D, background1->textureId());
	backGround1->shaderProgram->setUniformValue("Texture", background1->textureId());
	backGround1->shaderProgram->setUniformValue("Offset", QVector3D(0, 0, 0));
	backGround1->shaderProgram->setUniformValue("Scale", QVector3D(1.5, 1.5, 0));
	glGetFloatv(GL_MODELVIEW_MATRIX, ModelViewMatrix);
	glGetFloatv(GL_PROJECTION_MATRIX, ProjectionMatrix);
	backGround1->Paint(ProjectionMatrix, ModelViewMatrix);
	backGround1->End();

	//	BackGround2
	backGround2->Begin(0);
	//	Texture
	glActiveTexture(GL_TEXTURE0 + background2->textureId());
	glBindTexture(GL_TEXTURE_2D, background2->textureId());
	backGround2->shaderProgram->setUniformValue("Texture", background2->textureId());
	backGround2->shaderProgram->setUniformValue("Offset", QVector3D(3, 0, 0));
	backGround2->shaderProgram->setUniformValue("Scale", QVector3D(1.5, 1.5, 0));
	glGetFloatv(GL_MODELVIEW_MATRIX, ModelViewMatrix);
	glGetFloatv(GL_PROJECTION_MATRIX, ProjectionMatrix);
	backGround2->Paint(ProjectionMatrix, ModelViewMatrix);
	backGround2->End();
#pragma endregion

	CheckCollision();

#pragma region Character
	//	Character
	glPushMatrix();
	character->Begin(1);
	glMatrixMode(GL_MODELVIEW);
	glTranslatef(character->center.x(), character->center.y(), 0);
	glScalef(0.05, 0.1, 0);
	glGetFloatv(GL_MODELVIEW_MATRIX, ModelViewMatrix);
	glGetFloatv(GL_PROJECTION_MATRIX, ProjectionMatrix);
	character->Paint(ProjectionMatrix, ModelViewMatrix);
	character->End();
	glPopMatrix();
	glPopMatrix();

#pragma endregion

#pragma region Render On Screen
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	glViewport(0, 0, width(), height());

	//	Disable depth test to draw quad
	glDisable(GL_DEPTH_TEST);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	
	//	Game Content
	frameBufferObject->Begin(0);
	glGetFloatv(GL_MODELVIEW_MATRIX, ModelViewMatrix);
	glGetFloatv(GL_PROJECTION_MATRIX, ProjectionMatrix);
	glActiveTexture(GL_TEXTURE0 + renderedTexture);
	glBindTexture(GL_TEXTURE_2D, renderedTexture);
	frameBufferObject->shaderProgram->setUniformValue("Texture", renderedTexture);
	if (isapple0_col&& isapple1_col && isapple2_col) {
		glActiveTexture(GL_TEXTURE0 + finishTexture->textureId());
		glBindTexture(GL_TEXTURE_2D, finishTexture->textureId());
		isFinish = true;
		frameBufferObject->shaderProgram->setUniformValue("isFinish", isFinish);
		frameBufferObject->shaderProgram->setUniformValue("finishTexture", finishTexture->textureId());
	}
	else {
		frameBufferObject->shaderProgram->setUniformValue("isFinish", isFinish);
	}
	frameBufferObject->shaderProgram->setUniformValue("iTime", time);	
	frameBufferObject->shaderProgram->setUniformValue("Scale", QVector3D(1, 1, 0));
	frameBufferObject->shaderProgram->setUniformValue("Offset", QVector3D(0, 0, 0));
	frameBufferObject->Paint(ProjectionMatrix, ModelViewMatrix);
	frameBufferObject->End();
	
	//	MiniMap
	minimap->Begin(0);
	glGetFloatv(GL_MODELVIEW_MATRIX, ModelViewMatrix);
	glGetFloatv(GL_PROJECTION_MATRIX, ProjectionMatrix);
	glActiveTexture(GL_TEXTURE0 + smallmaprenderedTexture);
	glBindTexture(GL_TEXTURE_2D, smallmaprenderedTexture);
	minimap->shaderProgram->setUniformValue("Texture", smallmaprenderedTexture);
	minimap->shaderProgram->setUniformValue("Scale", QVector3D(0.25,0.2,0));
	minimap->shaderProgram->setUniformValue("Offset", QVector3D(-0.75,0.8,0));
	minimap->Paint(ProjectionMatrix, ModelViewMatrix);
	minimap->End();
#pragma endregion

	update();
;}

void MainView::addframe(){
	frame++;
}

void MainView::addoffset(bool left) {
	if (left)
		if(!isContactLeft)
			if (character->center.x() > -1.5f)
				character->center.setX(character->center.x() - 0.01f);
	if (!left)
		if(!isContactRight)
			if (character->center.x() < 4.5f)
				character->center.setX(character->center.x() + 0.01f);
}

void MainView::addjump() {
	if (isJump) {			
		if (character->jump_offset < 0.3f) {
			isContactDown = false;
			character->jump_offset += 0.015f;
			character->center.setY(character->center.y() + 0.015f);
		}			
		else {			
			isJump = false;			
			character->jump_offset = 0.0f;
		}			
	}	
}

void MainView::addattack() {
	if (isAttack) {
		CheckAttack();
		attack_frame += 1;
		if (attack_frame == 3) {
			isAttack = false;
			attack_frame = 0;
			if (character->m_status == character->attack_L)
				character->m_status = character->stand_L;
			if (character->m_status == character->attack_R)
				character->m_status = character->stand_R;
		}		
	}
}

void MainView::addy(int sign) {
	float cur_y = character->center.y();
	//character->center.setY(cur_y + sign * 0.01f);
}

void MainView::addGravaty() {
	if (!isJump)
		if (!isContactDown) {
			character->center.setY(character->center.y() - 0.015f);
		}			
}

void MainView::CheckCollision() {
	QVector2D c = character->center;
	QVector2D up = QVector2D(c.x(), c.y() + 0.125);
	QVector2D down = QVector2D(c.x(), c.y() - 0.125);
	QVector2D right = QVector2D(c.x() + 0.125, c.y());
	QVector2D left = QVector2D(c.x() - 0.125, c.y());

	//printf("x:%f y:%f up:%f down:%f right:%f left:%f\n", c.x(),c.y(),up.y(), down.y(), right.x(), left.x());

	if ((right.x()< 0.1275f)&& down.y() <= -1.275f) {
		isContactDown = true;
		if (character->m_status == character->jump_L && !isJump) {
			character->m_status = character->stand_L;		
		}			
		if (character->m_status == character->jump_R && !isJump) {
			character->m_status = character->stand_R;
		}
	}
	else if ((right.x() >= 0.1275f && right.x() < 1.35f) && down.y() <= -1.125f) {
		isContactDown = true;
		if (character->m_status == character->jump_L && !isJump) {
			character->m_status = character->stand_L;
		}
		if (character->m_status == character->jump_R && !isJump) {
			character->m_status = character->stand_R;
		}
	}
	else if ((right.x() >= 1.35f && right.x() < 2.3f) && down.y() <= -0.955f) {
		isContactDown = true;
		if (character->m_status == character->jump_L && !isJump) {
			character->m_status = character->stand_L;
		}
		if (character->m_status == character->jump_R && !isJump) {
			character->m_status = character->stand_R;
		}
	}
	else if ((right.x() >= 2.3f && down.x() < 3.15f) && down.y() <= -0.755f) {
		isContactDown = true;
		if (character->m_status == character->jump_L && !isJump) {
			character->m_status = character->stand_L;
		}
		if (character->m_status == character->jump_R && !isJump) {
			character->m_status = character->stand_R;
		}
	}
	else if ((down.x() >= 3.15f && down.x() < 3.3f) && down.y() <= (down.x()-3.15)*1.303f + -0.765) {
		isContactDown = true;
		character->center.setY((down.x() - 3.15)*1.303f + -0.765 + 0.124f);
		if (character->m_status == character->jump_L && !isJump) {
			character->m_status = character->stand_L;
		}
		if (character->m_status == character->jump_R && !isJump) {
			character->m_status = character->stand_R;
		}
	}
	else if ((down.x() >= 3.3f && down.x() < 4.5f) && down.y() <= -0.6) {
		isContactDown = true;
		if (character->m_status == character->jump_L && !isJump) {
			character->m_status = character->stand_L;
		}
		if (character->m_status == character->jump_R && !isJump) {
			character->m_status = character->stand_R;
		}
	}
	else {
		isContactDown = false;
	}

	if (right.y() < -1 && right.x() >= 0.1275f)
		isContactRight = true;
	else if (right.y() < -0.875 && right.x() >= 1.35f)
		isContactRight = true;
	else if (right.y() < -0.75 && right.x() >= 2.3f)
		isContactRight = true;
	else
		isContactRight = false;
}

void MainView::CheckAttack() {
	QVector2D c = character->center;
	if (character->m_status == character->attack_L) {
		if (c.x() < 0.58&&c.x() >= 0.27)
			isbox0_hit = true;
		if (c.x() < 2.16&&c.x() >= 1.9)
			isbox1_hit = true;
		if (c.x() < 3.2&&c.x() >= 3)
			isbox2_hit = true;
	}
	if (character->m_status == character->attack_R) {
		if (c.x() < 0.27&&c.x() >= 0.07)
			isbox0_hit = true;
		if (c.x() < 1.9&&c.x() >= 1.7)
			isbox1_hit = true;
		if (c.x() < 3&&c.x() >= 2.76)
			isbox2_hit = true;
	}
}

void MainView::CheckApple() {
	QVector2D c = character->center;
	if (c.x() >= 0.26 && c.x() < 0.30)
		isapple0_col = true;
	if (c.x() >= 1.85 && c.x() < 1.96)
		isapple1_col = true;
	if (c.x() >= 2.96 && c.x() < 3.05)
		isapple2_col = true;
}

void MainView::MoveLight() {
	if(!light_reverse)
		if (lightx < 1.0f)
			lightx += 0.1f;
		else if (lighty < 1.0f)
			lighty += 0.1f;
		else
			light_reverse = true;
	else
		if (lightx > 0.0f)
			lightx -= 0.1f;
		else if (lighty > 0.0f)
			lighty -= 0.1f;
		else
			light_reverse = false;
}