//
// Created by Ori Zohar on 31/05/2022.
//

#ifndef DS2_EMPLOYEENODE_H
#define DS2_EMPLOYEENODE_H
#include <memory>
#include "iostream"
#include "Employee.h"
namespace DATA_STRUCTURE_HW2 {
    using std::shared_ptr;
    class EmployeesTree;

    class EmployeeNode {
    private :
        Employee* data;
        int height = 0;
        int size = 1;
        long long grades = 0;
        shared_ptr<EmployeeNode> left;
        shared_ptr<EmployeeNode> right;
        shared_ptr<EmployeeNode> parent;


        EmployeeNode() = default;
        explicit EmployeeNode(Employee* value) : data(value), grades(value->getEmployeeGRADE()), left(nullptr), right(nullptr), parent(nullptr) {}
        EmployeeNode(EmployeeNode&other)
        {
            height = other.height;
            data = other.data;
        }
        void EmpUpdateHeight() ;
        int EmpBalanceFactor() const ;
        void EmpRotateLL() ;
        void EmpRotateRR() ;
        void EmpRotateLR() ;
        void EmpRotateRL() ;
        int EmpNumOfSons() const ;

    public:
        friend class EmployeesTree;

        ~EmployeeNode()
        {
            data= nullptr;
            right= nullptr;
            left=nullptr;
            parent= nullptr;
        }
        static shared_ptr<EmployeeNode> EmpSortedArrayToAVL_AUX(Employee **sorted_arr, int start, int end) ;
        static void EmpAVLToSortedArray_AUX(shared_ptr<EmployeeNode> &root, Employee **array, int *index) ;
        static void EmpAVLToSortedArray_AUX(shared_ptr<EmployeeNode> &root, Employee *array, int *index) ;
        static void EmpUpdateMergedTreeNodesPostOrder(shared_ptr<EmployeeNode> &root);
        void updateSizeAndGrades();
        EmployeeNode &operator=(const EmployeeNode &Other) = default;
        bool operator<=(EmployeeNode& other) ;
        bool operator>=(EmployeeNode& other) ;
        bool operator<(EmployeeNode& other) ;
        bool operator>(EmployeeNode& other) ;

             static void PrintInOrder(shared_ptr<EmployeeNode> &root) {
                 if (root == NULL) return;
                 PrintInOrder(root->left);
                 std::cout << "id: "<< root->data->getEmployeeID() << " ";
                 std::cout <<"grade: "<< root->data->getEmployeeGRADE() << " ";
                std::cout <<"salary: "<< root->data->getEmployeeSALARY() << " ";
                std::cout <<"company: "<< root->data->getEmployeeCOMPANY() << " ";
                std::cout << "size: "<< root->size << " ";
                std::cout << "grades: "<< root->grades << " "<<std::endl;
                PrintInOrder(root->right);
             }
    };
}
#endif //DS2_EMPLOYEENODE_H
