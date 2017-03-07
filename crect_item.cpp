/**************************************************************************
File:         cmain_frm.cpp
Author:       Song Xiaofeng
Date:         2016-05-05
Description:
**************************************************************************/
#include "crect_item.h"
#include <QtGui/QPen>
#include <QtGui/QFont>
#include <QtCore/QDebug>
const QPen rectPen(QBrush(Qt::white), 3);
const QPen triPen(QBrush(Qt::white), 2);
const QFont textFont("Times", 7, QFont::Bold);
const QColor textColor(Qt::white);
const QBrush triDirBrush(Qt::white);
const QBrush wallBrush(QColor("#DDDD00"));
CRectItem::CRectItem()
{
	m_text = 0;
	m_texts = 0;
	m_triItem = 0;
    m_triDirection = 0;
	m_vValue = 0;
	m_isWall = false;
	for (int i = 0; i < 4; i++)
		m_qValues[i] = 0;
    m_direction = 0;
	m_hasDirection = false;

	this->setPen(rectPen);
}

void CRectItem::initVModeUI() {
	/////////////////////////////////
	float x = m_rect.x();
	float y = m_rect.y();
	float w = m_rect.width();
	float h = m_rect.height();
	m_text = new QGraphicsTextItem;
	m_text->setParentItem(this);
	QString s;
	s.setNum(m_vValue);
	m_text->setPlainText(s);
	m_text->setPos(x + w / 2 - 15, y + h / 2 - 10);
	m_text->setDefaultTextColor(textColor);
	m_text->setFont(textFont);
	/////////////////////////////////
	if (!m_hasDirection) return;
	m_triDirection = new QGraphicsPolygonItem*[4];
	for (int i = 0; i < 4; i++) {
		m_triDirection[i] = new QGraphicsPolygonItem;
		m_triDirection[i]->setParentItem(this);
	}
	QPolygonF polygon[4];
    polygon[2] << QPointF(x + w / 2, y + h) << QPointF(x + w / 2 - 6, y + h - 8)  //down
		<< QPointF(x + w / 2 + 6, y + h - 8);
	polygon[1] << QPointF(x + w, y + h / 2) << QPointF(x + w - 8, y + h / 2 + 6)  //right
		<< QPointF(x + w - 8, y + h / 2 - 6);
    polygon[0] << QPointF(x + w / 2, y) << QPointF(x + w / 2 - 6, y + 8)      //up
		<< QPointF(x + w / 2 + 6, y + 8);
	polygon[3] << QPointF(x, y + h / 2) << QPointF(x + 8, y + h / 2 + 6)      //left
		<< QPointF(x + 8, y + h / 2 - 6);
	for (int i = 0; i < 4; i++) {
		m_triDirection[i]->setPolygon(polygon[i]);
		m_triDirection[i]->setBrush(triDirBrush);
		m_triDirection[i]->setVisible(false);
	}
	m_triDirection[m_direction]->setVisible(true);
	///////////////////////////////////
}

void CRectItem::initQModeUI() {

	float x = m_rect.x();
	float y = m_rect.y();
	float w = m_rect.width();
	float h = m_rect.height();
	m_triItem = new QGraphicsPolygonItem*[4];
	for (int i = 0; i < 4; i++) {
		m_triItem[i] = new QGraphicsPolygonItem;
		m_triItem[i]->setParentItem(this);
		m_triItem[i]->setPen(triPen);
	}
	QPointF p0(x, y);
	QPointF p1(x + w, y);
	QPointF p2(x, y + h);
	QPointF p3(x + w, y + h);
	QPointF p4(x + w / 2, y + h / 2);

	QPolygonF polygonL;
	polygonL << p0 << p2 << p4;
	QPolygonF polygonR;
	polygonR << p1 << p3 << p4;
	QPolygonF polygonU;
	polygonU << p0 << p1 << p4;
	QPolygonF polygonD;
	polygonD << p2 << p3 << p4;


	m_triItem[3]->setPolygon(polygonL);
    m_triItem[0]->setPolygon(polygonU);
	m_triItem[1]->setPolygon(polygonR);
    m_triItem[2]->setPolygon(polygonD);

	m_texts = new QGraphicsTextItem*[4];
	for (int i = 0; i < 4; i++) {
		m_texts[i] = new QGraphicsTextItem;
		m_texts[i]->setParentItem(this);
		QString s;
		s.setNum(m_qValues[i]);
		m_texts[i]->setPlainText(s);
		m_texts[i]->setDefaultTextColor(textColor);
		m_texts[i]->setFont(textFont);
	}
	m_texts[3]->setPos(x + 10, y + h / 2 - 10);
    m_texts[0]->setPos(x + w / 2 - 15, y + 10);
	m_texts[1]->setPos(x + w - 40, y + h / 2 - 10);
    m_texts[2]->setPos(x + w / 2 - 15, y + h - 30);

}

void CRectItem::updateItem() {
    char buf[20];
	//update VValue
	if (m_text != 0) {
        sprintf(buf,"%.3lf",m_vValue);
        QString s(buf);
		m_text->setPlainText(s);
	}
	//update QValue
	if (m_texts != 0) {
		for (int i = 0; i < 4; i++) {
            sprintf(buf,"%.3lf",m_qValues[i]);
            QString s(buf);
			m_texts[i]->setPlainText(s);
		}
	}
	//update direction
	if (m_hasDirection) {
		for (int i = 0; i < 4; i++) {
			m_triDirection[i]->setVisible(false);
		}
		m_triDirection[m_direction]->setVisible(true);
	}
	//update color
	if (m_isWall == true) {
		this->setBrush(wallBrush);
	}
	else if (m_triItem == 0) {
		this->setBrush(QBrush(getGradientColor(m_vValue)));
	}
	else if (m_triItem != 0) {
		for (int i = 0; i < 4; i++)
			m_triItem[i]->setBrush(QBrush(getGradientColor(m_qValues[i])));
	}
}

QColor CRectItem::getGradientColor(double value) {
	double v = value;
	if (v == 0) {
		return QColor("#000000");
	}
	else if (v > 0) {
		v = v / g_maxMapValue;
		return QColor(0, v * 255, 0);
	}
	else if (v < 0) {
		//v = -1 * v;
		v = v / g_minMapValue;
		return QColor(v * 255, 0, 0);
	}

}

void CRectItem::clearValues() {
	m_vValue = 0;
	for (int i = 0; i < 4; i++)
		m_qValues[i] = 0;
}
