/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Point.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svilla-d <svilla-d@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 13:25:33 by svilla-d          #+#    #+#             */
/*   Updated: 2024/11/08 13:25:33 by svilla-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Point.hpp"

Point::Point() : x(0), y(0) {
}

Point::Point(const float x, const float y) : x(Fixed(x)), y(Fixed(y)) {
}

Point::Point(const Point &p) {
	*this = p;
}

Point&	Point::operator=(const Point &p) {
	if (this != &p) {
		x = p.x;
		y = p.y;
	}
	return (*this);
}

Point::~Point() {}

Fixed	Point::getX() const {
	return (x);
}

Fixed	Point::getY() const {
	return (y);
}

bool Point::operator==(const Point &p) const {
		Fixed epsilon = Fixed(0.1f);
		return ((x - p.x).abs() < epsilon.toFloat() && 
				(y - p.y).abs() < epsilon.toFloat());
	}

std::ostream& operator<<(std::ostream &stream, const Point &p) {
	stream << "(" <<p.getX() << ", " << p.getY() << ")";
	return ((stream));
}
