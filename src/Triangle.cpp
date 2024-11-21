#include <Triangle.h>
#include <Utilities.h>
#include <cmath>
#include <vector>

Triangle::Triangle(const Vertex vertices[3]) {

	if (!isTriangleValid(vertices)) {
		buildDefault();
	}
	else {
		m_vertex0 = vertices[0];
		m_vertex1 = vertices[1];
		m_vertex2 = vertices[2];
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
	double minX = fmin(fmin(m_vertex0.m_col, m_vertex1.m_col), m_vertex2.m_col);
	double minY = fmin(fmin(m_vertex0.m_row, m_vertex1.m_row), m_vertex2.m_row);
	double maxX = fmax(fmax(m_vertex0.m_col, m_vertex1.m_col), m_vertex2.m_col);
	double maxY = fmax(fmax(m_vertex0.m_row, m_vertex1.m_row), m_vertex2.m_row);
	return Rectangle(Vertex(minX, minY), Vertex(maxX, maxY));
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
	Vertex center(getCenter());
	Vertex newVertex[3] = { m_vertex0, m_vertex1, m_vertex2 };
	for (int index = 0; index < 3; index++)
	{
		if (!newVertex[index].scale(factor, center))
		{
			return false;
		}
			
	}
	if (isTriangleValid(newVertex))
	{
		m_vertex0 = newVertex[0];
		m_vertex1 = newVertex[1];
		m_vertex2 = newVertex[2];
		return true;
	}
	return false;
}

bool Triangle::isTriangleValid(const Vertex vertices[3]) 
{
	
	return (vertices[0].isValid() && vertices[1].isValid() && vertices[2].isValid()
		&& (vertices[0].m_row == vertices[1].m_row || vertices[1].m_row == vertices[2].m_row || vertices[0].m_row == vertices[2].m_row));
	
}
