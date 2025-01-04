#include "RPN.hpp"

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        std::cerr << "must add 2 arguments";
        return (1);
    }
    try
    {
        RPN rpn = RPN(argv[1]);
        std::cout << rpn.getResult() << std::endl;
    }
    catch (const std::exception& e) {
        std::cerr << e.what() << '\n';
    }
    return (0);
}
