#pragma once
#include <unordered_map>
#include <vector>
#include <string>

using byte = unsigned char;
using HuffMap = std::unordered_map<byte, std::vector<bool>>;

HuffMap huffmanCoding(const std::string& str);
