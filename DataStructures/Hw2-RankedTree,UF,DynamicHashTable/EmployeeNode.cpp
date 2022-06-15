//
// Created by Ori Zohar on 31/05/2022.
//
#include "EmployeeNode.h"
namespace DATA_STRUCTURE_HW2 {

    int EmployeeNode::EmpBalanceFactor() const {
        if (this->left == NULL && this->right == NULL) return 0;
        if (this->left == NULL && this->right != NULL) return -1 + -1 * (this->right)->height;
        if (this->left != NULL && this->right == NULL) return 1 + (this->left)->height;
        int balance_factor = (this->left)->height - (this->right)->height;
        return balance_factor;
    }

    void EmployeeNode::EmpUpdateHeight() {
        int height_right = -1, height_left = -1;
        if (this->left != NULL) height_left = this->left->height;
        if (this->right != NULL) height_right = (this->right)->height;
        if (height_left > height_right) {
            height = height_left + 1;
            return;
        }
        height = height_right + 1;
    }

    void EmployeeNode::EmpRotateLL() {

        shared_ptr<EmployeeNode> left_son = this->left;
        shared_ptr<EmployeeNode> root = left_son->parent;
        shared_ptr<EmployeeNode> root_parent = this->parent;
        shared_ptr<EmployeeNode> left_right_grandson = left_son->right;

        shared_ptr<EmployeeNode> left_left_grandson = left_son->left;

        /**change**/
        int A_right_size=0;
        long long A_right_grades=0;
        int B_right_size=0;
        long long B_right_grades=0;

        int B_left_size=0;
        long long B_left_grades=0;

        if(right)
        {
            A_right_size = right->size;
            A_right_grades = right->grades;
        }
        if(left_son->right)
        {
            B_right_size = left_son->right->size;
            B_right_grades = left_son->right->grades;
        }
        if(left_son->left)
        {
            B_left_size = left_son->left->size;
            B_left_grades = left_son->left->grades;
        }

        size = A_right_size+B_right_size+1;
        grades = A_right_grades+B_right_grades+data->getEmployeeGRADE();
        left_son->size = size+B_left_size+1;
        left_son->grades = grades+B_left_grades+left_son->data->getEmployeeGRADE();
        /**change end**/


        if (root_parent != NULL) {
            if (root_parent->left == root) {
                root_parent->left = left_son;
            } else if (root_parent->right == root) {
                root_parent->right = left_son;
            }
        }
        left_son->parent = root_parent;

        /* Rotating the subtree */
        root->left = left_right_grandson;
        if (left_right_grandson != NULL) {
            left_right_grandson->parent = root;
        }
        left_son->right = root;
        left_son->right->EmpUpdateHeight();
        left_son->EmpUpdateHeight();
        if (left_son->parent) {
            left_son->parent->EmpUpdateHeight();
        }
        root->parent = left_son;
    }

    void EmployeeNode::EmpRotateRR() {
        shared_ptr<EmployeeNode> right_son = this->right;
        shared_ptr<EmployeeNode> root = right_son->parent;
        shared_ptr<EmployeeNode> root_parent = this->parent;
        shared_ptr<EmployeeNode> right_left_grandson = right_son->left;

        /**change**/
        int A_left_size=0;
        long long A_left_grades=0;
        int B_right_size=0;
        long long B_right_grades=0;

        int B_left_size=0;
        long long B_left_grades=0;

        if(left)
        {
            A_left_size = left->size;
            A_left_grades = left->grades;
        }
        if(right_son->right)
        {
            B_right_size = right_son->right->size;
            B_right_grades= right_son->right->grades;
        }
        if(right_son->left)
        {
            B_left_size = right_son->left->size;
            B_left_grades = right_son->left->grades;
        }

        size = B_left_size+A_left_size+1;
        grades = B_left_grades+A_left_grades+data->getEmployeeGRADE();
        right_son->size = size+B_right_size+1;
        right_son->grades = grades+B_right_grades+right_son->data->getEmployeeGRADE();
        /**change end**/

        if (root_parent != NULL) {
            if (root_parent->right == root) {
                root_parent->right = right_son;
            } else if (root_parent->left == root) {
                root_parent->left = right_son;
            }
        }
        right_son->parent = root_parent;
        /* EmpRotate the subtree */
        this->right = right_left_grandson;
        if (right_left_grandson != NULL) {
            right_left_grandson->parent = root;
        }
        right_son->left = root;
        this->parent = right_son;
        right_son->left->EmpUpdateHeight();
        right_son->EmpUpdateHeight();
        if (right_son->parent) {
            right_son->parent->EmpUpdateHeight();
        }
    };

