#ifndef MTMEX2_EMPLOYEE_H
#define MTMEX2_EMPLOYEE_H
#include "Citizen.h"
#include "Skill.h"
#include <set>
/*
 * Our Employee class;
 * Inherits from the Citizen class, an employee is a citizen with:
 *  - Score: the score is what determine if a skill can be taught or not.
 *  - Salary: the employee's salary.
 *  - set: a set container that holds all the skills the employee have learned.
 */
namespace mtm {
    class Employee : public Citizen {
        int Score;
        int Salary;
        std::set<Skill> set;

    public:
        //Constructors:
        Employee()=default;
        Employee( int id,const std::string& first_name,const std::string& last_name, int birth_year)
                : Citizen(id, first_name, last_name, birth_year), Score(0), Salary(0), set(std::set<Skill>()) {}
        Employee(const Employee& employee);
        //Destructor:
        ~Employee() override = default;
        //Assignment operator:
        Employee& operator=(const Employee& employee);
        //Getters and setters for score and salary:
        int getScore() const ;
        int getSalary() const override;
        void setSalary(int salary);
        void setScore(int score);
        /*
         * learnSkill: given a skill, will add it to the employee's set of skill.
         *  - Will throw SkillAlreadyLearned if our employees set holds a skill with the same id.
         *  - Will throw CanNotLearnSkill if our employees score is insufficient (smaller than requiredPoints in skill)
         */
        void learnSkill(Skill skill);
        /*
         * forgetSkill: given an id of a skill, will remove the corresponding skill from the employee's set.
         *  - Will throw DidNotLearnSkill if we don't have a skill with the same id in the employee's set.
         */
        void forgetSkill(int skill_id);
         // hasSkill: return rather or not we have a skill in the employee's set with the same id.
        bool hasSkill(int skill_id);
        /*
         * Printing functions:
         *  - printShort prints name salary and score.
         *  - printLong prints name, id, birth year, salary, score and the employee's skills.
         */
        std::ostream& printShort(std::ostream& os)  override;
        std::ostream& printLong(std::ostream& os) override;
        // Employee clone - returns a pointer to a new identical Employee.
        Employee* clone() const override;
         // employeeHasSkill: the same as hasSkill but receives a pointer to an employee.
        friend bool employeeHasSkill(Employee* employee, int skill_id);
    };
    bool employeeHasSkill(Employee* employee, int skill_id);
}
#endif //MTMEX2_EMPLOYEE_H
