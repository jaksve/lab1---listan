#include<iostream>
#include "List.h"
#define CATCH_CONFIG_MAIN
#include "catch.hpp"

TEST_CASE( "Create list" )
{

List lst{1,4,2,6,8,9};

CHECK(lst.at(2) == 2);
CHECK(lst.size() == 6);
List l2;
l2 = lst;
CHECK(l2.size() == lst.size());
CHECK(l2.front() == lst.front());
CHECK(l2.back() == lst.back());

CHECK(l2.back() == 9);
CHECK(l2.size() == 6);
CHECK(l2.at(0) == 1);

l2.push_back(6);
CHECK(l2.back() == 6);
l2.push_front(11);
CHECK(l2.front() == 11);
CHECK(!l2.empty());

List lst2{3,5,7};
l2 = std::move(lst2);
CHECK(l2.at(0) == 3);
CHECK(l2.size() == 3);
l2.at(0) = 15;
CHECK(l2.at(0) == 15);

l2.swap(lst);

CHECK(l2.at(0) == 1);
CHECK(lst.at(0) == 15);

for(auto it = lst.begin();it != lst.end();++it)
{
    std::cout<< *it <<std::endl;
}

}
