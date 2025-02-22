/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Point.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svilla-d <svilla-d@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 17:01:15 by svilla-d          #+#    #+#             */
/*   Updated: 2025/02/22 17:01:16 by svilla-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

    Point& operator+=(int a);
    Point& operator*=(int a);
    bool operator<(const Point& other) const;
    bool operator>(const Point& other) const;
};

std::ostream& operator<<(std::ostream& os, const Point& p);

#endif
