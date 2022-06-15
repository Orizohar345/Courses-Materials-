

#ifndef EMPLOYEESTREE_H_EMPLOYEEMANAGER_H
#define EMPLOYEESTREE_H_EMPLOYEEMANAGER_H

#include "CompaniesUF.h"
#include "EmployeesTree.h"
#include "EmployeesHash.h"

namespace  DATA_STRUCTURE_HW2 {

    class EmployeeManager {
    private:
        CompaniesUF companies;
        EmployeesTree employees_with_salary;
        EmployeesHash employees;
    public:
        explicit EmployeeManager(int num_of_companies) : companies(num_of_companies) {}

        ~EmployeeManager() {}

        bool AddEmployeeEUX(int EmployeeID, int CompanyID, int Grade);

        bool RemoveEmployeeEUX(int EmployeeID);

        bool AcquireCompanyEUX(int AcquirerID, int TargetID, double Factor);

        bool employeeSalaryIncreaseEUX(int EmployeeID, int SalaryIncrease);

        bool PromoteEmployeeEUX(int EmployeeID, int BumpGrade);

        long long sumOfBumpGradeBetweenTopWorkersByGroupEUX(int CompanyID, int m);

        double averageBumpGradeBetweenSalaryByGroupEUX(int CompanyID, int lowerSalary, int higherSalary);

        double companyValueEUX(int CompanyID);

        int getNumOfComapnies() const;
    };
}
#endif //EMPLOYEESTREE_H_EMPLOYEEMANAGER_H
