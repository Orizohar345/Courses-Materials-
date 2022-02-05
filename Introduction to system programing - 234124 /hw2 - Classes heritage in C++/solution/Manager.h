#ifndef MTMEX2_MANAGER_H
#define MTMEX2_MANAGER_H
#include "Employee.h"
#include <vector>
/*
 * Our Manager class;
 * Inherits from the Citizen class, a Manager is a citizen with:
 *  - Salary: the employee's salary.
 *  - Employees: a vector container that holds all the employees the manager have under him directly.
 */
namespace mtm {
    class Manager : public Citizen {
        int Salary ;
        std::vector<Employee*> Employees ;
    public :
        const static int initial_salary = 0 ;
        //Constructors:
        Manager() = default ;
        Manager(int id , const std::string& first_name , const std::string& last_name , int birth_year ) :
                Citizen(id,first_name,last_name ,birth_year) , Salary(initial_salary) ,
                Employees(std::vector<Employee*>()) {}
        Manager(const Manager& manager) = default;
        //Destructor:
        ~Manager() override = default ;
        //Assignment operator:
        Manager& operator=(const Manager&) = default;
        //Get and set for salary:
        int getSalary() const override;
        void setSalary(const int salary);
        /*
         * addEmployee: receives a pointer to an employee and adds it to the vector, then it sorts the vector
         * by the Employees ids.
         *  - Will throw EmployeeAlreadyHired if an employee with the same id is already in the vector.
         */
        void addEmployee (Employee* employee);
        /*
         * removeEmployee: receives an id and removes the employee with the corresponding id from the vector.
         *  - Will throw EmployeeIsNotHired if no such employee is found (with the same id).
         */
        void removeEmployee (const int id) ;
        /*
         * printing functions:
         *  - printShort: prints full name and salary.
         *  - printLong: prints full name, id, birth year, salary and a short print for each employee in Employees.
         */
        std::ostream& printShort(std::ostream& os)  override;
        std::ostream& printLong(std::ostream& os)  override;
        //Manager clone: returns a pointer to a new identical manager.
        Manager* clone() const override;
        /*
         * SetSalaryForEmployee: finds the employee with the same id as employee_id and sets his/hers Salary with
         * the salary that was given as a parameter.
         *  - Will throw EmployeeIsNotHired if no such employee is found (with the same id as was given).
         */
        void SetSalaryForEmployee(int employee_id, int salary);
        /*
         * FireAllEmployees: removes all employees from (the container)Employees and removes the given salary from each employee's
         * salary field.
         */
        void FireAllEmployees(int salary);
        //Returns rather or not the curr_manager has an employee with the given id in his Employees container.
        friend bool isEmployeeOfManager(Manager* curr_manager, int employee_id);
    };
    bool isEmployeeOfManager(Manager* curr_manager, int employee_id);
}

#endif //MTMEX2_MANAGER_H
