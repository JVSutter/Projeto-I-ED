#include <iostream>
#include <string>

#include "solutions.h"

int main()
{
    std::string xmlPath{};
    std::cin >> xmlPath;  // Arquivo de entrada
    
    if (not validateXml(xmlPath)) {
        std::cout << "erro" << '\n';
        return 1;
    }

    calculateCleanupArea(xmlPath);

    return 0;
}
