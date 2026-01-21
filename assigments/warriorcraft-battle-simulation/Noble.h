#ifndef NOBLE_H
#define NOBLE_H

#include <iostream>
#include <string>
#include <vector>
#include "Protector.h"

namespace WarriorCraft {
    class Protector;

    class Noble {
    public:
        Noble(const std::string &name);

        const std::string &getName() const;
        bool battleCheck(const Noble &enemy) const;
        void battle(Noble &enemy);
        virtual double getStrength() const = 0;
        virtual void reduceStrength(double change) = 0;
        virtual void attack() const = 0;
        bool isAlive() const;
        void setAlive(bool newStatus);

    private:
        std::string name;
        bool alive;
    };

    class Lord : public Noble {
        friend std::ostream &operator<<(std::ostream &os, const Lord &obj);

    public:
        Lord(const std::string &name);

        double getStrength() const;
        void reduceStrength(double change);
        bool hires(Protector &protector);
        bool fires(Protector &protector);
        bool removeProtector(Protector &protector);
        void attack() const;

    private:
        std::vector<Protector *> protectorPtrs;
    };

    class PersonWithStrengthToFight : public Noble {
        friend std::ostream &operator<<(std::ostream &os,
                                   const PersonWithStrengthToFight &obj);

    public:
        PersonWithStrengthToFight(const std::string &name, double strength);

        double getStrength() const;
        void reduceStrength(double change);
        void attack() const;

    private:
        double strength;
    };

}
#endif //NOBLE_H

