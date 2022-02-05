
#ifndef MTMEX2_FACULTY_H
#define MTMEX2_FACULTY_H
#include <iostream>
#include "Workplace.h"
#include "Skill.h"
#include <memory>
#include "Employee.h"

namespace mtm {
    class Condition
    {
    public:
        virtual bool operator()(Employee* employee) = 0;
    };

    /*
 * Our Faculty class;
 * A generic class representing a faculty where employees learn the skills if they meet the admission requirements.
 *  - Id : The faclty's Id.
 *  - Skill: The skill that the faculty wil teach the employee .
 *  - AddedPoints: The amount of points the faculty should add to the employee's score if the skill is taught .
 *  - t : Pointer to object function of the condition that wil determine if a skill can be taught or not.
 */
    template <typename T>
    class Faculty {
        int Id;
        Skill skill;
        int AddedPoints;
        T* t;
    public:
        //Constructors:
        Faculty(int id ,const class Skill& skill1 ,int added_points, T* condition) :
                Id(id) , skill(skill1) ,AddedPoints(added_points) , t(condition)  {}

        //Default Desctructor :
        ~Faculty()=default;

        // Default Copy Constructor :
        Faculty& operator=(const Faculty& faculty) = default ;

        //Default Assigment operator :
        Faculty(const Faculty& faculty) = default;

        // Getters for Id , AddedPoints and Skill :
        int getId() const {
            return Id;
        }
        int getAddedPoints() const {
            return AddedPoints;
        }
        const class Skill& getSkill() const  {
            return skill;
        }

        /*
         * teach Function :
         * Gets pointers of an Employee and try to learn him the faculty's skill .
         * If the emplyee can learn the skill , the skill will be added to his skills set and his score will be raise .
         * If the skill can't be taught the function will throw EmployeeNotAccepted exception .
         */
        void teach(Employee* employee)
        {
            if(!(t->operator()(employee)))
            {
                throw EmployeeNotAccepted();
            }
            employee->learnSkill(skill);
            employee->setScore(AddedPoints);
        }
    };
}

#endif //MTMEX2_FACULTY_H
