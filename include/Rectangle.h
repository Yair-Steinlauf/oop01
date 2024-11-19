#pragma once
	
#include <Vertex.h>
#include <Board.h>

class Rectangle {
public:
	Rectangle(const Vertex& bottomLeft, const Vertex& topRight); //constructor
	Rectangle(const Vertex vertices[2]);
	Rectangle(double x, double y, double width, double height);
	Rectangle(const Vertex& topRight, double width, double height);
	Vertex getBottomLeft()const;
	Vertex getTopRight()const;
	double getWidth()const;
	double getHeight()const;
	void draw(Board& board) const;
	Rectangle getBoundingRectangle()const;
	double getPerimeter() const;
	double getArea() const;
	Vertex getCenter() const;
	bool scale(double factor);
	void setToDef();
private:
	Vertex m_bottom_left,
		m_top_right;
	bool isValid(const Vertex& bottomLeft, const Vertex& topRight);
	void setVertex(double x, double y, Vertex& wanted);
};