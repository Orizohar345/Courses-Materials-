#ifndef MTMEX2_CITY_H
#define MTMEX2_CITY_H

#include <iostream>
#include "Manager.h"
#include "exceptions.h"
#include "Templates.h"
#include "exceptions.h"
#include "Faculty.h"
#include "Workplace.h"
//#include <algorithm>
namespace mtm{

    /* findWorkplace returns a shared pointer to the workplace that has the same id as the given id.
    *  Will return nullptr if no such workplace have been found. */
    std::shared_ptr<Workplace> findWorkplace(std::vector<std::shared_ptr<Workplace>> vec, int id);

    /* findCitizen returns a shared pointer to the Citizen (manager or employee) that have
    *  the same id as the given id. Will return nullptr if no such citizen (manager or employee) have been found. */
    std::shared_ptr<Citizen> findCitizen(std::vector<std::shared_ptr<Citizen>> vec, int id);

    /*
     * Our City class, represents the employment sector of a city;
     * Containing workplaces, faculties that teach skills for working in different workplaces,
     * and the citizens of the city (that are divided to employees and managers).
     *
     * Data fields:
     * 1) Name:         - the name of the city.
     * 2) Citizens:     - A vector of shared pointers to citizen class, which is the base class of employees
     *                    and managers. Holds all the citizens in our city.
     * 3) Work_places:  - A vector of shared pointers to workplace class.
     *                    Holds all the workplaces in the city.
     * 4) Faculties:    - A vector of shared pointers to faculty class.
     *                    Holds all the faculties in the city
     *
     * Methods:
     * 1)   City():                     - A default constructor.
     * 2)   City(name):                 - Constructor that initialize an empty city with a given name.
     * 3)   ~City():                    - Destructor. (default)
     * 4)   City(city):                 - Copy Constructor. (default)
     * 5)   operator=:                  - Assignment operator. (default)
     * 6)   addEmployee:                - Adds an employee to the city. (adds it to Citizens)
     * 7)   addManager:                 - Adds a manager to the city. (adds it to Citizens)
     * 8)   addFaculty:                 - Adds a faculty to the city. (adds it to Faculties)
     * 9)   createWorkplace:            - Initialize a workplace and adds it to the city. (adds it to Work_places)
     * 10)  teachAtFaculty:             - Sends an employee to learn at the faculty, to acquire the relevant skill.
     * 11)  hireManagerAtWorkplace:     - Hiring the given manager in the given workplace.
     * 12)  fireEmployeeAtWorkplace:    - Firing the given employee from the given workplace.
     * 13)  fireManagerAtWorkplace:     - Removing the given manager from the given workplace.
     * 14)  hireEmployeeAtWorkplace:    - A generic function that receives a condition, and if the given
     *                                    employee meets the condition it will hire him to the given workplace.
     * 15)  getAllAboveSalary:          - Prints a short description of all the citizens in the city that earn
     *                                    as much or above the given salary, in ascending order (by id),
     *                                    and returns the number of citizens it had printed.
     * 16) isWorkingInTheSameWorkplace: - Returns a bool that answers rather or not the two given employee's ids
     *                                    represents two employees that work in the same workplace.
     * 17)  printAllEmployeesWithSkill: - prints a short description of all the employees that hold the given skill,
     *                                    to the given std::ostream.
     */
    class City {
        std::string Name;
        std::vector<std::shared_ptr<Citizen>> Citizens;
        std::vector<std::shared_ptr<Workplace>> Work_places;
        std::vector<std::shared_ptr<Faculty<Condition>>> Faculties;
    public:
        City()= default;
        explicit City(const std::string& name) : Name(name) {};
        ~City() = default;
        City(const City& city) = default;
        City& operator=(const City&) = default;
        /*
         * addEmployee:
         * - Will throw CitizenAlreadyExists if we already have a citizen with the same id.
         */
        void addEmployee(int id, const std::string& first_name, const std::string& last_name, int birth_year);

        /*
         * addManager:
         * - Will throw CitizenAlreadyExists if we already have a citizen with the same id.
         */
        void addManager(int id, const std::string& first_name, const std::string& last_name, int birth_year);

