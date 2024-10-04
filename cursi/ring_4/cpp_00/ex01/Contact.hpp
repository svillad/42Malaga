#ifndef CONTACT_H
# define CONTACT_H

# include <iostream>
# include <iomanip>

# define COL_WIDTH 10

class Contact {
private:
    std::string first_name;
    std::string last_name;
    std::string nickname;
    std::string phone_number;
    std::string darkest_secret;

    bool    set_field(const std::string& name, std::string* field);

public:
    Contact();
    Contact(const Contact& c);
    Contact(const std::string& first_name, const std::string& last_name,
            const std::string& nickname, const std::string& phone_number,
            const std::string& darkest_secret);
    Contact& operator=(const Contact& c);
    ~Contact(){};

    const std::string&  get_first_name() const;
    const std::string&  get_last_name() const;
    const std::string&  get_nickname() const;
    const std::string&  get_phone_number() const;
    const std::string&  get_darkest_secret() const;

    void    print() const;
    void    print_full() const;
    void    create();
};

std::string formatColumn(const std::string& text);

#endif