/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svilla-d <svilla-d@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 13:21:49 by svilla-d          #+#    #+#             */
/*   Updated: 2024/11/16 15:13:04 by svilla-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Zombie.hpp"

int main(void) {
    Zombie* heapZombie = newZombie("Foo");
    heapZombie->announce();
    delete heapZombie;

    randomChump("Bar");

    return (0);
}
