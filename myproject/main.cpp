#include <iostream>
#include <cstdlib>
int main(int argc, char** argv)
{
    int a = atoi(argv[1]);
    int b = atoi(argv[2]);
    std::cout << a + b << std::endl;
    return 0;
}