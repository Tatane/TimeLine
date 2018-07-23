#include "Facts.h"

Facts::Facts()
{

}

std::vector<Fact *> *Facts::getVecFacts()
{
    return &vecFacts;
}

void Facts::add(Fact *fact)
{
    vecFacts.push_back(fact);
}

void Facts::erase(int index)
{
    vecFacts.erase(vecFacts.begin() + index);
}

Fact* & Facts::operator[](int index)
{
    return vecFacts[index];
}

size_t Facts::size() const
{
    return vecFacts.size();
}
