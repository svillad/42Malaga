#include "phonebook.h"

PhoneBook::PhoneBook(){
    size   = 0;
    oldest = 0;
}

PhoneBook::PhoneBook(PhoneBook *p){
    size   = p->size;
    oldest = p->oldest;
    for (int i = 0; i < size; i++)
        Contacts[i] = p->Contacts[i];
}

void PhoneBook::add(){
    Contact c;
    int pos;

    pos = size;
    if (size >= LIM)
        pos = oldest;    

    Contacts[pos] = c.create();
    size++;
    if(size >= LIM)
    {
        size = LIM;
        oldest = (oldest + 1) % LIM;
    }
}

Contact PhoneBook::search(){
    std::cout << "TODO" << std::endl;
    Contact c;

    return (c);
}

void PhoneBook::print()
{
    std::cout << "----- PhoneBook -----" << std::endl;
    for (int i = 0; i < size; i++)
    {
        std::cout << i << ") ";
        Contacts[i].print();
        std::cout << std::endl;

    }
}