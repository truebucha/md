#include <iostream>
#include <string>
#include <memory>

void change(std::string str3)
{
    // this will affect only local copy
    str3.replace(1, 1, "45");
    std::cout <<  "1 " << str3 << "\r\n";
}


int main()
{
    std::string str1("test");
    auto str2 = str1;
    std::cout << str1 << "\r\n";
    
    // this will affect only str2
    str2.replace(1, 1, "23");
    std::cout << str1 << "\r\n";
    
    change(str1);
    std::cout << str1 << "\r\n";
    
    std::cout << str2 << "\r\n";
}
