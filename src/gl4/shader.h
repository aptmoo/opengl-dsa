#ifndef SHADER_H
#define SHADER_H
#include <string>

/**
 * @brief Shader class. Tthat's all.
 * 
 */
class Shader
{
private:
    unsigned int m_ID;
public:
    // TODO: file parsing
    /**
     * @brief Construct a shader from source strings.
     * 
     * @param vs_source 
     * @param fs_source 
     */
    Shader(const std::string& vs_source, const std::string& fs_source);

    /**
     * @brief Delete this shader.
     * 
     */
    void Delete();
};

#endif