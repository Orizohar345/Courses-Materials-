//
// Created by Ori Zohar on 6 ינו׳ 2022.
//

#ifndef SKILL_CPP_TEMPLATES_H
#define SKILL_CPP_TEMPLATES_H
#include <iostream>
#include <memory>

namespace mtm {
template<class T>
class shared_ptr_Comparison
{
    int Id ;
public :
    explicit shared_ptr_Comparison(int id ) : Id(id) {}
    bool operator()(const std::shared_ptr<T> t)
    {
        return (t.get())->getId() == Id;
    }
};

template<class T>
class IdComparation
{
    int Id ;
public :
    explicit IdComparation(int id ) : Id(id) {}
    bool operator()(const T* t)
    {
        return t->getId() == Id;
    }
};
}
#endif //SKILL_CPP_TEMPLATES_H
