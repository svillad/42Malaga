/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Serializer.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svilla-d <svilla-d@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 16:34:56 by svilla-d          #+#    #+#             */
/*   Updated: 2025/02/22 16:34:57 by svilla-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Serializer.hpp"

ILogger* Serializer::logger = NULL;

Serializer::Serializer() {
}

Serializer::Serializer(const Serializer &) {
}

Serializer& Serializer::operator=(const Serializer &other) {
    (void)other;
    return *this;
}

void Serializer::setLogger(ILogger* log) {
    logger = log;
    if (logger)
        logger->log(DEBUG, "[Serializer] Logger initialized.");
}

uintptr_t Serializer::serialize(Data* ptr) {
    uintptr_t raw = reinterpret_cast<uintptr_t>(ptr);
    if (logger)
        logger->log(DEBUG, "[Serializer] Serialized pointer: " + to_string(raw));
    return raw;
}

// Convert unsigned integer back to pointer
Data* Serializer::deserialize(uintptr_t raw) {
    Data* ptr = reinterpret_cast<Data*>(raw);
    if (logger)
        logger->log(DEBUG, "[Serializer] Deserialized pointer: " + to_string(raw));
    return ptr;
}
