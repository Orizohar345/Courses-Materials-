//
// Created by Ori Zohar on 31/05/2022.
//
#include "EmployeesTree.h"
#define INF -1
namespace DATA_STRUCTURE_HW2 {

    void EmployeesTree::EmpRotate(shared_ptr<EmployeeNode> &sub_root_son) {
        int BF = sub_root_son->parent->EmpBalanceFactor();
        if (BF == 2) {
            if (sub_root_son->parent->left->EmpBalanceFactor() >= 0) {
                if (sub_root_son->parent == root) {
                    sub_root_son=sub_root_son->parent->left;
                    sub_root_son->parent->EmpRotateLL();
                    root = sub_root_son;
                } else {
                    sub_root_son->parent->EmpRotateLL();
                }
            } else if (sub_root_son->parent->left->EmpBalanceFactor() == -1) {
                if (sub_root_son->parent == root) {
                    sub_root_son = sub_root_son->parent->left ->right;
                    sub_root_son->parent->parent->EmpRotateLR();
                    root = sub_root_son;
                } else {
                    sub_root_son->parent->EmpRotateLR();
                }
            }
        } else if (BF == -2) {
            if (sub_root_son->parent->right->EmpBalanceFactor() <= 0) {
                if (sub_root_son->parent == root) {
                    sub_root_son=sub_root_son->parent->right;
                    sub_root_son->parent->EmpRotateRR();
                    root = sub_root_son;
                } else {
                    sub_root_son->parent->EmpRotateRR();
                }
            } else if (sub_root_son->parent->right->EmpBalanceFactor() == 1) {
                if (sub_root_son->parent == root) {
                    sub_root_son=sub_root_son->parent->right->left;
                    sub_root_son->parent->parent->EmpRotateRL();
                    root = sub_root_son;
                } else {
                    sub_root_son->parent->EmpRotateRL();
                }
            }
        }
    }

    void EmployeesTree::EmpSwap(shared_ptr<EmployeeNode> &node1, shared_ptr<EmployeeNode> &node2) {
        if (node1 == node2) {
            return;
        }
        shared_ptr<EmployeeNode> parent_1 = node1->parent;
        shared_ptr<EmployeeNode> left_son_1 = node1->left;
        shared_ptr<EmployeeNode> right_son_1 = node1->right;

        shared_ptr<EmployeeNode> parent_2 = node2->parent;
        shared_ptr<EmployeeNode> left_son_2 = node2->left;
        shared_ptr<EmployeeNode> right_son_2 = node2->right;

        /* Joint Nodes Casees */
        if (node1->right == node2 || node1->left == node2) {
            node1->right = node2->right;
            node1->left = node2->left;
            node1->parent = node2;
            if (right_son_1 == node2) {
                node2->right = node1;
                node2->parent = parent_1;
                node2->left = left_son_1;
            } else if (left_son_1 == node2) {
                node2->left = node1;
                node2->parent = parent_1;
                node2->right = right_son_1;
            }
            if (node2->left != NULL) node2->left->parent = node2;
            if (node2->parent != NULL && node2->parent->right == node1) node2->parent->right = node2;
            if (node2->parent != NULL && node2->parent->left == node1) node2->parent->left = node2;
            if (node1->left != NULL) node1->left->parent = node1;
            if (node1->right != NULL) node1->right->parent = node1;
        }

            /* Not Joint Case */
        else {
            node1->parent = node2->parent;
            if (node1->parent != NULL && node1->parent->left == node2) node1->parent->left = node1;
            if (node1->parent != NULL && node1->parent->right == node2) node1->parent->right = node1;
            node1->left = node2->left;
            if (node1->left != NULL) {
                node1->left->parent = node1;
            }
            node1->right = node2->right;
            if (node1->right != NULL) {
                node1->right->parent = node1;
            }
            /*put node2 where node1 was */
            node2->parent = parent_1;
            if (node2->parent != NULL && node2->parent->right == node1) node2->parent->right = node2;
            if (node2->parent != NULL && node2->parent->left == node1) node2->parent->left = node2;
            node2->left = left_son_1;
            if (node2->left != NULL) {
                node2->left->parent = node2;
            }
            node2->right = right_son_1;
            if (node2->right != NULL) {
                node2->right->parent = node2;
            }
        }

        node1->EmpUpdateHeight();
        node2->EmpUpdateHeight();
        if (node1 == root) {
            root = node2;
        }
    }

