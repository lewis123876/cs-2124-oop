//Deejuanae Lewis
#ifndef NOBLE_H
#define NOBLE_H

#include <string>
#include <vector>
#include "Warrior.h"

namespace WarriorCraft {

    class Noble {
        friend std::ostream& operator<<(std::ostream& os, const Noble& obj);
    public:
        Noble(const std::string& name);

        bool hire(Warrior& warrior);
        bool fire(Warrior& warrior);
        void battle(Noble& enemy);
        bool removeWarrior(Warrior& warrior);

        // Getters
        const std::string& getName() const;
        double getArmyStrength() const;
        bool isAlive() const;

        // Setters
        void setAlive(bool newStatus);
        void setStrengthToZero();
        void setStrengthByRatio(double ratio);

    private:
        std::string name;
        std::vector<Warrior*> warriorPtrs;
        bool alive;
    };

} // namespace WarriorCraft

#endif // NOBLE_H
