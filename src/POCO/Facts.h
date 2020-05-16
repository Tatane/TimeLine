#ifndef FACTS_H
#define FACTS_H

#include "POCO/Fact.h"
#include <vector>

class Facts
{
public:
    Facts();
    std::vector<Fact*> * getVecFacts();
    void add(Fact * fact);
    void erase(int index);

    Fact* & operator[](int index);
    size_t size() const;

private:
    std::vector<Fact*> vecFacts;
};

#endif // FACTS_H
