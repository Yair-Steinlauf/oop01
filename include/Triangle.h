#pragma once
#include <Vertex.h>
#include <Board.h>
#include <Rectangle.h>


class Triangle {
public:
	Triangle(const Vertex vertices[3]);
	Triangle(Vertex v0, Vertex v1, Vertex v2);
	void buildDefault();
	Vertex getVertex(int index) const;
	double getLength(int index) const;
	void draw(Board& board) const;
	Rectangle getBoundingRectangle() const;
	double getPerimeter() const;
	double getArea() const;
	Vertex getCenter() const;
	bool scale(double factor);


private:
	Vertex m_vertex0, m_vertex1, m_vertex2;
	bool isTriangleValid(const Vertex vertices[3]);
};