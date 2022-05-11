
#include "Company.h"

#define MULTIPLIER 10

namespace DATA_STRUCTURE_HW1 {


    void updateCompany_EmployeeById(const std::shared_ptr<AVLNode<EmployeeById>>& root ,int company);


    Company::Company(int company_id, int value, Company* main_comp) :
                        id(company_id), value(value) ,main(main_comp), employees(new EmployeesContainer){}

    Company::~Company()
    {
        if(main!= nullptr)
        {
            main=nullptr;
        }
        delete employees;
    }

    Company *Company::getMain() {
        return main;
    }
    void Company::setMain(Company* new_main) {
        main = new_main;
    }

    bool Company::IsAbleToAcquire(Company& other)
    {
        if (value < other.value * MULTIPLIER ) {
            return false;
        }
        return true;
    }

    EmployeeById* Company::find(int EmployeeID)
    {
        return employees->findById(EmployeeID);
    }

    int Company::getId() const {
        return id;
    }

    int Company::getValue() const {
        return value;
    }

    void Company::IncreaseValue(int value_addition)
    {
        value+=value_addition;
    }

    int Company::getNumOfEmployees() const {
        return employees->getNumOfEmployees();
    }

    EmployeeBySalary* Company::getHighestPaidEmployee() const {
        return employees->getHighestPaidEmployee();
    }

    bool Company::HireEmployee(int employee_id, int employee_salary, int employee_grade,EmployeeById* emp_by_id,EmployeeBySalary* emp_by_salary) {
        return employees->add(employee_id, employee_salary, employee_grade,id,emp_by_id,emp_by_salary);
    }

    bool Company::FireEmployee(int employee_id) {
        EmployeeById *to_fire_by_id = employees->findById(employee_id);
        if (!to_fire_by_id) {
            return false;
        }
        employees->del(employee_id);
        return true;
    }

    bool Company::BuyCompany(Company* other, double Factor, int new_main_companyID) {
        if(!IsAbleToAcquire(*other))
        {
            return false;
        }
        employees->acquireContainer(other->employees,new_main_companyID);
        value = (int) (Factor * (value + other->value));
        other->value = 0;
        return true;
    }

    bool Company::PromoteEmployee(int EmployeeID, int SalaryIncrease, int BumpGrade) {
        employees->promoteEmployee(EmployeeID, SalaryIncrease, BumpGrade);
        return true;
    }

    bool Company::GetHighestEarner(int *EmployeeID) {
        EmployeeBySalary *highest_paid = employees->getHighestPaidEmployee();
        if (highest_paid == nullptr) {
            return false;
        }
        *EmployeeID = highest_paid->getEmployeeBySalary_ID();
        return true;
    }

    bool Company::GetAllEmployeesBySalary(int **Employees, int *NumOfEmployees)
    {
        return employees->getAllEmployeesBySalary(Employees, NumOfEmployees);

    }

    bool Company::GetNumEmployeesMatching(int MinEmployeeID, int MaxEmployeeId, int MinSalary, int MinGrade,
                                 int *TotalNumOfEmployees, int *NumOfEmployees)
    {
        return employees->getNumEmployeesMatching(MinEmployeeID, MaxEmployeeId, MinSalary, MinGrade, TotalNumOfEmployees,
                                                 NumOfEmployees);
    }


  /*  std::ostream& operator<<(std::ostream& os, Company& company)
    {
        std::cout<< "Company ID:    " << company.getId()<<std::endl;
        std::cout<< "Company Value: " << company.getValue()<<std::endl;
        if(company.main)
        {
            std::cout << "MAIN: " << *company.main << std::endl;
        }
        else{
            printf("NULL!");
        }
        if(company.getNumOfEmployees()) {
            std::cout << "highest paid: " << company.getHighestPaidEmployee()->getEmployeeBySalary_ID() << std::endl;
        }
        std::cout<< *company.employees;
        return os;
    }*/

    bool operator<(const Company &company1,const Company &company2) {
        return company1.getId() < company2.getId();
    }

    bool operator>(const Company &company1, const Company &company2) {
        return company2 < company1;
    }

    bool operator<=(const Company &company1,const Company &company2) {
        return !(company1 > company2);
    }

    bool operator>=(const Company &company1,const Company &company2) {
        return !(company1 < company2);
    }

    bool operator==(const Company &company1,const Company &company2) {
        return ((company1 <= company2) & (company1 >= company2));
    }

    bool operator!=(const Company &company1,const Company &company2) {
        return !(company1 == company2);
    }
}
