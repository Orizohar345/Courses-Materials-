//
// Created by Ori Zohar on 20 Apr 2022.
//

#ifndef DRY2_PROJECT_NODE_H
#define DRY2_PROJECT_NODE_H
#include <iostream>
#include <memory>

    using std::shared_ptr;


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
            /* EmpRotate the subtree */
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

        public:
        
        friend class AVLTree<T>;

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
    };
#endif //DRY2_PROJECT_NODE_H
