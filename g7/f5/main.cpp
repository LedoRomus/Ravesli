#include <iostream>

int factorial(int n)
{
    if(n==1)
        return 1;
    else
        return factorial(n-1)*n;
}

int main()
{
   std::cout<<factorial(4)<<std::endl;

    return 0;
}
