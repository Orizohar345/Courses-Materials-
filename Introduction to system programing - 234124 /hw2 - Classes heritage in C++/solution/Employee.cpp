#include "Citizen.h"
#include "Skill.h"
#include "Employee.h"
#include "exceptions.h"
#include "Templates.h"
#include <set>
#include <iostream>
#include <algorithm>
using std::cout;
using std::endl;
using namespace mtm;
Employee::Employee(const Employee& employee)
        : Citizen(employee.getId(), employee.getFirstName(), employee.getLastName(), employee.getBirthYear()),
          Score(employee.getScore()), Salary(employee.getSalary()), set(employee.set) {}
Employee& Employee::operator=(const Employee& employee)
{
    if(this == &employee)
    {
        return *this;
    }
    set.clear();
    for(Skill i : employee.set)
    {
        set.insert(i);
    }
return *this;
}
int Employee::getScore() const
{
    return Score;
}
int Employee::getSalary() const
{
    return Salary;
}
void Employee::setSalary(int salary)
{
    this->Salary += salary;
    if(this->Salary < 0)
    {
        this->Salary =0;
    }
}
void Employee::setScore(int score)
{
    this->Score += score;
    if(this->Score < 0)
    {
        this->Score =0;
    }
}
void Employee::learnSkill(Skill skill)
{
    //if skill is in set (count != 0)
    if(set.count(skill))
    {
        throw SkillAlreadyLearned();
    }
    //if employee's score is insufficient
    if(Score < skill.getRequiredPoints())
    {
        throw CanNotLearnSkill();
    }
    auto result = set.insert(skill); //can we use auto????
    if(!result.second)
    {
        throw std::bad_alloc();
    }
}
void Employee::forgetSkill(int skill_id)
{
    if(!hasSkill(skill_id))
    {
        throw DidNotLearnSkill();
    }
    for(Skill i : set)
    {
        if(i.getId() == skill_id)
        {
            set.erase(i);
            return;
        }
    }
}
bool Employee::hasSkill(int skill_id)
{
    for(Skill i : set)
    {
        if(i.getId() == skill_id)
        {
            return true;
        }
    }
    return false;
}
std::ostream& Employee::printShort(std::ostream& os)
{
    os << getFirstName() << " " << getLastName() << endl;
    os << "Salary: " << getSalary() << " Score: " << getScore() << endl;
    return os; // ????????
}
std::ostream& Employee::printLong(std::ostream& os)
{
    os << getFirstName() << " " << getLastName() << endl;
    os << "id - " << getId() << " birth_year - " << getBirthYear() <<endl;
    os << "Salary: " << getSalary() << " Score: " << getScore();
    if(set.begin() != set.end())
    {
      os << " Skills: " << endl;
    }
    else {
        os << endl;
    }
    for(Skill i : set)
    {
        os << i;
    }
    return os;
}
Employee* Employee::clone() const
{
    return new Employee(*this); // not sure if it will work
}
bool mtm::employeeHasSkill(Employee* employee, int skill_id)
{
    for(Skill skill :employee->set)
    {
        if(skill.getId() == skill_id) {
            return true;
        }
    }
    return false;
}
