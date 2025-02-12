#ifndef POINT_HPP
#define POINT_HPP

#include <iostream>

class Point {
private:
    int x, y;

public:
    Point();
    Point(int x, int y);
    Point(const Point& other);
    Point& operator=(const Point& other);

    int getX() const;
    int getY() const;

    void setX(int x);
    void setY(int y);

    bool operator<(const Point& other) const;
    bool operator>(const Point& other) const;
};

std::ostream& operator<<(std::ostream& os, const Point& p);

#endif
