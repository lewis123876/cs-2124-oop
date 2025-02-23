//Deejuanae Lewis
#include "Noble.h"
#include <iostream>

namespace WarriorCraft {

    Noble::Noble(const std::string& name) : name(name), alive(true) {}

    const std::string& Noble::getName() const { return name; }
    double Noble::getArmyStrength() const {
        double total = 0;
        for (const Warrior* warrior : warriorPtrs) {
            total += warrior->getStrength();
        }
        return total;
    }

    bool Noble::isAlive() const { return alive; }

    void Noble::setAlive(bool newStatus) { alive = newStatus; }
    void Noble::setStrengthToZero() {
        for (Warrior* warrior : warriorPtrs) {
            warrior->setStrength(0);
        }
    }

    void Noble::setStrengthByRatio(double ratio) {
        for (Warrior* warrior : warriorPtrs) {
            warrior->setStrength(warrior->getStrength() * (1 - ratio));
        }
    }

    bool Noble::hire(Warrior& warrior) {
        if (!alive) {
            std::cout << name << " is dead and cannot hire anyone." << std::endl;
            return false;
        }
        if (warrior.isHired() || warrior.getStrength() == 0) {
            std::cout << name << " failed to hire " << warrior.getName() << std::endl;
            return false;
        }

        warriorPtrs.push_back(&warrior);
        warrior.setHired(true);
        warrior.setNoble(this);
        return true;
    }

    bool Noble::fire(Warrior& warrior) {
        if (!alive) {
            std::cout << name << " is dead. He can't fire a warrior." << std::endl;
            return false;
        }

        if (removeWarrior(warrior)) {
            std::cout << warrior.getName() << ", you don't work for me anymore! --" << name << std::endl;
            return true;
        }

        std::cout << name << " failed to fire " << warrior.getName() << std::endl;
        return false;
    }

    bool Noble::removeWarrior(Warrior& warrior) {
        for (auto it = warriorPtrs.begin(); it != warriorPtrs.end(); ++it) {
            if (*it == &warrior) {
                warriorPtrs.erase(it);
                warrior.setHired(false);
                return true;
            }
        }
        return false;
    }

    void Noble::battle(Noble& enemy) {
        std::cout << name << " battles " << enemy.getName() << std::endl;

        if (!alive && !enemy.isAlive()) {
            std::cout << "Oh, NO!  They're both dead!  Yuck!" << std::endl;
        } else if (!alive) {
            std::cout << "He's dead, " << enemy.getName() << std::endl;
        } else if (!enemy.isAlive()) {
            std::cout << "He's dead, " << name << std::endl;
        } else {
            double myStrength = getArmyStrength();
            double enemyStrength = enemy.getArmyStrength();

            if (myStrength > enemyStrength) {
                double ratio = enemyStrength / myStrength;
                setStrengthByRatio(ratio);
                enemy.setStrengthToZero();
                enemy.setAlive(false);
                std::cout << name << " defeats " << enemy.getName() << std::endl;
            } else if (enemyStrength > myStrength) {
                double ratio = myStrength / enemyStrength;
                enemy.setStrengthByRatio(ratio);
                setStrengthToZero();
                setAlive(false);
                std::cout << enemy.getName() << " defeats " << name << std::endl;
            } else {
                setStrengthToZero();
                setAlive(false);
                enemy.setStrengthToZero();
                enemy.setAlive(false);
                std::cout << "Mutual Annihilation: " << name << " and " << enemy.getName() << " die at each other's hands" << std::endl;
            }
        }
    }

    std::ostream& operator<<(std::ostream& os, const Noble& obj) {
        os << obj.getName() << " has an army of " << obj.warriorPtrs.size();
        for (const Warrior* warrior : obj.warriorPtrs) {
            os << "\n\t" << *warrior;
        }
        return os;
    }

} // namespace WarriorCraft
