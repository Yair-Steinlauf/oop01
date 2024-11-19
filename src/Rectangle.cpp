#include <iostream>
#include <Rectangle.h>
#include <cmath>
#include <Board.h>



Rectangle::Rectangle(const Vertex& bottomLeft, const Vertex& topRight)
	: m_bottom_left(bottomLeft), m_top_right(topRight) //constructor
{
	if (!isValid(bottomLeft, topRight))
	{
		this->setToDef();
	}
}
Rectangle::Rectangle(const Vertex vertices[2]):Rectangle(vertices[0], vertices[1])
{}
Rectangle::Rectangle(double x, double y, double width, double height)
	:Rectangle(Vertex(x,y), Vertex(x+width, y+height))
{}

Rectangle::Rectangle(const Vertex& topRight, double width, double height)
	:Rectangle(Vertex(topRight.m_col - width, topRight.m_row - height), topRight)
{}

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
double Rectangle::getWidth()const { return getTopRight().m_col- getBottomLeft().m_col; };
double Rectangle::getHeight()const { return getTopRight().m_row - getBottomLeft().m_row; };

void Rectangle::draw(Board& board) const
{
	Vertex bottom_left(getBottomLeft()),
		top_right = getTopRight(),
		bottom_right = Vertex(m_top_right.m_col, m_bottom_left.m_row),
		top_left = Vertex(m_bottom_left.m_col, m_top_right.m_row);
//	std::cout << "BL:" << bottom_left << "\n TR:" << m_top_right << "\n";
	board.drawLine(m_bottom_left, bottom_right);
	board.drawLine(bottom_right, m_top_right);
	board.drawLine(m_top_right, top_left);
	board.drawLine(top_left, m_bottom_left);
}

Rectangle Rectangle::getBoundingRectangle()const
{
	return *this;
}

double Rectangle::getPerimeter() const
{
	return getHeight() * 2 + getWidth() * 2;
}

double Rectangle::getArea() const
{
	return getHeight() * getWidth();
}

Vertex Rectangle::getCenter() const
{
	double center_x = (getBottomLeft().m_col + getTopRight().m_col) / 2;
	double center_y = (getBottomLeft().m_row + getTopRight().m_row) / 2;
	return Vertex(center_x, center_y);
}

bool Rectangle::scale(double factor)
{
	if (factor <= 0) return false;
	Vertex center = getCenter();
	Vertex new_bottom_left = m_bottom_left;
	Vertex new_Top_right = m_top_right;
	bool l_valid = new_bottom_left.scale(factor, center);
	bool r_valid = new_Top_right.scale(factor, center);
	if (l_valid && r_valid && isValid(new_bottom_left,new_Top_right))
	{
		m_bottom_left = new_bottom_left;
		m_top_right = new_Top_right;
		return true;
	}
	return true;
}
void Rectangle::setToDef()
{
	setVertex(20, 10, m_bottom_left);
	setVertex(30, 20, m_top_right);
}