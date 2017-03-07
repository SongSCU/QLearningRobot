/**************************************************************************
File:         ccret_item.h
Author:       Song Xiaofeng
Date:         2016-05-05
Description:
**************************************************************************/
#ifndef CRECTITEM_H
#define CRECTITEM_H

#include <QtWidgets/QGraphicsRectItem>
#include <QtWidgets/QGraphicsPolygonItem>
#include <QtWidgets/QGraphicsTextItem>
#include <QtGui/QBrush>
extern double g_maxMapValue;
extern double g_minMapValue;
//////////////////////////////////////////////////////////////////
///    Class:  CRectItem
///    Brief:  
//////////////////////////////////////////////////////////////////
class CRectItem : public QGraphicsRectItem
{
private:
	double m_vValue;
	double m_qValues[4];
	int m_direction;
	QRectF m_rect;
	bool m_hasDirection;
	QGraphicsPolygonItem ** m_triItem;
	QGraphicsTextItem * m_text;
	QGraphicsTextItem ** m_texts;
	QGraphicsPolygonItem ** m_triDirection;
public:
	bool m_isWall;
public:
	CRectItem();
	double getVValue() { return m_vValue; }
	double getQValue(int index) { return m_qValues[index]; }
	void  setVValue(double value) { m_vValue = value; }
	void  setQValue(double value, int index) { m_qValues[index] = value; }
	void  setTRect(QRectF rect) { m_rect = rect; }
	void  setDirection(int direction) { m_direction = direction; }
	void  setHasDirection(bool b) { m_hasDirection = b; }
	void  initQModeUI();
	void  initVModeUI();
	void  setTriColor(QColor color, int index) {
		if (m_triItem[index] != NULL)
			m_triItem[index]->setBrush(QBrush(color));
	}
	void updateItem();
	void clearValues();
private:
	QColor getGradientColor(double value);
};

#endif // CRECTITEM_H
