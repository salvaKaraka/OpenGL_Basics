#ifndef READSHADERS_H_INCLUDED
#define READSHADERS_H_INCLUDED

#include <fstream>
#include <string>

std::string readShaderFromFile(const std::string& filePath)
{
    std::ifstream file(filePath);
    std::string shaderCode;

    if (file)
    {
        std::string line;
        while (std::getline(file, line))
        {
            shaderCode += line + "\n";
        }
    }
    else
    {
        std::cout << "Failed to open file: " << filePath << std::endl;
    }

    return shaderCode;
}

#endif // READSHADERS_H_INCLUDED