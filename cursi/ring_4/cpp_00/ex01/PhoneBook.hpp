/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PhoneBook.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svilla-d <svilla-d@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 13:12:34 by svilla-d          #+#    #+#             */
/*   Updated: 2024/11/16 20:00:19 by svilla-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHONEBOOK_H
# define PHONEBOOK_H

# include <iostream>
# include "Contact.hpp"

# define LIM 8

class PhoneBook {
private:
    int size;
    int oldest;
    Contact contacts[LIM];

public:
    PhoneBook();
    PhoneBook(const PhoneBook& p);
    PhoneBook& operator=(const PhoneBook& p);
    ~PhoneBook(){};

    int get_size() const;
    bool add(void);
    void add(const Contact& c);
    Contact search(int index);
    void print(void) const;
};

#endif
