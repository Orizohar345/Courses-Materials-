
#include "EmployeesContainer.h"

namespace DATA_STRUCTURE_HW1 {

    EmployeesContainer::EmployeesContainer() : num_of_employees(0), employees_by_sa(new AVLTree<EmployeeBySalary>),
                                               employees_by_id(new AVLTree<EmployeeById>),
                                               highest_paid_employee(nullptr) {}

    EmployeesContainer::~EmployeesContainer() {

        delete employees_by_sa;
        delete employees_by_id;
    }

    void updateCompany_EmployeeById(const std::shared_ptr<AVLNode<EmployeeById>> &root, int companyID) {
        if (root == nullptr) return;
        updateCompany_EmployeeById(root->left, companyID);
       if(root->data->getEmployeeByID_COMPANY()!=companyID) {
           root->data->ChangeCOMPANY_EmployeeByID(companyID);
           if (root->data->getMainId()) {
               root->data->getMainId()->ChangeCOMPANY_EmployeeByID(companyID);
           }
       }
        updateCompany_EmployeeById(root->right, companyID);
    }

    void updateCompany_EmployeeBySalary(const std::shared_ptr<AVLNode<EmployeeBySalary>> &root, int companyID) {
        if (root == nullptr) return;
        updateCompany_EmployeeBySalary(root->left, companyID);
        if(root->data->getEmployeeBySalary_COMPANY() != companyID) {
            assert(root->data->getMainSalary());
            root->data->ChangeCOMPANY_EmployeeBySalary(companyID);
            if (root->data->getMainSalary()) {
                root->data->getMainSalary()->ChangeCOMPANY_EmployeeBySalary(companyID);
            }
        }
        updateCompany_EmployeeBySalary(root->right, companyID);
    }

    void EmployeesContainer::checkAndUpdateHighestSalary(EmployeeBySalary *employee_sa) {
        if (highest_paid_employee == nullptr ||
            (employee_sa != nullptr && (*highest_paid_employee) < (*employee_sa))) {
            if (employee_sa)
                highest_paid_employee = (employee_sa);
        }
    }

    int EmployeesContainer::getNumOfEmployees() const {
        return num_of_employees;
    }

    EmployeeBySalary *EmployeesContainer::getHighestPaidEmployee() const {
        return highest_paid_employee;
    }

    void EmployeesContainer::setHighestPaidEmployee(EmployeeBySalary *employee) {
        highest_paid_employee = employee;
    }

    EmployeeById *EmployeesContainer::findById(int employee_id) {
        EmployeeById emp(employee_id);

        return employees_by_id->findAVL(&emp);
    }

    EmployeeBySalary *EmployeesContainer::findBySalary(int employee_id, int employee_salary) {
        EmployeeBySalary emp(employee_id, employee_salary);

        return employees_by_sa->findAVL(&emp);
    }

    bool EmployeesContainer::add(int employee_id, int salary, int grade, int hiringCompanyID,
                                 EmployeeById *emp_by_id, EmployeeBySalary *emp_by_salary) {
        EmployeeById* emp_id = new EmployeeById(employee_id, salary, grade, hiringCompanyID, emp_by_id);
        EmployeeBySalary* emp_sa = new EmployeeBySalary(employee_id, salary, grade, hiringCompanyID, emp_by_salary);

        if(!employees_by_id->insertAVL(emp_id))
        {
            delete emp_id;
            delete emp_sa;
            return false;
        }
        employees_by_sa->insertAVL(emp_sa);
        checkAndUpdateHighestSalary(emp_sa);
        num_of_employees++;
        return true;
    }

    bool EmployeesContainer::del(int employee_id) {
        bool replace_highest_paid = false;

        EmployeeById *to_delete_id = findById(employee_id);
        if (to_delete_id == nullptr) {
            return false;
        }

        EmployeeBySalary *to_delete_sa = findBySalary(employee_id, to_delete_id->getEmployeeByID_SALARY());
        if (to_delete_sa != nullptr && highest_paid_employee != nullptr) {
            if (*to_delete_sa == *highest_paid_employee) {
                highest_paid_employee= nullptr;
                replace_highest_paid = true;
            }
        }

        EmployeeById tempId(employee_id);
        EmployeeBySalary tempSalary(employee_id, to_delete_sa->getEmployeeBySalary_SALARY());

        employees_by_id->deleteAVL(tempId);
        employees_by_sa->deleteAVL(tempSalary);
        delete to_delete_id;
        delete to_delete_sa;
       // std::cout<<*this;

        if (replace_highest_paid) {
            setHighestPaidEmployee((employees_by_sa->getMax()));
        }
        num_of_employees--;
        return true;
    }

