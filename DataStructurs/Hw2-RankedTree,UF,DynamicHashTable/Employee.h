//
// Created by Ori Zohar on 31/05/2022.
//

#ifndef DS2_EMPLOYEE_H
#define DS2_EMPLOYEE_H
#include <iostream>
namespace  DATA_STRUCTURE_HW2 {

    class Employee {
    private :
        int id;
        int salary;
        int grade;
        int companyID;

    public:

        explicit Employee(int employee_id, int employee_salary = 0, int employee_grade = 0, int company_ID = 0);

        Employee() = default;

        ~Employee() = default;

        Employee(const Employee &other);


        int getEmployeeID() const;

        int getEmployeeSALARY() const;

        int getEmployeeGRADE() const ;

        int getEmployeeCOMPANY() const;

        void IncSALARY(int salary_increase);

        void PromoteGRADE(int bump_grade);

        bool operator<(const Employee &employee1) const;

        friend std::ostream &operator<<(std::ostream &os, const Employee &employee);

    };

    bool operator<=(const Employee &employee1, const Employee &employee2);

    bool operator>(const Employee &employee1, const Employee &employee2);

    bool operator>=(const Employee &employee1, const Employee &employee2);

    bool operator==(const Employee &employee1, const Employee &employee2);

    bool operator!=(const Employee &employee1, const Employee &employee2);
}
#endif //DS2_EMPLOYEE_H
