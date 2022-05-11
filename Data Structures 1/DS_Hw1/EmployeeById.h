
#ifndef COMPANY_CPP_EMPLOYEE_H
#define COMPANY_CPP_EMPLOYEE_H
#include <iostream>
#include <memory>

namespace DATA_STRUCTURE_HW1 {

    class Company;

        class EmployeeById  {

        private :
        int id=0;
        int salary=0;
        int grade=0;
        int companyID=0;
        EmployeeById* points_main;

        public:

           explicit EmployeeById(int employee_id , int employee_salary = 0, int employee_grade = 0, int company_id = 0,EmployeeById* main=nullptr);

           EmployeeById() = default ;

           ~EmployeeById() =default ;

            EmployeeById(const EmployeeById& other) ;


            EmployeeById& operator=(const EmployeeById &employee) = default;

            int getEmployeeByID_ID() const;

            int getEmployeeByID_SALARY() const;

             int getEmployeeByID_GRADE() const;

            int getEmployeeByID_COMPANY() const;

            void IncSALARY_EmployeeByID(int salary_increase);

            void PromoteGRADE_EmployeeByID();

            void ChangeCOMPANY_EmployeeByID(int new_company_id);

            EmployeeById* getMainId() const;

            void setMainId(EmployeeById* emp_by_Id) ;

            bool operator<(const EmployeeById &employee1) const;

      //  friend std::ostream &operator<<(std::ostream &os, const EmployeeById &employee);

    };

    bool operator<=(const EmployeeById &employee1, const EmployeeById &employee2);

    bool operator>(const EmployeeById &employee1, const EmployeeById &employee2);

    bool operator>=(const EmployeeById &employee1, const EmployeeById &employee2);

    bool operator==(const EmployeeById &employee1, const EmployeeById &employee2);

    bool operator!=(const EmployeeById &employee1, const EmployeeById &employee2);

}

#endif //COMPANY_CPP_EMPLOYEE_H