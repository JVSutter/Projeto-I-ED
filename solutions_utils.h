#ifndef SOLUTIONS_UTILS_H
#define SOLUTIONS_UTILS_H

using str_size_t = std::string::size_type;
using matrix_size_t = std::vector<std::vector<int>>::size_type;

constexpr str_size_t NOT_FOUND{std::string::npos};

std::string readFile(const std::string& path);
std::string popTag(std::string& text, const std::string& tag);
std::vector<std::vector<int>> strToMatrix(const std::string& str, const int& height, const int& width);
int computeMatrixArea(std::vector<std::vector<int>>& matrix, const int& height,
                      const int& width, const int& initialX, const int& initialY);

#endif
