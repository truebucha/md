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