    void EmployeesTree::EmpDestroyAndBreakCycleForEver(shared_ptr<EmployeeNode> &node) {
        if (node == NULL) return;
        EmpDestroyAndBreakCycleForEver(node->left);
        EmpDestroyAndBreakCycleForEver(node->right);
        node->parent = NULL;
        delete node->data;
        node->data=NULL;
        node.reset();
        node= nullptr;
    }

    void EmployeesTree::EmpDestroyAndBreakCycle(shared_ptr<EmployeeNode> &node) {
        if (node == NULL) return;
        EmpDestroyAndBreakCycle(node->left);
        EmpDestroyAndBreakCycle(node->right);
        node->data=nullptr;
        node->parent = nullptr;
        node.reset();
        node= nullptr;
    }

    bool EmployeesTree::EmpInsertAUX(Employee* value) {

        if (EmpFindAUX(value) != NULL) {
            return false;
        }

        shared_ptr<EmployeeNode> inserted(new(std::nothrow) EmployeeNode(value));
        if (inserted == nullptr) throw std::bad_alloc();
        if (root == nullptr) {
            root=inserted;
            root->size=1;
            root->grades=root->data->getEmployeeGRADE();
            inserted=nullptr;
            return true;
        }
        shared_ptr<EmployeeNode> temp(root);
        while (true) {
            (temp->size)++; /**change**/
            (temp->grades)+=inserted->data->getEmployeeGRADE(); /**change**/
            if (*(temp->data) > *(inserted->data)) {
                if (temp->left == NULL) {
                    temp->left = inserted;
                    inserted->parent = temp;
                    break;
                } else temp = temp->left;
            } else {
                if (temp->right == NULL) {
                    temp->right = inserted;
                    inserted->parent = temp;
                    break;
                } else temp = temp->right;
            }
        }
        inserted->height = 0;
        while (temp) {
            temp->EmpUpdateHeight();
            temp = temp->parent;
        }

        while (inserted != root) {
            int BF = inserted->parent->EmpBalanceFactor();
            if (BF == 2 || BF == -2) {
                EmpRotate(inserted);
                break;
            }
            inserted = inserted->parent;
        }
        return true;
    }

    bool EmployeesTree::EmpDeleteAUX(Employee* value) {
        shared_ptr<EmployeeNode> to_delete = EmpFindAUX(value);
        shared_ptr<EmployeeNode> it;
        if (to_delete == NULL) {
            return false;
        }
        UpdateSizeAndRightGradeForDelete(value, to_delete->data->getEmployeeGRADE());
        //int to_delete_grade = to_delete->data->getEmployeeGRADE(); /*change*/
        to_delete->data = nullptr;
        if (to_delete->EmpNumOfSons() == 2) {
            shared_ptr<EmployeeNode> to_swap = to_delete;

            to_swap = to_swap->right;
            while (to_swap->left != NULL)
            {
                to_swap = to_swap->left;
            }
            EmpSwap(to_delete, to_swap);
        }
        if (to_delete->EmpNumOfSons() == 0) {
            if (to_delete == root) {
                to_delete.reset();
                root = NULL;
                return true;
            } else {
                if (to_delete->parent->left == to_delete) to_delete->parent->left = nullptr;
                else if (to_delete->parent->right == to_delete) to_delete->parent->right = nullptr;
                it = to_delete->parent;
                to_delete->parent = nullptr;
            }
        } else if (to_delete->EmpNumOfSons() == 1) {
            if (to_delete == root) {
                if (to_delete->right) {
                    root = to_delete->right;
                    to_delete->right = nullptr;

                } else if (to_delete->left) {
                    root = to_delete->left;
                    to_delete->left = nullptr;
                }
                root->parent = nullptr;
                to_delete.reset();
                return true;
            } else {
                if (to_delete->parent->left == to_delete) {
                    if (to_delete->left) {
                        to_delete->parent->left = to_delete->left;
                        to_delete->left->parent = to_delete->parent;
                        it = to_delete->left;
                        to_delete->parent=nullptr;
                        to_delete->left=nullptr;
                    } else if (to_delete->right) {
                        to_delete->parent->left = to_delete->right;
                        to_delete->right->parent = to_delete->parent;
                        it = to_delete->right;
                        to_delete->parent=nullptr;
                        to_delete->right=nullptr;
                    }
                } else {
                    if (to_delete->left) {
                        to_delete->parent->right = to_delete->left;
                        to_delete->left->parent = to_delete->parent;
                        it = to_delete->left;
                        to_delete->left=nullptr;
                        to_delete->parent=nullptr;
                    } else if (to_delete->right) {
                        to_delete->parent->right = to_delete->right;
                        to_delete->right->parent = to_delete->parent;
                        it = to_delete->right;
                        to_delete->right=nullptr;
                        to_delete->parent=nullptr;
                    }
                }
            }
        }
        to_delete.reset();
        shared_ptr<EmployeeNode> to_update = it;
        while (to_update) {
           to_update->updateSizeAndGrades(); /*change*/
            to_update->EmpUpdateHeight();
            to_update = to_update->parent;
        }
        if (it->parent == NULL && it->left) it = it->left;
        if (it->parent == NULL && it->right) it = it->right;
        while (true) {
            if (it == NULL || it->parent == NULL) break;
            int BF = it->parent->EmpBalanceFactor();
            if (BF == 2 || BF == -2) {
                EmpRotate(it);
            }
            it = it->parent;
        }
        return true;
    }

