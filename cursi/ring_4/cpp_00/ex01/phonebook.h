#ifndef PHONEBOOK_H
# define PHONEBOOK_H

# include <iostream>
# include "contact.h"

# define LIM 2

class PhoneBook
{
private:
    int size;
    int oldest;
    Contact Contacts[LIM];

public:
    
    PhoneBook();
    PhoneBook(PhoneBook *p);
    ~PhoneBook(){};

    void add();
    Contact search();
    void print();
};

#endif