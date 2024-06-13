#include <fstream>
#include <iostream>
#include <string>
#include <tuple>
#include <vector>

#include "../data_structures/array_stack.h"
#include "../data_structures/array_queue.h"
#include "solutions_utils.h"
#include "solutions.h"

/*
    -------------- Módulo principal --------------
    Cada função corresponde a uma tarefa do trabalho

    validateXml -> questão 1
    computeCleanupArea -> questão 2
*/

static bool validateXml(const std::string& text)
{
    // Função responsável por determinar a validade da sintaxe no arquivo XML

    structures::ArrayStack<std::string> stack{};
    str_size_t currentChar{0};

    while (true) {
        str_size_t openingBracketPos{text.find('<', currentChar)};
        str_size_t closeBracketPos{text.find('>', currentChar)};

        if ((closeBracketPos < openingBracketPos) or  // '>' antes de '<'
           (openingBracketPos == NOT_FOUND and closeBracketPos != NOT_FOUND) or // '>' sem '<'
           (openingBracketPos != NOT_FOUND and closeBracketPos == NOT_FOUND)) { // '<' sem '>'
            return false;
        }
        else if (openingBracketPos == NOT_FOUND and closeBracketPos == NOT_FOUND) { // Fim do arquivo
            break;
        }

        int tagSize{static_cast<int>(closeBracketPos - openingBracketPos) - 1};
        std::string tag{text.substr(openingBracketPos + 1, tagSize)};

        if (tag.find('<') != NOT_FOUND) { // < dentro da tag. Ex: <tag<tag>>
            return false;
        }

        if (tag[0] == '/') { // Tag de fechamento
            std::string endTag{text.substr(openingBracketPos + 2, tagSize - 1)};

            if (stack.top() != endTag) {
                return false;
            }
            stack.pop();
        }
        else {
            stack.push(tag);
        }

        currentChar = closeBracketPos + 1;
    }

    return stack.empty(); // Não sobrou nenhuma tag? Então o XML é válido
}

void computeCleanupAreaXML(const std::string& path)
{
    /*
        Função responsável por computar a área de limpeza do
        robô no arquivo XML presente em "path"
    */

    std::string text{readFile(path)};

    // Antes de mais nada, precisamos ter certeza que o arquivo XML é válido
    if (not validateXml(text)) {
        std::cout << "erro" << '\n';
        return;
    }
    
    while (true) {
        std::string scenario{popTag(text, "cenario")};
        if (scenario == "") {
            break;
        }

        std::cout << popTag(scenario, "nome") << " ";
        int height{std::stoi(popTag(scenario, "altura"))};
        int width{std::stoi(popTag(scenario, "largura"))};
        int initialX{std::stoi(popTag(scenario, "x"))};
        int initialY{std::stoi(popTag(scenario, "y"))};

        std::string matrixStr{popTag(scenario, "matriz")};
        std::vector<std::vector<int>> matrix{strToMatrix(matrixStr, height, width)};
        std::cout << computeMatrixArea(matrix, height, width, initialX, initialY) << '\n';
    }
}