    shared_ptr<EmployeeNode> EmployeesTree::EmpFindAUX(const Employee* value) const
    {
        if(this->root==nullptr) return nullptr;
        shared_ptr<EmployeeNode> iterator(this->root);
        while (iterator != NULL) {
            if (*(iterator->data) == *value) break;
            else if (*(iterator->data) > *value) {
                iterator = iterator->left;
            }
            else if (*(iterator->data) < *value) {
                iterator = iterator->right;
            }
        }
        return iterator;
    }

    int EmployeesTree::calcNumOfSmallerElements(const Employee* value) const {
        int index=0;
        shared_ptr<EmployeeNode> iterator(this->root);
        while (iterator != nullptr) {
            if(*(iterator->data) == *value)
            {
                int left_size = 0;
                if(iterator->left!=nullptr)
                {
                    left_size += iterator->left->size;
                }
                index += left_size;
                break;
            }
            if (*(iterator->data) > *value) {
                iterator = iterator->left;
            }
            else if (*(iterator->data) < *value) {
                int left_size = 1;
                if(iterator->left!=nullptr)
                {
                    left_size+= iterator->left->size;
                }
                index += left_size;
                iterator = iterator->right;
            }
        }
        return index;
    }

    /** the update doesn't include the value node**/
    void EmployeesTree::UpdateSizeAndRightGradeForDelete(const Employee* value,int grade) const {
        shared_ptr<EmployeeNode> iterator(this->root);
        while (iterator != NULL) {
            if (*(iterator->data) == *value) break;
            (iterator->size)--;
            iterator->grades-=grade;
            if (*(iterator->data) > *value) {
                iterator = iterator->left;
            }
            else if (*(iterator->data) < *value) {
                iterator = iterator->right;
            }
        }
    }

    void EmployeesTree::EmpMergeSort(Employee **merged_arr, Employee **arr1, Employee **arr2, int n, int m) {
        int i = 0, j = 0, k = 0;
        while (i < n && j < m) {
            if (*arr1[i] < *arr2[j]) {
                merged_arr[k] = arr1[i];
                arr1[i]= nullptr;
                i++;
            } else {
                merged_arr[k] = arr2[j];
                arr2[j]= nullptr;
                j++;
            }
            k++;
        }
        while (i < n) {
            merged_arr[k] = arr1[i];
            arr1[i]= nullptr;
            i++;
            k++;
        }

        // If there are more elements in second array
        while (j < m) {
            merged_arr[k] = arr2[j];
            arr2[j]= nullptr;
            j++;
            k++;
        }

    }

    long long EmployeesTree::topWorkersGradeSum(int m)
    {
        return topWorkersGradeSumEUX(root, m);
    }

