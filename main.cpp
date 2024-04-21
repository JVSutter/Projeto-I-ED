#include <iostream>
#include <string>

#include "xml_validation.h"

int main()
{
    std::string xmlPath{};
    std::cin >> xmlPath;  // Arquivo de entrada
    
    if (not validateXml(xmlPath)) {
        std::cout << "output=erro" << '\n';
        return 1;
    }

    return 0;
}
