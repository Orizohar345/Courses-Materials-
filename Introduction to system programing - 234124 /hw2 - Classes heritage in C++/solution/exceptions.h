#include <iostream>
#include <exception>

#ifndef MTMEX2_EXCEPTIONS_H
#define MTMEX2_EXCEPTIONS_H
namespace mtm {

    /* Exception Class :
     * inherits from std:exception and all the exceptions that connecting with city
     * will hire from her .
     */

    class Exception : public std::exception
    {
    protected:
        std::string error_message;
        std::string detalis ;
        std::string out_message = error_message + detalis;

    public :
        explicit Exception(std::string message , std::string details = "") :
                error_message(message) , detalis(details) {}
        virtual ~Exception() = default ;
        const char*  what() const noexcept override {
            return out_message.c_str();
        }
    };

    /* Negative Points exception :
     * Exception for Skill class - operator + and operator += .
      * - Need to be thrown when negative number is used as a parameter for this operators  .
     */
    class NegativePoints : public Exception {
    public :
        NegativePoints() : Exception("Negative Points") {}
    } ;

    /* SkillAlreadyLearned exception :
     * Exception for Employee class - learnSkill function .
      * - Need to be thrown when the user try to learn the employee a skill that he has already leraned .
     */
    class SkillAlreadyLearned : public Exception {
    public :
        SkillAlreadyLearned() : Exception("SkillAlreadyLearned") {}
    };

    /* CanNotLearnSkill exception :
   * Exception for Employee class - learnSkill function .
    * - Need to be thrown when the user try to learn the employee a skill
    * - but the employee can not learn the skill .
   */
    class CanNotLearnSkill : public Exception {
    public :
        CanNotLearnSkill() : Exception("CanNotLearnSkill") {}
    };

    /* DidNotLearnSkill exception :
     * Exception for Employee class - forgetSkill function  .
      * - Need to be thrown when the user try to delete a skill from the employee's skills set
      * - but the skill is not in the skill set .
    */
    class DidNotLearnSkill : public Exception {
    public :
        DidNotLearnSkill() : Exception("DidNotLearnSkill") {}
    };

    /* EmployeeAlreadyHired exception :
     * Exception for Manager class - addEmployee :
      * - Need to be thrown when the user try to add employee to a group of the manager
      * - but the employee is already works there :
     * Exception for Workplace class - hireEmployee .
      * - Need to be thrown if the employee is already in the group of the manager in the workplace .
     */
    class EmployeeAlreadyHired : public Exception {
    public :
        EmployeeAlreadyHired() : Exception("EmployeeAlreadyHired") {}
    };

    /* EmployeeIsNotHired exception :
     * Exception for Manager class - removeEmployee function :
      * - Need to be thrown when the user try to delete employee from the group of the manager
      * - but the employee is not one of the group .
    */
    class EmployeeIsNotHired : public Exception {
    public :
        EmployeeIsNotHired() : Exception("EmployeeNotHired") {}
    };

    /* EmployeeIsNotSelected exception :
        * Exception for Workplace class - hireEmployee function .
        * - Need to be thrown when the user try to add employee to work in the workplace
        * - but the employee is meeting the condition recuired to work in the workplace .
       */
    class EmployeeNotSelected : public Exception {
    public :
        EmployeeNotSelected() : Exception("EmployeeNotSelected") {}
    };

    /* ManagerIsNotHired exception :
     * Exception for Workplace class - hireEmployee function .
      * - Need to be thrown when the user try to add employee to work in the workplace
      * - but the manager that he needs to join to his group is not hired .
    * Exception for Workplace class - fireEmployee function .
     * - should be thrown when the manager we want to fire not working in the workplace.
    */
    class ManagerIsNotHired : public Exception {
    public :
        ManagerIsNotHired() : Exception("ManagerIsNotHired") {}
    };

    /* ManagerAlreadyHired exception :
     * Exception for Workplace class - hireManager function .
      * - Need to be thrown when the user try to add manager to work in the workplace
      * - but the manager is already works there .
    */
    class ManagerAlreadyHired : public Exception {
    public :
        ManagerAlreadyHired() : Exception("ManagerAlreadyHired") {}
    };

