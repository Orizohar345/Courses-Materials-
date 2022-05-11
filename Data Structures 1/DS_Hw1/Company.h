//
// Created by levid on 20/04/2022.
//

#ifndef DRY1_PROJECT_COMPANY_H
#define DRY1_PROJECT_COMPANY_H

#include "AVL.h"
#include "EmployeesContainer.h"
namespace DATA_STRUCTURE_HW1 {
    class Company {
    private:
        int id=0;
        int value=0;
        Company* main;
        EmployeesContainer* employees;
    public:
        explicit Company(int company_id=0 , int value = 0, Company* main_comp=NULL);

        Company(const Company& company)= default ;
        ~Company();

        Company& operator=(const Company& company) = default ;

        EmployeeById* find(int EmployeeID);

        Company* getMain();
        void setMain(Company* new_main);
        int getId() const;

        int getValue() const;
        void IncreaseValue(int value_addition);

        int getNumOfEmployees() const;

        bool HireEmployee(int employee_id, int employee_salary, int employee_grade,EmployeeById* emp_by_id,EmployeeBySalary* emp_by_salary);

        EmployeeBySalary* getHighestPaidEmployee() const;

        bool FireEmployee(int employee_id);

        bool PromoteEmployee(int EmployeeID, int SalaryIncrease, int BumpGrade);

        bool GetHighestEarner(int *employeeID);

        bool GetAllEmployeesBySalary(int **Employees, int *NumOfEmployees);

        bool GetNumEmployeesMatching(int MinEmployeeID, int MaxEmployeeId, int MinSalary, int MinGrade,
                                     int *TotalNumOfEmployees, int *NumOfEmployees);

        bool IsAbleToAcquire(Company& other);


        bool BuyCompany(Company* other, double Factor, int new_main_company_id);

       // friend std::ostream& operator<<(std::ostream& os, Company& company);

        class getHighestPaidId{
        public:
        int operator()(Company* company){
            return int(company->getHighestPaidEmployee()->getEmployeeBySalary_ID());
        }
    };

    };

    bool operator<(const Company &company1,const Company &company2);

    bool operator<=(const Company &company1, const Company &company2);

    bool operator>(const Company &company1,const Company &company2);

    bool operator>=(const Company &company1,const Company &company2);

    bool operator==(const Company &company1, const Company &company2);

    bool operator!=(const Company &company1,const Company &company2);
}

#endif //DRY1_PROJECT_COMPANY_H
