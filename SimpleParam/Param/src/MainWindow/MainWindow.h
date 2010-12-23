#ifndef MAINWINDOW_H_
#define MAINWINDOW_H_

#include <QtGui/QMainWindow>

class QGLViewer;
class CrossParamControl;

class QActionGroup;
class QAction;
class QMenu;
class QTextEdit;

#include <QStyle>

class MainWindow : public QMainWindow
{
	Q_OBJECT

public:
	MainWindow(QWidget* parent=0);
	~MainWindow();

public:
	void setStyle(QStyle* style);

private: // inherited
//	void resizeEvent(QResizeEvent * /* event */);

private:
	void createActions();
	void createMenus();
	void createToolBars();

private slots:
	void openModel();
	void saveModel();
	void openTextureImage();
	void openQuadFile();
	void saveAsBmp();
	void recentFiles();

	void toobBar();
	void stateBar();

	void about();

	void mouseSpin();
	void mouseMove();
	void mouseZoom();

	void findCorrespondingOnA();
	void findCorrespondingOnB();
private:
	// menus
	QMenu* fileMenu;
	QMenu* editMenu;
	QMenu* viewMenu;
	QMenu* windowMenu;
	QMenu* quadMenu;
	QMenu* helpMenu;

	// toolbars
	QToolBar* fileToolBar;
	QToolBar* mouseActToolBar;

	// file menu actions
	QAction* openModelAct;
	QAction* saveModelAct;
	QAction* saveAsBmpAct;
	QAction* recentFileAct;
	QAction* exitAct;

	QAction* openTextureFileAct;
	QAction* openQuadFileAct;


	// view menu actions
	QAction* toolBarAct;
	QAction* stateBarAct;

	// window menu actions

	// quad menu actions
	QAction* loadEigenAct;
	QAction* connectLineAct;
	QAction* removeNoiseAct;

	// help menu actions;
	QAction* aboutAct;

	// mouse actions
	QAction* mouseSpinAct;
	QAction* mouseMoveAct;
	QAction* mouseZoomAct;

public:
	QGLViewer* glViewer_1;
	QGLViewer* glViewer_2;

	CrossParamControl* m_cross_param_control;
};

#endif
