//
// Created by Levi on 06/06/2022.
//
#include "library2.h"
#include "EmployeeManager.h"

using namespace DATA_STRUCTURE_HW2;
void *Init(int k){
    EmployeeManager* DS = new(std::nothrow) EmployeeManager(k);
    return (void*)DS;
}
StatusType AddEmployee(void *DS, int EmployeeID, int CompanyID, int Grade){
    if (DS == NULL || EmployeeID <= 0 || CompanyID <= 0  || CompanyID > ((EmployeeManager*)DS)->getNumOfComapnies()|| Grade < 0) {
        return INVALID_INPUT;
    }
    try {
        if(((EmployeeManager*)DS)->AddEmployeeEUX(EmployeeID,CompanyID,Grade)) return SUCCESS;
        return FAILURE;
    }
    catch ( const std::bad_alloc& e ){
        return ALLOCATION_ERROR;
    }
}

StatusType RemoveEmployee(void *DS, int EmployeeID){
    if(DS==NULL || EmployeeID<=0)
    {
        return INVALID_INPUT;
    }
    if(((EmployeeManager*)DS)->RemoveEmployeeEUX(EmployeeID)) return SUCCESS;
    return FAILURE;
}

StatusType AcquireCompany(void *DS,int AcquirerID, int TargetID, double Factor){
    if (DS == nullptr || AcquirerID <= 0  || AcquirerID > ((EmployeeManager*)DS)->getNumOfComapnies()
                || TargetID <= 0  || TargetID >((EmployeeManager*)DS)->getNumOfComapnies() || AcquirerID==TargetID || Factor <= 0) {
        return INVALID_INPUT;
    }
    try {
        if(((EmployeeManager*)DS)->AcquireCompanyEUX(AcquirerID,TargetID,Factor))
        return SUCCESS;
        else return INVALID_INPUT;
    }
    catch ( const std::bad_alloc& e ){
        return ALLOCATION_ERROR;
    }

}

StatusType EmployeeSalaryIncrease(void *DS,  int EmployeeID, int SalaryIncrease){
    if(DS==NULL || EmployeeID<=0 || SalaryIncrease<=0)
    {
        return INVALID_INPUT;
    }
    if(((EmployeeManager*)DS)->employeeSalaryIncreaseEUX(EmployeeID,SalaryIncrease)) return SUCCESS;
    return FAILURE;
}

StatusType PromoteEmployee(void *DS, int employeeID, int bumpGrade){
    if(DS==NULL || employeeID<=0)
    {
        return INVALID_INPUT;
    }
    if(((EmployeeManager*)DS)->PromoteEmployeeEUX(employeeID,bumpGrade)) return SUCCESS;
    return FAILURE;
}

StatusType SumOfBumpGradeBetweenTopWorkersByGroup(void *DS, int companyID, int m){
    if (DS == nullptr || companyID < 0  || companyID > ((EmployeeManager*)DS)->getNumOfComapnies() || m<=0 ) {
        return INVALID_INPUT;
    }
    try {
        long long sum = ((EmployeeManager*)DS)->sumOfBumpGradeBetweenTopWorkersByGroupEUX(companyID,m) ;
        if(sum==-1) return FAILURE;
        else {
            printf("SumOfBumpGradeBetweenTopWorkersByGroup: %d\n",(int)sum);
            return SUCCESS;
        }
    }
    catch ( const std::bad_alloc& e ){
        return ALLOCATION_ERROR;
    }
}

StatusType AverageBumpGradeBetweenSalaryByGroup(void *DS, int companyID, int lowerSalary, int higherSalary){
    if (DS == NULL || companyID < 0  || companyID > ((EmployeeManager*)DS)->getNumOfComapnies() || lowerSalary<0 || higherSalary<0 || lowerSalary>higherSalary )
        return INVALID_INPUT;
    try {
        double average = ((EmployeeManager *) DS)->averageBumpGradeBetweenSalaryByGroupEUX(companyID, lowerSalary,
                                                                                    higherSalary);
        if(average<0) return FAILURE;

        printf("AverageBumpGradeBetweenSalaryByGroup: %.1f\n", average);
                return SUCCESS;
            }
    catch ( const std::bad_alloc& e ){
        return ALLOCATION_ERROR;
    }
}

StatusType CompanyValue(void *DS, int CompanyID){
    try {
    if (DS == nullptr || CompanyID <= 0 || CompanyID > ((EmployeeManager*)DS)->getNumOfComapnies() ) return INVALID_INPUT;
    double val =((EmployeeManager *) DS)->companyValueEUX(CompanyID);
    printf("CompanyValue: %.1f\n",val);
    return SUCCESS;
    }
    catch ( const std::bad_alloc& e ){
        return ALLOCATION_ERROR;
    }
}

void Quit(void **DS) {
    if (DS != nullptr/* && *DS!= nullptr*/) {
        delete (EmployeeManager *) (*DS);
    }
    if (DS != nullptr) {
        *DS = nullptr;
    }
}
