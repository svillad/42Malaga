#ifndef POINT_HPP
#define POINT_HPP

# include "Fixed.hpp"

# define STEP 0.5f

class Point {
private:
	Fixed x;
	Fixed y;

public:
	Point();
	Point(const float x, const float y);
	Point(const Point &p);
	Point& operator=(const Point &p);
	~Point();

	Fixed	getX() const;
	Fixed	getY() const;

	bool	operator==(const Point &p) const;
};

std::ostream&	operator<<(std::ostream &stream, const Point &p);
void			plot_triangle(const Point &a, const Point &b, const Point &c, const Point &p);
bool			is_valid_triangle(const Point &a, const Point &b, const Point &c);
Fixed			triangle_area(const Point &a, const Point &b, const Point &c);
bool			bsp(Point const a, Point const b, Point const c, Point const point);

#endif
