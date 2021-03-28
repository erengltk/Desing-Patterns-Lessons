#include<iostream>
#include<cstdio>
#include<string>
#include<vector>
#include<tuple>
#include<memory>
#include <string>
#include <iostream>
#include <memory>
#include <functional>
#include <boost/serialization/serialization.hpp>
#include <boost/archive/binary_iarchive.hpp>
#include <boost/archive/binary_oarchive.hpp>
#include <sstream>
using namespace std;

struct Address
{
    string street,city;
    int suite;
    Address(const string &street,const string &city,int suite): street(street),city(city),suite(suite){}
    friend ostream &operator<<(ostream &os, const Address *address)
    {
        os<<"street: "<<address->street<<" city: "<<address->city<<" suite: "<<address->suite;
        return os;

    }
};
struct Contact
{
    string name;
    Address *address;
    Contact(const string &name, Address *adress ) :name(name), address(adress) {}
    Contact(const Contact &other)
    : name{other.name},address{new Address{other.address->street,other.address->city,other.address->suite}}
    {

    }
    friend ostream &operator<<(ostream &os, const Contact &contact)
    {
        os<<" name: "<<contact.name<<" address: "<<contact.address;
        return os;
    }
    ~Contact(){ delete address;};
};
int main()
{
    Contact Kane{"Kane",new Address{"street name X","Chesterfield",25}};
    //Contact Jamie{"Jamie",Address{"street name X","Chesterfield",54}};
  //  Contact Jamie= Kane; //shallow copy
    Contact Jamie{Kane};//deep copy
    Jamie.name="Jamie";
    Jamie.address->suite=54;
    cout<<Kane<<"\n"<<Jamie;

}
