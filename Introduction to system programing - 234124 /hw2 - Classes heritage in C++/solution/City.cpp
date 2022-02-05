#include "City.h"
#include "Workplace.h"
#include "Manager.h"
#include "exceptions.h"
#include "Templates.h"
#include <algorithm>
#include <iostream>
#include "Skill.h"
#include <memory>
using std::string;
using std::vector;
using std::cout;
using std::endl;
using namespace mtm;
std::shared_ptr<mtm::Citizen> mtm::findCitizen(std::vector<std::shared_ptr<Citizen>> vec, int id)
{
    shared_ptr_Comparison<Citizen> compare(id);
    auto result = std::find_if(vec.begin(),vec.end(),compare);
    if(result == vec.end())
    {
        return nullptr;
    }
    return *result;
}
std::shared_ptr<mtm::Workplace> mtm::findWorkplace(std::vector<std::shared_ptr<Workplace>> vec, int id)
{
    shared_ptr_Comparison<Workplace> compare(id);
    auto result = std::find_if(vec.begin(),vec.end(),compare);
    if(result == vec.end())
    {
        return nullptr;
    }
    return *result;
}
void mtm::City::addEmployee(const int id, const std::string& first_name,
                            const std::string& last_name, const int birth_year){
    for(std::shared_ptr<Citizen> i : Citizens)
    {
        if(i->getId() == id)
        {
            throw mtm::CitizenAlreadyExists();
        }
    }
    Employee new_employee(id,first_name,last_name,birth_year);
    Employee* ptr_employee = new Employee(new_employee);
    std::shared_ptr<Employee> shared_ptr_employee(ptr_employee);
    Citizens.push_back(shared_ptr_employee);
}
void mtm::City::addManager(const int id, const std::string& first_name,
                           const std::string& last_name, const int birth_year){
    for(std::shared_ptr<Citizen> i : Citizens)
    {
        if(i->getId() == id)
        {
            throw CitizenAlreadyExists();
        }
    }
    Manager new_manager(id,first_name,last_name,birth_year);
    Manager* ptr_manager = dynamic_cast<Manager*>(new_manager.clone());
    std::shared_ptr<Manager> shared_ptr_manager(ptr_manager);
    Citizens.push_back(shared_ptr_manager);
}
void mtm::City::addFaculty(const int id , const class Skill& skill,
        const int added_points, Condition* condition) {
    for(std::shared_ptr<Faculty<Condition>> i : Faculties)
    {
        if((i.get())->getId() == id)
        {
            throw FacultyAlreadyExists();
        }
    }
    Faculty<Condition>* ptr_faculty = new Faculty<Condition>(id, skill, added_points, condition);
    std::shared_ptr<Faculty<Condition>> shared_ptr_faculty(ptr_faculty);
    Faculties.push_back(shared_ptr_faculty);
}
void mtm::City::createWorkplace(const int id, const std::string& name,
                                const int workers_salary, const int managers_salary ){
    for(std::shared_ptr<Workplace> i : Work_places)
    {
        if((i.get())->getId() == id)
        {
            throw WorkplaceAlreadyExists();
        }
    }
    Workplace* ptr_workplace = new Workplace(id,name,workers_salary,managers_salary);
    std::shared_ptr<Workplace> shared_ptr_workplace(ptr_workplace);
    Work_places.push_back(shared_ptr_workplace);
}
void mtm::City::teachAtFaculty(const int employee_id, const int faculty_id){
    for(std::shared_ptr<Citizen> employee : Citizens)
    {
        if((employee.get())->getId() == employee_id)
        {
           for(std::shared_ptr<Faculty<Condition>> faculty : Faculties)
           {
               if((faculty.get())->getId() == faculty_id)
               {
                   Employee* new_employee = dynamic_cast<Employee*>(employee.get());
                   if(!new_employee)
                   {
                       throw EmployeeDoesNotExist();
                   }
                   faculty->teach(new_employee);
                   return;
               }
           }
           throw FacultyDoesNotExist();
        }
    }
    throw EmployeeDoesNotExist();
}

void mtm::City::hireManagerAtWorkplace(const int manager_id, const int work_place_id){
    std::shared_ptr<Citizen> manager = findCitizen(Citizens,manager_id);
    if(manager == nullptr)
    {
        throw ManagerDoesNotExist();
    }
    std::shared_ptr<Workplace> work_place = mtm::findWorkplace(Work_places,work_place_id);
    if(work_place == nullptr)
    {
        throw WorkplaceDoesNotExist();
    }
    work_place->hireManager(dynamic_cast<Manager*>(manager.get()));
}
void mtm::City::fireEmployeeAtWorkplace(const int employee_id, const int manager_id, const int work_place_id){
    std::shared_ptr<Citizen> employee = findCitizen(Citizens, employee_id);
    if(employee == nullptr)
    {
        throw EmployeeDoesNotExist();
    }
    std::shared_ptr<Citizen> manager = findCitizen(Citizens,manager_id);
    if(manager == nullptr)
    {
        throw ManagerDoesNotExist();
    }
    std::shared_ptr<Workplace> work_place = findWorkplace(Work_places,work_place_id);
    if(work_place == nullptr)
    {
        throw WorkplaceDoesNotExist();
    }
    work_place->fireEmployee(employee_id,manager_id);
}
void mtm::City::fireManagerAtWorkplace(const int manager_id, const int work_place_id){
    std::shared_ptr<Citizen> manager = findCitizen(Citizens,manager_id);
    if(manager == nullptr)
    {
        throw ManagerDoesNotExist();
    }
    std::shared_ptr<Workplace> work_place = findWorkplace(Work_places,work_place_id);
    if(work_place == nullptr)
    {
        throw WorkplaceDoesNotExist();
    }
    Manager* new_manager = dynamic_cast<Manager*>(manager.get());
    new_manager->FireAllEmployees((*work_place).getWorkersSalary());
    work_place->fireManager(manager_id);
}
int mtm::City::getAllAboveSalary(std::ostream& os, const int salary) //needs sorting :(
{
    std::sort(Citizens.begin(), Citizens.end(),[](std::shared_ptr<Citizen> a
            ,std::shared_ptr<Citizen> b)
    {return a->getId() < b->getId() ;} );
    int counter =0;
    for(std::shared_ptr<Citizen> i : Citizens)
    {
        if(i->getSalary() >= salary)
        {
            i->printShort(os);
            counter++;
        }
    }
    return counter;
}
bool mtm::City::isWorkingInTheSameWorkplace(const int employee1_id, const int employee2_id) const {

    std::shared_ptr<Citizen> employee1 = findCitizen(Citizens, employee1_id);
    std::shared_ptr<Citizen> employee2 = findCitizen(Citizens, employee2_id);
    if(employee1 == nullptr || employee2 == nullptr)
    {
        throw EmployeeDoesNotExist();
    }
    for(std::shared_ptr<Workplace> curr : Work_places)
    {
        if(isEmployeeInWorkplace(*curr,employee1_id) && isEmployeeInWorkplace(*curr,employee2_id))
        {
            return true;
        }
    }
    return false;
}
void mtm::City::printAllEmployeesWithSkill(std::ostream& os, const int skill_id) const {
    for(std::shared_ptr<Citizen> citizen : Citizens)
    {
        if(dynamic_cast<Employee*>(citizen.get()) != nullptr && employeeHasSkill(dynamic_cast<Employee*>(citizen.get()), skill_id))
        {
            citizen->printShort(os);
        }
    }
}
