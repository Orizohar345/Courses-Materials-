//
// Created by Ori Zohar on 02/06/2022.
//

#include "EmployeesHash.h"
namespace  DATA_STRUCTURE_HW2 {

    EmployeesHash::EmployeesHash() : arr_size(4) ,employees_counter(0) {
        arr = new HashTree *[4];
        ResetArray(arr, 4);
    }

    int EmployeesHash::HashFunction(int i) const {
        return (i % this->arr_size);
    }

    void EmployeesHash::ResetArray(HashTree **to_reset, int size) {
        for (int i = 0; i < size; i++) {
            to_reset[i] = nullptr;
        }
    }

    int EmployeesHash::getHashSize() const {
        return this->arr_size;
    }

    void EmployeesHash::Resize(HashTree **new_arr, int old_size) {
        for (int i = 0; i < old_size; i++) {
            // Hash only if there is tree in the current index
            if (arr[i] != nullptr) {
                // save the HashEmployees in the current tree into array
                int number_of_employees = arr[i]->getNumOfElements();
                HashEmployee **emp_array = new HashEmployee *[number_of_employees];

                // use AVLTree function to put them into array
                arr[i]->ElemToArr(emp_array);

                //iterate over the array to get each employee
                for (int j = 0; j < number_of_employees; j++) {
                    int index = HashFunction(emp_array[j]->getEmployeeID());
                    // there is no tree in the current index so lets make a new one .
                    if (new_arr[index] == nullptr) {
                        new_arr[index] = new HashTree;
                    }
                    // inserting the current employee.
                    new_arr[index]->insertAVL(emp_array[j]);
                    // delete him for the old tree (to avoid delete his pointer when delete the old tree) .
                    arr[i]->deleteAVL(*emp_array[j]);
                    emp_array[j] = nullptr;
                }
                // delete the old tree and the emp_array
                delete arr[i];
                delete[] emp_array;
            }
        }
        // delete the old array and set the new arr .
        delete[] arr;
        arr = new_arr;
    }

    Employee *EmployeesHash::OutMember(int EmployeeId) {
        // Get the index of the employee from hash func
        int index = HashFunction(EmployeeId);
        // if the employee is not in the HashTable and for the index there is not pointer to tree .
        if (this->arr[index] == nullptr) {
            return nullptr;
        }
        // if there is three for the Hashing index
        HashTree *employees_tree = this->arr[index];
        // Make dummy employee for searching .
        HashEmployee *dummy = new HashEmployee(EmployeeId, 0, 0, 0);

        // EmpFindAUX if the employee in the tree
        HashEmployee *found = employees_tree->findAVL(dummy);

        // delete the dummy for no memory lost
        delete dummy;

        // if not found return null ptr
        if (found == nullptr) return nullptr;

        // make new ptr for employee to return from the func
        Employee *return_employee = new Employee(found->getEmployeeID(), found->getEmployeeSALARY(),
                                                 found->getEmployeeGRADE(), found->getEmployeeCOMPANY());
        return return_employee;
    }

    HashEmployee *EmployeesHash::InMember(int EmployeeId) {
        // Get the index of the employee from hash func
        int index = HashFunction(EmployeeId);
        // if the employee is not in the HashTable and for the index there is not pointer to tree .
        if (this->arr[index] == nullptr) {
            return nullptr;
        }
        // if there is three for the Hashing index
        HashTree *employees_tree = this->arr[index];
        // Make dummy employee for searching .
        HashEmployee *dummy = new HashEmployee(EmployeeId, 0, 0, 0);

        // EmpFindAUX if the employee in the tree
        HashEmployee *found = employees_tree->findAVL(dummy);

        // delete the dummy for no memory lost
        delete dummy;

        // if not found return null ptr
        if (found == nullptr) return nullptr;

        // make new ptr for employee to return from the func

        return found;
    }

    bool EmployeesHash::Insert(HashEmployee *employee) {

        int index = HashFunction(employee->getEmployeeID());
       // HashEmployee *dummy = new HashEmployee(employee->getEmployeeID(), employee->getEmployeeSALARY(),
                                           //    employee->getEmployeeGRADE(), employee->getEmployeeCOMPANY());
        /* Check if employee is already in the Hash */

        // case 1 : there is tree in the hashing index
        if (arr[index] != nullptr) {
            HashEmployee *found = arr[index]->findAVL(employee);
            if (found != nullptr) {
                return false;
            }
        }
            // case2 : there is not Tree for hashing index -> we need to insert him but make a three .
        else {
            this->arr[index] = new HashTree;
        }
        // if we are here we are going to insert him for the tree

        arr[index]->insertAVL(employee);
        employees_counter++;

        // delete the Employee* ptr because the user don't know we transfer it to HashEmployee*

        // if Array is full make it bigger .
        if (employees_counter == arr_size)
            MakeBigger();
        return true;
    }

