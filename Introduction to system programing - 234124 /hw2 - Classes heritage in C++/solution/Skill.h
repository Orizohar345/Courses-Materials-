
#ifndef MTMEX2_SKILL_H
#define MTMEX2_SKILL_H
#include <iostream>
#include <string>
#include <utility>
#include "exceptions.h"
/*
 * Our Skill class, represents an ability that an employee can learn in a faculty.
 *  Data Fields:
 *  - Id: the skill's id that makes it unique.
 *  - Name: the skill's name.
 *  - RequiredPoints: the minimal Score an employee must have to learn the skill.
 */
namespace mtm {
    class Skill {
    private:
        int Id;
        std::string Name;
        int RequiredPoints;

    public:
        //Constructors:
        Skill() = delete;
        explicit Skill(int id,const std::string& name, int required_points)
                : Id(id), Name(name), RequiredPoints(required_points) {
            if(required_points<0)
                throw NegativePoints();
        }
        Skill(const Skill&) = default;
        //Destructor:
        ~Skill() = default;
        //A default Assigment operator:
        Skill& operator=(const Skill&) = default;
        //Getters: return by value.
        int getId() const;
        std::string getName() const;
        int getRequiredPoints() const;
        //Operators - All work by the id value.
        bool operator<(const Skill& skill) const;
        bool operator>(const Skill& skill) const;
        bool operator<=(const Skill& skill) const;
        bool operator>=(const Skill& skill) const;
        bool operator==(const Skill& skill) const;
        bool operator!=(const Skill& skill) const;
        Skill operator++(int);
        // Will throw NegativePoints if the points given are less than 0.
        Skill& operator+=(const int points);
        // Prints only the name field.
        friend std::ostream& operator<<(std::ostream& os, const Skill& skill);
        // Will throw NegativePoints if the points given are less than 0.
        friend Skill operator+(const Skill& skill , const int points);
        // Will throw NegativePoints if the points given are less than 0.
        friend Skill operator+(const int points , const Skill& skill);
    };
    std::ostream& operator<<(std::ostream& os, const Skill& skill);
     Skill operator+(const Skill& skill , const int points);
     Skill operator+(const int points , const Skill& skill);
}
#endif //MTMEX2_SKILL_H
