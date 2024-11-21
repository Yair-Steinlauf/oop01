#include <IsoscelesTriangle.h>
#include <Utilities.h>
#include <cmath>

bool isIsoscelesTriangle(const Vertex vertices[3]);
bool isTriangleValid(const Vertex vertices[3]);


IsoscelesTriangle::IsoscelesTriangle(const Vertex vertices[3]) : m_vertex0(vertices[0]), m_vertex1(vertices[1]), m_vertex2(vertices[2])
{
	if (!isTriangleValid(vertices) || !isIsoscelesTriangle(vertices))
	{
		buildDefault();
	}
}

IsoscelesTriangle::IsoscelesTriangle(const Vertex &left, const Vertex &right, double height)
{
	if (left.isValid() && right.isValid() && left.m_row == right.m_row && height != 0)
	{
		m_vertex0 = left;
		m_vertex1 = right;
		m_vertex2 = Vertex((left.m_col + right.m_col) / 2, left.m_row + height);
	}
	else
	{
		buildDefault();
	}
}

Vertex IsoscelesTriangle::getVertex(int index) const
{
	switch (index)
	{
	case 0:
		return m_vertex0;
		break;
	case 1:
		return m_vertex1;
		break;
	default:
		return m_vertex2;
		break;
	}
}

double IsoscelesTriangle::getLength(int index) const
{
	switch (index)
	{
	case 0:
		return distance(m_vertex0, m_vertex1);
		break;
	case 1:
		return distance(m_vertex1, m_vertex2);
		break;
	default:
		return distance(m_vertex0, m_vertex2);
		break;
	}
}

double IsoscelesTriangle::getHeight() const
{

	if (m_vertex0.m_row == m_vertex1.m_row)
	{
		Vertex center = Vertex((m_vertex0.m_col + m_vertex1.m_col) / 2, m_vertex0.m_row);
		return distance(center, m_vertex2);
	}
	else if (m_vertex1.m_row == m_vertex2.m_row)
	{
		Vertex center = Vertex((m_vertex1.m_col + m_vertex2.m_col) / 2, m_vertex1.m_row);
		return distance(center, m_vertex0);
	}
	Vertex center = Vertex((m_vertex0.m_col + m_vertex2.m_col) / 2, m_vertex0.m_row);
	return distance(center, m_vertex1);
}
void IsoscelesTriangle::buildDefault()
{
	m_vertex0 = Vertex(20, 20);
	m_vertex1 = Vertex(30, 20);
	m_vertex2 = Vertex(25, 20 + sqrt(75));
}
bool isIsoscelesTriangle(const Vertex vertices[3])
{
	return (distance(vertices[0], vertices[1]) == distance(vertices[1], vertices[0]) || distance(vertices[1], vertices[2]) == distance(vertices[2], vertices[0]) || distance(vertices[0], vertices[2]) == distance(vertices[1], vertices[0]));
}
bool isTriangleValid(const Vertex vertices[3])
{

	return (vertices[0].isValid() && vertices[1].isValid() && vertices[2].isValid() && (vertices[0].m_row == vertices[1].m_row || vertices[1].m_row == vertices[2].m_row || vertices[0].m_row == vertices[2].m_row));
}


void IsoscelesTriangle::draw(Board& board) const
{
	board.drawLine(m_vertex0, m_vertex1);
	board.drawLine(m_vertex1, m_vertex2);
	board.drawLine(m_vertex2, m_vertex0);
}

Rectangle IsoscelesTriangle::getBoundingRectangle() const
{
	double minX = fmin(fmin(m_vertex0.m_col, m_vertex1.m_col), m_vertex2.m_col);
	double minY = fmin(fmin(m_vertex0.m_row, m_vertex1.m_row), m_vertex2.m_row);
	double maxX = fmax(fmax(m_vertex0.m_col, m_vertex1.m_col), m_vertex2.m_col);
	double maxY = fmax(fmax(m_vertex0.m_row, m_vertex1.m_row), m_vertex2.m_row);
	return Rectangle(Vertex(minX, minY), Vertex(maxX, maxY));
}


double IsoscelesTriangle::getPerimeter() const {
	return distance(m_vertex0, m_vertex1) + distance(m_vertex1, m_vertex2) + distance(m_vertex0, m_vertex2);
}

double IsoscelesTriangle::getArea() const {
	double halfArea = getPerimeter() / 2;	
	// use heron algorithem
	return halfArea * (halfArea - distance(m_vertex0, m_vertex1)) 
		* (halfArea - distance(m_vertex1, m_vertex2)) 
		* (halfArea - distance(m_vertex0, m_vertex2));
}

Vertex IsoscelesTriangle::getCenter() const{
	return Vertex((m_vertex0.m_col + m_vertex1.m_col + m_vertex2.m_col) / 3, (m_vertex0.m_row + m_vertex1.m_row + m_vertex2.m_row) / 3);
}

bool IsoscelesTriangle::scale(double factor)
{
	Vertex center = getCenter();
	Vertex newVer0 = Vertex(center.m_col - (abs(center.m_col - m_vertex0.m_col) * factor),
		center.m_row - (abs(center.m_row - m_vertex0.m_row) * factor));

	Vertex newVer1 = Vertex(center.m_col - (abs(center.m_col - m_vertex1.m_col) * factor),
		center.m_row - (abs(center.m_row - m_vertex1.m_row) * factor));

	Vertex newVer2 = Vertex(center.m_col - (abs(center.m_col - m_vertex2.m_col) * factor),
		center.m_row - (abs(center.m_row - m_vertex2.m_row) * factor));
	if (newVer0.isValid() && newVer1.isValid() && newVer2.isValid()) {
		m_vertex0 = newVer0;
		m_vertex1 = newVer1;
		m_vertex2 = newVer2;
		return true;
	}
	return false;

	
}