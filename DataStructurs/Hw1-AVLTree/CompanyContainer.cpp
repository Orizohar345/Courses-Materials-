
#include "cassert"
#include "CompanyContainer.h"
namespace DATA_STRUCTURE_HW1 {
    CompanyContainer::~CompanyContainer()
    {
        delete companies;
        delete companies_with_employees;
    };
    Company* CompanyContainer::find(int CompanyID)
    {
        Company company(CompanyID);
        return companies->findAVL(&company);
    }

    Company* CompanyContainer::findInWithEmployees(int CompanyID)
    {
        Company company(CompanyID);
        return companies_with_employees->findAVL(&company);
    }

    bool CompanyContainer::addCompany(int company_id, int value)
    {
        if(find(company_id))
        {
            return false;
        }
        Company* company = new(std::nothrow) Company(company_id, value);
        if(company== nullptr) throw std::bad_alloc();
        return companies->insertAVL(company);
    }

    bool CompanyContainer::getCompanyInfo(int CompanyID, int *Value, int *NumEmployees)
    {
        Company* company = find(CompanyID);
        if(company==nullptr)
        {
            return false;
        }
        *NumEmployees = company->getNumOfEmployees();
        *Value = company->getValue();
        return true;
    }

    bool CompanyContainer::removeCompany(int company_id)
    {
        Company* company_with_emp = findInWithEmployees(company_id);
        if(company_with_emp)
        {
            return false;
        }
        Company* to_delete = find(company_id);
        if(!to_delete)
        {
            return false;
        }
        Company to_delete_temp(company_id);
        companies->deleteAVL(to_delete_temp);
        delete to_delete;
        return true;
    }

    bool CompanyContainer::increaseCompanyValue(int CompanyID, int ValueIncrease)
    {
        Company* company = find(CompanyID);
        if(!company)
        {
            return false;
        }
        company->IncreaseValue(ValueIncrease);
        Company* company_in_with_employees = findInWithEmployees(CompanyID);
        if(company_in_with_employees!=nullptr)
        {
            company_in_with_employees->IncreaseValue(ValueIncrease);
        }
        return true;
    }

    bool CompanyContainer::acquireCompany(int AcquirerID, int TargetID, double Factor)
    {
        Company target_company_temp(TargetID);
        Company* acquirer_company = find(AcquirerID);

        Company* acquirer_with_emp = findInWithEmployees(AcquirerID);
        Company* target_company = find(TargetID);
        Company* target_with_emp = findInWithEmployees(TargetID);

        if((!acquirer_company) || (!target_company) || (AcquirerID==TargetID))
        {
            return false;
        }
        int AcquirerValue = acquirer_company->getValue();
        if(target_company->getNumOfEmployees()==0)
        {
            if(!acquirer_company->IsAbleToAcquire(*target_company))
            {
                return false;
            }
            increaseCompanyValue(acquirer_company->getId(),((Factor * (acquirer_company->getValue() + target_company->getValue()))-acquirer_company->getValue()));
        }
        else {
            int bought = acquirer_company->BuyCompany(target_company, Factor, acquirer_company->getId());
            if (!bought) {
                return false;
            }
            if (acquirer_with_emp!= nullptr) {
                acquirer_with_emp->BuyCompany(target_with_emp, Factor, acquirer_company->getId());
            }
            else
            {
                Company* new_acquirer_with_emp = new(std::nothrow) Company(AcquirerID, AcquirerValue, acquirer_company);
                if(new_acquirer_with_emp== nullptr) throw std::bad_alloc();
                companies_with_employees->insertAVL(new_acquirer_with_emp);
                new_acquirer_with_emp->BuyCompany(target_with_emp, Factor, acquirer_company->getId());
            }
            companies_with_employees->deleteAVL(target_company_temp);
            target_with_emp->setMain(nullptr);
            delete target_with_emp;
        }

        companies->deleteAVL(target_company_temp);
        delete target_company;
        return true;
    }

    bool CompanyContainer::getHighestEarner(int CompanyID, int *EmployeeID){
        Company* company = find(CompanyID);
        if(!company)
        {
            return false;
        }
        return company->GetHighestEarner(EmployeeID);
    }

    bool CompanyContainer::getHighestEarnerInEachCompany(int NumOfCompanies, int **Employees)
    {
        if(companies_with_employees->getNumOfElements()<NumOfCompanies)
        {
            return false;
        }
        Company::getHighestPaidId getHighest;
        (*Employees) = (int*)malloc(sizeof(int)*NumOfCompanies);
        if((*Employees)==nullptr) throw std::bad_alloc();
        companies_with_employees->limitedDataToTypeArray<Company::getHighestPaidId>(*Employees, NumOfCompanies,getHighest);
        return true;
    }

    bool CompanyContainer::getAllEmployeesBySalary(int CompanyID, int **Employees, int *NumOfEmployees)
    {
        Company* company = find(CompanyID);
        if(!company)
        {
            return false;
        }
        return company->GetAllEmployeesBySalary(Employees,NumOfEmployees);
    }

    bool CompanyContainer::getNumEmployeesMatching(int CompanyID, int MinEmployeeID, int MaxEmployeeId, int MinSalary, int MinGrade,
                                                   int *TotalNumOfEmployees, int *NumOfEmployees)
    {
        Company* company = find(CompanyID);
        if((!company))
        {
            return false;
        }
        return company->GetNumEmployeesMatching(MinEmployeeID,MaxEmployeeId,MinSalary,MinGrade,TotalNumOfEmployees,NumOfEmployees);
    }

    bool CompanyContainer::addEmployee(int EmployeeID, int CompanyID, int Salary, int Grade,EmployeeById* employee_by_id,EmployeeBySalary* employee_by_salary)
    {
        Company* company = find(CompanyID) ;
        if(!company)
        {
            return false;
        }
        bool hired = company->HireEmployee(EmployeeID, Salary, Grade,employee_by_id,employee_by_salary);
        if(!hired)
        {
            return false;
        }
        Company* company_with_employees;
        if(company->getNumOfEmployees()==1)
        {
            Company* new_company_copy = new Company(CompanyID, company->getValue(), company);
            companies_with_employees->insertAVL(new_company_copy);

        }
        company_with_employees = findInWithEmployees(CompanyID);
        company_with_employees->HireEmployee(EmployeeID, Salary, Grade,employee_by_id,employee_by_salary);
        return true;
    }

    bool CompanyContainer::removeEmployee(int EmployeeID, int CompanyID)
    {
        Company* company_with_employees = findInWithEmployees(CompanyID);
        if(!company_with_employees) {
            return false;
        }
        Company* company = company_with_employees->getMain();
        company->FireEmployee(EmployeeID);
        company_with_employees->FireEmployee(EmployeeID);
        if(company_with_employees->getNumOfEmployees()==0)
        {
            Company temp_company_to_delete(CompanyID);
            companies_with_employees->deleteAVL(temp_company_to_delete);
            company_with_employees->setMain(nullptr);
            delete company_with_employees;
        }
        return true;
    }
/*
    std::ostream& operator<<(std::ostream& os, CompanyContainer& CC)
    {
        std::cout<< "print all companies:"<<std::endl;
        AVLNode<Company>::PrintInOrder(CC.companies->getRoot());
        std::cout<< std::endl<< "print companies with employees:"<<std::endl;
        AVLNode<Company>::PrintInOrder(CC.companies_with_employees->getRoot());
        std::cout<<std::endl;

        return os;
    }
    */

}
