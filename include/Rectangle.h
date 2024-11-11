#include <Board.h>
#include <Vertex.h>
#pragma once

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
	bool isValid(const Vertex& bottomLeft, const Vertex& topRight);
	void setVertex(double x, double y, Vertex &wanted);
	void draw(Board& board);
private:
	Vertex m_bottom_left,
		m_top_right;
	double m_widgth,
		m_heigth;

};