//
// Created by Ori Zohar on 02/06/2022.
//

#ifndef HW2_DS_COMPANIESUF_H
#define HW2_DS_COMPANIESUF_H
#include "EmployeesTree.h"
#include "EmployeesHash.h"
namespace  DATA_STRUCTURE_HW2 {

    class Company;
    class Connector;

    typedef class Connector *ConnectorPtr;
    typedef class Company *CompanyPtr;

    class Connector {
    public:
        int num;
        double mValue;
        CompanyPtr master;
        EmployeesTree* employeesTree;
        EmployeesHash employeesHash;
        Connector() : num(0),mValue(0),master(nullptr),employeesTree(nullptr),employeesHash(){
            employeesTree = new EmployeesTree;
        }
        ~Connector(){
            if(employeesTree!=nullptr) delete employeesTree;
        }
    };

    class Company {
    public :
        int CompanyId;
        double partialVal;
        CompanyPtr parent;
        ConnectorPtr connector;

        Company() = default;

        explicit Company(int CompanyId) : CompanyId(CompanyId), partialVal(CompanyId), parent(nullptr),
                                          connector(nullptr) {}
    };

    class CompaniesUF {
    private:

        CompanyPtr *companies;
        ConnectorPtr *groups;
        int size;

    public:

        explicit CompaniesUF(int Size);

        int getCompaniesNumber() const;

        double getCompanyValue(int CompanyId);

        ConnectorPtr getConnector(int CompanyId);

        bool Union(int AquirerId, int TargetId, int Factor);

        void AddAndIncreaseEmployeeGrade(int CompanyId, HashEmployee* emp);

        static void DelAndDecreaseGrade(HashEmployee* emp);

        void DelNoDecreaseGrade(HashEmployee* emp);

        static void delEmployee(HashEmployee* emp)  ;

        void addEmployee(Employee* emp,HashEmployee* hash_emp,int SalaryIncrease);

        void decGrade(HashEmployee* emp);

        void changeGrade(HashEmployee* emp,int Bump_Grade);

        long long UFtopWorkersGradesSum(int CompanyID,int m);

        double UFgradeAveragePerRange(int CompanyId,int minSalary ,int maxSalary);

        ~CompaniesUF();
    };
}
#endif //HW2_DS_COMPANIESUF_H
