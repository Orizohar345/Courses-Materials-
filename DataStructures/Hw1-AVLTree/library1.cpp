//
// Created by levid on 24/04/2022.
//
#include "library1.h"
#include "EmployeeManager.h"
using namespace DATA_STRUCTURE_HW1;

    void *Init() {
        EmployeeManager* DS = new(std::nothrow) EmployeeManager;
        return (void*)DS;
    }

    StatusType AddCompany(void* DS, int CompanyID, int Value)
    {
        try {
            if (DS == NULL || CompanyID <= 0 || Value <= 0)  return INVALID_INPUT;
            if(((EmployeeManager*)DS)->AddCompany(CompanyID,Value)) return SUCCESS;
            return FAILURE;
            }
        catch(const std::bad_alloc& e){
            return ALLOCATION_ERROR;
        }
    }

    StatusType AddEmployee(void *DS, int EmployeeID, int CompanyID, int Salary, int Grade)
    {

            if (DS == NULL || EmployeeID <= 0 || CompanyID <= 0 || Salary <= 0 || Grade < 0) {
                return INVALID_INPUT;
            }
            try {
                if(((EmployeeManager*)DS)->AddEmployee(EmployeeID,CompanyID,Salary,Grade)) return SUCCESS;
                return FAILURE;
            }
            catch ( const std::bad_alloc& e ){
                return ALLOCATION_ERROR;
            }
    }

    StatusType RemoveCompany(void *DS, int CompanyID)
    {
        if(DS==NULL || CompanyID<=0)
        {
            return INVALID_INPUT;
        }
        int success=((EmployeeManager*)DS)->RemoveCompany(CompanyID);
        if(success) return SUCCESS;
        return FAILURE;
    }

    StatusType RemoveEmployee(void *DS, int EmployeeID)
    {
        if(DS==NULL || EmployeeID<=0)
        {
            return INVALID_INPUT;
        }
        if(((EmployeeManager*)DS)->RemoveEmployee(EmployeeID)) return SUCCESS;
        return FAILURE;
    }

    StatusType GetCompanyInfo(void *DS, int CompanyID, int *Value, int *NumEmployees) {
        if (DS == NULL || CompanyID <= 0 || Value == NULL || NumEmployees == NULL) return INVALID_INPUT;
            if (((EmployeeManager *) DS)->GetCompanyInfo(CompanyID, Value, NumEmployees)) return SUCCESS;
            return FAILURE;
    }

    StatusType GetEmployeeInfo(void *DS, int EmployeeID, int *EmployerID, int *Salary, int *Grade)
    {
        if(DS==NULL || EmployeeID<=0 || EmployerID==NULL || Salary==NULL || Grade==NULL)
        {
            return INVALID_INPUT;
        }
        if(((EmployeeManager*)DS)->GetEmployeeInfo(EmployeeID,EmployerID,Salary,Grade)) return SUCCESS;
        return FAILURE;
    }

    StatusType IncreaseCompanyValue(void *DS, int CompanyID, int ValueIncrease)
    {
        if(DS==NULL || CompanyID<=0 || ValueIncrease<=0)
        {
            return INVALID_INPUT;
        }
        if(((EmployeeManager*)DS)->IncreaseCompanyValue(CompanyID,ValueIncrease)) return SUCCESS;
        return FAILURE;
    }

    StatusType PromoteEmployee(void *DS, int EmployeeID, int SalaryIncrease, int BumpGrade)
    {
        if(DS==NULL || EmployeeID<=0 || SalaryIncrease<=0)
        {
            return INVALID_INPUT;
        }
        if(((EmployeeManager*)DS)->PromoteEmployee(EmployeeID,SalaryIncrease,BumpGrade)) return SUCCESS;
        return FAILURE;
    }

    StatusType HireEmployee(void *DS, int EmployeeID, int NewCompanyID)
    {
        if(DS==NULL || EmployeeID<=0 || NewCompanyID<=0)
        {
            return INVALID_INPUT;
        }
        if(((EmployeeManager*)DS)->HireEmployee(EmployeeID,NewCompanyID)) return SUCCESS;
        return FAILURE;
    }

    StatusType AcquireCompany(void *DS, int AcquirerID, int TargetID, double Factor)
    {
        if(DS==NULL || AcquirerID<=0 || TargetID<=0 || AcquirerID==TargetID || Factor<1.00)
        {
            return INVALID_INPUT;
        }
        if(((EmployeeManager*)DS)->AcquireCompany(AcquirerID,TargetID,Factor)) return SUCCESS;
        return FAILURE;
    }

    StatusType GetHighestEarner(void *DS, int CompanyID, int *EmployeeID)
    {
        if(DS==NULL || CompanyID==0 || EmployeeID==NULL )
        {
            return INVALID_INPUT;
        }
        if(((EmployeeManager*)DS)->GetHighestEarner(CompanyID,EmployeeID)) return SUCCESS;
        return FAILURE;
    }

    StatusType GetAllEmployeesBySalary(void *DS, int CompanyID, int **Employees, int *NumOfEmployees) {
        if (DS == NULL || CompanyID == 0 || Employees == NULL || NumOfEmployees == NULL) {
            return INVALID_INPUT;
        }
        if (((EmployeeManager *) DS)->GetAllEmployeesBySalary(CompanyID,Employees,NumOfEmployees)) return SUCCESS;
        return FAILURE;
    }

    StatusType GetHighestEarnerInEachCompany(void *DS, int NumOfCompanies, int **Employees)
    {
        if(DS==NULL || NumOfCompanies<1 || Employees==NULL)
        {
            return INVALID_INPUT;
        }
        if (((EmployeeManager *) DS)->GetHighestEarnerInEachCompany(NumOfCompanies,Employees)) return SUCCESS;
        return FAILURE;
    }

    StatusType GetNumEmployeesMatching(void *DS, int CompanyID, int MinEmployeeID, int MaxEmployeeID,
                                           int MinSalary, int MinGrade, int *TotalNumOfEmployees, int *NumOfEmployees) {
        if (DS == NULL || CompanyID == 0 || MinEmployeeID < 0 || MaxEmployeeID < 0 || MinSalary < 0 || MinGrade < 0
            || MaxEmployeeID < MinEmployeeID || TotalNumOfEmployees == NULL || NumOfEmployees == NULL) {
            return INVALID_INPUT;
        }
        if (((EmployeeManager *) DS)->GetNumEmployeesMatching(CompanyID,MinEmployeeID, MaxEmployeeID,
                MinSalary,MinGrade,TotalNumOfEmployees,NumOfEmployees) ) return SUCCESS;
        return FAILURE;
    }

    void Quit(void **DS)
    {
       if(DS!=nullptr/* && *DS!= nullptr*/)
       {
           delete (EmployeeManager*)(*DS);
       }
       if(DS!=nullptr)
       {
           *DS=nullptr;
       }
    }
