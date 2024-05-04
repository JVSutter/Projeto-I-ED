#include <iostream>
#include <string>

#include "solutions.h"

int main()
{
    std::string xmlPath{};
    std::cin >> xmlPath;  // Arquivo de entrada

    computeCleanupArea(xmlPath);

    return 0;
}
