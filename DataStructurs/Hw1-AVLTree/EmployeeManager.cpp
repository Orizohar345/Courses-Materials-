//
// Created by Ori Zohar on 01/05/2022.
//
#include "EmployeeManager.h"
#include "cassert"
namespace  DATA_STRUCTURE_HW1 {

    bool EmployeeManager::AddCompany(int CompanyID, int Value) {
        bool was_added = companies.addCompany(CompanyID, Value);
        if (!was_added) {
            return false;
        }
        return true;
    }

    bool EmployeeManager::AddEmployee(int EmployeeID, int CompanyID, int Salary, int Grade) {
        Company *hiring_company = companies.find(CompanyID);
        if (!hiring_company || employees.findById(EmployeeID)) {
            return false;
        }

        if (!employees.add(EmployeeID, Salary, Grade, hiring_company->getId(),NULL,NULL)) {
            return false;
        }

        EmployeeById* employee_by_id = employees.findById(EmployeeID);
        EmployeeBySalary* employee_by_salary = employees.findBySalary(EmployeeID,Salary);
        if (!companies.addEmployee(EmployeeID, CompanyID, Salary, Grade,employee_by_id,employee_by_salary)) {
            return false;
        }
        return true;
    }

    bool EmployeeManager::RemoveCompany(int CompanyID) {
        int removed = companies.removeCompany(CompanyID);
        if (!removed) {
            return false;
        }
        return true;
    }

    bool EmployeeManager::RemoveEmployee(int EmployeeID) {
        EmployeeById *employee = employees.findById(EmployeeID);
        if (!employee) {
            return false;
        }

        int hiring_company_id = employee->getEmployeeByID_COMPANY();
        employees.del(EmployeeID);
        companies.removeEmployee(EmployeeID, hiring_company_id);
        return true;
    }

    bool EmployeeManager::GetCompanyInfo(int CompanyID, int *Value, int *NumEmployees) {
        bool success = companies.getCompanyInfo(CompanyID, Value, NumEmployees);
        if (!success) {
            return false;
        }
        return true;

    }

    bool EmployeeManager::GetEmployeeInfo(int EmployeeID, int *EmployerID, int *Salary, int *Grade) {

        bool success = employees.getEmployeeInfo(EmployeeID, EmployerID, Salary, Grade);
        if (!success) {
            return false;
        }
        return true;
    }

    bool EmployeeManager::IncreaseCompanyValue(int CompanyID, int ValueIncrease) {
        bool success = companies.increaseCompanyValue(CompanyID, ValueIncrease);
        if (!success) {
            return false;
        }
        return true;
    }

    bool EmployeeManager::PromoteEmployee(int EmployeeID, int SalaryIncrease, int BumpGrade) {
        EmployeeById *employee = employees.findById(EmployeeID);
        if (!employee) {
            return false;
        }
        bool success = employees.promoteEmployee(EmployeeID, SalaryIncrease, BumpGrade);
        Company *hiring_company_in_with_employees = companies.findInWithEmployees(
                employee->getEmployeeByID_COMPANY());
        hiring_company_in_with_employees->PromoteEmployee(EmployeeID, SalaryIncrease, BumpGrade);
        hiring_company_in_with_employees->getMain()->PromoteEmployee(EmployeeID,SalaryIncrease,BumpGrade);
        return success;
    }

    bool EmployeeManager::HireEmployee(int EmployeeID, int NewCompanyID)
    {
        EmployeeById* employee_id = employees.findById(EmployeeID);
        if(!employee_id)
        {
            return false;
        }
        Company* new_company = companies.find(NewCompanyID);
        if (!new_company) {
            return false;
        }
        if (employee_id->getEmployeeByID_COMPANY() && employee_id->getEmployeeByID_COMPANY() == NewCompanyID) {
            return false;
        }

        int Salary = employee_id->getEmployeeByID_SALARY();
        int Grade = employee_id->getEmployeeByID_GRADE();

        RemoveEmployee(EmployeeID);
        AddEmployee(EmployeeID,NewCompanyID,Salary,Grade);
        return true;
    }

    bool EmployeeManager::AcquireCompany(int AcquirerID, int TargetID, double Factor) {
        if(AcquirerID==TargetID) return false;
        bool success = companies.acquireCompany(AcquirerID, TargetID, Factor);
        return success;
    }

    bool EmployeeManager::GetHighestEarner(int CompanyID, int *EmployeeID) {
        bool success = false;
        if (CompanyID > 0) {
            success = companies.getHighestEarner(CompanyID, EmployeeID);
        } else if (CompanyID < 0) {
            EmployeeBySalary *highest_earner = employees.getHighestPaidEmployee();
            if (highest_earner != nullptr) {
                *EmployeeID = highest_earner->getEmployeeBySalary_ID();
                success = true;
            }
        }
        if (!success) {
            return false;
        }
        return true;
    }

    bool EmployeeManager::GetAllEmployeesBySalary(int CompanyID, int **Employees, int *NumOfEmployees) {
        bool success = false;
        if (CompanyID > 0) {
            success = companies.getAllEmployeesBySalary(CompanyID, Employees, NumOfEmployees);
        } else if (CompanyID < 0) {
            success = employees.getAllEmployeesBySalary(Employees, NumOfEmployees);
        }
        if (!success) {
            return false;
        }
        return true;
    }

    bool EmployeeManager::GetHighestEarnerInEachCompany(int NumOfCompanies, int **Employees) {
        int success = companies.getHighestEarnerInEachCompany(NumOfCompanies, Employees);
        if (!success) {
            return false;
        }
        return true;
    }

    bool EmployeeManager::GetNumEmployeesMatching(int CompanyID, int MinEmployeeID, int MaxEmployeeID,
                                                  int MinSalary, int MinGrade, int *TotalNumOfEmployees,
                                                  int *NumOfEmployees) {
        bool success = false;
        if (CompanyID > 0) {
            success = companies.getNumEmployeesMatching(CompanyID, MinEmployeeID, MaxEmployeeID,
                                                        MinSalary, MinGrade, TotalNumOfEmployees, NumOfEmployees);
        } else if (CompanyID < 0) {
            success = employees.getNumEmployeesMatching(MinEmployeeID, MaxEmployeeID,
                                                        MinSalary, MinGrade, TotalNumOfEmployees, NumOfEmployees);
        }
        if (!success) {
            return false;
        }
        return true;
    }
}
