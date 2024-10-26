#include "Point.hpp"

Fixed triangle_area(const Point &a, const Point &b, const Point &c) {
	Fixed pa(a.getX() * (b.getY() - c.getY()));
	Fixed pb(b.getX() * (c.getY() - a.getY()));
	Fixed pc(c.getX() * (a.getY() - b.getY()));
	Fixed area = (pa + pb + pc) / Fixed(2.0f);
	Fixed zero = Fixed(0);
	if (area < zero)
		return (area * -1);
	else
		return (area);
}

void calculate_bounds(const Point &a, const Point &b, const Point &c, const Point &point, Fixed bounds[4]) {
    bounds[0] = a.getX();
    bounds[1] = a.getX();
    bounds[2] = a.getY();
    bounds[3] = a.getY();

    const Point *points[4] = { &a, &b, &c, &point };
    for (int i = 0; i < 4; ++i) {
        const Point *p = points[i];
        if (p->getX() < bounds[0]) bounds[0] = p->getX();
        if (p->getX() > bounds[1]) bounds[1] = p->getX();
        if (p->getY() < bounds[2]) bounds[2] = p->getY();
        if (p->getY() > bounds[3]) bounds[3] = p->getY();
    }
    bounds[0] = bounds[0] - Fixed(2);
    bounds[1] = bounds[1] + Fixed(2);
    bounds[2] = bounds[2] - Fixed(2);
    bounds[3] = bounds[3] + Fixed(2);
}

void draw_triangle(const Point &a, const Point &b, const Point &c, const Point &point, const Fixed bounds[4]) {
    for (Fixed y = bounds[2]; y <= bounds[3]; y = y + STEP) {
        for (Fixed x = bounds[0]; x <= bounds[1]; x = x + STEP) {
            Point p(x.toFloat(), y.toFloat());
            if (bsp(a, b, c, p)) {
                if (p == point)
                    std::cout << "-";
                else
                    std::cout << "*";
            } else {
                if (p == point)
                    std::cout << "-";
                else
                    std::cout << " ";
            }
        }
        std::cout << std::endl;
    }
}

void plot_triangle(const Point &a, const Point &b, const Point &c, const Point &point) {
    Fixed bounds[4]; 
    calculate_bounds(a, b, c, point, bounds);
    draw_triangle(a, b, c, point, bounds);
}

bool is_valid_triangle(const Point &a, const Point &b, const Point &c) {
	return triangle_area(a, b, c) > Fixed(0);
}

bool bsp(Point const a, Point const b, Point const c, Point const point) {	
	if (!is_valid_triangle(a, b, c)) {
		return false;
	}

	Fixed totalArea = triangle_area(a, b, c);
	Fixed area1 = triangle_area(point, b, c);
	Fixed area2 = triangle_area(a, point, c);
	Fixed area3 = triangle_area(a, b, point);

	return (area1 + area2 + area3 == totalArea);
}
