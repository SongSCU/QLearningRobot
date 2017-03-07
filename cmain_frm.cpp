/**************************************************************************
File:         cmain_frm.cpp
Author:       Song Xiaofeng
Date:         2016-05-04
Description:
**************************************************************************/
#include "cmain_frm.h"
#include "ui_cmain_frm.h"
#include "baseDataStruct.h"
#include <QtCore/QDebug>
#include <QtWidgets/QMessageBox>
#include <QWheelEvent>
#include <QMouseEvent>
double g_maxMapValue = 0;
double g_minMapValue = 0;
CMainFrm::CMainFrm(QWidget *parent) :
	QWidget(parent),
	ui(new Ui::CMainFrm)
{
	initView();
	initDefaultValue();
	initEnvironment();
	initUIV();
	initUIQ();

}

void CMainFrm::initView() {
	ui->setupUi(this);
	m_scene = new QGraphicsScene(this);
	m_view = new CSceneView(ui->frame);

   initPixRobot();

	m_view->setDragMode(QGraphicsView::ScrollHandDrag);
	m_totalIterations = 0;
	QVBoxLayout *layout = new QVBoxLayout(ui->frame);
	layout->addWidget(m_view);

	m_view->setScene(m_scene);
	fSetStyle();
}

void CMainFrm::initDefaultValue() {

	//set default values
	m_width = 4;
	m_height = 3;
	m_in_buf = new string*[m_width];
	for (int i = 0; i < m_width; i++) {
		m_in_buf[i] = new string[m_height];
	}
    for (int j = 0; j < m_height; j++)
		for (int i = 0; i < m_width; i++)
			m_in_buf[i][j] = "0";
	m_in_buf[1][1] = "#";
    m_in_buf[3][2] = "1";
	m_in_buf[3][1] = "-1";

	m_noise = 0.2;
	m_discount = 0.9;
	m_living_reward = 0;
	m_epsion = 0.5;
	m_alpha = 0.2;

	g_maxMapValue = getMaxMapValue();
	g_minMapValue = getMinMapValue();
}

CMainFrm::~CMainFrm()
{
	delete ui;
	for (int i = 0; i < 12; i++) {
		delete m_rectV[i];
		delete m_rectQ[i];
	}
	delete[] m_rectV;
	delete[] m_rectQ;
}

void CMainFrm::initEnvironment() {

    m_evironment = Evironment::create(m_width, m_height,m_in_buf,
        m_noise, m_living_reward);
	m_robot = new QLearningRobot(m_width, m_height, 0, 0,
        m_epsion, m_alpha, m_discount);

}

void CMainFrm::initUIQ() {
	float gridSize = 100;
	float width = gridSize*m_width;
	float height = gridSize*m_height;
    float bgX = -300 + width + 50;
    float bgY = -150;
	int size = m_width*m_height;
	m_rectQ = new CRectItem*[size];
	int gridX, gridY;
	QRectF rectT;
	for (int i = 0; i < size; i++) {
		m_rectQ[i] = new CRectItem();
		gridX = i%m_width;
		gridY = i / m_width;
		rectT.setRect(bgX + gridX*(gridSize), bgY + gridY*(gridSize), gridSize, gridSize);
		m_rectQ[i]->setRect(rectT);
		m_scene->addItem(m_rectQ[i]);
		m_rectQ[i]->setBrush(Qt::black);
		m_rectQ[i]->setTRect(rectT);
        m_rectQ[i]->setZValue(0);
        string s = m_in_buf[gridX][m_height-gridY-1];
		if (s == "0") {
			m_rectQ[i]->initQModeUI();
		}
		else if (s == "#") {
			m_rectQ[i]->setBrush(QColor("#DDDD00"));
			m_rectQ[i]->m_isWall = true;
		}
		else {
			m_rectQ[i]->initVModeUI();
		}

	}
}

