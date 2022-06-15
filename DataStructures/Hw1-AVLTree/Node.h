//
// Created by Ori Zohar on 20 Apr 2022.
//

#ifndef DRY1_PROJECT_NODE_H
#define DRY1_PROJECT_NODE_H
#include <iostream>
#include <memory>
#include <cmath>
#include <assert.h>

namespace DATA_STRUCTURE_HW1 {
    using std::shared_ptr;

    class Company;
    class EmployeeById;
    class EmployeeBySalary;

    template<class T>
    class AVLTree;

    template<class T>
    class AVLNode {
    private :
        T* data;
        int height = 0;
        shared_ptr<AVLNode<T>> left;
        shared_ptr<AVLNode<T>> right;
        shared_ptr<AVLNode<T>> parent;

        AVLNode() = default;

        explicit AVLNode<T>(T* value) : data(value), left(nullptr), right(nullptr), parent(nullptr) {}

        AVLNode<T>(AVLNode<T> &other)
        {
            height = other.height;
            data = other.data;
        }

        void updateHeight() {
            int height_right = -1, height_left = -1;
            if (this->left != NULL) height_left = this->left->height;
            if (this->right != NULL) height_right = (this->right)->height;
            if (height_left > height_right) {
                height = height_left + 1;
                return;
            }
            height = height_right + 1;
        }

        int BalanceFactor() const {
            if (this->left == NULL && this->right == NULL) return 0;
            if (this->left == NULL && this->right != NULL) return -1 + -1 * (this->right)->height;
            if (this->left != NULL && this->right == NULL) return 1 + (this->left)->height;
            int balance_factor = (this->left)->height - (this->right)->height;
            return balance_factor;
        }

        void RotateLL() {
            shared_ptr<AVLNode<T>> left_son = this->left;
            shared_ptr<AVLNode<T>> root = left_son->parent;
            shared_ptr<AVLNode<T>> root_parent = this->parent;
            shared_ptr<AVLNode<T>> left_right_grandson = left_son->right;

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
            left_son->right->updateHeight();
            left_son->updateHeight();
            if (left_son->parent) {
                left_son->parent->updateHeight();
            }
            root->parent = left_son;
        }

        void RotateRR() {
            shared_ptr<AVLNode<T>> right_son = this->right;
            shared_ptr<AVLNode<T>> root = right_son->parent;
            shared_ptr<AVLNode<T>> root_parent = this->parent;
            shared_ptr<AVLNode<T>> right_left_grandson = right_son->left;
            if (root_parent != NULL) {
                if (root_parent->right == root) {
                    root_parent->right = right_son;
                } else if (root_parent->left == root) {
                    root_parent->left = right_son;
                }
            }
            right_son->parent = root_parent;
            /* Rotate the subtree */
            this->right = right_left_grandson;
            if (right_left_grandson != NULL) {
                right_left_grandson->parent = root;
            }
            right_son->left = root;
            this->parent = right_son;
            right_son->left->updateHeight();
            right_son->updateHeight();
            if (right_son->parent) {
                right_son->parent->updateHeight();
            }
        };

        void RotateLR() {
            shared_ptr<AVLNode<T>> temp;
            this->left->RotateRR();
            this->RotateLL();
        }

        void RotateRL() {
            shared_ptr<AVLNode<T>> temp;
            this->right->RotateLL();
            this->RotateRR();
        };

        int NumOfSons() const {
            int num_of_sons = 0;
            if (left != NULL) {
                num_of_sons++;
            }
            if (right != NULL) {
                num_of_sons++;
            }
            return num_of_sons;
        }

        static shared_ptr<AVLNode<T>> sortedArrayToAVL_Nodes(T **sorted_arr, int start, int end) {
            if (start > end) return NULL;
            int mid = (start + end) / 2;
            shared_ptr<AVLNode<T>> curr_root(new(std::nothrow) AVLNode<T>(sorted_arr[mid]));
            if(curr_root==NULL) {
                throw std::bad_alloc();
            }
            curr_root->left = sortedArrayToAVL_Nodes(sorted_arr, start, mid - 1);
            if(curr_root->left) curr_root->left->parent = curr_root;
            curr_root->right = sortedArrayToAVL_Nodes(sorted_arr, mid + 1, end);
            if(curr_root->right) curr_root->right->parent = curr_root;
            return curr_root;
        }

        static void AVLToSortedArray_Aux(shared_ptr<AVLNode<T>> &root, T **array, int *index) {
            if (root == NULL) return;
            AVLToSortedArray_Aux(root->left, array, index);
            array[*index] = root->data;
            (*index)++;
            AVLToSortedArray_Aux(root->right, array, index);
        }

