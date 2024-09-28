#include "contact.h"

Contact::Contact()
{
    first_name = "";
    last_name = "";
    nickname = "";
    phone_number = "";
    darkest_secret = "";
}

Contact::Contact(Contact *c)
{
    first_name      = c->first_name;
    last_name       = c->last_name;
    nickname        = c->nickname;
    phone_number    = c->phone_number;
    darkest_secret  = c->darkest_secret;
}

void Contact::print()
{
    std::cout << "Name: " << first_name;
    std::cout << ", Last: " << last_name;
    std::cout << ", Nickname: " << nickname;
    std::cout << ", Phono: " << phone_number;
    std::cout << ", Secret: " << darkest_secret;
}

Contact Contact::create()
{
    set_field("first name", &first_name);
    set_field("last name", &last_name);
    set_field("nickname", &nickname);
    set_field("phone number", &phone_number);
    set_field("darkest secret", &darkest_secret);

    return (*this);
}

bool Contact::set_field(std::string name, std::string *field)
{
    std::string temp = "";

    while (temp == "")
    {
        std::cout << "Ingrese el " << name << ": ";
        std::cin >> temp;
    }
    *field = temp;
    return (true);
}

