//
// Created by Ori Zohar on 31/05/2022.
//

#ifndef DS2_EMPLOYEESTREE_H
#define DS2_EMPLOYEESTREE_H
#include "EmployeeNode.h"
namespace DATA_STRUCTURE_HW2 {
    using std::shared_ptr;


    class EmployeesTree {
    private :
        shared_ptr<EmployeeNode> root;
        int number_of_elements = 0;
        int num_of_free_workers = 0 ;
        long long grades_sum_of_free_workers=0;

        void EmpRotate(shared_ptr<EmployeeNode> &sub_root_son);

        void EmpSwap(shared_ptr<EmployeeNode> &node1, shared_ptr<EmployeeNode> &node2);

        void EmpDestroyAndBreakCycleForEver(shared_ptr<EmployeeNode> &node);

        bool EmpInsertAUX(Employee* value);

        bool EmpDeleteAUX(Employee* value);
        shared_ptr<EmployeeNode> EmpFindAUX(const Employee* value) const;
        void EmpMergeSort(Employee **merged_arr, Employee **arr1, Employee **arr2, int n, int m);

    public:

        EmployeesTree() = default;

        ~EmployeesTree();

        EmployeesTree(const EmployeesTree &other) = delete;

        EmployeesTree& operator=(const EmployeesTree &other) = delete;

        Employee* EmpFindAVL(const Employee* value) const ;

        shared_ptr<EmployeeNode> &EmpGetRoot();

        bool EmpInsertAVL(Employee* value) ;

        bool EmpDeleteAVL(Employee& value) ;

        int EmpGetNumOfElements() const ;

        void EmpMergeTrees(EmployeesTree &other, Employee** arr1, Employee** arr2, Employee** merged_arr);

        void UpdateSizeAndRightGradeForDelete(const Employee* value, int grade) const;

        long long topWorkersGradeSum(int m);

        long long topWorkersGradeSumEUX(shared_ptr<EmployeeNode> root, int m);

        double gradeAveragePerRange(int lowerSalary, int higherSalary);

        int calcNumOfSmallerElements(const Employee* value) const;

        void IncreaseNumOfFreeWorkers();

        void DecreaseNumOfFreeWorkers();

        void IncreaseGradeOfFreeWorkers(int Grade);

        void DecreaseGradeOfFreeWorkers(int Grade);

        void EmpDestroyAndBreakCycle(shared_ptr<EmployeeNode> &node);
    };
}

#endif //DS2_EMPLOYEESTREE_H
