//
// Created by Ori Zohar on 02/06/2022.
//

#ifndef HW2_DS_EMPLOYEESHASH_H
#define HW2_DS_EMPLOYEESHASH_H
#include <iostream>
#include "Employee.h"
#include "AVL.h"


namespace  DATA_STRUCTURE_HW2 {

    class Connector ;
    typedef Connector* ConnectorPtr;

    class HashEmployee : public Employee {
    private :
        ConnectorPtr connector ;
        HashEmployee* pMain;
    public :

        explicit HashEmployee(int employee_id, int employee_salary = 0,
                              int employee_grade = 0, int company_ID = 0) :
                Employee(employee_id, employee_salary, employee_grade, company_ID) , connector( nullptr ) , pMain(nullptr){}

        HashEmployee(const HashEmployee &other)
                : Employee(other.getEmployeeID(), other.getEmployeeSALARY(),
                  other.getEmployeeGRADE(),other.getEmployeeCOMPANY()),connector(other.getConnectorEmp()) {}

        ~HashEmployee(){
        pMain=nullptr;
        connector=nullptr;
    }

        ConnectorPtr getConnectorEmp() const {
            return connector ;
        }

        HashEmployee* getpMain() const {
            return pMain;
        }

        void setpMain(HashEmployee* employee)  {
            pMain = employee;
        }

        void setConnectorEmp(ConnectorPtr pConnector){
            connector=pConnector;
        }

        bool operator<(const HashEmployee &employee1) const {
            return this->getEmployeeID() < employee1.getEmployeeID();
        }

        bool operator>(const HashEmployee &employee1) const {
            return this->getEmployeeID() > employee1.getEmployeeID();
        }

        bool operator==(const HashEmployee &employee1) const {
                return this->getEmployeeID() == employee1.getEmployeeID();
            }

        bool operator!=(const HashEmployee &employee1) const {
            return this->getEmployeeID() != employee1.getEmployeeID();
        }

        bool operator<=(const HashEmployee &employee1) const {
            return this->getEmployeeID() <= employee1.getEmployeeID();
        }

        bool operator>=(const HashEmployee &employee1) const {
            return this->getEmployeeID() >= employee1.getEmployeeID();
        }
    };

    typedef AVLTree <HashEmployee> HashTree;

    class EmployeesHash {
    private:
        HashTree **arr;
        int arr_size;
        int employees_counter;

        int HashFunction(int i) const;

        static void ResetArray(HashTree **to_reset, int size);

        void Resize(HashTree **new_arr, int old_size);

    public:


        EmployeesHash();

        ~EmployeesHash();

        int getHashSize() const ;

        Employee *OutMember(int EmployeeId);

        HashEmployee *InMember(int EmployeeId);

        bool Insert(HashEmployee *employee);

        bool Delete(HashEmployee *employee);

        void MakeBigger();

        void MakeSmaller();

        void IncSalary(int EmployeeId,int Salary);

        void ChangeGrade(int EmployeeId,int Bump_Grade);

        void mergeHash(EmployeesHash& other,ConnectorPtr connector);

        void changeSize(int new_size){
            arr_size=new_size;
        }

        void MergeResize(HashTree **new_arr, int old_size,ConnectorPtr connector);
    };
}
#endif //HW2_DS_EMPLOYEESHASH_H
