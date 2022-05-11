
#include "EmployeeById.h"

namespace DATA_STRUCTURE_HW1 {

    EmployeeById::EmployeeById(int employee_id , int employee_salary, int employee_grade, int company_id,EmployeeById* main)
            : id(employee_id), salary(employee_salary), grade(employee_grade),companyID(company_id) , points_main(main){};

    EmployeeById::EmployeeById(const EmployeeById& other) : id(other.getEmployeeByID_ID()), salary(
            other.getEmployeeByID_SALARY()), grade(other.getEmployeeByID_GRADE()),
            companyID(other.getEmployeeByID_COMPANY()) ,points_main(other.getMainId()) {}

    int EmployeeById::getEmployeeByID_ID() const {
        return id;
    }

    int EmployeeById::getEmployeeByID_SALARY() const {
        return salary;
    }

    int EmployeeById::getEmployeeByID_GRADE() const {
        return grade;
    }

    int EmployeeById::getEmployeeByID_COMPANY() const {
        return companyID;
    }


    void EmployeeById::IncSALARY_EmployeeByID(int salary_increase) {
        salary += salary_increase;
    }

    void EmployeeById::PromoteGRADE_EmployeeByID() {
        grade++;
    }

    void EmployeeById::ChangeCOMPANY_EmployeeByID(int new_company_id) {

        companyID = new_company_id ;
    }

    EmployeeById* EmployeeById::getMainId() const{
        return points_main;
    }

    void EmployeeById::setMainId(EmployeeById* emp_by_Id){
        points_main=emp_by_Id;
    }

    bool EmployeeById::operator<(const EmployeeById &other) const {
       return this->getEmployeeByID_ID() < other.getEmployeeByID_ID();;
    }

    bool operator<=(const EmployeeById &employee1, const EmployeeById &employee2) {
        return (!(employee1 > employee2));
    }

    bool operator>(const EmployeeById &employee1, const EmployeeById& employee2)
    {
        return (employee2 < employee1);
    }

    bool operator>=(const EmployeeById &employee1, const EmployeeById &employee2) {
        return !(employee1 < employee2);
    }

    bool operator==(const EmployeeById &employee1, const EmployeeById &employee2) {
        return ((employee1 <= employee2) && (employee2 <= employee1));
    }

    bool operator!=(const EmployeeById &employee1, const EmployeeById &employee2) {
        return !(employee1 == employee2);
    }

  /*  std::ostream &operator<<(std::ostream &os, const EmployeeById &employee) {
        os << "employee Id: " << employee.getEmployeeByID_ID() << std::endl;
        os << "employee Salary: " << employee.getEmployeeByID_SALARY() << std::endl;
        os << "employee Grade: " << employee.getEmployeeByID_GRADE() << std::endl;
        return os;
    }*/
}