/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   MateriaSource.hpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svilla-d <svilla-d@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 13:30:18 by svilla-d          #+#    #+#             */
/*   Updated: 2024/11/08 13:30:18 by svilla-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MATERIASOURCE_HPP
#define MATERIASOURCE_HPP

# include "IMateriaSource.hpp"
# include "Logger.hpp"

# define TEMP_SIZE 4

class MateriaSource : public IMateriaSource {
private:
    AMateria* templates[TEMP_SIZE];
    Logger    log;

    void freeArray(AMateria* array[], int size);
    void copyArray(AMateria* dst[], AMateria* const src[], int size);
    int exists(AMateria* m) const;

public:
    MateriaSource();
    MateriaSource(MateriaSource const &m);
    MateriaSource& operator=(MateriaSource const &other);
    virtual ~MateriaSource();

    void learnMateria(AMateria* m);
    AMateria* createMateria(std::string const &type);
};

#endif
