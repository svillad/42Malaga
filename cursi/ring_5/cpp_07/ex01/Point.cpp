#include "Point.hpp"

Point::Point() : x(0), y(0) {}

Point::Point(int x, int y) : x(x), y(y) {}

Point::Point(const Point& other) : x(other.x), y(other.y) {}

Point& Point::operator=(const Point& other) {
    if (this != &other) {
        x = other.x;
        y = other.y;
    }
    return *this;
}

int Point::getX() const {
    return x;
}

int Point::getY() const {
    return y;
}

void Point::setX(int x) {
    this->x = x;
}

void Point::setY(int y) {
    this->y = y;
}

Point& Point::operator+=(int a) {
    x += a;
    y += a;
    return *this;
}

Point& Point::operator*=(int a) {
    x *= a;
    y *= a;
    return *this;
}

bool Point::operator<(const Point& other) const {
    return (x + y) < (other.x + other.y);
}

bool Point::operator>(const Point& other) const {
    return (x + y) > (other.x + other.y);
}

std::ostream& operator<<(std::ostream& os, const Point& p) {
    os << "(" << p.getX() << ", " << p.getY() << ")";
    return os;
}
