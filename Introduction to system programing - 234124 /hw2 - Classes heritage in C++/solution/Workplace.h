
#ifndef MTMEX2_WORKPLACE_H
#define MTMEX2_WORKPLACE_H
#include "Manager.h"
#include "exceptions.h"
#include "Templates.h"
#include "exceptions.h"
#include <algorithm>

namespace mtm {
    /*
 * Our Workplace class;
 * A class that represents a workplace that contains managers (each manager has his own employees).
 *  - Id: the workplace's ID .
 *  - Name: the workplace's  name .
 *  - WorkersSalary: The salary that will be given to an employee that working in the workplace.
 *  - ManagersSalary : The salary that will be given to a manager that working in the workplace .
 *  - Managers : Container that will include all the mangers that working in the workplace .
 */
    class Workplace {
        int Id;
        std::string Name;
        int WorkersSalary;
        int ManagersSalary;
        std::vector<Manager*> Managers;
    public :
        // Constructors :
        Workplace()=default;
        Workplace(const int id , const std::string& name , int workers_salary , int managers_salary ) :
                Id(id), Name(name), WorkersSalary(workers_salary), ManagersSalary(managers_salary),Managers(std::vector<Manager*>() ) {}

        // Destructor :
        ~Workplace()=default;

        // Copy Constructor :
        Workplace(const Workplace& workplace) = default ;

        // Assigment Operator :
        Workplace& operator=(const Workplace&)=default;

        // Getters for Id , Name , WorkersSalary and ManagersSalary :
        int getId() const ;
        std::string getName () const ;
        int getWorkersSalary() const ;
        int getManagersSalary() const ;

        /* hireManager Function :
         * Gets pointer to a manager and try to add the manager to the workplace .
         * If the manager is already in the workplace the function will throw exception : ManagerAlreadyHired .
         * If the manager work in other workplace the function will throw exception : CanNotHireManager .
         * If the manager can be join to the workplace the function will add him to the Manager's container and will raise his salary .
         */
        void hireManager(Manager* manager) ;

        /* fireEmployee Function :
         * Receives an employee ID number, and the manager's ID number.
         * The function tries to remove it from the group of manager she receives.
         * The method throws an EmployeeIsNotHired exception in case the employee does not exist in the manager group .
         * The method throws an ManagerIsNotHired in case the manager does not exist in the workplace.
         */
        void fireEmployee(const int& employee_id ,const int& manager_id) ;

        /* fireManager Function :
         * Gets an ID number for the manager and removes him and his group from the workplace.
         * If the manager does not exist in the workplace the function will throw ManagerIsNotHired exception .
         */
        void fireManager(const int& manager_id);

         /* operator<< :
         * Prints the Workplace name and the all the mangers and the employees in the work place .
         * For example :
         * Workplace name - XXX
         * Groups :
         * Manger YYY's name
         * // Here's YYY Long print that includes the manager's details and all the employee that working under him information .
         */
        friend std::ostream& operator<< (std::ostream& os ,const Workplace& workplace);

        /* isEmployeeInWorkplace
         * Gets the workplace and the employee's id .
         * check if the employee works in the work place and return true or false .
         */
        friend bool isEmployeeInWorkplace(Workplace workplace, int employee_id);

        /* hireEmployee function :
         * Is a generic function that represents a condition for receiving the employee (which is an object function) .
         * Gets The condition function ( that always need to return bool ) ,pointer to the employee  and the ID number of the manager
         * If the employee she gets meets the condition, and the manager is found in the work place
         * the method adds it to the company under in the group of the manager it receives.
         * If the employee does not meet the condition the function throw EmployeeNotSelected exception .
         * If the manager does not exist in the workplace the function throw ManagerIsNotHired exception .
         * If the employee already works in the group of the manager who received it the function throw EmployeeAlreadyHired exception .
         */
        template<class Predicate>
        void hireEmployee(Predicate pred,Employee* employee ,int manager_id )
        {
            if(!pred.operator()(employee))
            {
                throw EmployeeNotSelected() ;
            }
            IdComparation<Manager> CompareForEmployee(manager_id);
            auto manager_is_found = std::find_if(Managers.begin(), Managers.end(),CompareForEmployee);
            if(manager_is_found == Managers.end()) {
                throw ManagerIsNotHired();
            }
            try {
                (*manager_is_found)->addEmployee(employee);
            }
            catch (EmployeeAlreadyHired& e) {
                throw EmployeeAlreadyHired();
            }
            employee->setSalary(WorkersSalary);
        }
    };
}
#endif //MTMEX2_WORKPLACE_H
