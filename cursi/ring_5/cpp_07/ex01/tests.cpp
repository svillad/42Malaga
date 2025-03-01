/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tests.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svilla-d <svilla-d@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 16:54:14 by svilla-d          #+#    #+#             */
/*   Updated: 2025/02/22 16:54:15 by svilla-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "iter.hpp"
#include "Point.hpp"
#include <iostream>

class Awesome{
public:
	Awesome( void ) : _n( 42 ) { return; }
	int get( void ) const { return this->_n; }

private:
	int _n;
};

std::ostream & operator<<( std::ostream & o, Awesome const & rhs ) { o << rhs.get(); return o; }

template< typename T >
void print( T const &x ) { std::cout << x << std::endl; return; }

template< typename T >
void print2( T  &x ) { std::cout << x << std::endl; return; }

int main() {
    int tab[] = {0, 1, 2, 3, 4 };
	Awesome tab2[5];
	
	iter(tab, 5, print2);
	iter(tab2, 5, print);
    return 0;
}
