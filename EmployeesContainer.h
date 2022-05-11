//
// Created by levid on 24/04/2022.
//

#ifndef COMPANY_CPP_EMPLOYEESCONTAINER_H
#define COMPANY_CPP_EMPLOYEESCONTAINER_H

#include "EmployeeById.h"
#include "EmployeeBySalary.h"


#include "AVL.h"

namespace DATA_STRUCTURE_HW1 {
    class Company;
    class EmployeesContainer {
    protected:
        int num_of_employees;
        AVLTree<EmployeeBySalary>* employees_by_sa;
        AVLTree<EmployeeById>* employees_by_id;
        EmployeeBySalary* highest_paid_employee ;

        void setHighestPaidEmployee(EmployeeBySalary* employee);
    public:
        EmployeesContainer();

        ~EmployeesContainer();

        EmployeesContainer(EmployeesContainer &other)=default;

        EmployeesContainer& operator=(const EmployeesContainer &other)=default;

        int getNumOfEmployees() const;

        EmployeeBySalary* getHighestPaidEmployee() const;

        void checkAndUpdateHighestSalary(EmployeeBySalary *employee_sa);

        EmployeeById *findById(int employee_id);

        EmployeeBySalary *findBySalary(int employee_id, int employee_salary);

        bool add(int employee_id, int salary, int grade ,int hiringCompanyID ,EmployeeById* emp_by_id,EmployeeBySalary* emp_by_salary);

        bool del(int employee_id);

        void acquireContainer(EmployeesContainer* other, int companyID);

        bool getAllEmployeesBySalary(int **Employees, int* NumOfEmployees);

        bool getNumEmployeesMatching(int minId, int maxId, int minSalary, int minGrade, int *TotalNumOfEmployees,
                                     int *NumOfEmployees);

        friend std::ostream &operator<<(std::ostream &os, EmployeesContainer &EC);

        bool getEmployeeInfo(int EmployeeID, int *EmployerID, int *Salary, int *Grade);

        bool promoteEmployee(int EmployeeID, int SalaryIncrease, int BumpGrade);

        void ChangeHiringCompany(EmployeeById* employeeById,int companyID);
    };
        void updateCompany_EmployeeById(const std::shared_ptr<AVLNode<EmployeeById>>& root , int company);

        void updateCompany_EmployeeBySalary(const std::shared_ptr<AVLNode<EmployeeBySalary>>& root, int companyID);
}
#endif //COMPANY_CPP_EMPLOYEESCONTAINER_H
