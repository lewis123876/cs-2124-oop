//Deejuanae Lewis

#ifndef PROTECTOR_H
#define PROTECTOR_H
#include <iostream>
#include <string>
#include "Noble.h"


namespace WarriorCraft {
    class Lord;

    class Protector {
        friend std::ostream &operator<<(std::ostream &os, const Protector &obj);

    public:
        Protector(const std::string &name, double strength);

        const std::string &getName() const;
        double getStrength() const;
        void setStrength(double change);
        bool isHired() const;
        void setHired(bool newStatus);
        void setLord(Lord *newLord);
        void runaway();
        virtual void attack() const = 0;

    protected:
        std::string name;
        double strength;
        bool hired;
        Lord *lord;
    };

    class Wizard : public Protector {
    public:
        Wizard(const std::string &name, double strength);

        void attack() const;
    };

    class Warrior : public Protector {
    public:
        Warrior(const std::string &name, double strength);
    };

    class Archer : public Warrior {
    public:
        Archer(const std::string &name, double strength);

        void attack() const;
    };

    class Swordsman : public Warrior {
    public:
        Swordsman(const std::string &name, double strength);

        void attack() const;
    };
}
#endif //PROTECTOR_H