    void EmployeesHash::MakeBigger() {

        //Make new tree array by factor 2 than the one exist and reset it.
        HashTree **new_arr = new HashTree *[2 * arr_size];

        ResetArray(new_arr, 2 * arr_size);

        // change the size for using Hash function
        arr_size = arr_size * 2;

        /* Hashing the old employeesTree from the old arr to the new one */

        // Resize the old array
        Resize(new_arr, arr_size / 2);
    }

    bool EmployeesHash::Delete(HashEmployee* emp) {

        int index = HashFunction(emp->getEmployeeID());
        //  no tree for the index - no employee to delete ;
        if (arr[index] == nullptr) return false;

        /* there is tree for the index */
        // make dummy for search

        HashEmployee *found = arr[index]->findAVL(emp);

        // if not found - there is no employee to delete .
        if (found == nullptr) {
            delete emp;
            return false;
        }

        /* now we have employee to delete */
        arr[index]->deleteAVL(*found);
        // if tree is empty ;
        if (arr[index]->getNumOfElements() == 0) {
            delete arr[index];
            arr[index] = nullptr;
        }
        employees_counter--;
        /* check if he have to make the arr smaller */
        if (employees_counter == 0.25 * arr_size) MakeSmaller();
        delete emp;
        return true;
    }

    void EmployeesHash::MakeSmaller() {

        //Make new tree array by factor 2 than the one exist and reset it.
        HashTree **new_arr = new HashTree *[arr_size / 2];
        ResetArray(new_arr, arr_size / 2);

        // change the size for using Hash function
        arr_size = arr_size / 2;

        /* Hashing the old employeesTree from the old arr to the new one */

        // Resize old array
        Resize(new_arr, arr_size * 2);
    }

    void EmployeesHash::IncSalary(int EmployeeId,int Salary){
        HashEmployee* to_inc = InMember(EmployeeId);
        to_inc->IncSALARY(Salary);
    }

    void EmployeesHash::ChangeGrade(int EmployeeId,int Bump_Grade){
        HashEmployee* member = InMember(EmployeeId);
        member->PromoteGRADE(Bump_Grade);
        }

    void EmployeesHash::MergeResize(HashTree **new_arr, int old_size, ConnectorPtr connector) {
        for (int i = 0; i < old_size; i++) {
            // Hash only if there is tree in the current index
            if (arr[i] != nullptr) {
                // save the HashEmployees in the current tree into array
                int number_of_employees = arr[i]->getNumOfElements();
                HashEmployee **emp_array = new HashEmployee *[number_of_employees];

                // use AVLTree function to put them into array
                arr[i]->ElemToArr(emp_array);

                //iterate over the array to get each employee
                for (int j = 0; j < number_of_employees; j++) {
                    int index = HashFunction(emp_array[j]->getEmployeeID());
                    // there is no tree in the current index so lets make a new one .
                    if (new_arr[index] == nullptr) {
                        new_arr[index] = new HashTree;
                    }
                    // inserting the current employee.
                    HashEmployee* empMain = emp_array[j]->getpMain();
                    emp_array[j]->setConnectorEmp(connector);
                    empMain->setConnectorEmp(connector);
                    new_arr[index]->insertAVL(emp_array[j]);

                    // delete him for the old tree (to avoid delete his pointer when delete the old tree) .
                    arr[i]->deleteAVL(*emp_array[j]);

                    emp_array[j] = nullptr;
                }
                //delete the old tree and the emp_array
                delete arr[i];
                delete[] emp_array;
            }
        }
        // delete the old array and set the new arr .
        delete[] arr;
        arr = new_arr;
    }

    void EmployeesHash::mergeHash(EmployeesHash& other,ConnectorPtr connector) {
        int this_old_size = getHashSize();
        int other_old_size=other.getHashSize();
        HashTree** merged_arr = new HashTree*[getHashSize()+other.getHashSize()];
        HashTree** merged_arr2 = new HashTree*[getHashSize()+other.getHashSize()];
        ResetArray(merged_arr,getHashSize()+other.getHashSize());
        ResetArray(merged_arr2,getHashSize()+other.getHashSize());
        changeSize(getHashSize()+other.getHashSize());
        other.changeSize(this_old_size+other_old_size);
        other.MergeResize(merged_arr,other_old_size,connector);
        MergeResize(merged_arr2,this_old_size,connector);
        MergeResize(merged_arr,this_old_size+other_old_size,connector);
        other.arr=nullptr;
    }

    EmployeesHash::~EmployeesHash() {
        if(arr!=nullptr) {
            for (int i = 0; i < arr_size; i++) {
                if(arr[i]!=nullptr) delete arr[i];
                arr[i] = nullptr;
            }
            delete[] arr;
        }
    }

}