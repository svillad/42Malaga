#ifndef CONTACT_H
# define CONTACT_H

# include <iostream>

class Contact
{
private:
    std::string first_name;
    std::string last_name;
    std::string nickname;
    std::string phone_number;
    std::string darkest_secret;

    bool set_field(std::string name, std::string *field);

public:
    Contact();
    Contact(Contact *c);
    ~Contact(){};

    void print();
    Contact create();
};

#endif