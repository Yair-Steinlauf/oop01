#include <iostream>
#include <Rectangle.h>


Rectangle::Rectangle(const Vertex& bottomLeft, const Vertex& topRight)
	: m_bottom_left(bottomLeft), m_top_right(topRight) //constructor
{
	if (!isValid(m_bottom_left, m_top_right))
	{//not valid -> default values
		m_bottom_left = Vertex(20, 10);
		setVertex(20, 10, m_bottom_left);
		setVertex(30, 20, m_top_right);
	}
	m_heigth = m_top_right.m_row - m_bottom_left.m_row;
	m_widgth = m_top_right.m_col - m_bottom_left.m_col;
}
Rectangle::Rectangle(const Vertex vertices[2])
{
	Rectangle(vertices[0], vertices[1]);
}
Rectangle::Rectangle(double x, double y, double width, double height)
{
	setVertex(x, y, m_bottom_left);
	setVertex(x + width, y + height, m_top_right);
	Rectangle(m_bottom_left, m_top_right);//this counstractor 
	//valid check will fail if height or width is negative
}

Rectangle::Rectangle(const Vertex& topRight, double width, double height)
{
	setVertex(topRight.m_col - width, topRight.m_row - height, m_bottom_left);
	Rectangle(m_bottom_left, topRight);
}

bool Rectangle::isValid(const Vertex& bottomLeft, const Vertex& topRight)
{
	if (bottomLeft.isValid() && topRight.isValid() &&
		topRight.isHigherThan(bottomLeft) && topRight.isToTheRightOf(bottomLeft))
		return true;
	return false;
}

void Rectangle::setVertex(double x, double y, Vertex& wanted)
{
	wanted.m_col = x;
	wanted.m_row = y;
}

Vertex Rectangle::getBottomLeft()const { return m_bottom_left; };
Vertex Rectangle::getTopRight()const { return m_top_right;};
double Rectangle::getWidth()const { return m_widgth; };
double Rectangle::getHeight()const { return m_heigth; };

void Rectangle::draw(Board& board)
{
	Vertex bottom_left = getBottomLeft(),
		top_right = getTopRight(),
		bottom_right = Vertex(top_right.m_col, bottom_left.m_row),
		top_left = Vertex(bottom_left.m_col, top_right.m_row);
	board.drawLine(bottom_left, bottom_right);
	board.drawLine(bottom_right, top_right);
	board.drawLine(top_right, top_left);
	board.drawLine(top_left, bottom_left);
}