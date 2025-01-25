/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Character.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svilla-d <svilla-d@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 13:29:39 by svilla-d          #+#    #+#             */
/*   Updated: 2025/01/25 18:49:40 by svilla-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Character.hpp"

Character::Character() : name("unnamed") {
    log.print(DEBUG, "\e[31m[Character]\e[0m Default constructor called for " + name);
    initArray(slot, SLOT_SIZE);
    initArray(bag, BAG_SIZE);
}

Character::Character(std::string const &name) : name(name) {
    log.print(DEBUG, "\e[31m[Character]\e[0m Overload constructor called for " + name);
    initArray(slot, SLOT_SIZE);
    initArray(bag, BAG_SIZE);
}

Character::Character(Character const &c) {
    log.print(DEBUG, "\e[31m[Character]\e[0m Copy constructor called for " + c.name);
    *this = c;
}

Character &Character::operator=(Character const &c) {
    log.print(DEBUG, "\e[31m[Character]\e[0m Copy assignment operator called for " + c.name);
    if (this != &c)
    {
        name = c.name;
        copyArray(slot, c.slot, SLOT_SIZE);
        copyArray(bag, c.bag, BAG_SIZE);
    }
    return *this;
}

Character::~Character() {
    log.print(DEBUG, "\e[31m[Character]\e[0m Destructor called for " + name);
    freeArray(slot, SLOT_SIZE);
    freeArray(bag, BAG_SIZE);
}

std::string const &Character::getName() const {
    return (name);
}

void Character::equip(AMateria *m) {
    log.print(DEBUG, "\e[31m[Character]\e[0m Start equip process");
    if (!m) {
        log.print(ERROR, "\e[31m[Character]\e[0m Trying equip a null materia. Operation not completed");
        return ;
    }
    int p = exists(m);
    if (p != -1) {
        log.print(WARN, "\e[31m[Character]\e[0m Materia already equipped in slot " + to_string(p)
                    + ". Operation not completed");
        return ;
    }
    log.print(DEBUG, "\e[31m[Character]\e[0m Trying equip '" + m->getType() + "' for " + name);
    for (int i = 0; i < SLOT_SIZE; ++i) {
        if (!slot[i]) {
            slot[i] = m;
            log.print(DEBUG, "\e[31m[Character]\e[0m '" + m->getType()
                        + "' successfully equipped in slot " + to_string(i));
            return ;
        }
    }
    log.print(WARN, "\e[31m[Character]\e[0m '" + name + "' has reached the limit of "
                + "equipped items. Operation not completed");
}

void Character::unequip(int idx) {
    log.print(DEBUG, "\e[31m[Character]\e[0m Start unequip process");
    log.print(DEBUG, "\e[31m[Character]\e[0m Trying unequip slot '" + to_string(idx) + "' for " + name);
    if (idx < 0 || idx >= SLOT_SIZE) {
        log.print(ERROR, "\e[31m[Character]\e[0m '" + name + "' are trying to unequip "
                    + "an invalid slot("+ to_string(idx) + "). "
                    + "It must be between 0 and " + to_string(SLOT_SIZE - 1));
        return ;
    }
    if (!slot[idx]) {
        log.print(WARN, "\e[31m[Character]\e[0m slot '" + to_string(idx) + "' was already empty");
        return ;
    }
    for (int i = 0; i < BAG_SIZE; ++i)
    {
        if (!bag[i])
        {
            bag[i] = slot[idx];
            slot[idx] = NULL;
            log.print(DEBUG, "\e[31m[Character]\e[0m '" + bag[i]->getType()
                        + "' successfully unequipped from slot " + to_string(i));
            return ;
        }
    }
    log.print(WARN, "\e[31m[Character]\e[0m '" + name + "' has reached the limit of "
                + "unequipped items. Operation not completed");
}

void Character::use(int idx, ICharacter &target) {
    if (idx < 0 || idx >= SLOT_SIZE) {
        log.print(ERROR, "\e[31m[Character]\e[0m '" + name + "' are trying to use "
                    + "an invalid slot("+ to_string(idx) + "). "
                    + "It must be between 0 and " + to_string(SLOT_SIZE - 1));
        return ;
    }
    if (!slot[idx]) {
        log.print(WARN, "\e[31m[Character]\e[0m '" + name + "' doesn't have slot "
                    + to_string(idx) + " equipped");
        return ;
    }
    slot[idx]->use(target);
}

void Character::initArray(AMateria* array[], int size) {
    for (int i = 0; i < size; ++i)
        array[i] = NULL;
}

void Character::freeArray(AMateria* array[], int size) {
    for (int i = 0; i < size; ++i) {
        if (array[i]) {
            delete array[i];
            array[i] = NULL;
        }
    }
}

void Character::copyArray(AMateria* dst[], AMateria* const src[], int size) {
    freeArray(dst, size);
    for (int i = 0; i < size; ++i) {
        dst[i] = src[i] ? src[i]->clone() : NULL;
    }
}

int Character::exists(AMateria* m) const {
    for (int i = 0; i < SLOT_SIZE; ++i)
    {
        if (slot[i] && slot[i] == m)
            return (i);
    }
    return (-1);
}

template<typename T>
std::string to_string(const T& value) {
    std::ostringstream oss;
    oss << value;
    return oss.str();
}
