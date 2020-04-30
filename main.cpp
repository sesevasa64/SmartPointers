#include <iostream>
#include <memory>
#include <string>
#include <utility>
#include "lib/UniquePtr.h"
#include "lib/SharedPtr.h"
using namespace std;

class Person {
private:
    string name;
    int age;
public:
    Person() = delete;
    ~Person() {
        cout << "Calls destructor" << endl;
    }
    Person(string name, int age) : name(move(name)), age(age) {}
    string Hello() {
        return "Hello, World!";
    }
    friend ostream& operator<<(ostream& os, const Person& person);
};

ostream& operator<<(ostream& os, const Person& person)
{
    os << "Name: " << person.name << '\n';
    os << "Age: " << person.age << '\n';
    return os;
}

int main() {
    {
        auto a(makeShared<int>(5));
    }
    cout << endl;
    {
        SharedPtr<int> a(new int(3));
        SharedPtr<int> b(a);
        SharedPtr<int> c = b;
        b = makeShared<int>(5);
        auto d = makeShared<int>(5);
        auto e = makeShared<int[5]>();
    }
    cout << endl;
    {
        UniquePtr<int[]> ptr(new int[6]);
        ptr = makeUnique<int[]>(1, 2, 3);
        ptr = makeUnique<int[100]>();
        ptr[3] = 5;
        cout << ptr[3] << endl;
    }
    cout << endl;
    {
        auto uptr = make_unique<int>(42);
        auto uptr2(make_unique<int>(42));
        auto uptr3 = move(uptr2);
        unique_ptr<int[]> ptr5(new int[4]{0, 1, 2, 3});
        cout << *(ptr5.get() + 1) << endl;
        ptr5 = make_unique<int[]>(54);
        auto ptr(makeUnique<int>(2));
        cout << *ptr << endl;
        auto ptr2 = move(ptr);
        cout << *ptr2 << endl;
    }
    cout << endl;
    {
        auto ptr = makeUnique<int>(5);
        ptr.Reset(new int(7));
        cout << *ptr.Get() << endl;
    }
    cout << endl;
    {
        int *p = new int(3);
        unique_ptr<int> ptr(p);
        cout << *p << endl;
        ptr = make_unique<int>(5);
        cout << *p << endl;
    }
    cout << endl;
    {
        int *source = new int(9);
        UniquePtr<int> ptr(source);
        ptr = makeUnique<int>(3);
        UniquePtr<int> ptr2;
        cout << *source << endl;
        cout << *ptr.Get() << endl;
    }
    cout << endl;
    {
        UniquePtr<int> ptr(new int(3));
        auto data = ptr.Get();
        cout << *data << endl;
    }
    cout << endl;
    {
        auto ptr = makeUnique<int*>(new int[3] {1,2,3});
        int** data = ptr.Get();
        for(int i = 0; i < 3; i++) {
            cout << (*data)[i] << endl;
        }
    }
    cout << endl;
    {
        auto ptr = makeUnique<Person>("Name", 40);
        auto data = ptr.Get();
        cout << *data << endl;
        auto ptr2 = makeUnique<Person*>(new Person[2] {{"2", 3}, {"1", 2}});
    }
    cout << endl;
    {
        UniquePtr<int> ptr(nullptr);
    }
    cout << endl;
    {
        auto ptr = makeUnique<int>(228);
        auto *release = ptr.Release();
        cout << *release << endl;
    }
    cout << endl;
    {
        auto ptr = make_unique<Person>("Ivan", 228);
        auto ptr2 = makeUnique<Person>("Ivan", 229);
        auto ptr3 = make_unique<int>(2);
        auto ptr4 = makeUnique<int>(2);
        cout << ptr2->Hello() << endl;
        cout << ptr->Hello() << endl;
    }
    return 0;
}
void TestStdUniquePtr() {
    /*unique_ptr<int> a(new int(3));
    unique_ptr<int> b = make_unique<int>(3);
    unique_ptr<int> e;
    e = make_unique<int>(3);
    int*&& data = e.get();
    delete data;
    data = new int(5);
    cout << *(e.get()) << endl;
    int* res = a.get();
    //delete res;
    cout << *res << endl;
    unique_ptr<Person> c(new Person{"Vasya", 40});
    unique_ptr<Person> d = make_unique<Person>(Person{"Vasya", 40});
    cout << *(c.get()) << endl;
    int *h = new int(3);
    cout << h << endl;
    {
        //auto ptr = make_unique<int>(*h);
        unique_ptr<int> ptr(h);
        cout << (ptr.get()) << endl;
        ptr = make_unique<int>(9);
        cout << (ptr.get()) << endl;
        cout << *(ptr.get()) << endl;
        cout << *h << endl;
    }
    cout << *h << endl;
    delete h;*/
}