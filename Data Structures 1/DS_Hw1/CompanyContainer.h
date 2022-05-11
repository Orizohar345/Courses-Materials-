//
// Created by levid on 27/04/2022.
//

#ifndef AVL_H_COMPANYCONTAINER_H
#define AVL_H_COMPANYCONTAINER_H
#include "Company.h"

namespace DATA_STRUCTURE_HW1 {





    class CompanyContainer {
    private:
        AVLTree<Company>* companies_with_employees;
        AVLTree<Company>* companies;
    public:
        CompanyContainer() : companies_with_employees(new AVLTree<Company>) , companies(new AVLTree<Company>){}

        ~CompanyContainer();

        Company* find(int CompanyID);
        Company* findInWithEmployees(int CompanyID);


        bool getCompanyInfo(int CompanyID, int *Value, int *NumEmployees);

        bool addCompany(int company_id, int value);

        bool removeCompany(int company_id);

        bool increaseCompanyValue(int CompanyID, int ValueIncrease);

        bool addEmployee(int EmployeeID, int CompanyID, int Salary, int Grade,EmployeeById* employee_by_id,EmployeeBySalary* employee_by_salary);

        bool removeEmployee(int EmployeeID, int CompanyID);

        bool acquireCompany(int AcquirerID, int TargetID, double Factor);

        bool getHighestEarner(int CompanyID, int *EmployeeID);

        bool getHighestEarnerInEachCompany(int NumOfCompanies, int **Employees);

        bool getAllEmployeesBySalary(int CompanyID, int **Employees, int *NumOfEmployees);

        bool getNumEmployeesMatching(int CompanyID, int MinEmployeeID, int MaxEmployeeId, int MinSalary, int MinGrade,
                                     int *TotalNumOfEmployees, int *NumOfEmployees);

       /* friend std::ostream& operator<<(std::ostream& os, CompanyContainer& CC);*/

    };

}

#endif //AVL_H_COMPANYCONTAINER_H
