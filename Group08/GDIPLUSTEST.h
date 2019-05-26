#pragma once

#include "resource.h"
#include<gdiplus.h>
#include <iostream>
#include <vector>
#include "rapidxml-1.13/rapidxml_utils.hpp"

using namespace std;
using namespace Gdiplus;
#pragma comment (lib, "Gdiplus.lib")

#include<string>

//class Element {
//	friend class Attribute;
//public:
//	virtual void draw(HDC hdc) = 0;
//	Element();
//protected:
//	int _x, _y;
//};
class Attribute {
protected:
	string name;
public:
	Attribute()
	{
	}
	virtual char* getName() = 0;
	virtual void set(char* value/*, Element* in*/) = 0;
};

/*
The value read from the SVG by RapidXML is returned as a char array,
given in as a char*
Your task is to take that array, turn the number into int and set
it to the object
*/
class SVGx1 : public Attribute {
public:
	SVGx1();
	char* getName()
	{
		char *s = _strdup("x1");
		return s;
	}
	void set(char* value/*, Element* in*/);
	/*
	set the value to the _x elemnt of in
	*/
};

class SVGx2 : public Attribute {
public:
	SVGx2();
	char* getName()
	{
		char *s = _strdup("x2");
		return s;
	}
	void set(char* value/*, Element* in*/);
};

class SVGy1 : public Attribute {
public:
	SVGy1();
	char* getName()
	{
		char *s = _strdup("y1");
		return s;
	}	void set(char* value/*, Element* in*/);
};
class SVGy2 : public Attribute {
public:
	SVGy2();
	char* getName()
	{
		char *s = _strdup("y2");
		return s;
	}
	void set(char* value/*, Element* in*/);
};

class cx : public Attribute {
public:
	cx();
	char* getName()
	{
		char *s = _strdup("cx");
		return s;
	}
	void set(char* value/*, Element* in*/);
};

class cy : public Attribute {
public:
	cy();
	char* getName()
	{
		char *s = _strdup("cy");
		return s;
	}
	void set(char* value/*, Element* in*/);
};

class r : public Attribute {
public:
	r();
	char* getName()
	{
		char *s = _strdup("r");
		return s;
	}
	void set(char* value/*, Element* in*/);
};

class rx : public Attribute {
public:
	rx();
	char* getName()
	{
		char *s = _strdup("rx");
		return s;
	}
	void set(char* value/*, Element* in*/);
};

class ry : public Attribute {
public:
	ry();
	char* getName()
	{
		char *s = _strdup("ry");
		return s;
	}
	void set(char* value/*, Element* in*/);
};

class SVGFillColor : public Attribute {
public:
	SVGFillColor();
	char* getName()
	{
		char *s = _strdup("fill");
		return s;
	}	void set(char* value/*, Element* in*/);
	/*
	The input is of the form rgb(x,y,z)
	set in->fill_r = x; in->fill_g = y; fill_b = z;
	*/
};

class SVGStrokeColor : public Attribute {
public:
	SVGStrokeColor();
	char* getName()
	{
		char *s = _strdup("stroke");
		return s;
	}	void set(char* value/*, Element* in*/);
	/*
	The input is of the form rgb(x,y,z)
	set in->fill_r = x; in->fill_g = y; in->fill_b = =z;
	*/
};

class SVGStrokeWidth : public Attribute {
public:
	SVGStrokeWidth();
	char* getName()
	{
		char *s = _strdup("stroke-width");
		return s;
	}	void set(char* value/*, Element* in*/);
	/*
	  set in->stroke_width = value;
	*/
};

class SVGFillOpacity : public Attribute {
public:
	SVGFillOpacity();
	char* getName()
	{
		char *s = _strdup("fill-opacity");
		return s;
	}	void set(char* value/*, Element* in*/);
	/*
	  set in->fill_a = (value * 256) + 1 (turn it to int)
	*/
};

class SVGStrokeOpacity : public Attribute {
public:
	SVGStrokeOpacity();
	char* getName()
	{
		char *s = _strdup("stroke-opacity");
		return s;
	}	void set(char* value/*, Element* in*/);
	/*
	  set in->stroke_a = (value * 256) + 1 (turn it to int)
	*/
};

class SVGWidth : public Attribute {
public:
	SVGWidth();
	char* getName()
	{
		char *s = _strdup("width");
		return s;
	}	void set(char* value/*, Element* in*/);
	/*
	set in->_w = value;
	*/
};

class SVGHeight : public Attribute {
public:
	SVGHeight();
	char* getName()
	{
		char *s = _strdup("height");
		return s;
	}	void set(char* value/*, Element* in*/);
	/*
	set in->_h = value;
	*/
};

