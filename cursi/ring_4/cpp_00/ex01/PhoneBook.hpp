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
    void add(void);
    void add(const Contact& c);
    Contact search(int index);
    void print(void) const;
};

void clear_buffer(void);

#endif