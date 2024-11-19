#include <Window.h>

Window::Window(const Rectangle& rectangle, const Vertex& point)
	:m_rectangle(rectangle), m_point(point)
{
	if (point.isHigherThan(rectangle.getTopRight()) ||
		point.isToTheRightOf(rectangle.getTopRight()) ||
		rectangle.getBottomLeft().isHigherThan(point) ||
		rectangle.getBottomLeft().isToTheRightOf(point))
	{
		this->m_rectangle.setToDef();
	}
}

Window::Window(const Vertex& topRight, double width, double height, const Vertex& point)
	:Window(Rectangle(topRight, width, height), point)
{}

Vertex Window::getBottomLeft()const {
	return m_rectangle.getBottomLeft();
}
Vertex Window::getTopRight()const {
	return m_rectangle.getTopRight();
}
Vertex Window::getPoint() const { return m_point; }

void Window::draw(Board& board) const
{
	m_rectangle.draw(board);
	board.drawLine(Vertex(m_point.m_col, m_rectangle.getBottomLeft().m_row),
				   Vertex(m_point.m_col, m_rectangle.getTopRight().m_row));
	board.drawLine(Vertex(m_rectangle.getBottomLeft().m_col, m_point.m_row),
				   Vertex(m_rectangle.getTopRight().m_col, m_point.m_row));
}

Rectangle Window::getBoundingRectangle()const
{
	return this->m_rectangle;
}

double Window::getPerimeter()const
{
	return m_rectangle.getPerimeter() + 2 * m_rectangle.getHeight() + 2 * m_rectangle.getWidth();
}

double Window::getArea() const
{
	return m_rectangle.getArea();
}

Vertex Window::getCenter() const
{
	return m_point;
}

bool Window::scale(double factor)
{
	return m_rectangle.scale(factor);
}