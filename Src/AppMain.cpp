#include "AppMain.h"
#include <math.h>
#include <time.h>

AppMain* AppMain::Instance = NULL;
AppMain::AppMain(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	mainview = new MainView();
	setGeometry(100,25,1000,768);   
	ui.mainLayout->layout()->addWidget(mainview);
	mainview->installEventFilter(this);
	mainview->setFocusPolicy(Qt::FocusPolicy::StrongFocus);
	setWindowTitle( "2D Game" );

	myTimer = new QTimer(this);
	myTimer->start(200);
	connect(myTimer, SIGNAL(timeout()), this, SLOT(addframe()));

	myTimer2 = new QTimer(this);
	myTimer2->start(20);
	connect(myTimer2, SIGNAL(timeout()), this, SLOT(addoffset()));

	myTimer3 = new QTimer(this);
	myTimer3->start(20);
	connect(myTimer3, SIGNAL(timeout()), this, SLOT(addjump()));

	myTimer4 = new QTimer(this);
	myTimer4->start(20);
	connect(myTimer4, SIGNAL(timeout()), this, SLOT(addy()));

	myTimer5 = new QTimer(this);
	myTimer5->start(400);
	connect(myTimer5, SIGNAL(timeout()), this, SLOT(addattack()));

	myTimer6 = new QTimer(this);
	myTimer6->start(400);
	connect(myTimer6, SIGNAL(timeout()), this, SLOT(movelight()));

}

AppMain::~AppMain()
{

}