        /*
         * addFaculty:
         * - Will throw FacultyAlreadyExists if a faculty with the same id ia already in our city.
         */
        void addFaculty(int id , const class Skill& skill, int added_points, Condition* condition);

        /*
         * createWorkplace:
         * - Will throw WorkplaceAlreadyExists if a Workplace with the same id ia already in our city.
         */
        void createWorkplace(int id, const std::string& name, int workers_salary, int managers_salary );

        /*
         * teachAtFaculty:
         *  - Will throw FacultyDoesNotExist if we do not have a faculty with the given id in our city.
         *  - Will throw EmployeeDoesNotExist if we do not have an employee with the given id in our city.
         *  - Will throw EmployeeNotAccepted if the employee did not meet the faculty condition.
         */
        void teachAtFaculty(int employee_id, int faculty_id);

        /*
         * hireManagerAtWorkplace:
         *  - Will throw ManagerDoesNotExist if we do not have a manager with the given id in our city.
         *  - Will throw WorkplaceDoesNotExist if we do not have a Workplace with the given id in our city.
         *  - Will throw ManagerAlreadyHired if the manager already works at the workplace.
         *  - Will throw CanNotHireManager if the manager already works somewhere else.
         */
        void hireManagerAtWorkplace(int manager_id, int work_place_id);

        /*
         * fireEmployeeAtWorkplace:
         *  - Will throw ManagerDoesNotExist if we do not have a manager with the given id in our city.
         *  - Will throw WorkplaceDoesNotExist if we do not have a Workplace with the given id in our city.
         *  - Will throw EmployeeDoesNotExist if we do not have an employee with the given id in our city.
         *  - Will throw ManagerIsNotHired if we do not have a manager with the given id in the Workplace given.
         */
        void fireEmployeeAtWorkplace(int employee_id, int manager_id, int work_place_id);

        /*
         * fireManagerAtWorkplace: removes all the employees from the manager and then removes the manager
         * from the workplace.
         *  - Will throw ManagerDoesNotExist if we do not have a manager with the given id in our city.
         *  - Will throw WorkplaceDoesNotExist if we do not have a Workplace with the given id in our city.
         *  - Will throw ManagerIsNotHired if we do not have a manager with the given id in the given workplace.
         */
        void fireManagerAtWorkplace(int manager_id, int work_place_id);

        /*
         * hireEmployeeAtWorkplace:
         *  - Will throw ManagerDoesNotExist if we do not have a manager with the given id in our city.
         *  - Will throw WorkplaceDoesNotExist if we do not have a Workplace with the given id in our city.
         *  - Will throw EmployeeDoesNotExist if we do not have an employee with the given id in our city.
         *  - Will throw EmployeeNotSelected if the employee does not meet the condition given.
         *  - Will throw ManagerIsNotHired if the manager is not in the given workplace.
         *  - Will throw EmployeeAlreadyHired if the employee is already employed under the given manager
         *      in the given workplace.
         */
        template <class Predicate>
        void hireEmployeeAtWorkplace(Predicate condition , const int employee_id,
                                     const int manager_id, const int work_place_id) {
            auto employee = findCitizen(Citizens, employee_id);
            Citizen* new_employee = employee.get();
            if(!employee || !(dynamic_cast<Employee*>(new_employee)))
            {
                throw EmployeeDoesNotExist();
            }
            auto manager = findCitizen(Citizens,manager_id);
            Citizen* new_manager = manager.get();
            if(!manager || !(dynamic_cast<Manager*>(new_manager)))
            {
                throw ManagerDoesNotExist();
            }
            auto work_place = findWorkplace(Work_places,work_place_id);
            if(work_place == nullptr)
            {
                throw WorkplaceDoesNotExist();
            }
            (work_place)-> hireEmployee<Predicate>(condition,dynamic_cast<Employee*>(employee.get()),
                                                   (manager)->getId());
        }

        int getAllAboveSalary(std::ostream& os, int salary);

        /*
         * isWorkingInTheSameWorkplace:
         *  - Will throw EmployeeDoesNotExist if one of the employees given are not in our city. (by id)
         */
        bool isWorkingInTheSameWorkplace(int employee1_id, int employee2_id) const;

        void printAllEmployeesWithSkill(std::ostream& os, int skill_id) const;
    };
}

#endif //MTMEX2_CITY_H
