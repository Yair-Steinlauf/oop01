#include <Triangle.h>
#include <Utilities.h>
#include <cmath>

Triangle::Triangle(const Vertex vertices[3]) : m_vertex0(vertices[0]), m_vertex1(vertices[1]), m_vertex2(vertices[2]) {

	if (!isTriangleValid(vertices)) {
		buildDefault();
	}
	
}

Triangle::Triangle(Vertex v0, Vertex v1, Vertex v2) : m_vertex0(v0), m_vertex1(v1), m_vertex2(v2){
	const Vertex vertices[3] = {v0, v1, v2};
	if (!isTriangleValid(vertices)) {
		buildDefault();
	}
}

void Triangle::buildDefault(){
		m_vertex0 = Vertex(20, 20);
		m_vertex1 = Vertex(30, 20);
		m_vertex2 = Vertex(25, 20 + sqrt(75));
}

Vertex Triangle::getVertex(int index) const
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

double Triangle::getLength(int index) const
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
void Triangle::draw(Board& board) const
{
	board.drawLine(m_vertex0, m_vertex1);
	board.drawLine(m_vertex1, m_vertex2);
	board.drawLine(m_vertex2, m_vertex0);
}
Rectangle Triangle::getBoundingRectangle() const
{
	
	if (m_vertex0.m_row == m_vertex1.m_row) {
		Vertex center = Vertex((m_vertex0.m_col + m_vertex1.m_col) / 2, m_vertex0.m_row);
		return Rectangle(fmin(m_vertex0.m_col, m_vertex1.m_col), m_vertex0.m_row, abs(m_vertex0.m_col - m_vertex1.m_col), abs(m_vertex2.m_row - m_vertex0.m_row));
	}
	else if (m_vertex1.m_row == m_vertex2.m_row){
		return Rectangle(fmin(m_vertex1.m_col, m_vertex2.m_col), m_vertex1.m_row, abs(m_vertex1.m_col - m_vertex2.m_col), abs(m_vertex0.m_row - m_vertex1.m_row));
	}
	else {
		return Rectangle(fmin(m_vertex0.m_col, m_vertex2.m_col), m_vertex0.m_row, abs(m_vertex0.m_col - m_vertex2.m_col), abs(m_vertex1.m_row - m_vertex0.m_row));
	}	
}


double Triangle::getPerimeter() const {
	return distance(m_vertex0, m_vertex1) + distance(m_vertex1, m_vertex2) + distance(m_vertex0, m_vertex2);
}

double Triangle::getArea() const {
	double halfArea = getPerimeter() / 2;	
	// use heron algorithem
	return halfArea * (halfArea - distance(m_vertex0, m_vertex1)) 
		* (halfArea - distance(m_vertex1, m_vertex2)) 
		* (halfArea - distance(m_vertex0, m_vertex2));
}

Vertex Triangle::getCenter() const{
	return Vertex((m_vertex0.m_col + m_vertex1.m_col + m_vertex2.m_col) / 3, (m_vertex0.m_row + m_vertex1.m_row + m_vertex2.m_row) / 3);
}

bool Triangle::scale(double factor)
{
	Vertex center = getCenter();
	double x = center.m_col - (abs(center.m_col - m_vertex0.m_col) * factor);
	double y = center.m_row - (abs(center.m_row - m_vertex0.m_row) * factor);
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


bool isTriangleValid(const Vertex vertices[3]) {
	
	return (vertices[0].isValid() && vertices[1].isValid() && vertices[2].isValid()
		&& (vertices[0].m_row == vertices[1].m_row || vertices[1].m_row == vertices[2].m_row || vertices[0].m_row == vertices[2].m_row));
	
}
