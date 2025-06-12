/********************************** Module 00 **********************************/
#ifndef WARLOCK_HPP
#define WARLOCK_HPP

#include <string>
#include <iostream>

class Warlock {
private:
    std::string name;
    std::string title;

public:
    Warlock(const std::string& n, const std::string& t);
    ~Warlock()

    const std::string& getName() const;
    const std::string& getTitle() const;
    void setTitle(const std::string& newTitle);

    void introduce() const;
}

#endif

#include "Warlock.hpp"

Warlock::Warlock(const std::string& n, const std::string& t) : name(n), title(t) {
    std::cout << name << ": This looks like another boring day." << std::endl;
}

Warlock::~Warlock() {
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

/********************************** Module 01 **********************************/

#ifndef ASPELL_HPP
#define ASPELL_HPP

#include <string>
#include <iostream>

class ATarget;

class ASpell {
protected:
    std::string name;
    std::string effects;

public:
    ASpell();
    ASpell(const std::string& n, const std::string& t);
    ASpell(const ASpell& o);
    ASpell& operator=(const ASpell &o);
    virtual ~ASpell()

    const std::string& getName() const;
    const std::string& getEffects() const;

    virtual ASpell* clone() const = 0;

    void launch(const ATarget& target) const;
}

#endif

ASpell::ASpell() {
}

ASpell::ASpell(const std::string& n, const std::string& e) : name(n), effects(e) {
}

ASpell::ASpell(const ASpell& o) : name(o.name), effects(o.effects) {
}

ASpell& ASpell::operator=(const ASpell &o) {
    if(this != &o) {
        name = o.name;
        effects = o.effects;
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

#ifndef ATARGET_HPP
#define ATARGET_HPP

#include <string>
#include <iostream>

class ASpell;

class ATarget {
protected:
    std::string type;

public:
    ATarget();
    ATarget(const std::string& t);
    ATarget(const ATarget& o);
    ATarget& operator=(const ATarget &o);
    virtual ~ATarget()

    const std::string& getType() const;

    virtual ATarget* clone() const = 0;

    void getHitBySpell(const ASpell& spell) const;
}

#endif

ATarget::ATarget() {
}

ATarget::ATarget(const std::string& t) : type(t) {
}

ATarget::ATarget(const ATarget& o) : type(o.type) {
}

ATarget& ATarget::operator=(const ATarget &o) {
    if(this != &o) {
        type = o.type;
    }
    return *this;
}

ATarget::~ATarget() {
}

const std::string& ATarget::getType() const {
    return type;
}

void ATarget::getHitBySpell(const ASpell& spell) const {
    std::cout << type << " has benn " << spell.getEffects() << "!" << std::endl;
}

#ifndef FWOOSH_HPP
#define FWOOSH_HPP

#include "ASpell.hpp"

class Fwoosh : public ASpell {
public:
    Fwoosh();
    virtual ~Fwoosh();

    virtual Fwoosh* clone() const;
}

#endif

Fwoosh::Fwoosh() : ASpell("Fwoosh", "fwooshed") {
}

Fwoosh::~Fwoosh() {
}

Fwoosh* Fwoosh::clone() const {
    return new Fwoosh(*this);
}

#ifndef DUMMY_HPP
#define DUMMY_HPP

#include "ATarget.hpp"

class Dummy : public ATarget {
public:
    Dummy();
    virtual ~Dummy();

    virtual Dummy* clone() const;
}

#endif

Dummy::Dummy() : ATarget("Target Practice Dummy") {
}

Dummy::~Dummy() {
}

Dummy* Dummy::clone() const {
    return new Dummy(*this);
}

#ifndef WARLOCK_HPP
#define WARLOCK_HPP

#include "ASpell.hpp"
#include <string>
#include <iostream>
#include <map>

class ASpell;
class ATarget;

class Warlock {
private:
    std::string name;
    std::string title;
    std::map<std::string, ASpell*> spellBook;

public:
    Warlock(const std::string& n, const std::string& t);
    ~Warlock()

    const std::string& getName() const;
    const std::string& getTitle() const;
    void setTitle(const std::string& newTitle);

    void introduce() const;
    void learnSpell(ASpell* spell);
    void forgetSpell(const std::string& spellName);
    void launchSpell(const std::string& spellName, const ATarget& target);
}

#endif

Warlock::Warlock(const std::string& n, const std::string& t)
    : name(n), title(t) {
    std::cout << name << ": This looks like another boring day." << std::endl;
}

Warlock::~Warlock() {
    for(std::map<std::string, ASpell*>::iterator it = spellBook.begin(); it!=spellBook.end(); ++it)
        delete (it->second);
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
    if (spellBook.find(spell->getName()) == spellBook.end())
        spellBook[spell->getName()] = spell->clone();
}

void Warlock::forgetSpell(const std::string& spellName) {
    std::map<std::string, ASpell*>::iterator it = spellBook.find(spellName);
    if (it != spellBook.end()) {
        delete (it->second);
        spellBook.erese(it);
    }
}

void Warlock::launchSpell(const std::string& spellName, const ATarget& target) {
    std::map<std::string, ASpell*>::iterator it = spellBook.find(spellName);
    if (it != spellBook.end()) {
        it->second->launch(target);
    }
}

/********************************** Module 02 **********************************/

#ifndef FIREBALL_HPP
#define FIREBALL_HPP

#include "ASpell.hpp"

class Fireball : public ASpell {
public:
    Fireball();
    virtual ~Fireball();

    virtual Fireball* clone() const;
}

#endif

Fireball::Fireball() : ASpell("Fireball", "burnt to a crisp") {
}

Fireball::~Fireball() {
}

Fireball* Fireball::clone() const {
    return new Fireball(*this);
}

#ifndef POLYMORPH_HPP
#define POLYMORPH_HPP

#include "ASpell.hpp"

class Polymorph : public ASpell {
public:
    Polymorph();
    virtual ~Polymorph();

    virtual Polymorph* clone() const;
}

#endif

Polymorph::Polymorph() : ASpell("Polymorph", "turned into critter") {
}

Polymorph::~Polymorph() {
}

Polymorph* Polymorph::clone() const {
    return new Polymorph(*this);
}

#ifndef BRICKWALL_HPP
#define BRICKWALL_HPP

#include "ATarget.hpp"

class BrickWall : public ATarget {
public:
    BrickWall();
    virtual ~BrickWall();

    virtual BrickWall* clone() const;
}

#endif

BrickWall::BrickWall() : ATarget("Inconspicuous Red-brick Wall") {
}

BrickWall::~BrickWall() {
}

BrickWall* BrickWall::clone() const {
    return new BrickWall(*this);
}

#ifndef SPELLBOOK_HPP
#define SPELLBOOK_HPP

#include "ASpell.hpp"
#include <string>
#include <iostream>
#include <map>

class ASpell;

class SpellBook {
private:
    std::map<std::string, ASpell*> spells;

    SpellBook(const SpellBook& o);
    SpellBook& operator=(const SpellBook& o);

public:
    SpellBook();
    ~SpellBook()

    void learnSpell(ASpell* spell);
    void forgetSpell(const std::string& spellName);
    ASpell* createSpell(const std::string& spellName);
}

#endif

SpellBook::SpellBook() {
}

SpellBook::~SpellBook() {
    for(std::map<std::string, ASpell*>::iterator it = spells.begin(); it!=spells.end(); ++it)
        delete (it->second);
}

void SpellBook::learnSpell(ASpell* spell) {
    if (!spell) return;
    if (spells.find(spell->getName()) == spells.end())
        spells[spell->getName()] = spell->clone();
}

void SpellBook::forgetSpell(const std::string& spellName) {
    std::map<std::string, ASpell*>::iterator it = spells.find(spellName);
    if (it != spells.end()) {
        delete (it->second);
        spells.erese(it);
    }
}

ASpell* SpellBook::createSpell(const std::string& spellName) {
    std::map<std::string, ASpell*>::iterator it = spells.find(spellName);
    if (it != spells.end()) {
        return it->second->clone();
    }
    return 0;
}

#ifndef WARLOCK_HPP
#define WARLOCK_HPP

#include "SpellBook.hpp"
#include <string>
#include <iostream>
#include <map>

class ASpell;
class ATarget;

class Warlock {
private:
    std::string name;
    std::string title;
    SpellBook book;

public:
    Warlock(const std::string& n, const std::string& t);
    ~Warlock()

    const std::string& getName() const;
    const std::string& getTitle() const;
    void setTitle(const std::string& newTitle);

    void introduce() const;
    void learnSpell(ASpell* spell);
    void forgetSpell(const std::string& spellName);
    void launchSpell(const std::string& spellName, const ATarget& target);
}

#endif

Warlock::Warlock(const std::string& n, const std::string& t)
    : name(n), title(t) {
    std::cout << name << ": This looks like another boring day." << std::endl;
}

Warlock::~Warlock() {
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
    book.learnSpell(spell);
}

void Warlock::forgetSpell(const std::string& spellName) {
    book.forgetSpell(spellName);
}

void Warlock::launchSpell(const std::string& spellName, const ATarget& target) {
    ASpell *tmp = book.createSpell(spellName);
    if (tmp) {
        tmp->launch(target);
        delete tmp;
    }
}

#ifndef TARGETGENERATOR_HPP
#define TARGETGENERATOR_HPP

#include "ATarget.hpp"
#include <string>
#include <iostream>
#include <map>

class ATarget;

class TargetGenerator {
private:
    std::map<std::string, ASpell*> targets;

    TargetGenerator(const TargetGenerator& o);
    TargetGenerator& operator=(const TargetGenerator& o);

public:
    TargetGenerator();
    ~TargetGenerator()

    void learnTargetType(ATarget* target);
    void forgetTargetType(const std::string& type);
    ATarget* createTarget(const std::string& type);
}

#endif

TargetGenerator::TargetGenerator() {
}

TargetGenerator::~TargetGenerator() {
    for(std::map<std::string, ATarget*>::iterator it = targets.begin(); it != targets.end(); ++it)
        delete (it->second);
}

void TargetGenerator::learnTargetType(ATarget* target) {
    if (!target) return;
    if (targets.find(target->getType()) == targets.end())
        targets[target->getType()] = target->clone();
}

void TargetGenerator::forgetTargetType(const std::string& type) {
    std::map<std::string, ATarget*>::iterator it = targets.find(type);
    if (it != targets.end()) {
        delete (it->second);
        targets.erese(it);
    }
}

ATaget* TargetGenerator::createTarget(const std::string& type) {
    std::map<std::string, ATarget*>::iterator it = targets.find(type);
    if (it != targets.end()) {
        return it->second->clone();
    }
    return 0;
}