        static void AVLToSortedArray(shared_ptr<AVLNode<T>> &root, T *array, int *index) {
            if (root == NULL) return;
            AVLToSortedArray(root->left, array, index);
            array[*index] = *(root->data);
            (*index)++;
            AVLToSortedArray(root->right, array, index);
        }


        template <class Operation,class Type>
        static void LimitedDataToTypeArray_Nodes(shared_ptr<AVLNode<T>> root, Type* array, int *index, int limit_index, Operation op) {
            if (root == nullptr ||*index >= limit_index)
            {
                return;
            }
            LimitedDataToTypeArray_Nodes(root->left, array, index, limit_index, op);
            if(*index >= limit_index) return;
            array[*index] =op(root->data);
            (*index)++;
            LimitedDataToTypeArray_Nodes(root->right, array, index, limit_index, op);
        }

        static void CountElementsByRange_Nodes(shared_ptr<AVLNode<T>>& root, T &max, T &min, int *counter) {
            if (root == NULL) return;
            else if (*(root->data) >= min && *(root->data) <= max) {
                (*counter)++;
                CountElementsByRange_Nodes(root->left, max, min, counter);
                CountElementsByRange_Nodes(root->right, max, min, counter);
            } else if (*(root->data) > max) {
                CountElementsByRange_Nodes(root->left, max, min, counter);
            } else {
                CountElementsByRange_Nodes(root->right, max, min, counter);
            }
        }

        static void RangeElemToSortedArray_Nodes(shared_ptr<AVLNode<T>> root, T &max, T &min, T **range_array, int *index) {
            if (root == NULL) return;
            else if (*(root->data) >= min && *(root->data) <= max) {
                RangeElemToSortedArray_Nodes(root->left, max, min, range_array, index);
                range_array[*index] = (root->data);
                (*index)++;
                RangeElemToSortedArray_Nodes(root->right, max, min, range_array, index);
            } else if (*(root->data) > max) {
                RangeElemToSortedArray_Nodes(root->left, max, min, range_array, index);
            } else if (*(root->data) < min) {
                RangeElemToSortedArray_Nodes(root->right, max, min, range_array, index);
            }
        }

    public:
        friend class AVLTree<T>;
        friend class EmployeesContainer;

        ~AVLNode()
        {
            data= nullptr;
            right= nullptr;
            left=nullptr;
            parent= nullptr;
        }

        AVLNode<T> &operator=(const AVLNode<T> &Other) = default;

        bool operator<=(AVLNode other) {
            return *(this->data) <= *(other->data);
        }
        bool operator>=(AVLNode other) {
            return *(this->data) >= *(other->data);
        }

        bool operator<(AVLNode other) {
            return *(this->data) < *(other->data);
        }
        bool operator>(AVLNode other) {
            return *(this->data) > *(other->data);
        }

       /* static void PrintPreOrder(shared_ptr<AVLNode<T>> &root) {
            if (root == NULL) return;
            std::cout << (*(root->data)).getEmployeeBySalary_ID() << std::endl;
            if (root->left) std::cout << root->left->data->getEmployeeBySalary_ID() << std::endl;
            if (root->right) std::cout << root->right->data->getEmployeeBySalary_ID() << std::endl;
            if (root->parent) std::cout << root->parent->data->getEmployeeBySalary_ID() << std::endl;
            std::cout << std::endl;
            PrintPreOrder(root->left);
            PrintPreOrder(root->right);
        }

        static void PrintInOrderID(shared_ptr<AVLNode<T>> &root) {
            if (root == NULL) return;
            PrintInOrderID(root->left);
            std::cout << root->data->getEmployeeByID_ID() << " ";
            PrintInOrderID(root->right);
        }
        static void PrintInOrderSALARY(shared_ptr<AVLNode<T>> &root) {
            if (root == NULL) return;
            PrintInOrderSALARY(root->left);
            std::cout << root->data->getEmployeeBySalary_ID() << " ";
            PrintInOrderSALARY(root->right);
        }

        static void PrintPostOrder(shared_ptr<AVLNode<T>> &root) {
            if (root == NULL) return;
            PrintPostOrder(root->left);
            PrintPostOrder(root->right);
            std::cout << (*(root->data)) << std::endl;
        }*/
        friend void updateCompany_EmployeeById(const std::shared_ptr<AVLNode<EmployeeById>>& root ,int company);
        friend void updateCompany_EmployeeBySalary(const std::shared_ptr<AVLNode<EmployeeBySalary>>& root ,int companyID);
    };
}
#endif //DRY1_PROJECT_NODE_H