void CMainFrm::initUIV() {
	float gridSize = 100;
	//float width=gridSize*m_width;
	//float height=gridSize*m_height;
    float bgX =-300;
    float bgY =-150;
	int size = m_width*m_height;
	m_rectV = new CRectItem*[size];
	int gridX, gridY;
	QRectF rectT;
	for (int i = 0; i < size; i++) {
		m_rectV[i] = new CRectItem();
		gridX = i%m_width;
		gridY = i / m_width;
		rectT.setRect(bgX + gridX*(gridSize), bgY + gridY*(gridSize), gridSize, gridSize);
		m_rectV[i]->setRect(rectT);
		m_scene->addItem(m_rectV[i]);
		m_rectV[i]->setBrush(Qt::black);
		m_rectV[i]->setTRect(rectT);
        m_rectV[i]->setZValue(0);
        string s = m_in_buf[gridX][m_height-gridY-1];
		if (s == "0") {
			m_rectV[i]->setHasDirection(true);
			m_rectV[i]->initVModeUI();
		}
		else if (s == "#") {
			m_rectV[i]->setBrush(QColor("#DDDD00"));
			m_rectV[i]->m_isWall = true;
		}
		else {
			m_rectV[i]->initVModeUI();
		}
	}
}

void CMainFrm::initPixRobot(){
    m_pixRobot=new QGraphicsPixmapItem();
    m_pixRobot->setPixmap(QPixmap(":/picture/robot.png"));
    m_scene->addItem(m_pixRobot);
    m_pixRobot->setZValue(2);
    m_pixRobot->hide();

    m_point=new QGraphicsEllipseItem(0,0,10,10);
    m_point->setBrush(QBrush(Qt::blue));
    m_scene->addItem(m_point);
    m_point->setZValue(2);
    m_point->hide();
}

void CMainFrm::fSetStyle() {
	//this->setStyleSheet();
	m_scene->setBackgroundBrush(QBrush(Qt::gray));
}

double CMainFrm::getMaxMapValue() {
	double max = 0;
	for (int j = 0; j < m_height; j++)
		for (int i = 0; i < m_width; i++) {
			double temp = QString(m_in_buf[i][j].c_str()).toDouble();
			if (temp > max) max = temp;
		}
	return max;
}

double CMainFrm::getMinMapValue() {
	double min = 0;
	for (int j = 0; j < m_height; j++)
		for (int i = 0; i < m_width; i++) {
			double temp = QString(m_in_buf[i][j].c_str()).toDouble();
			if (temp < min) min = temp;
		}
	return min;
}

void CMainFrm::on_pushButton_reset_clicked()
{
	// reset parameters
	if (false == resetParameter())
		return;


    m_evironment->setLivingReward(m_living_reward);
    m_evironment->setNoise(m_noise);
    m_robot->setAlpha(m_alpha);
    m_robot->setDiscount(m_discount);
    m_robot->setEpisilon(m_epsion);
    //delete m_robot;
    //m_robot = 0;

   // m_robot = new QLearningRobot(m_width, m_height, 0, 0,
    //    m_epsion, m_alpha, m_discount);


	//init environment
    //initEnvironment();

	//update map item values
    /*for (int i = 0; i < m_width*m_height; i++) {
		m_rectQ[i]->clearValues();
		m_rectV[i]->clearValues();
		m_rectQ[i]->updateItem();
		m_rectV[i]->updateItem();
	}
	m_totalIterations = 0;
    resetTotal();*/
}

