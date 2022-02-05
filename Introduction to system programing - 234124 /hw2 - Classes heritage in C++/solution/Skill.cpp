#include <iostream>
#include <string>
#include "Skill.h"
#include "exceptions.h"
using std::string;
using std::cout;
using std::endl;
using namespace mtm;
/* The implementation of the Skill class, which holds 3 values:
 * -Id
 * -Name
 * -RequiredPoints */

// Getters:
int Skill::getId() const
{
    return Id;
}
string Skill::getName() const
{
    return Name;
}
int Skill::getRequiredPoints() const
{
    return RequiredPoints;
}

// Operators:
bool Skill::operator<(const Skill& skill) const
{
    return Id < skill.Id;
}
bool Skill::operator>(const Skill& skill) const
{
    return Id > skill.Id;
}
bool Skill::operator<=(const Skill& skill) const
{
    return !(*this > skill);
}
bool Skill::operator>=(const Skill& skill) const
{
    return !(*this < skill);
}
bool Skill::operator==(const Skill& skill) const
{
    return Id == skill.Id;
}
Skill Skill::operator++(int)
{
    Skill skill(*this);
    RequiredPoints++;
    return skill;
}
Skill& Skill::operator+=(const int points)
{
    if(points < 0)
    {
        throw NegativePoints();
    }
    RequiredPoints += points;
    return *this;
}
std::ostream& mtm::operator<<(std::ostream& os, const Skill& skill)
{
    return os << skill.Name << endl;
}
bool Skill::operator!=(const Skill& skill) const
{
    return !(*this == skill);
}
Skill mtm::operator+(const Skill& skill , const int points)
{
    if(points < 0)
    {
        throw NegativePoints();
    }
    Skill new_skill(skill.Id, skill.Name, skill.RequiredPoints + points);
    return new_skill;
}
Skill mtm::operator+(const int points , const Skill& skill)
{
    if(points < 0)
    {
        throw NegativePoints();
    }
    Skill new_skill(skill.Id, skill.Name, skill.RequiredPoints + points);
    return new_skill;
}