bool AppMain::eventFilter(QObject *watched, QEvent *e) {
	if (e->type() == QEvent::MouseButtonPress) {
		QMouseEvent *mouseEvent = static_cast<QMouseEvent*> (e);
	}

	if (e->type() == QEvent::MouseButtonRelease) {
		QMouseEvent *mouseEvent = static_cast<QMouseEvent*> (e);
	}

	if (e->type() == QEvent::Wheel) {
		QWheelEvent *event = static_cast<QWheelEvent*> (e);
		mainview->update();
	}

	if (e->type() == QEvent::MouseMove) {
		QMouseEvent *mouseEvent = static_cast<QMouseEvent*> (e);
		mainview->update();
	}

	if (e->type() == QEvent::KeyPress) {
		QKeyEvent *keyEvent = static_cast<QKeyEvent*> (e);
		if (keyEvent->key() == Qt::Key_Alt)
			AltButtonDown = true;
		if (keyEvent->key() == Qt::Key_Control)
			CtrlButtonDown = true;
		if (keyEvent->key() == Qt::Key_Left)
			LeftArrowButtonDown = true;
		if (keyEvent->key() == Qt::Key_Right)
			RightArrowButtonDown = true;
		if (keyEvent->key() == Qt::Key_Up)
			UpArrowButtonDown = true;
		if (keyEvent->key() == Qt::Key_Down)
			DownArrowButtonDown = true;
		if (keyEvent->key() == Qt::Key_Z)
			ZButtonDown = true;
		if (keyEvent->key() == Qt::Key_Q)
			mainview->lightx += 0.1f;
		if (keyEvent->key() == Qt::Key_W)
			mainview->lightx -= 0.1f;
		if (keyEvent->key() == Qt::Key_A)
			mainview->lighty += 0.1f;
		if (keyEvent->key() == Qt::Key_S)
			mainview->lighty -= 0.1f;
		if (keyEvent->key() == Qt::Key_Z)
			mainview->lightz += 0.1f;
		if (keyEvent->key() == Qt::Key_X)
			mainview->lightz -= 0.1f;
		//printf("x:%f y:%f z:%f\n", mainview->lightx, mainview->lighty, mainview->lightz);
	}
	if (e->type() == QEvent::KeyRelease) {
		QKeyEvent *keyEvent = static_cast<QKeyEvent*> (e);
		if (keyEvent->key() == Qt::Key_Alt)
			AltButtonDown = false;
		if (keyEvent->key() == Qt::Key_Control)
			CtrlButtonDown = false;
		if (keyEvent->key() == Qt::Key_Left) {
			LeftArrowButtonDown = false;
			if (mainview->isContactDown && !mainview->isAttack) {
				mainview->character->m_status = mainview->character->stand_L;			
			}				
		}
		if (keyEvent->key() == Qt::Key_Right) {
			RightArrowButtonDown = false;
			if (mainview->isContactDown && !mainview->isAttack) {
				mainview->character->m_status = mainview->character->stand_R;
			}				
		}
		if (keyEvent->key() == Qt::Key_Up) 
			UpArrowButtonDown = false;
		if (keyEvent->key() == Qt::Key_Down) 
			DownArrowButtonDown = false;		
		if (keyEvent->key() == Qt::Key_Z)
			ZButtonDown = false;
	}

	if (CtrlButtonDown) {
		if (mainview->character->m_status == mainview->character->stand_L) {
			if (mainview->isContactDown) {
				mainview->character->m_status = mainview->character->attack_L;
				mainview->isAttack = true;
			}
		}
		if (mainview->character->m_status == mainview->character->walk_L) {
			if (LeftArrowButtonDown) {
				if (mainview->isContactDown) {
					mainview->character->m_status = mainview->character->attack_L;
					mainview->isAttack = true;
				}
			}
		}

		if (mainview->character->m_status == mainview->character->stand_R) {
			if (mainview->isContactDown) {
				mainview->character->m_status = mainview->character->attack_R;
				mainview->isAttack = true;
			}
		}

		if (mainview->character->m_status == mainview->character->walk_R) {
			if (RightArrowButtonDown) {
				if (mainview->isContactDown) {
					mainview->character->m_status = mainview->character->attack_R;
					mainview->isAttack = true;
				}
			}
		}
	}

	if (AltButtonDown && !mainview->isAttack) {
		if (mainview->character->m_status == mainview->character->stand_L) {
			if (mainview->isContactDown) {
				mainview->character->m_status = mainview->character->jump_L;
				mainview->isJump = true;
			}			
		}
		if (mainview->character->m_status == mainview->character->walk_L) {
			if (LeftArrowButtonDown) {
				if (mainview->isContactDown) {
					mainview->character->m_status = mainview->character->jump_L;
					mainview->isJump = true;
				}				
			}
		}

		if (mainview->character->m_status == mainview->character->stand_R) {
			if (mainview->isContactDown) {
				mainview->character->m_status = mainview->character->jump_R;
				mainview->isJump = true;
			}			
		}

		if (mainview->character->m_status == mainview->character->walk_R) {
			if (RightArrowButtonDown) {
				if (mainview->isContactDown){
					mainview->character->m_status = mainview->character->jump_R;
					mainview->isJump = true;
				}			
			}
		}
	}

	if (LeftArrowButtonDown && !mainview->isAttack) {
		if (mainview->isContactDown && !mainview->isJump )
			mainview->character->m_status = mainview->character->walk_L;
		if (!mainview->isContactDown)
			mainview->character->m_status = mainview->character->jump_L;
	}

	if (RightArrowButtonDown && !mainview->isAttack) {
		if (mainview->isContactDown && !mainview->isJump)
			mainview->character->m_status = mainview->character->walk_R;
		if (!mainview->isContactDown)
			mainview->character->m_status = mainview->character->jump_R;
	}

	if (ZButtonDown) {
		mainview->CheckApple();
	}
	mainview->update();
	return QWidget::eventFilter(watched, e);
}

void AppMain::addframe() {
	mainview->addframe();
}

void AppMain::addoffset() {
	if (!mainview->isAttack) {
		if (LeftArrowButtonDown)
			mainview->addoffset(true);
		if (RightArrowButtonDown)
			mainview->addoffset(false);
	}	
}
void AppMain::addjump() {
	if (mainview->isJump)
		mainview->addjump();
}

void AppMain::addattack() {
	if (mainview->isAttack)
		mainview->addattack();
}

void AppMain::addy() {
	if (UpArrowButtonDown)
		mainview->addy(1);
	if (DownArrowButtonDown)
		mainview->addy(-1);
	mainview->addGravaty();
}

void AppMain::movelight() {
	mainview->MoveLight();
}

AppMain * AppMain::getInstance()
{
	if( !Instance )
	{
		Instance = new AppMain();
		return Instance;
	}
	else 
		return Instance;
}