void CMainFrm::on_pushButton_next_clicked()
{
	/////////////////////////////////
	bool ok = true;
	int step = ui->lineEdit_next->text().toInt(&ok);
	if (!ok) {
		QMessageBox::warning(this, tr("warning"), tr("invalid input!"));
		return;
	}
	if (!(step >= 0 && step <= 100000)) {
		QMessageBox::warning(this, tr("warning"), tr("the value of step out of range!"));
		return;
	}
	//////////////////////////////////

	for (int s = step; s > 0; s--) {
		m_robot->runNextIteration(1);
	}
	m_totalIterations += step;
	resetTotal();
	for (int j = 0; j < m_height; j++) {
		for (int i = 0; i < m_width; i++) {
            double v = m_robot->getValueMap()[i][m_height-j-1].getValue();
            double q0 = m_robot->getValueMap()[i][m_height-j-1].getQValue(0);
            double q1 = m_robot->getValueMap()[i][m_height-j-1].getQValue(1);
            double q2 = m_robot->getValueMap()[i][m_height-j-1].getQValue(2);
            double q3 = m_robot->getValueMap()[i][m_height-j-1].getQValue(3);

            //int p = m_robot->getValueMap()[i][m_height-j-1].getPolicy();
            int p = m_robot->getValueMap()[i][m_height-j-1].getPolicy();
			m_rectV[m_width*j + i]->setVValue(v);
			m_rectV[m_width*j + i]->setDirection(p);
			m_rectV[m_width*j + i]->updateItem();

			m_rectQ[m_width*j + i]->setVValue(v);
			m_rectQ[m_width*j + i]->setQValue(q0, 0);
			m_rectQ[m_width*j + i]->setQValue(q1, 1);
			m_rectQ[m_width*j + i]->setQValue(q2, 2);
			m_rectQ[m_width*j + i]->setQValue(q3, 3);
			m_rectQ[m_width*j + i]->updateItem();

		}
	}
    Vect2 vect2=m_robot->getPositon();
    setRobotPos(vect2);
}

void CMainFrm::on_pushButton_reset_map_clicked() {
	//reset map values
	if (false == resetMapValue())
		return;
	g_maxMapValue = getMaxMapValue();
	g_minMapValue = getMinMapValue();
	//clear all
	delete m_robot;
	m_robot = 0;
	m_scene->clear();

    initPixRobot();

	m_totalIterations = 0;
	resetTotal();
	//init all
	initEnvironment();
	initUIQ();
	initUIV();
    Vect2 vect2=m_robot->getPositon();
    setRobotPos(vect2);
}

bool CMainFrm::resetMapValue() {
	/////////////////////////////////////
	bool ok_w = true, ok_h = true;
	int width = ui->lineEdit_w->text().toInt(&ok_w);
	int height = ui->lineEdit_h->text().toInt(&ok_h);
	if (!(width > 1 && width <= 8)) {
		QMessageBox::warning(this, tr("warning"), tr("the value of 'map-width' is out of range!"));
		return false;
	}
	if (!(height > 1 && height <= 8)) {
		QMessageBox::warning(this, tr("warning"), tr("the value of 'map-height' is out of range!"));
		return false;
	}
	/////////////////////////////////////
	string ** sArray = new string*[width];
	for (int i = 0; i < width; i++) {
		sArray[i] = new string[height];
	}
	bool ok_map = true;
	for (int j = 0; j < height; j++)
		for (int i = 0; i < width; i++) {
            sArray[i][height-j-1] = ui->tableWidget->item(j, i)->text().toStdString();
		}
	//reset map values
	for (int i = 0; i < m_width; i++)
		delete[] m_in_buf[i];
	delete[] m_in_buf;

	m_width = width;
	m_height = height;

	m_in_buf = new string*[m_width];
	for (int i = 0; i < m_width; i++)
		m_in_buf[i] = new string[m_height];

	for (int j = 0; j < height; j++)
		for (int i = 0; i < width; i++) {
			m_in_buf[i][j] = sArray[i][j];
		}
	//delete sArray
	for (int i = 0; i < width; i++)
		delete[] sArray[i];
	delete[] sArray;
	//
	return true;
}

