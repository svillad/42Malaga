#include "Warlock.hpp"
#include "BrickWall.hpp"
#include "Polymorph.hpp"
#include "Fireball.hpp"
#include "TargetGenerator.hpp"

int main()
{
    Warlock richard("Richard", "foo");
    richard.setTitle("Hello, I'm Richard the Warlock!");

    BrickWall  model1;
    Polymorph *polymorph = new Polymorph();
    Fireball  *fireball  = new Fireball();

    TargetGenerator tarGen;
    tarGen.learnTargetType(&model1);

    richard.learnSpell(polymorph);
    richard.learnSpell(fireball);

    ATarget *wall = tarGen.createTarget("Inconspicuous Red-brick Wall");

    richard.introduce();
    richard.launchSpell("Polymorph", *wall);
    richard.launchSpell("Fireball",  *wall);

    delete polymorph;
    delete fireball;
}