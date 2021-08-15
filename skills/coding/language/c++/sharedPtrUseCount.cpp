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