    void EmployeeNode::EmpRotateLR() {
        shared_ptr<EmployeeNode> temp;
        this->left->EmpRotateRR();
        this->EmpRotateLL();
    }

    void EmployeeNode::EmpRotateRL() {
        shared_ptr<EmployeeNode> temp;
        this->right->EmpRotateLL();
        this->EmpRotateRR();
    };

    int EmployeeNode::EmpNumOfSons() const {
        int num_of_sons = 0;
        if (left != NULL) {
            num_of_sons++;
        }
        if (right != NULL) {
            num_of_sons++;
        }
        return num_of_sons;
    }

    shared_ptr<EmployeeNode> EmployeeNode::EmpSortedArrayToAVL_AUX(Employee **sorted_arr, int start, int end) {
        if (start > end) return NULL;
        int mid = (start + end) / 2;
        shared_ptr<EmployeeNode> curr_root(new(std::nothrow) EmployeeNode(sorted_arr[mid]));
        if(curr_root==NULL) {
            throw std::bad_alloc();
        }
        curr_root->left = EmpSortedArrayToAVL_AUX(sorted_arr, start, mid - 1);
        if(curr_root->left) curr_root->left->parent = curr_root;
        curr_root->right = EmpSortedArrayToAVL_AUX(sorted_arr, mid + 1, end);
        if(curr_root->right) curr_root->right->parent = curr_root;
        return curr_root;
    }

    void EmployeeNode::EmpAVLToSortedArray_AUX(shared_ptr<EmployeeNode> &root, Employee **array, int *index) {
        if (root == NULL) return;
        EmpAVLToSortedArray_AUX(root->left, array, index);
        array[*index] = root->data;
        (*index)++;
        EmpAVLToSortedArray_AUX(root->right, array, index);
    }

    void EmployeeNode::EmpAVLToSortedArray_AUX(shared_ptr<EmployeeNode> &root, Employee *array, int *index) {
        if (root == NULL) return;
        EmpAVLToSortedArray_AUX(root->left, array, index);
        array[*index] = *(root->data);
        (*index)++;
        EmpAVLToSortedArray_AUX(root->right, array, index);
    }

    bool EmployeeNode::operator<=(EmployeeNode& other) {
        return *(this->data) <= *(other.data);
    }

    bool EmployeeNode::operator>=(EmployeeNode& other) {
        return *(this->data) >= *(other.data);
    }

    bool EmployeeNode::operator<(EmployeeNode& other) {
        return *(this->data) < *(other.data);
    }

    bool EmployeeNode::operator>(EmployeeNode& other) {
        return *(this->data) > *(other.data);
    }

    void EmployeeNode::EmpUpdateMergedTreeNodesPostOrder(shared_ptr<EmployeeNode> &root) {
        if (root == NULL) return;
        EmpUpdateMergedTreeNodesPostOrder(root->left);
        EmpUpdateMergedTreeNodesPostOrder(root->right);

        root->size = 1;
        root->grades = root->data->getEmployeeGRADE();
        if (root->right != NULL) {
            root->size += root->right->size;
            root->grades += root->right->grades;
            // root->height = root->right->height+1;
        }
        if (root->left != NULL) {
            root->size += root->left->size;
            root->grades += root->left->grades;
           // if(root->left->height>root->right->height)
          //  {
          //      root->height = root->left->height+1;
          //  }
        }
    }

    void EmployeeNode::updateSizeAndGrades()
    {
        size=1;
        grades=data->getEmployeeGRADE();
        if(left)
        {
            size+=left->size;
            grades+=left->grades;
        }
        if(right)
        {
            size+=right->size;
            grades+=right->grades;
        }
    }
}
