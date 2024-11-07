#include "MateriaSource.hpp"

MateriaSource::MateriaSource() {
	log.print(DEBUG, "\e[35m[Materia]\e[0m Default constructor called");
    for (int i = 0; i < TEMP_SIZE; ++i)
        templates[i] = 0;
}

MateriaSource::MateriaSource(MateriaSource const &m) {
	log.print(DEBUG, "\e[35m[Materia]\e[0m Copy constructor called");
    if (this != &m)
    {
        copyArray(templates, m.templates, TEMP_SIZE);
    }
}

MateriaSource& MateriaSource::operator=(MateriaSource const &m){
    log.print(DEBUG, "\e[35m[Materia]\e[0m Copy assignment operator called");
    if (this != &m)
    {
        copyArray(templates, m.templates, TEMP_SIZE);
    }
    return *this;
}


MateriaSource::~MateriaSource() {
	log.print(DEBUG, "\e[35m[Materia]\e[0m Destructor called");
    freeArray(templates, TEMP_SIZE);
}

void MateriaSource::learnMateria(AMateria* m) {
    log.print(DEBUG, "\e[35m[Materia]\e[0m Start learn materia process");
    if (!m) {
        log.print(ERROR, "\e[35m[Materia]\e[0m Trying learn a null materia");
        return ;
    }
    int p = exists(m);
    if (p != -1) {
        log.print(WARN, "\e[35m[Materia]\e[0m Materia already learned");
        return ;
    }
    log.print(DEBUG, "\e[35m[Materia]\e[0m Trying learn '" + m->getType() + "' materia");
    for (int i = 0; i < TEMP_SIZE; ++i) {
        if (!templates[i]) {
            templates[i] = m->clone();
            log.print(DEBUG, "\e[35m[Materia]\e[0m '" + m->getType() + "' successfully learned");
            return ;
        }
    }
    log.print(WARN, "\e[35m[Materia]\e[0m The limit of learned materia ("
                + m->getType() + ") has been reached. Operation not completed");
}

AMateria* MateriaSource::createMateria(std::string const &type) {
    log.print(DEBUG, "\e[35m[Materia]\e[0m Start create '" + type + "' materia");
    for (int i = 0; i < TEMP_SIZE; ++i) {
        if (templates[i] && templates[i]->getType() == type) {
            AMateria* tmp = templates[i]->clone();
            log.print(DEBUG, "\e[35m[Materia]\e[0m '" + tmp->getType() + "' successfully created");
            return (tmp);
        }
    }
    log.print(WARN, "\e[35m[Materia]\e[0m The materia '" + type + "' not found. Operation not completed");
    return (nullptr);
}

void MateriaSource::freeArray(AMateria* array[], int size) {
    for (int i = 0; i < size; ++i) {
        if (array[i]) {
            delete array[i];
            array[i] = nullptr;
        }
    }
}

void MateriaSource::copyArray(AMateria* dst[], AMateria* const src[], int size) {
    freeArray(dst, size);
    for (int i = 0; i < size; ++i) {
        dst[i] = src[i] ? src[i]->clone() : nullptr;
    }
}

int MateriaSource::exists(AMateria* m) const {
    for (int i = 0; i < TEMP_SIZE; ++i)
    {
        if (templates[i] && templates[i] == m)
            return (i);
    }
    return (-1);
}
