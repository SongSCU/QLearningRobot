/**************************************************************************
File:         cmain_frm.h
Author:       Song Xiaofeng
Date:         2016-05-04
Description:
**************************************************************************/
#ifndef CMAIN_FRM_H
#define CMAIN_FRM_H

#include <QtWidgets/QWidget>
#include <QtWidgets/QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsPixmapItem>
#include "crect_item.h"
#include <string>
#include "Evironment.h"
#include "QLearningRobot.h"

using namespace std;
namespace Ui {
	class CMainFrm;
}

extern double g_maxMapValue;
extern double g_minMapValue;
//////////////////////////////////////////////////////////////////
///    Class:  CSceneView
///    Brief:  
//////////////////////////////////////////////////////////////////
class CSceneView : public QGraphicsView {
///////////////////////////////////////////////////////////////////
//all public functions are here
///////////////////////////////////////////////////////////////////
public:
	CSceneView(QWidget* parent = 0);
///////////////////////////////////////////////////////////////////
//all private functions are here
///////////////////////////////////////////////////////////////////
private:
	void wheelEvent(QWheelEvent* event);
	void mousePressEvent(QMouseEvent * event);
	void mouseReleaseEvent(QMouseEvent * event);
};
//////////////////////////////////////////////////////////////////
///    Class:  CMainFrm
///    Brief:  
//////////////////////////////////////////////////////////////////
class CMainFrm : public QWidget
{
	Q_OBJECT
///////////////////////////////////////////////////////////////////
//all public functions are here
///////////////////////////////////////////////////////////////////
public:
	explicit CMainFrm(QWidget *parent = 0);
	~CMainFrm();
	double getMaxMapValue();
	double getMinMapValue();
///////////////////////////////////////////////////////////////////
//all private slots are here
///////////////////////////////////////////////////////////////////
private slots:
	void on_pushButton_reset_map_clicked();
	void on_pushButton_reset_clicked();
	void on_pushButton_next_clicked();
	void on_lineEdit_w_editingFinished();
	void on_lineEdit_h_editingFinished();
///////////////////////////////////////////////////////////////////
//all properties are here
///////////////////////////////////////////////////////////////////
private:
	Ui::CMainFrm *ui;
	QGraphicsScene *m_scene;
	CSceneView * m_view;
	CRectItem ** m_rectV;
	CRectItem ** m_rectQ;
	string **m_in_buf;
	Evironment * m_evironment;
	QLearningRobot * m_robot;
    QGraphicsPixmapItem * m_pixRobot;
    QGraphicsEllipseItem * m_point;
	int m_width;
	int m_height;
	double m_noise;
	double m_discount;
	double m_living_reward;
	double m_epsion;
	double m_alpha;
	int m_totalIterations;
///////////////////////////////////////////////////////////////////
//all private functions are here
///////////////////////////////////////////////////////////////////
private:
	void initUIQ();
	void initUIV();
	void initEnvironment();
	void fSetStyle();
	bool resetMapValue();
	bool resetParameter();
	void initDefaultValue();
	void initView();
    void initPixRobot();
	void resetTotal();
    void setRobotPos(Vect2 pos);

};

#endif // CMAIN_FRM_H
