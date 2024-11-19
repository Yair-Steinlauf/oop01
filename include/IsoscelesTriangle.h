#pragma once
#include <Vertex.h>
#include <Board.h>
#include <Rectangle.h>


class IsoscelesTriangle {

	IsoscelesTriangle(const Vertex vertices[3]);
	IsoscelesTriangle (const Vertex& left, const Vertex& right, double height);
	Vertex getVertex (int index) const;
	double getLength (int index) const;
	double getHeight() const;
	void draw(Board& board) const;
	Rectangle getBoundingRectangle() const;
	double getPerimeter() const;
	double getArea() const;
	Vertex getCenter() const;
	bool scale(double factor);

	void buildDefault();


private:
	Vertex m_vertex0, m_vertex1, m_vertex2;
};