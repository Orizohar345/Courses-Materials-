
#ifndef MTMEX2_CITIZEN_H
#define MTMEX2_CITIZEN_H
#include <iostream>
#include <string>

namespace mtm {
    /*
 * Our Citizen class;
 * Abstract Class for a citizen in the city .
 *  - Id: the citizen's ID .
 *  - FirstName: the citizen's first name .
 *  - LastName: the citizen's last name.
 *  - BirthYear  the citizen's bearth year .
 */
    class Citizen {
        int Id;
        std::string FirstName;
        std::string LastName;
        int BirthYear;

    public :
        //Constructors:
        Citizen() = default;
        Citizen(int id, const std::string &first_name, const std::string &last_name, int birth_year)
                : // may make aloocation problem
                Id(id), FirstName(first_name), LastName(last_name), BirthYear(birth_year) {}

        /* Destructor:
         * virtual destructor because its abstract class and may be inheriting in the future .
        */
        virtual ~Citizen() = default;

        //Default copy constructor :
        Citizen(const Citizen &citizen) = default;

        //Assignment operator:
        Citizen &operator=(const Citizen &citizen) = default;

        // Getters  for FirstName , LastYear and BirthYear .
        int getId() const;
        std::string getFirstName() const;
        std::string getLastName() const;
        int getBirthYear() const;

        /* Getter for Salary :
         * Its virtual function and the heirs should implement it .
         * Returns the salary of the citizen .
        */
        virtual int getSalary() const =0 ;

        /* Friend Operators of Citizen :
         * the operator will return true or false if the Id
         * of one citizen is smaller (for <) or equal (for == ) than the other citizen.
         */
        friend bool operator<(const Citizen &citizen1, const Citizen &citizen2);
        friend bool operator==(const Citizen &citizen1, const Citizen &citizen2);

        /* printShort and printLong :
         * Both function print a description of the citizen to the chosen ostream .
         * For limited description -> printShort .
         * For Full description -> printLong .
         * in Citizen class both function are pure virtual and this function will be implemented by the heirs .
         */
        virtual std::ostream &printShort(std::ostream &os) = 0;
        virtual std::ostream &printLong(std::ostream &os)  = 0;

        /* Clone function :
         * Pure virtual function and the heirs must implement it .
         * allocate a new copy of this and returns pointer to the new copy .
         */
        virtual Citizen* clone() const = 0  ;
    };

    /* Rest operators of the class :
     * Returns true or false if the first citizen's Id is < , <= , >= , < from the the second citizen's Id .
     */
    bool operator>(const Citizen& citizen1 ,const Citizen& citizen2);
    bool operator<=(const Citizen& citizen1 ,const Citizen& citizen2);
    bool operator>=(const Citizen& citizen1 ,const Citizen& citizen2 );
    bool operator<(const Citizen &citizen1, const Citizen &citizen2);
    bool operator==(const Citizen &citizen1, const Citizen &citizen2);
}

#endif //MTMEX2_CITIZEN_H