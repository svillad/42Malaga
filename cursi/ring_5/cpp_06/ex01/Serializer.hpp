/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Serializer.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svilla-d <svilla-d@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 16:34:59 by svilla-d          #+#    #+#             */
/*   Updated: 2025/02/22 16:35:00 by svilla-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERIALIZER_HPP
#define SERIALIZER_HPP

#include "ILogger.hpp"
#include <iostream>
#include <sstream>
#include <stdint.h>

struct Data {
    int id;
    char name[30];
    float value;
};

class Serializer {
private:
    Serializer();
    Serializer(const Serializer &);
    Serializer &operator=(const Serializer &);

    static ILogger* logger;

public:
    static void setLogger(ILogger* log);

    static uintptr_t serialize(Data* ptr);
    static Data* deserialize(uintptr_t raw);
};

template<typename T>
std::string to_string(const T& value) {
    std::ostringstream oss;
    oss << value;
    return oss.str();
}

#endif