bool CMainFrm::resetParameter() {
	////////////////////////////////////////////////////////////////
	bool ok1 = true, ok2 = true, ok3 = true, ok4 = true, ok5 = true;
	m_noise = ui->lineEdit_noise->text().toDouble(&ok1);
	m_discount = ui->lineEdit_discount->text().toDouble(&ok2);
	m_living_reward = ui->lineEdit_reward->text().toDouble(&ok3);
	m_epsion = ui->lineEdit_epsion->text().toDouble(&ok4);
	m_alpha = ui->lineEdit_alpha->text().toDouble(&ok5);
	if (!(ok1 && ok2 && ok3 && ok4 && ok5)) {
		QMessageBox::warning(this, tr("warning"), tr("invalid input!"));
		return false;
	}
	if (!(m_noise >= 0 && m_noise <= 1)) {
		QMessageBox::warning(this, tr("warning"), tr("the value of 'noise' is out of range!"));
		return false;
	}
	if (!(m_discount >= 0 && m_discount <= 1)) {
		QMessageBox::warning(this, tr("warning"), tr("the value of 'discount' is out of range!"));
		return false;
	}
	//if (!(m_living_reward >= 0 && m_living_reward <= 1)) {
	//	QMessageBox::warning(this, tr("warning"), tr("the value of 'living reward' is out of range!"));
	//	return false;
	//}
	if (!(m_epsion >= 0 && m_epsion <= 1)) {
		QMessageBox::warning(this, tr("warning"), tr("the value of 'epsilon' is out of range!"));
		return false;
	}
	if (!(m_alpha >= 0 && m_alpha <= 1)) {
		QMessageBox::warning(this, tr("warning"), tr("the value of 'alpha' is out of range!"));
		return false;
	}
	/////////////////////////////////////////////////////////////////////////////
	return true;
}

void CMainFrm::resetTotal() {
	ui->label_iterNum->setText(QString::number(m_totalIterations));
}

void CMainFrm::on_lineEdit_w_editingFinished() {

	/////////////////////////////////////
	bool ok_w = true;
	int width = ui->lineEdit_w->text().toInt(&ok_w);
	if (!(width > 1 && width <= 8)) {
		QMessageBox::warning(this, tr("warning"), tr("the value of 'map-width' is out of range!"));
		return;
	}
    ui->tableWidget->setColumnCount(width);
    /////////////////////////////////////
}

void CMainFrm::on_lineEdit_h_editingFinished() {
	bool ok_h = true;
	int height = ui->lineEdit_h->text().toInt(&ok_h);
	if (!(height > 1 && height <= 8)) {
		QMessageBox::warning(this, tr("warning"), tr("the value of 'map-height' is out of range!"));
		return;
	}
    ui->tableWidget->setRowCount(height);
}

void CMainFrm::setRobotPos(Vect2 pos){
    int x=pos.x;
    int y=m_height-pos.y-1;
    qDebug()<<x<<y;
    QPointF p(m_rectV[x+y*m_width]->rect().x(),m_rectV[x+y*m_width]->rect().y());
    m_pixRobot->setPos(p);
    QPointF p2(m_rectQ[x+y*m_width]->rect().x()+45,m_rectQ[x+y*m_width]->rect().y()+45);
    m_point->setPos(p2);

    m_pixRobot->show();
    m_point->show();
}

CSceneView::CSceneView(QWidget* parent) {
	this->setParent(parent);
	this->setSceneRect(-5000, -5000, 10000, 10000);
	this->setDragMode(QGraphicsView::ScrollHandDrag);
	this->setResizeAnchor(QGraphicsView::AnchorUnderMouse);
	this->setTransformationAnchor(QGraphicsView::AnchorUnderMouse);
	this->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	this->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	this->setAcceptDrops(true);
	this->show();
}

void CSceneView::wheelEvent(QWheelEvent *event) {
	int numDegrees = event->delta() / 8;
	int numSteps = numDegrees / 15;
	float s = 1 + ((float)numSteps) / 10;
	this->scale(s, s);
}

void CSceneView::mousePressEvent(QMouseEvent *event) {
	if (event->button() == Qt::RightButton) {
		this->setDragMode(QGraphicsView::ScrollHandDrag);
	}
	else {
		QGraphicsView::mousePressEvent(event);
	}
}

void CSceneView::mouseReleaseEvent(QMouseEvent *event) {
	if (event->button() == Qt::RightButton) {
		this->setDragMode(QGraphicsView::RubberBandDrag);
	}
	else {
		QGraphicsView::mouseReleaseEvent(event);
	}
}
