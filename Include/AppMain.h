#ifndef APPMAIN_H
#define APPMAIN_H

#include <QtWidgets/QMainWindow>
#include <QtWidgets/QWidget>
#include <QtWidgets/QFileDialog>
#include "ui_AppMain.h"
#include <QtOpenGL/qgl.h>
#include "MainView.h"  

class AppMain : public QMainWindow
{
	Q_OBJECT

public:
	AppMain(QWidget *parent = 0);
	~AppMain();
	static AppMain *getInstance();
	static AppMain *Instance;
public:

	// the widgets that make up the Window
	MainView* mainview;
	QTimer *myTimer;
	QTimer *myTimer2;
	QTimer *myTimer3;
	QTimer *myTimer4;
	QTimer *myTimer5;
	QTimer *myTimer6;
	bool LeftMouseDown = false;
	bool RightMouseDown = false;
	bool AltButtonDown = false;
	bool CtrlButtonDown = false;
	bool RightArrowButtonDown = false;
	bool LeftArrowButtonDown = false;
	bool UpArrowButtonDown = false;
	bool DownArrowButtonDown = false;
	bool ZButtonDown = false;
	
private:
	Ui::AppMainClass ui;

	private slots:
		void addframe();
		void addoffset();
		void addjump();
		void addattack();
		void addy();
		void movelight();

protected:
	bool eventFilter(QObject *watched, QEvent *e); 
};

#endif // APPMAIN_H
