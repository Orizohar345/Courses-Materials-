

#include "EmployeeBySalary.h"

namespace DATA_STRUCTURE_HW1 {

    EmployeeBySalary::EmployeeBySalary(int employee_id , int employee_salary, int employee_grade, int company_ID, EmployeeBySalary* main)
            : id(employee_id), salary(employee_salary), grade(employee_grade),companyID(company_ID),points_main(main){}

    EmployeeBySalary::EmployeeBySalary(const EmployeeBySalary& other)
    : id(other.getEmployeeBySalary_ID()), salary(other.getEmployeeBySalary_SALARY()),
    grade(other.getEmployeeBySalary_GRADE()), companyID( other.getEmployeeBySalary_COMPANY()),points_main(other.getMainSalary()){}

    int EmployeeBySalary::getEmployeeBySalary_ID() const {
        return id;
    }

    int EmployeeBySalary::getEmployeeBySalary_SALARY() const {
        return salary;
    }

    int EmployeeBySalary::getEmployeeBySalary_GRADE() const {
        return grade;
    }

    int EmployeeBySalary::getEmployeeBySalary_COMPANY() const {
        return companyID;
    }


    void EmployeeBySalary::IncSALARY_EmployeeBySalary(int salary_increase) {
        salary += salary_increase;
    }

    void EmployeeBySalary::PromoteGRADE_EmployeeBySalary() {
        grade++;
    }

    void EmployeeBySalary::ChangeCOMPANY_EmployeeBySalary(int new_company_id) {

        companyID = new_company_id ;
    }

    bool EmployeeBySalary::operator<(const EmployeeBySalary &other) const
    {
        if (this->getEmployeeBySalary_SALARY() != other.getEmployeeBySalary_SALARY()) {
            return this->getEmployeeBySalary_SALARY() < other.getEmployeeBySalary_SALARY();
        }
        return this->getEmployeeBySalary_ID() > other.getEmployeeBySalary_ID();

    }

    EmployeeBySalary* EmployeeBySalary::getMainSalary() const{
        return points_main;
    }

    void EmployeeBySalary::setMainSalary(EmployeeBySalary* emp_by_salary){
        points_main=emp_by_salary;
    }
    bool operator<=(const EmployeeBySalary &employee1, const EmployeeBySalary &employee2) {
        return (!(employee1 > employee2));
    }

    bool operator>(const EmployeeBySalary &employee1, const EmployeeBySalary& employee2)
    {
        return (employee2 < employee1);
    }

    bool operator>=(const EmployeeBySalary &employee1, const EmployeeBySalary &employee2) {
        return !(employee1 < employee2);
    }

    bool operator==(const EmployeeBySalary &employee1, const EmployeeBySalary &employee2) {
        return ((employee1 <= employee2) && (employee2 <= employee1));
    }

    bool operator!=(const EmployeeBySalary &employee1, const EmployeeBySalary &employee2) {
        return !(employee1 == employee2);
    }


   /* std::ostream &operator<<(std::ostream &os, const EmployeeBySalary &employee) {
        os << "employee Id: " << employee.getEmployeeBySalary_ID() << std::endl;
        os << "employee Salary: " << employee.getEmployeeBySalary_SALARY() << std::endl;
        os << "employee Grade: " << employee.EmployeeBySalary::getEmployeeBySalary_GRADE() << std::endl;
        return os;
    }*/
}