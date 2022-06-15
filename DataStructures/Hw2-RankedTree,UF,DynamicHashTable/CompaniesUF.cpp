//
// Created by Ori Zohar on 02/06/2022.
//

#include "CompaniesUF.h"
namespace  DATA_STRUCTURE_HW2 {

    CompaniesUF::CompaniesUF(int Size) : size(Size) {
        companies = new CompanyPtr[size];
        groups = new ConnectorPtr[size];
        for (int i = 0; i < size; ++i) {
            ConnectorPtr new_connector = new Connector;
            CompanyPtr new_company = new Company(i + 1);
            new_company->connector = new_connector;
            new_connector->num = 1;
            new_connector->master = new_company;
            new_connector->mValue=i+1;
            companies[i] = new_company;
            groups[i]=new_connector;
        }
    }

    CompaniesUF::~CompaniesUF() {

        for (int i = 0; i < size; i++) {
            if(groups[i]) {
                delete groups[i];
            }
            delete companies[i];
        }

        delete[] companies;
        delete[] groups;
    }

    double CompaniesUF::getCompanyValue(int CompanyId) {
        CompanyPtr company = companies[CompanyId - 1];
        CompanyPtr root = company;
        double valueSum = 0;

        //Finding the root and update the sum
        while (root->parent != nullptr) {
            valueSum += root->partialVal;
            root = root->parent;
        }
        // Changes all the parent of company's parents to root and update partialVal
        CompanyPtr temp = company;
        while (temp != root) {
            CompanyPtr parent = temp->parent;
            temp->parent = root;
            valueSum -= temp->partialVal;
            temp->partialVal += valueSum;
            temp = parent;
        }
      //  // Return the value of the required company
        if (company != root) return (company->partialVal + root->partialVal);
        else return company->partialVal;
    }

    ConnectorPtr CompaniesUF::getConnector(int CompanyId) {
        CompanyPtr company = companies[CompanyId - 1];
        CompanyPtr root = company;
        double valueSum = 0;

        //Finding the root and update the sum
        while (root->parent != nullptr) {
            valueSum += root->partialVal;
            root = root->parent;
        }
        // Changes all the parent of company's parents to root and update partialVal
        CompanyPtr temp = company;
        while (temp != root) {
            CompanyPtr parent = temp->parent;
            temp->parent = root;
            valueSum -= temp->partialVal;
            temp->partialVal += valueSum;
            temp = parent;
        }
        //  // Return the value of the required company
        return root->connector;
    }

    bool CompaniesUF::Union(int AquirerId, int TargetId, int Factor) {

        ConnectorPtr aquirer_connector = getConnector(AquirerId);
        ConnectorPtr target_connector = getConnector(TargetId);;
        if (aquirer_connector == target_connector) return false;
        CompanyPtr b_root = aquirer_connector->master;
        CompanyPtr a_root = target_connector->master;
        int aquirer_size = aquirer_connector->num;
        int target_size = target_connector->num;
        double a_value = target_connector->mValue;
        if(a_root==b_root) return false ;


            Employee **aquirer_arr = new Employee *[aquirer_connector->employeesTree->EmpGetNumOfElements()];
            Employee **target_arr = new Employee *[target_connector->employeesTree->EmpGetNumOfElements()];
            Employee **merged_arr = new Employee *[target_connector->employeesTree->EmpGetNumOfElements() +
                                                   aquirer_connector->employeesTree->EmpGetNumOfElements()];

            aquirer_connector->employeesTree->EmpMergeTrees(*target_connector->employeesTree, aquirer_arr, target_arr,
                                                            merged_arr);


        delete[] aquirer_arr;
        delete[] target_arr;
        delete[] merged_arr;


            aquirer_connector->employeesHash.mergeHash(target_connector->employeesHash,aquirer_connector);
            aquirer_connector->mValue+= Factor*target_connector->mValue;

        if (target_size >= aquirer_size) {

            b_root->parent = a_root;
            b_root->connector = nullptr;
            b_root->partialVal = b_root->partialVal + (-1) * (a_root->partialVal) + (Factor)*a_value;
            aquirer_connector->num = aquirer_size + target_size;
            aquirer_connector->master = a_root;
            a_root->connector = aquirer_connector;
            a_root->parent=nullptr;
            //groups[TargetId - 1] = aquirer_connector;
            //groups[AquirerId - 1] = aquirer_connector;


        } else {

            a_root->parent = b_root;
            a_root->connector = nullptr;
            b_root->parent=nullptr;

            b_root->partialVal+= (Factor) * (a_value);
            a_root->partialVal -= b_root->partialVal;

            aquirer_connector->num = aquirer_size + target_size;
           // groups[TargetId - 1] = aquirer_connector;
           // groups[AquirerId - 1] = aquirer_connector;
        }
        return true ;
    }