    /* CanNotHireManager exception :
   * Exception for Workplace class - hireManager function .
   * - Need to be thrown when the user try to add manager to work in the workplace
   * -  but the manager is already working in other workplace .
  */
    class CanNotHireManager : public Exception {
    public :
        CanNotHireManager() : Exception("CannotHireManager") {}
    };

    /* EmployeeNotAccepted exception :
     * Exception for Faculty class - teach function .
      * - Need to be thrown when the user try to teach the employee a skill in the class
      * - but the employee is not making the condition to learn it .
    */
    class EmployeeNotAccepted : public Exception {
    public :
        EmployeeNotAccepted() : Exception("EmployeeNotAccepted") {}
    };

    /* CitizenAlreadyExists exception :
     * Exception for City class - addEmployee function .
     * Exception for City class - addManager function .
     * - need to be thrown when we try to add a citizen to the city ,
     * - but he is already a citizen in the city .
    */
    class CitizenAlreadyExists : public Exception {
    public :
        CitizenAlreadyExists() : Exception("CitizenAlreadyExists") {}
    };

    /* FacultyAlreadyExists exception :
    * Exception for City class - addFaculty function .
    * - need to be thrown when we try to add a faculty to the city ,
    * - but the faculty is already exists .
    */
    class FacultyAlreadyExists : public Exception {
    public :
        FacultyAlreadyExists() : Exception("FacultyAlreadyExists") {}
    };

    /* WorkplaceAlreadyExists exception :
    * Exception for City class - createWorkplace function .
    * - need to be thrown when we try to add a workplace to the city ,
    * - but there is a workplace with the same Id .
    */
    class WorkplaceAlreadyExists : public Exception {
    public :
        WorkplaceAlreadyExists() : Exception("WorkplaceAlreadyExists") {}
    };

    /* FacultyDoesNotExist exception :
    * Exception for City class - teachAtFaculty function :
    * - need to be thrown when we try to teach in the faculty ,
    * - but is not exists .
*/
    class FacultyDoesNotExist : public Exception {
    public :
        FacultyDoesNotExist() : Exception("FacultyDoesNotExist") {}
    };

    /* EmployeeDoesNotExist exception :
    * Exception for City class - teachAtFaculty function :
     * - need to be thrown when we try to teach in the faculty ,
     * - but the employee we want to be taught is not exist in the city .
    * Exception for City class - HireEmployeeAtWorkplace function :
     * - If the employee that we want to start working in the work place
     * - is not a employee of the city the exception should be thrown .
    * Exception for City class - FireEmployeeAtWorkplace function :
     * - if the employee does not exist in the city this exception will be thrown .
    */
    class EmployeeDoesNotExist : public Exception {
    public :
        EmployeeDoesNotExist() : Exception("EmployeeDoesNotExist") {}
    };

    /* WorkplaceDoesNotExist exception :
      * Exception for City class - teachAtFaculty function :
     * - need to be thrown when we try to teach in the faculty ,
      * - but the workplace we want the employee to be taught is not exist in the city .
     * Exception for City class - hireManagerAtWorkplace function :
      * - Should be thrown if the workplace is not exist in the city .
     * Exception for City class - fireEmployeeAtWorkplace function :
      * if the workplace that we want to fire the employee from is not exists
      * in the city this exception should be thrown .
    *  Exception for City class - fireManagerAtWorkplace function :
     *  if the workplace the want to fire the manager from is not exist in the city
     *  this exception should be thrown .
     */
    class WorkplaceDoesNotExist : public Exception {
    public :
        WorkplaceDoesNotExist() : Exception("WorkplaceDoesNotExist") {}
    };

    /* ManagerDoesNotExist exception :
     * Exception for City class - teachAtFaculty function :
      * - need to be thrown when we try to teach in the faculty
      * - but the manager that the employee is working in his group is not exist in the city .
     * Exception for City class - hireManagerAtWorkplace function :
      * - Should be thrown if the manager we want to hire in workplace is not exist in the city .
     * Exception for City class - fireEmployeeAtWorkplace function :
      * - if the manager of the employee is not exists in the city this exception should be thrown .
    *  Exception for City class - fireManagerAtWorkplace function :
     *  if the manager we want to fire is not exist in the city this exception should be thrown .
     */
    class ManagerDoesNotExist : public Exception {
    public :
        ManagerDoesNotExist() : Exception("ManagerDoesNotExist") {}
    };
}
#endif //MTMEX2_EXCEPTIONS_H
