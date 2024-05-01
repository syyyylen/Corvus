#pragma once
#include "Core.h"

namespace CorvusEngine {

enum class ShaderType
{
    Vertex,
    Pixel,
    Compute
};

struct Shader
{
    ShaderType Type;
    std::vector<uint32_t> Bytecode;
};

class ShaderCompiler 
{
public:
    static void CompileShader(const std::string& path, ShaderType type, Shader& outShader);
};

} // CorvusEngine
