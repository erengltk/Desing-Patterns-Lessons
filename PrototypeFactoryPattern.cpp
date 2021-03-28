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
struct EmployeeFactory
{
    static unique_ptr<Contact> new_main_office_employee(const string &name,const int suite)
    {
        static Contact p{"",new Address{"123 east dr","London",0}};
        return new_employee(name,suite,p);
    }
private:
    static unique_ptr<Contact> new_employee(const string &name, const int suite,
    const Contact & prototype)
    {
        unique_ptr<Contact> result =make_unique<Contact>(prototype);
   //   unique_ptr<int> p = make_unique<int>(42);
        result->name=name;
        result->address->suite=suite;
        return result;

    }
};

int main()
{
    unique_ptr<Contact> Kane= EmployeeFactory::new_main_office_employee("Kane",45);
    cout<<*Kane<<"\n";;

}
