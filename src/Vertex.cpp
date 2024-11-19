#include "Vertex.h"
#include "macros.h"

#include <iostream>

bool Vertex::isHigherThan(const Vertex& other) const
{
    return m_row > other.m_row;
}

bool Vertex::isToTheRightOf(const Vertex& other) const
{
    return m_col > other.m_col;
}

bool Vertex::isValid() const
{
    return m_col >= 0 && m_col <= MAX_COL && m_row >= 0 && m_row <= MAX_ROW;
}

std::istream& operator>>(std::istream& istr, Vertex& v)
{
    return istr >> v.m_col >> v.m_row;
}

std::ostream& operator<<(std::ostream& ostr, const Vertex& v)
{
    return ostr << "(" << v.m_col << ", " << v.m_row << ")";
}


bool Vertex::scale(double factor, Vertex& other)
{
    if (factor <= 0) return false;
    double diffCol = factor * (other.m_col - m_col),
           diffRow = factor * (other.m_row - m_row);
    Vertex newVertex(other.m_col - diffCol, other.m_row - diffRow);
    if (newVertex.isValid())
    {
        *this = newVertex;
        return true;
    }
    return false;
}

