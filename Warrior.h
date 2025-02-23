//Deejuanae Lewis
#ifndef WARRIOR_H
#define WARRIOR_H

#include <string>
#include <iostream>

namespace WarriorCraft {

    class Noble; // Forward declaration

    class Warrior {
        friend std::ostream& operator<<(std::ostream& os, const Warrior& obj);
    public:
        Warrior(const std::string& name, double strength);

        void runaway();

        // Getters
        const std::string& getName() const;
        double getStrength() const;
        bool isHired() const;

        // Setters
        void setHired(bool newStatus);
        void setStrength(double newStrength);
        void setNoble(Noble* newNoble);

    private:
        std::string name;
        double strength;
        bool hired;
        Noble* noble;
    };

} // namespace WarriorCraft

#endif // WARRIOR_H
