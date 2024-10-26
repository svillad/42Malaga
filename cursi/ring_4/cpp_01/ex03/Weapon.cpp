#include "Weapon.hpp"

Weapon::Weapon() : type("none") {}

Weapon::Weapon(const std::string& type) : type(type) {}

Weapon::Weapon(const Weapon &w) : type(w.type) {}

Weapon&	Weapon::operator=(const Weapon &w) {
	if (this != &w) {
		type = w.type;
	}
	return (*this);
}

Weapon::~Weapon() {}

const std::string& Weapon::getType() const {
	return (type);
}

void Weapon::setType(const std::string& newType) {
	type = newType;
}