    void EmployeesContainer::acquireContainer(EmployeesContainer* other, int companyID) {


        EmployeeById **arr1_1 = new(std::nothrow) EmployeeById*[num_of_employees];
        if (arr1_1 == NULL) throw std::bad_alloc();
        EmployeeById** arr2_1 = new(std::nothrow) EmployeeById*[other->num_of_employees];
        if (arr2_1 == NULL) {
            delete[] arr1_1;
            throw std::bad_alloc();
        }
        EmployeeById** merged_arr_1 = new(std::nothrow) EmployeeById*[num_of_employees + other->num_of_employees];
        if (merged_arr_1 == NULL) {
            delete[] arr1_1;
            delete[] arr2_1;
            throw std::bad_alloc();
        }

        employees_by_id->mergeTrees(*(other->employees_by_id), arr1_1,arr2_1,merged_arr_1);

        for(int i=0; i<num_of_employees; i++)
        {
            arr1_1[i]= nullptr;
        }
        delete[] arr1_1;
        for(int i=0; i<other->num_of_employees; i++)
        {
            arr2_1[i]= nullptr;
        }
        delete[] arr2_1;
        for(int i=0; i<num_of_employees+other->num_of_employees; i++)
        {
            merged_arr_1[i]= nullptr;
        }
        delete[] merged_arr_1;


        EmployeeBySalary **arr1_2 = new(std::nothrow) EmployeeBySalary*[num_of_employees];
        if (arr1_2 == NULL) throw std::bad_alloc();
        EmployeeBySalary** arr2_2 = new(std::nothrow) EmployeeBySalary*[other->num_of_employees];
        if (arr2_2 == NULL) {
            delete[] arr1_2;
            throw std::bad_alloc();
        }
        EmployeeBySalary** merged_arr_2 = new(std::nothrow) EmployeeBySalary*[num_of_employees + other->num_of_employees];
        if (merged_arr_2 == NULL) {
            delete[] arr1_2;
            delete[] arr2_2;
            throw std::bad_alloc();
        }

        employees_by_sa->mergeTrees(*(other->employees_by_sa), arr1_2,arr2_2,merged_arr_2);

        for(int i=0; i<num_of_employees; i++)
        {
            arr1_2[i]= nullptr;
        }
        delete[] arr1_2;
        for(int i=0; i<other->num_of_employees; i++)
        {
            arr2_2[i]= nullptr;
        }
        delete[] arr2_2;
        for(int i=0; i<num_of_employees+other->num_of_employees; i++)
        {
            merged_arr_2[i]= nullptr;
        }
        delete[] merged_arr_2;


        highest_paid_employee = employees_by_sa->getMax();
        other->highest_paid_employee = nullptr;


        updateCompany_EmployeeById(employees_by_id->getRoot(), companyID);
        updateCompany_EmployeeBySalary(employees_by_sa->getRoot(), companyID);
        num_of_employees += other->num_of_employees;
        other->num_of_employees = 0;
    }

    bool EmployeesContainer::getAllEmployeesBySalary(int **Employees, int *NumOfEmployees) {
        if (num_of_employees == 0) {
            return false;
        }
        *NumOfEmployees = num_of_employees;
        EmployeeBySalary **employees_by_sa_array = new EmployeeBySalary*[*NumOfEmployees];
        *Employees = (int *) malloc(sizeof(int) * (*NumOfEmployees));
        employees_by_sa->reversedElemToArr(employees_by_sa_array);
        for (int i = 0; i < *NumOfEmployees; i++) {
            (*Employees)[i] = employees_by_sa_array[i]->getEmployeeBySalary_ID();
        }
        for(int i=0; i<num_of_employees; i++)
        {
            employees_by_sa_array[i]=nullptr;
        }
        delete[] employees_by_sa_array;
        return true;
    }