    void CompaniesUF::AddAndIncreaseEmployeeGrade(int CompanyId, HashEmployee* emp){

        ConnectorPtr connector = getConnector(CompanyId);
        emp->getpMain()->setConnectorEmp(connector);
        connector->employeesTree->IncreaseNumOfFreeWorkers();
        int grade = emp->getEmployeeGRADE();
        connector->employeesTree->IncreaseGradeOfFreeWorkers(grade);
        connector->employeesHash.Insert(emp);
    }

    void CompaniesUF::DelAndDecreaseGrade(HashEmployee* emp) {
        ConnectorPtr connector = emp->getConnectorEmp();
        HashEmployee* hash_emp = connector->employeesHash.InMember(emp->getEmployeeID());
        connector->employeesTree->DecreaseNumOfFreeWorkers();
        connector->employeesTree->DecreaseGradeOfFreeWorkers(emp->getEmployeeGRADE());
        connector->employeesHash.Delete(hash_emp);
    }

    void CompaniesUF::DelNoDecreaseGrade(HashEmployee* emp) {
        ConnectorPtr connector = emp->getConnectorEmp();
        HashEmployee* hash_emp = connector->employeesHash.InMember(emp->getEmployeeID());
        Employee* to_delete = connector->employeesTree->EmpFindAVL(emp);
        connector->employeesTree->EmpDeleteAVL(*emp);
        connector->employeesHash.Delete(hash_emp);
        delete to_delete;
    }

    void CompaniesUF::addEmployee(Employee* emp,HashEmployee* hash_emp,int SalaryIncrease)
    {
        ConnectorPtr connector = hash_emp->getConnectorEmp();
        connector->employeesTree->EmpInsertAVL(emp);
        connector->employeesHash.IncSalary(emp->getEmployeeID(),SalaryIncrease);
    }

    void CompaniesUF::delEmployee(HashEmployee* emp){
        ConnectorPtr connector = emp->getConnectorEmp();
        Employee* to_delete = connector->employeesTree->EmpFindAVL(emp);

        connector->employeesTree->EmpDeleteAVL(*emp);
        delete to_delete;
         }

    void CompaniesUF::decGrade(HashEmployee* emp){
        ConnectorPtr connector = emp->getConnectorEmp();
        connector->employeesTree->DecreaseGradeOfFreeWorkers(emp->getEmployeeGRADE());
        connector->employeesTree->DecreaseNumOfFreeWorkers();
    }

    int CompaniesUF::getCompaniesNumber() const{
        return size;
    }

    void CompaniesUF::changeGrade(HashEmployee* emp,int Bump_Grade) {
        ConnectorPtr connector = emp->getConnectorEmp();

        if (emp->getEmployeeSALARY() == 0) {
            connector->employeesTree->IncreaseGradeOfFreeWorkers(Bump_Grade);

        } else if (emp->getEmployeeSALARY() > 0) {
            Employee *found = connector->employeesTree->EmpFindAVL(emp);
            found->PromoteGRADE(Bump_Grade);
            connector->employeesTree->EmpDeleteAVL(*emp);
            connector->employeesTree->EmpInsertAVL(found);
        }

    }

    long long CompaniesUF::UFtopWorkersGradesSum(int CompanyID,int m){
        ConnectorPtr connector = getConnector(CompanyID);
        if(connector->employeesTree->EmpGetNumOfElements() < m) return -1;
        return connector->employeesTree->topWorkersGradeSum(m);
    }

    double CompaniesUF::UFgradeAveragePerRange(int CompanyId,int minSalary ,int maxSalary){
        ConnectorPtr connector = getConnector(CompanyId);
        return connector->employeesTree->gradeAveragePerRange(minSalary, maxSalary);
    }

}