    long long EmployeesTree::topWorkersGradeSumEUX(shared_ptr<EmployeeNode> root, int m)
    {
        if(root == nullptr || m==0)
        {
            return 0;
        }
        if(root->size<=m)
        {
            return root->grades;
        }
        int right_size = 1;
        long long right_grades = (long long)root->data->getEmployeeGRADE();
        if(root->right!=NULL)
        {
            right_size += root->right->size;
            right_grades += root->right->grades;
        }

        if(right_size<=m)
        {
            return right_grades + topWorkersGradeSumEUX(root->left, m-(right_size));
        }
        return topWorkersGradeSumEUX(root->right, m);
    }

    double EmployeesTree::gradeAveragePerRange(int lowerSalary, int higherSalary)
    {
        Employee broke_employee(0, lowerSalary);
        Employee rich_employee(INF, higherSalary);

        int smaller_than_min = calcNumOfSmallerElements(&broke_employee);
        int smaller_than_max = calcNumOfSmallerElements(&rich_employee);

        int smaller_m = number_of_elements - smaller_than_min;
        int bigger_m = number_of_elements - smaller_than_max;

        long long grade_sum = topWorkersGradeSum(smaller_m)-topWorkersGradeSum(bigger_m)+ ((long long)rich_employee.getEmployeeGRADE())  ;
        int num_of_employees_in_range = smaller_m - bigger_m ;

        if (lowerSalary==0)
        {
            num_of_employees_in_range += num_of_free_workers;
            grade_sum += grades_sum_of_free_workers;
        }
        if(num_of_employees_in_range==0) return -1;
        return (double)grade_sum / (double)num_of_employees_in_range ;
    }

    EmployeesTree::~EmployeesTree() {
        EmpDestroyAndBreakCycleForEver(root);
        root.reset();
        root = nullptr;
    }

    Employee* EmployeesTree::EmpFindAVL(const Employee* value) const {

        shared_ptr<EmployeeNode> node_ptr = EmpFindAUX(value);
        if(node_ptr!=nullptr)
        {
            return node_ptr->data;
        }
        return nullptr;
    }

    shared_ptr<EmployeeNode> &EmployeesTree::EmpGetRoot(){
        return root;
    }

    bool EmployeesTree::EmpInsertAVL(Employee* value) {
        if (EmpInsertAUX(value)) {
            number_of_elements += 1;
            return true;
        }
        else return false ;

    }

    bool EmployeesTree::EmpDeleteAVL(Employee& value) {
        if (EmpDeleteAUX(&value)) {
            number_of_elements -= 1;
            return true;
        }
        else return false ;

    }

    int EmployeesTree::EmpGetNumOfElements() const {
        return number_of_elements;
    }

    void EmployeesTree::EmpMergeTrees(EmployeesTree &other, Employee** arr1, Employee** arr2, Employee** merged_arr) {

        int i = 0, j = 0, n = EmpGetNumOfElements(), m = other.EmpGetNumOfElements();

        number_of_elements+=other.number_of_elements;
        num_of_free_workers+=other.num_of_free_workers;
        grades_sum_of_free_workers+=other.grades_sum_of_free_workers;
        EmployeeNode::EmpAVLToSortedArray_AUX(root, arr1, &i);
        EmpDestroyAndBreakCycle(root);
        root.reset();
        root = nullptr;
        EmployeeNode::EmpAVLToSortedArray_AUX(other.EmpGetRoot(), arr2, &j);
        EmpDestroyAndBreakCycle(other.EmpGetRoot());
        other.root.reset();
        other.root = nullptr;
        EmpMergeSort(merged_arr, arr1, arr2, n, m);
        root = EmployeeNode::EmpSortedArrayToAVL_AUX(merged_arr, 0, m + n - 1);
        EmployeeNode::EmpUpdateMergedTreeNodesPostOrder(root);
    }

    void EmployeesTree::IncreaseNumOfFreeWorkers(){num_of_free_workers++;}

    void EmployeesTree::DecreaseNumOfFreeWorkers(){num_of_free_workers--;}

    void EmployeesTree::IncreaseGradeOfFreeWorkers(int Grade){grades_sum_of_free_workers+=(long long)Grade;}

    void EmployeesTree::DecreaseGradeOfFreeWorkers(int Grade){grades_sum_of_free_workers-=(long long)Grade;}
}

