
#ifndef COMPANY_CPP_EMPLOYEEBYSALARY_H
#define COMPANY_CPP_EMPLOYEEBYSALARY_H

#include <memory>
#include "EmployeeById.h"


    namespace DATA_STRUCTURE_HW1 {

        class Company;

        class EmployeeBySalary {

        private :
            int id=0;
            int salary=0;
            int grade=0;
            int companyID=0;
            EmployeeBySalary* points_main ;

        public:

            explicit EmployeeBySalary(int employee_id , int employee_salary = 0, int employee_grade = 0, int company_ID = 0, EmployeeBySalary* main=NULL);
            EmployeeBySalary() = default ;
            ~EmployeeBySalary() =default ;

            EmployeeBySalary(const EmployeeBySalary& other) ;


            int getEmployeeBySalary_ID() const;

            int getEmployeeBySalary_SALARY() const;

            int getEmployeeBySalary_GRADE() const;

            int getEmployeeBySalary_COMPANY() const;

            void IncSALARY_EmployeeBySalary(int salary_increase);

            void PromoteGRADE_EmployeeBySalary();

            void ChangeCOMPANY_EmployeeBySalary(int new_company_id);

            EmployeeBySalary* getMainSalary() const;

            void setMainSalary(EmployeeBySalary* emp_by_salary);



            bool operator<(const EmployeeBySalary &employee1) const;

           // friend std::ostream &operator<<(std::ostream &os, const EmployeeBySalary &employee);

        };

        bool operator<=(const EmployeeBySalary &employee1, const EmployeeBySalary &employee2);

        bool operator>(const EmployeeBySalary &employee1, const EmployeeBySalary &employee2);

        bool operator>=(const EmployeeBySalary &employee1, const EmployeeBySalary &employee2);

        bool operator==(const EmployeeBySalary &employee1, const EmployeeBySalary &employee2);

        bool operator!=(const EmployeeBySalary &employee1, const EmployeeBySalary &employee2);

    }
#endif //COMPANY_CPP_EMPLOYEEBYSALARY_H
