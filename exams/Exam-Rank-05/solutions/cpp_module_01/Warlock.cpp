#include "Warlock.hpp"

Warlock::Warlock(const std::string& n, const std::string& t)
    : name(n), title(t) {
    std::cout << name << ": This looks like another boring day." << std::endl;
}

Warlock::~Warlock() {
    for (std::map<std::string, ASpell*>::iterator it = spells.begin(); it != spells.end(); ++it)
        delete it->second;
    std::cout << name << ": My job here is done!" << std::endl;
}

const std::string& Warlock::getName() const {
    return name;
}

const std::string& Warlock::getTitle() const {
    return title;
}

void Warlock::setTitle(const std::string& newTitle) {
    title = newTitle;
}

void Warlock::introduce() const {
    std::cout << name << ": I am " << name << ", " << title << "!" << std::endl;
}

void Warlock::learnSpell(ASpell* spell) {
    if (!spell) return;
    if (spells.find(spell->getName()) == spells.end())
        spells[spell->getName()] = spell->clone();
}

void Warlock::forgetSpell(const std::string& spellName) {
    std::map<std::string, ASpell*>::iterator it = spells.find(spellName);
    if (it != spells.end()) {
        delete it->second;
        spells.erase(it);
    }
}

void Warlock::launchSpell(const std::string& spellName, const ATarget& target) {
    std::map<std::string, ASpell*>::iterator it = spells.find(spellName);
    if (it != spells.end())
        it->second->launch(target);
}
