#include "Workplace.h"
#include "Manager.h"
#include "exceptions.h"
#include "Templates.h"
#include "exceptions.h"
#include <algorithm>
using std::string ;
using std::vector;
int mtm::Workplace::getId() const
{
    return Id;
}
string mtm::Workplace::getName() const
{
    return Name;
}
int mtm::Workplace::getWorkersSalary() const {
    return WorkersSalary;
}
int mtm::Workplace::getManagersSalary()  const {
    return ManagersSalary;
}
void mtm::Workplace::hireManager(Manager* manager)
{
 for(Manager* i : Managers)
 {
     if(i->getId() == manager->getId()) {
         throw ManagerAlreadyHired();
     }
     }
     if(manager->getSalary())
     {
         throw CanNotHireManager();
     }
     manager->setSalary(ManagersSalary);
     Managers.push_back(manager);
    std::sort(Managers.begin(), Managers.end(),[](mtm::Manager* a , mtm::Manager* b){ return a->getId() < b->getId();});
}

void mtm::Workplace::fireEmployee (const int& employee_id ,const int& manager_id)
{
    IdComparation<Manager> CompareForEmployee(manager_id);
    auto manager_is_found = std::find_if(Managers.begin(), Managers.end(),CompareForEmployee);
    if(manager_is_found == Managers.end()) {
        throw ManagerIsNotHired();
    }
    (*manager_is_found)->SetSalaryForEmployee(employee_id, -WorkersSalary);
    (*manager_is_found)->removeEmployee(employee_id);
}
void mtm::Workplace::fireManager(const int &manager_id) {
    IdComparation<Manager> CompareForEmployee(manager_id);
    auto manager_is_found = std::find_if(Managers.begin(), Managers.end(),CompareForEmployee);
    if(manager_is_found == Managers.end()) {
        throw ManagerIsNotHired();
    }

    //(*manager_is_found)->FireAllEmployees(WorkersSalary);
    (*manager_is_found)->setSalary(-ManagersSalary);
    Managers.erase(std::find_if(Managers.begin(), Managers.end(),CompareForEmployee) );
}


namespace mtm {
    std::ostream& operator<< (std::ostream& os ,const Workplace& workplace)
    {
        os << "Workplace name -"<<" "<<workplace.getName() ;
        if(workplace.Managers.begin()==workplace.Managers.end()) {
            return os<<std::endl;
        }
        os <<" "<<"Groups:"<<std::endl;
        for(Manager* i :workplace.Managers)
        {
            os<<"Manager"<<" ";
            i->printLong(os);
        }
        return os;
    }
    bool isEmployeeInWorkplace(Workplace workplace, int employee_id)
    {
        for(Manager* curr_manager : workplace.Managers)
        {
            if(isEmployeeOfManager(curr_manager, employee_id))
            {
                return true;
            }
        }
        return false;
    }
}