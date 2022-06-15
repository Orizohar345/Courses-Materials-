//
// Created by Levi on 06/06/2022.
//

#include "EmployeeManager.h"
namespace  DATA_STRUCTURE_HW2 {

    bool EmployeeManager::AddEmployeeEUX(int EmployeeID, int CompanyID, int Grade)
    {

    if(employees.InMember(EmployeeID)) return false;

    HashEmployee* main_emp = new HashEmployee(EmployeeID,0,Grade,CompanyID);
    HashEmployee* emp = new HashEmployee(EmployeeID,0,Grade,CompanyID);
    emp->setpMain(main_emp);
    employees_with_salary.IncreaseNumOfFreeWorkers();
    employees_with_salary.IncreaseGradeOfFreeWorkers(Grade);
    companies.AddAndIncreaseEmployeeGrade(CompanyID, emp);
    employees.Insert(main_emp);
    emp->setConnectorEmp(main_emp->getConnectorEmp());

    return true;
    }

    bool EmployeeManager::RemoveEmployeeEUX(int EmployeeID)
    {
        Employee* to_delete = employees.OutMember(EmployeeID);
        HashEmployee* to_delete_hash = employees.InMember(EmployeeID);
        if(to_delete==nullptr) return false ;
        if(to_delete->getEmployeeSALARY()==0){
            employees_with_salary.DecreaseNumOfFreeWorkers();
            employees_with_salary.DecreaseGradeOfFreeWorkers(to_delete->getEmployeeGRADE());
            companies.DelAndDecreaseGrade(to_delete_hash);
        }
        else {
            Employee* to_delete_with_salary = employees_with_salary.EmpFindAVL(to_delete);
            employees_with_salary.EmpDeleteAVL(*to_delete);
            delete to_delete_with_salary;
            companies.DelNoDecreaseGrade(to_delete_hash);
        }
        employees.Delete(to_delete_hash);
        delete to_delete;

        return true;
    }

    bool EmployeeManager::AcquireCompanyEUX(int AcquirerID, int TargetID, double Factor)
    {
    return companies.Union(AcquirerID,TargetID,Factor);
    }

    bool EmployeeManager::employeeSalaryIncreaseEUX(int EmployeeID, int SalaryIncrease)
    {
        Employee* to_inc = employees.OutMember(EmployeeID);
        HashEmployee* to_inc_hash = employees.InMember(EmployeeID);
        if(to_inc==nullptr) return false ;
        if(to_inc->getEmployeeSALARY()==0){
            employees_with_salary.DecreaseNumOfFreeWorkers();
            employees_with_salary.DecreaseGradeOfFreeWorkers(to_inc->getEmployeeGRADE());
            companies.decGrade(to_inc_hash);
            employees.IncSalary(EmployeeID,SalaryIncrease);
            to_inc->IncSALARY(SalaryIncrease);
            // to_inc_hash->IncSALARY(SalaryIncrease);
            Employee* to_add = new Employee(*to_inc);
            Employee* to_add_with_salary = new Employee(*to_inc);
            employees_with_salary.EmpInsertAVL(to_add_with_salary);
            companies.addEmployee(to_add,to_inc_hash,SalaryIncrease);
            delete to_inc;
            return true;
        }
        else {

            Employee* to_delete = employees_with_salary.EmpFindAVL(to_inc);
             employees_with_salary.EmpDeleteAVL(*to_inc);
            companies.delEmployee(to_inc_hash);
            to_inc->IncSALARY(SalaryIncrease);
            to_inc_hash->IncSALARY(SalaryIncrease);
            Employee* to_inc_with_salary = new Employee(*to_inc);
            employees_with_salary.EmpInsertAVL(to_inc_with_salary);
            companies.addEmployee(to_inc,to_inc_hash,SalaryIncrease);

            delete to_delete;
            return true;
            }
    }

    bool EmployeeManager::PromoteEmployeeEUX(int EmployeeID, int BumpGrade)
    {
        Employee* emp = employees.OutMember(EmployeeID);
        HashEmployee* hash_emp = employees.InMember(EmployeeID);
        if(emp==nullptr) return false;



        if(BumpGrade<=0) {
            delete emp;
            return true;
        }

        if(emp->getEmployeeSALARY()==0){
         employees_with_salary.IncreaseGradeOfFreeWorkers(BumpGrade);
         companies.changeGrade(hash_emp,BumpGrade);
         employees.ChangeGrade(EmployeeID,BumpGrade);
         delete emp;
         return true;
     }
        if(emp->getEmployeeSALARY()>0)  {
        employees.ChangeGrade(EmployeeID,BumpGrade);
         companies.changeGrade(hash_emp,BumpGrade);
         Employee* deleted = employees_with_salary.EmpFindAVL(emp);
         employees_with_salary.EmpDeleteAVL(*emp);
         deleted->PromoteGRADE(BumpGrade);
         employees_with_salary.EmpInsertAVL(deleted);
         delete emp;
         return true;
     }
        return true;
    }

    long long EmployeeManager::sumOfBumpGradeBetweenTopWorkersByGroupEUX(int CompanyID, int m)
    {
        if(CompanyID==0){
            if(employees_with_salary.EmpGetNumOfElements()<m) return -1;
            return employees_with_salary.topWorkersGradeSum(m);
        }
        return companies.UFtopWorkersGradesSum(CompanyID,m);
    }

    double EmployeeManager::averageBumpGradeBetweenSalaryByGroupEUX(int CompanyID, int lowerSalary, int higherSalary)
    {
        if(CompanyID==0){
           return employees_with_salary.gradeAveragePerRange(lowerSalary,higherSalary);
            }
        else {
            return companies.UFgradeAveragePerRange(CompanyID,lowerSalary,higherSalary);
        }
    return true;
    }

    double EmployeeManager::companyValueEUX(int CompanyID)
    {
    return companies.getCompanyValue(CompanyID);
    }

    int EmployeeManager::getNumOfComapnies() const {
        return companies.getCompaniesNumber();
    }}
