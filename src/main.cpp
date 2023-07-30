#include <iostream>
#include <memory>
#include <ncurses.h>

#include "MathParser.hpp"
#include "MathFunctionGraphConsole.hpp"

int main(int argc, char *argv[])
{
    VectorState *pointer = nullptr;
    double unit;
    while (true)
    {
        system("clear"); //TODO cross platform

        std::cout << "\033[106m\033[97m Insert a f(x) : \033[39m\033[49m" << std::endl;
        std::string raw;
        std::cin >> raw;
        MathParser expression(raw);
        auto f = [&](double x)
        {
            return expression.evaluateFunctionInX(x);
        };
        if (pointer == nullptr)
        {
            std::cout << "\033[41m\033[97m Insert a unit : \033[39m\033[49m" << std::endl;
            while (!(std::cin >> unit))
            {
                std::cin.clear();
                std::cin.ignore(2147483647, '\n');
                std::cout << "[X] Invalid input: pls provide a decimal number...\n";
            }
            pointer = mfgc::graph(25, unit, f);
        }
        else
        {
            mfgc::graph(25, unit, f, pointer);
        }

        // std::cout << "f(2)" << expression.evaluateFunctionInX(2) << std::endl;

        std::cout << "\nDo you want to add?:";
        char in;
        std::cin >> in;
        if (in != 'y' && pointer != nullptr) {
            delete[] pointer;
            pointer = nullptr;
        }
    }
    return 0;
}