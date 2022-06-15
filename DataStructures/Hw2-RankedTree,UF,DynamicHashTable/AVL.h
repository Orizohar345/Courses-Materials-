
#ifndef DRY1_PROJECT_AVL_H
#define DRY1_PROJECT_AVL_H

#include <memory>
#include "Node.h"
//using std::shared_ptr;

/**
 * AVLTree:
 *
 * Data Fields :
 * 1) root : pointer the root of the AVL tree
 * 2) number_of_elements : the number of elemens in the three .
 *
 * Methods :
 * 1) EmpFindAVL - check if there an element in the three with value of T .
 *    Parameters:
 *    T - the generic data we want to search in the AVL Tree .
 *    Return Value:
 *    pointer to the data found .
 *    Exceptions:
 *    ElementNotExists in case the element not in the AVL Tree.
 *    Complexity :
 *    time complexity of O(log(n)) (n is number of elements in the three ) .
 *    space complexity of O(1) .
 *
 * 2) EmpGetRoot - get pointer the root of the AVL .
 *    No Paramaters.
 *    Return Value:
 *    pointer to the data of the root in case theres elements in the AVL tree and NULL ptr in case the three is empty .
 *    Complexity :
 *    time complexity of O(1) .
 *    space complexity of O(1) .
 *
 * 3) EmpGetMax - get pointer the max element by key (compare operator of generic element T) in the AVL .
 *    No Paramaters.
 *    Return Value:
 *    pointer to the max of the root in case theres elements in the AVL tree and NULL ptr in case the three is empty .
 *    Complexity :
 *    time complexity of O(log(n)) .
 *    space complexity of O(1) .
 *
 * 4) EmpInsertAVL - inserting an element to the AVLTree .
 *    Parameters:
 *    T - the generic data we want to in the AVL Tree .
 *    Return Value:
 *    bool operand , true in case of success
 *    Exceptions:
 *    std::bad_alloc - Throw C++ Exception in case of allocation error.
 *    Complexity :
 *    time complexity of O(log(n)) (n is number of elements in the three ) .
 *    space complexity of O(1) .
 *
 * 5) EmpDeleteAVL - delete an element from the three , time complexity of log(number_of_elements) .
 *    Parameters:
 *    T - the generic data we want to in the AVL Tree .
 *    Return Value:
 *    bool operand , true in case of success and false in case of failure .
 *    Complexity :
 *    time complexity of O(log(n)) (n is number of elements in the three ) .
 *    space complexity of O(1) .
 *
 * 6) EmpGetNumOfElements - get the current number of element in the AVLTree .
 *    No Paramaters.
 *    Return Value:
 *    number of elemenst in the AVL tree (integer) .
 *    Complexity :
 *    time complexity of O(1) .
 *    space complexity of O(1) .
 * 7) EmpMergeTrees - merges two trees into one tree so that all the elements are in the present object .
 *    Parameters:
 *    AVL three object of the other three we want to merge with .
 *    No return value.
 *    Exceptions :
 *    std::bad_alloc - in case of memory allocation problem .
 *    Complexity :
 *    n - number of elements in the current three .
 *    m - number of elements in the other three .
 *    time complexity of O(n+m) .
 *    space complexity of O(n+m) .
 *
 *  8) reversedElemToArr - get pointer to array of class T , and put the current tree elements in reversed order (from the bigger to the smaller) .
 *    Parameters:
 *    reversed_array - pointer of T , the function will fill the array with the elements of the three in sorting reversed order
 *    Return Value :
 *    No return value.
 *    Exceptions :
 *    std::bad_alloc - in case of memory allocation problem .
 *    Complexity :
 *    n - number of elements in the current three .
 *    time complexity of O(n) .
 *    space complexity of O(n) .
 *
 *  9) limitedDataToTypeArray - Fills the array with the elements of the three according to the desired number in sorting order .
 *    Parameters:
 *    array - Array of T elements in the size of amount .
 *    amount - the number of elements required .
 *    Return Value :
 *    No return value.
 *    Complexity :
 *    time complexity of O(amount) .
 *    space complexity of O(amount).
 *
 *  10) RangeElemToSortedArray - Fills the array with the elements of the three according to the range of numbers in sorting order .
 *    Parameters:
 *    max_element - The upper boundary of the elements in the array according to the comparison operator of T .
 *    min_element - The lower boundary of the elements in the array according to the comparison operator of T .
 *    number_of_elements_in_range - pointer to int , should transfer that the value inside is 0 , the function will change it to the number of elements in the range .
 *    Return Value :
 *    the function wil return an array of T in size of the number_of_elements_in_range (updated) .
 *    Exceptions :
 *    std::bad_alloc - in case of memory allocation problem .
 *    Complexity :
 *    n - number of elements in the AVL three .
 *    number_of_elements_in_range - number of elements between max_element to min_element exists in the AVL tree .
 *    time complexity of O(log(n) + number_of_elements_in_range) .
 *    space complexity of O(number_of_elements_in_range).
**/
    template<class T>
    class AVLTree {
    private :
        shared_ptr<AVLNode<T>> root;
        int number_of_elements = 0;

        void Rotate(shared_ptr<AVLNode<T>> &sub_root_son) {
            int BF = sub_root_son->parent->BalanceFactor();
            if (BF == 2) {
                if (sub_root_son->parent->left->BalanceFactor() >= 0) {
                    if (sub_root_son->parent == root) {
                        sub_root_son=sub_root_son->parent->left;
                        sub_root_son->parent->RotateLL();
                        root = sub_root_son;
                    } else {
                        sub_root_son->parent->RotateLL();
                    }
                } else if (sub_root_son->parent->left->BalanceFactor() == -1) {
                    if (sub_root_son->parent == root) {
                        sub_root_son = sub_root_son->parent->left ->right;
                        sub_root_son->parent->parent->RotateLR();
                        root = sub_root_son;
                    } else {
                        sub_root_son->parent->RotateLR();
                    }
                }
            } else if (BF == -2) {
                if (sub_root_son->parent->right->BalanceFactor() <= 0) {
                    if (sub_root_son->parent == root) {
                        sub_root_son=sub_root_son->parent->right;
                        sub_root_son->parent->RotateRR();
                        root = sub_root_son;
                    } else {
                        sub_root_son->parent->RotateRR();
                    }
                } else if (sub_root_son->parent->right->BalanceFactor() == 1) {
                    if (sub_root_son->parent == root) {
                        sub_root_son=sub_root_son->parent->right->left;
                        sub_root_son->parent->parent->RotateRL();
                        root = sub_root_son;
                    } else {
                        sub_root_son->parent->RotateRL();
                    }
                }
            }
        }

        void Swap(shared_ptr<AVLNode<T>> &node1, shared_ptr<AVLNode<T>> &node2) {
            if (node1 == node2) {
                return;
            }
            shared_ptr<AVLNode<T>> parent_1 = node1->parent;
            shared_ptr<AVLNode<T>> left_son_1 = node1->left;
            shared_ptr<AVLNode<T>> right_son_1 = node1->right;

            shared_ptr<AVLNode<T>> parent_2 = node2->parent;
            shared_ptr<AVLNode<T>> left_son_2 = node2->left;
            shared_ptr<AVLNode<T>> right_son_2 = node2->right;

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

            node1->updateHeight();
            node2->updateHeight();
            if (node1 == root) {
                root = node2;
            }
        }

        bool Insert_AUX(T* value) {

            if (Find_AUX(value) != NULL) {
                return false;
            }

            shared_ptr<AVLNode<T>> inserted(new(std::nothrow) AVLNode<T>(value));
            if (inserted == nullptr) throw std::bad_alloc();
            if (root == nullptr) {
                root = inserted;
                return true;
            }
            shared_ptr<AVLNode<T>> temp(root);
            while (true) {
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
                temp->updateHeight();
                temp = temp->parent;
            }

            while (inserted != root) {
                int BF = inserted->parent->BalanceFactor();
                if (BF == 2 || BF == -2) {
                    Rotate(inserted);
                    break;
                }
                inserted = inserted->parent;
            }
            return true;
        }

        bool Delete_AUX(T* value) {
            shared_ptr<AVLNode<T>> to_delete = Find_AUX(value);
            shared_ptr<AVLNode<T>> it;
            if (to_delete == NULL) {
                return false;
            }
            to_delete->data= nullptr;
            if (to_delete->NumOfSons() == 2) {
                shared_ptr<AVLNode<T>> to_swap = to_delete;

                to_swap = to_swap->right;
                while (to_swap->left != NULL) to_swap = to_swap->left;
                Swap(to_delete, to_swap);
            }
            if (to_delete->NumOfSons() == 0) {
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
            } else if (to_delete->NumOfSons() == 1) {
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
            shared_ptr<AVLNode<T>> to_update = it;
            while (to_update) {
                to_update->updateHeight();
                to_update = to_update->parent;
            }
            if (it->parent == NULL && it->left) it = it->left;
            if (it->parent == NULL && it->right) it = it->right;
            while (true) {
                if (it == NULL || it->parent == NULL) break;
                int BF = it->parent->BalanceFactor();
                if (BF == 2 || BF == -2) {
                    Rotate(it);
                }
                it = it->parent;
            }
            return true;
        }

        shared_ptr<AVLNode<T>> Find_AUX(const T* value) const {
            shared_ptr<AVLNode<T>> iterator(this->root);
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

    public:

        AVLTree<T>() = default;

        ~AVLTree<T>() {
            DestroyAndBreakCycleForEver(root);
            root.reset();
            root = nullptr;
        };

        void DestroyAndBreakCycle(shared_ptr<AVLNode<T>> &node) {
            if (node == NULL) return;
            DestroyAndBreakCycle(node->left);
            DestroyAndBreakCycle(node->right);
            node->parent = nullptr;
            node.reset();
            node= nullptr;
        }

        AVLTree<T>(const AVLTree<T> &other) = delete;

        AVLTree<T> &operator=(const AVLTree<T> &other) = delete;

        T* findAVL(const T* value) const {

            shared_ptr<AVLNode<T>> node_ptr = Find_AUX(value);
            if(node_ptr!=nullptr)
            {
                return node_ptr->data;
            }
            return nullptr;
        }

        shared_ptr<AVLNode<T>> &getRoot(){
            return root;
        }

        bool insertAVL(T* value) {
            if (Insert_AUX(value)) {
                number_of_elements += 1;
                return true;
                }
            else return false ;

        }

        bool deleteAVL(T& value) {
            if (Delete_AUX(&value)) {
                number_of_elements -= 1;
                return true;
            }
            else return false ;

        }

        int getNumOfElements() const {
            return number_of_elements;
        }

        void ElemToArr(T** array){
            int i=0;
            if(array==NULL) throw std::bad_alloc();
            AVLNode<T>::AVLToSortedArray_Aux(root, array, &i);
        }

        void DestroyAndBreakCycleForEver(shared_ptr<AVLNode<T>> &node) {
            if (node == NULL) return;
            DestroyAndBreakCycleForEver(node->left);
            DestroyAndBreakCycleForEver(node->right);
            node->parent = NULL;
            delete node->data;
            node->data=NULL;
            node.reset();
            node= nullptr;
        }
    };

#endif //DRY1_PROJECT_AVL_H