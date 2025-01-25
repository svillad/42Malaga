/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Character.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svilla-d <svilla-d@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 13:29:41 by svilla-d          #+#    #+#             */
/*   Updated: 2025/01/25 17:02:22 by svilla-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CHARACTER_HPP
#define CHARACTER_HPP

# include "ICharacter.hpp"
# include "AMateria.hpp"
# include "Logger.hpp"
# include <iostream>
# include <sstream>

# define SLOT_SIZE 4
# define BAG_SIZE 100

class Character : public ICharacter {
private:
    std::string name;
    AMateria*   slot[SLOT_SIZE];
    AMateria*   bag[BAG_SIZE];
    Logger      log;

    void initArray(AMateria* array[], int size);
    void freeArray(AMateria* array[], int size);
    void copyArray(AMateria* dst[], AMateria* const src[], int size);
    int exists(AMateria* m) const;

public:
    Character();
    Character(std::string const &name);
    Character(Character const &other);
    Character& operator=(Character const &other);
    virtual ~Character();

    std::string const & getName() const;
    void equip(AMateria* m);
    void unequip(int idx);
    void use(int idx, ICharacter& target);
};

template<typename T>
std::string to_string(const T& value);

#endif
