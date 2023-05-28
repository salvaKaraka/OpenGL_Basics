#ifndef READ_SHADERS_H
#define READ_SHADERS_H

#include "ReadShaders.h"
#include <fstream>
#include <sstream>
#include <iostream>

std::string readShaderFromFile(const std::string& filePath)
{
    std::ifstream shaderFile;
    std::stringstream shaderStream;

    // Verificar si podemos abrir el archivo
    shaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    try
    {
        shaderFile.open(filePath);
        shaderStream << shaderFile.rdbuf();
        shaderFile.close();
    }
    catch (std::ifstream::failure& e)
    {
        std::cout << "Error al leer el archivo shader: " << filePath << std::endl;
    }

    return shaderStream.str();
}

#endif