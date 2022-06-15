//
// Created by Ori Zohar on 31/05/2022.
//



#include "Employee.h"
#define INF -1
namespace  DATA_STRUCTURE_HW2 {
    Employee::Employee(int employee_id, int employee_salary, int employee_grade, int company_ID)
            : id(employee_id), salary(employee_salary), grade(employee_grade), companyID(company_ID) {}

    Employee::Employee(const Employee &other)
            : id(other.getEmployeeID()), salary(other.getEmployeeSALARY()),
              grade(other.getEmployeeGRADE()), companyID(other.getEmployeeCOMPANY()) {}

    int Employee::getEmployeeID() const {
        return id;
    }

    int Employee::getEmployeeSALARY() const {
        return salary;
    }

    int Employee::getEmployeeGRADE() const {
        return grade;
    }

    int Employee::getEmployeeCOMPANY() const {
        return companyID;
    }

    void Employee::IncSALARY(int salary_increase) {
        salary += salary_increase;
    }

    void Employee::PromoteGRADE(int bump_grade) {
        grade+=bump_grade;
    }

    bool Employee::operator<(const Employee &other) const {
        if (this->getEmployeeSALARY() != other.getEmployeeSALARY()) {
            return this->getEmployeeSALARY() < other.getEmployeeSALARY();
        }

        if (this->getEmployeeID() == INF) {
            return false;
        } else if (other.getEmployeeID() == INF) {
            return true;
        }
        return this->getEmployeeID() < other.getEmployeeID();

    }

    bool operator<=(const Employee &employee1, const Employee &employee2) {
        return (!(employee1 > employee2));
    }

    bool operator>(const Employee &employee1, const Employee &employee2) {
        return (employee2 < employee1);
    }

    bool operator>=(const Employee &employee1, const Employee &employee2) {
        return !(employee1 < employee2);
    }

    bool operator==(const Employee &employee1, const Employee &employee2) {
        return ((employee1 <= employee2) && (employee2 <= employee1));
    }

    bool operator!=(const Employee &employee1, const Employee &employee2) {
        return !(employee1 == employee2);
    }

    std::ostream &operator<<(std::ostream &os, const Employee &employee) {
        os << " " << employee.getEmployeeID();
        return os;
    }
}