/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svilla-d <svilla-d@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 13:25:28 by svilla-d          #+#    #+#             */
/*   Updated: 2024/11/08 13:25:29 by svilla-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Point.hpp"
#include <iostream>

void test_inside_point_1(void)
{
	Point	a(-2, 3);
	Point	b(3, -1);
	Point	c(5, 6);
	Point	point(1, 3);

	std::cout << "\n*********   test_inside_point   *********" << std::endl;
	plot_triangle(a, b, c, point);
	std::cout << "Triangle area: " << triangle_area(a, b, c) << std::endl;
	std::cout << "Inside point: " << bsp(a, b, c, point) << std::endl;
	std::cout << "\033[32mOK\033[0m" << std::endl;
}

void test_inside_point_2(void)
{
	Point	a(3, 4);
	Point	b(8, 4);
	Point	c(2, -2);
	Point	point(4, 3);

	std::cout << "\n*********   test_inside_point   *********" << std::endl;
	plot_triangle(a, b, c, point);
	std::cout << "Triangle area: " << triangle_area(a, b, c) << std::endl;
	std::cout << "Inside point: " << bsp(a, b, c, point) << std::endl;
	std::cout << "\033[32mOK\033[0m" << std::endl;
}

void test_inside_point_3(void)
{
	Point	a(-10, 0);
	Point	b(10, 0);
	Point	c(0, 20);
	Point	point(0, 5);

	std::cout << "\n*********   test_inside_point   *********" << std::endl;
	plot_triangle(a, b, c, point);
	std::cout << "Triangle area: " << triangle_area(a, b, c) << std::endl;
	std::cout << "Inside point: " << bsp(a, b, c, point) << std::endl;
	std::cout << "\033[32mOK\033[0m" << std::endl;
}

void test_outside_point(void)
{
	Point	a(-2, 3);
	Point	b(3, -1);
	Point	c(5, 6);
	Point	point(-2.5, 1);

	std::cout << "\n*********   test_outside_point   *********" << std::endl;
	plot_triangle(a, b, c, point);
	std::cout << "Triangle area: " << triangle_area(a, b, c) << std::endl;
	std::cout << "Outside point: " << bsp(a, b, c, point) << std::endl;
	std::cout << "\033[32mOK\033[0m" << std::endl;
}

void test_invalid_triangle(void)
{
	Point	a(1, -1);
	Point	b(3, -1);
	Point	c(5, -1);
	Point	point(-2.5, 1);

	std::cout << "\n*********   test_inavlid_triangle  *********" << std::endl;
	plot_triangle(a, b, c, point);
	std::cout << "Triangle area: " << triangle_area(a, b, c) << std::endl;
	std::cout << bsp(a, b, c, point) << std::endl;
	std::cout << "\033[32mOK\033[0m" << std::endl;
}

int main() {

	test_inside_point_1();
	test_inside_point_2();
	test_inside_point_3();
	test_outside_point();
	test_invalid_triangle();
	std::cout << "All tests passed successfully." << std::endl;
	return 0;
}