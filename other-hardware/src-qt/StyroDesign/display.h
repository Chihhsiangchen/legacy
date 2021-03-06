#ifndef DISPLAY_H
#define DISPLAY_H

#include <QWidget>
#include <QString>
#include <QStringList>
#include <QTextEdit>
#include <QList>
#include <QImage>

#include "controllPoint.h"

class DrawArea : public QWidget {
	Q_OBJECT

public:
	DrawArea(QTextEdit *textedit, QWidget *parent);
	~DrawArea();
	void setZoom(float zoom);
	float getZoom();
	void setImage(QString fileName);
	void setShowControlElements(bool state);
	QString getChainCode();

protected:
	void paintEvent(QPaintEvent *event);
	void mousePressEvent(QMouseEvent * e);
	void keyPressEvent(QKeyEvent * e);
	void mouseReleaseEvent(QMouseEvent * e);
	void mouseMoveEvent(QMouseEvent * e);
	
public slots:
	void checkAndDraw();

private:
	void drawLineTo(Point p, QPainter *g, int lineNo);
	void drawBezier(Point p2, Point p3, Point p4, QPainter *g, int lineNo);
	void drawBezierRec(Point p1, Point p2, Point p3, Point p4, int level, QPainter *g);
	void drawCircle(Point p2, float angle, QPainter *g, int lineNo);
	
	Point midpoint(Point p1, Point p2);
	
	void chainLineTo(Point p);
	void chainBezier(Point p2, Point p3, Point p4);
	void chainBezierRec(Point p1, Point p2, Point p3, Point p4, int level);
	void chainCircle(Point p2, float angle);
	void startChain(int px, int py);
	void addToChain(int px, int py);
	void addControlPoint(Point p, int line, int firstElement, QPainter *g, bool hasAngle = false, float angle = 0.0);
	void deleteControlPoints();
	
	void scaleP(float sx, float sy, Point scaleP);
	void rotateP(float a, Point rotateP);
	void identity();
	void identityInverse();
	
	void translate(Point p);
	void multMatrix(float *mat1, float *mat2, float *resultMatrix);
	Point transform(Point p);
	void calcInverse();
	Point transformBack(Point p, float* inverse);
	
	/*  0 1 2
		3 4 5
		6 7 8
	 */
	float curTrans[9];
	float curTransInverse[9];
	float dragInverse[9];
	
	QList<ControllPoint*> controllPoints;
	QString chain;
	QStringList list;
	int currentAngle;
  	int height, width;
	float zoom, scale;
	
	int chainPosX;
	int chainPosY;
	int drawLevel;
	int chainLevel;
	Point CurrentPoint;
	Point DragPoint;
	int dragLine;
	int dragElement;
	bool drag;
	bool dragHasAngle;
	bool dragAbort;
	int dragImage;
	float dragAngle;
	bool imageScaleChanged;
	bool showControlElements;
	QTextEdit *text;
	QImage image;
	QImage imageBuf;
	Point imageBegin, imageEnd, imageLastPos;
};

#endif // DISPLAY_H
