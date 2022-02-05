#include "Employee.h"
#include "Manager.h"
#include "Templates.h"
#include "exceptions.h"
#include <vector>
#include <algorithm>
using std::cout;
using std::endl;

void mtm::Manager::FireAllEmployees(int salary)
{
    unsigned long long init_size = Employees.size();
    for(unsigned long long i = 0; i < init_size ;i++)
    {
        //updates the last employee's (in the vector) salary, and then pops it out of the vector.(deleting it)
        Employees[init_size - i - 1]->setSalary(-salary);
        Employees.pop_back();
    }
}
void mtm::Manager::SetSalaryForEmployee(const int employee_id, const int salary)
{
    IdComparation<Employee> compare_for_employees(employee_id);
    std::vector<Employee*>::iterator wanted_employee = std::find_if(Employees.begin(), Employees.end(),
                                                                    compare_for_employees);
    if (wanted_employee == Employees.end())
    {
        throw EmployeeIsNotHired();
    }
    (*wanted_employee)->setSalary(salary);
}
int mtm::Manager::getSalary() const
{
    return Salary;
}
void mtm::Manager::setSalary( int salary)
{
    Salary += salary;
    if(this->Salary < 0)
    {
        this->Salary =0;
    }
}
void mtm::Manager::addEmployee(Employee* employee)
{
    IdComparation<Employee> compare_for_employees(employee->getId());
    if(Employees.end() != std::find_if(Employees.begin(), Employees.end(), compare_for_employees))
    {
        throw EmployeeAlreadyHired();
    }
    Employees.push_back(employee);
    std::sort(Employees.begin(), Employees.end(),[](Employee* a , Employee* b){return a->getId()<b->getId() ;} );
}
void mtm::Manager::removeEmployee(const int id)
{
    IdComparation<Employee> compare_for_employees(id);
    if(Employees.end() == std::find_if(Employees.begin(), Employees.end(), compare_for_employees))
    {
        throw EmployeeIsNotHired();
    }
    for(std::vector<Employee*>::iterator i =Employees.begin() ; i != Employees.end(); i++)
    {
        if((**i).getId() == id)
        {
            Employees.erase(i);
            return;
        }
    }
}
std::ostream& mtm::Manager::printShort(std::ostream& os)
{
    os << getFirstName() << " " << getLastName() << endl;
    os << "Salary: " << getSalary() << endl;
    return os;
}
std::ostream& mtm::Manager::printLong(std::ostream& os)
{
    os << getFirstName() << " " << getLastName() << endl;
    os << "id - " << getId() << " birth_year - " << getBirthYear() << endl;
    os << "Salary: " << getSalary();
    if(Employees.begin() != Employees.end())
    {
        os << endl << "Employees: " << endl;
    }
    else {
        os << endl;
    }
    for(Employee* i : Employees)
    {
        (*i).printShort(os);
    }
    return os;
}
mtm::Manager* mtm::Manager::clone() const
{
    return new Manager(*this);
}
bool mtm::isEmployeeOfManager(Manager* curr_manager, int employee_id)
{
    for(Employee* employee : curr_manager->Employees)
    {
        if(employee->getId() == employee_id)
        {
            return true;
        }
    }
    return false;
}