class SVGPoints : public Attribute {
public:
	SVGPoints();
	char* getName()
	{
		char *s = _strdup("points");
		return s;
	}	void set(char* value/*, Element* in*/);
	/*
	The input point list will be like this x1,y1 x2,y2 ...
	separate them and push into the vector so that it looks
	like this: {x1,y1,x2,y2,..}
	*/
};

class Shapes /*: public Element*/ {
protected:
	vector<Attribute*> attributes;
public:
	void setAttribute(char* attr_name, char* attr_value)
	{
		int size = attributes.size();
		for (int i = 0; i < size; i++)
		{
			if (this->attributes[i]->getName() == attr_name)
			{
				this->attributes[i]->set(attr_value);
				return;
			}
		}
	}

};


class rectangle : public Shapes {
private:
	vector<PointF> points;
	
public:
	rectangle(vector<PointF> o) : points(o) {}
	void MyPaint(HDC hdc)
	{
		Graphics graphics(hdc);
		Pen pen1(Color(200, 200, 0, 200));
		SolidBrush brush1(Color(50, 100, 0, 150));
		Pen pen2(Color(255, 0, 255, 255));
		SolidBrush brush2(Color(155, 0, 100, 255));

		//graphics.DrawRectangle()
		graphics.DrawRectangle(&pen1, 25, 25, 800, 400);
		graphics.FillRectangle(&brush1, 20, 20, 800, 400);
	}
};

class ellipse : public Shapes {
private:
	PointF mTam;
	float _width;
	float _height;
public:
	ellipse(PointF i, int width, int height) : mTam(i), _width(width), _height(height) {};
	void MyPaint(HDC hdc)
	{
		Graphics graphics(hdc);
		SolidBrush brush1(Color(255, 0, 0));
		SolidBrush brush2(Color(255, 250, 0));
		graphics.FillEllipse(&brush1, mTam.X, mTam.Y, _width, _height);

		graphics.FillEllipse(&brush2, mTam.X + 5, mTam.Y + 5, _width - 10, _height - 10);
	}
};

class polyLine : public Shapes {
private:
	vector<PointF> points;
public:
	/* Neu nguoi dung nhap vao mang Point thi f ep kieu lai ve PointF vi polyLine nhan vao 1 mang kieu PointF - not Point */
	/*polyLine(vector<Point> o) {
		for (auto& i : o) {
			points.push_back(PointF(float(i.X), float(i.Y)));
		}
	}*/
	polyLine(vector<PointF> o) : points(o) {}
	void MyPaint(HDC hdc)
	{
		Graphics graphics(hdc);
		Pen pen(Color(255, 255, 0, 255));
		graphics.DrawLines(&pen, points.data(), int(points.size()));
	}
};

class polygon : public Shapes {
private:
	vector<PointF> points;
public:
	/*polygon(vector<Point> o) {
		for (auto& i : o) {
			points.push_back(PointF(float(i.X), float(i.Y)));
		}
	}*/
	polygon(vector<PointF> o) : points(o) {}
	void MyPaint(HDC hdc)
	{
		Graphics graphics(hdc);
		Pen pen(Color(255, 200, 0));
		graphics.DrawPolygon(&pen, points.data(), int(points.size()));
		SolidBrush brush1(Color(255, 200, 0));
		graphics.FillPolygon(&brush1, points.data(), int(points.size()));
	}
};

void star(HDC hdc)
{
	Point *point = new Point[10];
	point[0] = Point(350, 75);
	point[1] = Point(379, 161);
	point[2] = Point(469, 161);
	point[3] = Point(397, 215);
	point[4] = Point(423, 301);
	point[5] = Point(350, 250);
	point[6] = Point(277, 301);
	point[7] = Point(303, 215);
	point[8] = Point(231, 161);
	point[9] = Point(321, 161);
	
	Point *point1 = new Point[10];
	point1[0] = Point(355, 80);
	point1[1] = Point(384, 166);
	point1[2] = Point(474, 166);
	point1[3] = Point(402, 220);
	point1[4] = Point(428, 306);
	point1[5] = Point(355, 255);
	point1[6] = Point(282, 306);
	point1[7] = Point(308, 220);
	point1[8] = Point(236, 166);
	point1[9] = Point(326, 166);

	Graphics graphics(hdc);
	Pen pen(Color(255, 0 ,0));
	Pen pen1(Color(255, 250, 0));

	SolidBrush brush1(Color(255, 0, 0));//do
	SolidBrush brush2(Color(255, 250, 0));//vang

	graphics.DrawPolygon(&pen, point, 10);
	graphics.DrawPolygon(&pen1, point, 10);
	graphics.FillPolygon(&brush2, point, 10);
	graphics.FillPolygon(&brush1, point1, 10);
	delete[]point;
	delete[]point1;

}