    bool EmployeesContainer::getNumEmployeesMatching(int minId, int maxId, int minSalary, int minGrade,
                                                     int *TotalNumOfEmployees, int *NumOfEmployees) {
        if (num_of_employees == 0) {
            return false;
        }
        EmployeeById minEmployee(minId);
        EmployeeById maxEmployee(maxId);

        EmployeeById **employees_in_range = employees_by_id->RangeElemToSortedArray(maxEmployee, minEmployee,
                                                                                    TotalNumOfEmployees);

        int employees_counter = 0;
        int num_of_employees_in_range = *TotalNumOfEmployees;
        for (int i = 0; i < num_of_employees_in_range; i++) {
            EmployeeById* curr_employee = employees_in_range[i];
            if (minSalary <= curr_employee->getEmployeeByID_SALARY() &&
                minGrade <= curr_employee->getEmployeeByID_GRADE()) {
                employees_counter++;
            }
        }
        *NumOfEmployees = employees_counter;
        for(int i=0; i<*TotalNumOfEmployees; i++)
        {
            employees_in_range[i]=nullptr;
        }
        delete[] employees_in_range;
        return true;
    }

    bool EmployeesContainer::getEmployeeInfo(int EmployeeID, int *EmployerID, int *Salary, int *Grade) {
        EmployeeById *employee = findById(EmployeeID);
        if (employee == NULL) {
            return false;
        }
        *EmployerID = employee->getEmployeeByID_COMPANY();
        *Salary = employee->getEmployeeByID_SALARY();
        *Grade = employee->getEmployeeByID_GRADE();
        return true;
    }

    bool EmployeesContainer::promoteEmployee(int EmployeeID, int SalaryIncrease, int BumpGrade) {
        EmployeeById *to_update_by_id = findById(EmployeeID);
        if (to_update_by_id == NULL) {
            return false;
        }
        EmployeeBySalary* to_update_by_sa = findBySalary(EmployeeID, to_update_by_id->getEmployeeByID_SALARY());
        if (to_update_by_sa == NULL) {
            return false;
        }
        EmployeeBySalary to_delete_by_salary(EmployeeID, to_update_by_id->getEmployeeByID_SALARY());
        employees_by_sa->deleteAVL(to_delete_by_salary);

        to_update_by_sa->IncSALARY_EmployeeBySalary(SalaryIncrease);
        to_update_by_id->IncSALARY_EmployeeByID(SalaryIncrease);
        if (BumpGrade>0) {
            to_update_by_sa->PromoteGRADE_EmployeeBySalary();
            to_update_by_id->PromoteGRADE_EmployeeByID();
        }

        employees_by_sa->insertAVL(to_update_by_sa);
        highest_paid_employee = employees_by_sa->getMax();
        return true;
    }

    void EmployeesContainer::ChangeHiringCompany(EmployeeById *employee_by_id, int companyID) {
        employee_by_id->ChangeCOMPANY_EmployeeByID(companyID);
        EmployeeBySalary *employee_by_salary = findBySalary(employee_by_id->getEmployeeByID_SALARY(),
                                                            employee_by_id->getEmployeeByID_SALARY());
        employee_by_salary->ChangeCOMPANY_EmployeeBySalary(companyID);
    }

  /*  std::ostream &operator<<(std::ostream &os, EmployeesContainer &EC) {
        std::cout << "number of employees:" << EC.getNumOfEmployees() << std::endl;

        std::cout << "employees tree by id print:" << std::endl;
        AVLNode<EmployeeById>::PrintInOrderID(EC.employees_by_id->getRoot());
        std::cout << std::endl << "employees tree by salary print:" << std::endl;
        AVLNode<EmployeeBySalary>::PrintInOrderSALARY(EC.employees_by_sa->getRoot());
        std::cout << std::endl << "highest paid employee:" << std::endl;
           if (EC.getHighestPaidEmployee() == NULL) {
            std::cout << "NULL!!" << std::endl;
            return os;
        }
        std::cout << *EC.getHighestPaidEmployee() << std::endl;

        return os;
    }*/

}