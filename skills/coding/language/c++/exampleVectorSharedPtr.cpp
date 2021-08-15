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
