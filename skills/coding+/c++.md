
#variables naming

I use:

* m for members
* c for constants/readonlys
* p for pointer (and pp for pointer to pointer)
* v for volatile
* s for static
* i for indexes and iterators
* e for events
* w for witnesses
* r for reducers

# Good links

<https://www.geeksforgeeks.org/copy-constructor-in-cpp/>

<https://docs.microsoft.com/en-us/cpp/cpp/how-to-create-and-use-shared-ptr-instances?view=vs-2019>

# Interesting things

## Templates

<https://www.codeproject.com/Articles/257589/An-Idiots-Guide-to-Cplusplus-Templates-Part-1#DefArgClassTempl>

## Inheritance

### copy constructor

<https://www.geeksforgeeks.org/copy-constructor-in-cpp/>

### class variables 

in case you define same class member variable as in base class -> there will be 2 instances, one in the base class, one in the derived class.

pointer to the base class will return instance in the base class, pointer to the derived class will return instance of the derived class.

### class functions

in case you define overriden function in a base class without "virtual" keyword -> there will be two instances of such func

one in the base class, one in the derived class.

pointer to the base class will call instance of the base class, pointer to the derived class will call instance of the derived class.

the better way is to use "virtual" in the base class and "override" in the derived class. "override" will fail compiler in case function in a base class not defined with "virtual".

### slicing 

```
  Derived derived;

 vector<Base> vect;
 vect.push_back(derived);
 vect[0].identify();  // <= calls Base class identify func;
```

<https://stackoverflow.com/questions/8777724/store-derived-class-objects-in-base-class-variables>

You are storing object of Derived class in an vector which is supposed to store objects of Base class, this leads to Object slicing and the derived class specific members of the object being stored get sliced off, thus the object stored in the vector just acts as object of Base class.

Solution:

You should store pointer to object of Base class in the vector:

`vector<Base*>`

```
// Example program
#include <iostream>
#include <string>

#include <memory>
#include <vector>

struct A
{
    A(int i) : m_i(i)
    {
    }
    ~A()
    {
         std::cout << "dealloc A: " << m_i << ";\r\n";
    }
    int getI() const
    {
        return m_i;
    }
    void setI(int i) 
    {
        m_i = i;
    }
    
    private:
    int m_i = 0;
};

void print(std::vector<std::shared_ptr<A const>> const vector)
{
  for (auto iA = vector.begin(); iA != vector.end(); iA++) {
  
    std::cout << (*iA)->getI() << "; ";
  }
}

int main()
{
    
  std::vector<std::shared_ptr<A const>> vector;
  
  vector.push_back(std::make_shared<A>(1));
  vector.push_back(std::make_shared<A>(2));
  vector.push_back(std::make_shared<A>(3));
  vector.push_back(std::make_shared<A>(4));
  
//   vector[0]->setI(3);
  vector[0] = std::make_shared<A>(3);
  print(vector);
}
```
```
struct Object
{
  virtual std::string description() const {  };
};

struct Event : public Object
{
  
};

struct MyEvent : public Event
{
  std::string description() const override { };
};

main 
{


    std::vector<std::shared_ptr<Event>> events;
    for (auto pEvent : events)
    {
        ParameterAssert_NotNullPtr(pEvent, "EventsQueue::proceed pEvent nullptr");
        auto event = *(pEvent.get());

        Lss(pEvent->description()); // will call MyEvent::description();
        Lss(event.description()); // will call Object::description();
        Ll("event");
    }
}
```
```
// Example program
#include <iostream>
#include <string>

#include <memory>
#include <vector>

struct A
{
    A(int i) : m_i(i)
    {
    }
    ~A()
    {
         std::cout << "dealloc A: " << m_i << ";\r\n";
    }
    int getI() const
    {
        return m_i;
    }
    void setI(int i) 
    {
        m_i = i;
    }
    
    private:
    int m_i = 0;
};

void print(std::vector<std::shared_ptr<A const>> const vector)
{
  for (auto iA = vector.begin(); iA != vector.end(); iA++) {
  
    std::cout << (*iA)->getI() << "; ";
  }
}

int main()
{
    
    std::shared_ptr<A const> const pAConst = std::make_shared<A>(1);
    //pAConst = std::make_shared<A>(2); //error: discards qualifiers [-fpermissive]
    std::shared_ptr<A const> pBConst = std::make_shared<A>(2);
    pBConst = std::make_shared<A>(3);
    pBConst = pAConst;
    
    
    std::shared_ptr<A> const pA = std::make_shared<A>(11);
    // pA = std::make_shared<A>(2); //error: discards qualifiers [-fpermissive]
    std::shared_ptr<A> pB = std::make_shared<A>(12);
    pB = std::make_shared<A>(13);
    pB = pA;
    
    // pB = pBConst; //error: invalid conversion from 'const A*' to 'A*
    pBConst = pA;
    
    std::shared_ptr<A const> pC = std::make_shared<A>(11);
    
    // pA = pC; // error: discards qualifiers [-fpermissive] and error: invalid conversion from 'const A*' to 'A*' [-fpermissive]
    // pAConst = pC; // error: discards qualifiers [-fpermissive]
    
    std::shared_ptr<A const> const pCConst = std::make_shared<A>(11);
    
    // pA = pCConst // error: discards qualifiers [-fpermissive] and error: invalid conversion from 'const A*' to 'A*' [-fpermissive]
    // pAConst = pCConst; // error: discards qualifiers [-fpermissive]
}
```
```
#include <iostream>
#include <string>
#include <memory>

struct A
{
    A(int a) : m_a(a){}
    ~A() { std::cout << "dealloc: " << m_a << "\r\n"; }
    void setA(int a) { m_a = a; }
    int getA() const { return m_a; }
private:
    int m_a = 0;
};

struct B 
{
    B(std::shared_ptr<A const> const pA) : mp_a(pA){}
    std::shared_ptr<A const> const getPA() const { return mp_a; }
    int refCount() const { return mp_a.use_count(); };
private:
    std::shared_ptr<A const> mp_a = nullptr;
};



int main()
{
  auto pA = std::make_shared<A>(4);
  
  std::cout << "1) " << "_" << " "<< pA.use_count() << "\n\r";
  
  auto b = std::make_shared<B>(pA);
  
  std::cout << "2) " << "_" << " "<< pA.use_count() << "\n\r";
  
  // we increment ref count make a copy each time when passing pointer by value here "b->getPA() or using ="
  auto bPA1 = b->getPA();
  std::cout << "3) " << b->refCount() << " "<< pA.use_count() <<  " " << bPA1.use_count() << "\n\r";
  
  // we increment ref count make a copy each time when passing pointer by value here "b->getPA() or using ="
  auto bPA2 = bPA1;
  std::cout << "4) " << b->refCount() << " "<< pA.use_count() <<  " " << bPA1.use_count() << "\n\r";
  
  // we increment ref count make a copy each time when passing pointer by value here "b->getPA() or using ="
  auto bPA3 = bPA1;
  std::cout << "5) " << b->refCount() << " "<< pA.use_count() <<  " " << bPA3.use_count() << "\n\r";
  
  // we increment ref count make a copy each time when passing pointer by value here "b->getPA() or using = or copy constructor"
  
  auto bPA4(bPA1);
  std::cout << "6) " << b->refCount() << " "<< pA.use_count() <<  " " << bPA4.use_count() << "\n\r";
  
  // each copy knows exact references count of a resource
}
```







