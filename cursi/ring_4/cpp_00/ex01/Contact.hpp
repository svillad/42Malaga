/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Contact.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svilla-d <svilla-d@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 13:12:18 by svilla-d          #+#    #+#             */
/*   Updated: 2024/11/23 16:49:32 by svilla-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONTACT_H
# define CONTACT_H

# include <iostream>
# include <iomanip>
# include <limits>

# define COL_WIDTH 10

class Contact {
private:
    std::string first_name;
    std::string last_name;
    std::string nickname;
    std::string phone_number;
    std::string darkest_secret;

    std::string format_field(const std::string &str);
    bool        set_field(const std::string& name, std::string* field);
    bool        set_number(const std::string& name, std::string* field);
    bool        trim_spaces(std::string& temp);
    bool        is_valid_number_format(const std::string& temp);
    bool        validate_number(const std::string& temp);

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
    bool    create();
};

std::string formatColumn(const std::string& text);
void clear_buffer(void);

#endif
