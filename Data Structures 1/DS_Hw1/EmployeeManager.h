//
// Created by Ori Zohar on 01/05/2022.
//
#include "CompanyContainer.h"
#include "EmployeesContainer.h"

#ifndef AVL_H_EMPLOYEEMANAGER_H
#define AVL_H_EMPLOYEEMANAGER_H
namespace  DATA_STRUCTURE_HW1 {


    class EmployeeManager {
    private:
        CompanyContainer companies;
        EmployeesContainer employees;
    public:
        EmployeeManager() = default;
        bool AddCompany(int CompanyID, int Value);

        bool AddEmployee(int EmployeeID, int CompanyID, int Salary, int Grade);

        bool RemoveCompany(int CompanyID);

        bool RemoveEmployee(int EmployeeID);

        bool GetCompanyInfo(int CompanyID, int *Value, int *NumEmployees);

        bool GetEmployeeInfo(int EmployeeID, int *EmployerID, int *Salary, int *Grade);

        bool IncreaseCompanyValue(int CompanyID, int ValueIncrease);

        bool PromoteEmployee(int EmployeeID, int SalaryIncrease, int BumpGrade);

        bool HireEmployee(int EmployeeID, int NewCompanyID);

        bool AcquireCompany(int AcquirerID, int TargetID, double Factor);

        bool GetHighestEarner(int CompanyID, int *EmployeeID);

        bool GetAllEmployeesBySalary(int CompanyID, int **Employees, int *NumOfEmployees);

        bool GetHighestEarnerInEachCompany(int NumOfCompanies, int **Employees);

        bool GetNumEmployeesMatching(int CompanyID, int MinEmployeeID, int MaxEmployeeID,
                                     int MinSalary, int MinGrade, int *TotalNumOfEmployees, int *NumOfEmployees);
    };
}
#endif //AVL_H_EMPLOYEEMANAGER_H
