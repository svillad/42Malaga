#include "ASpell.hpp"
#include "ATarget.hpp"

ASpell::ASpell() {
}

ASpell::ASpell(const std::string& n, const std::string& e) : name(n), effects(e) {
}

ASpell::ASpell(const ASpell& other) : name(other.name), effects(other.effects) {
}

ASpell& ASpell::operator=(const ASpell& other) {
    if (this != &other) {
        name    = other.name;
        effects = other.effects;
    }
    return *this;
}

ASpell::~ASpell() {
}

const std::string& ASpell::getName() const {
    return name;
}

const std::string& ASpell::getEffects() const {
    return effects;
}

void ASpell::launch(const ATarget& target) const {
    target.getHitBySpell(*this);
}
