#ifndef RESOURCE_MANAGER_H
#define RESOURCE_MANAGER_H

#include <map>
#include <string>
#include <glad/glad.h>
#include "Texture.h"
#include "Shader.h"

// A static singleton resource manager class that hosts serveral functions to load textures and shaders.
// Each loaded textures and shaders is also stored for future reference by string handles.
// All functions and resources and static and no public constructor is defined.
class ResourceManager
{
public:
    // resource storage
    static std::map<std::string, Shader> Shaders;
    static std::map<std::string, Texture2D> Textures;
    // loads (and generates) a shader program from file loading vertex, fragment (and geometry) shader's source code.
    // if gShaderFile is not null ptr, is also loads a geometry shader
    static Shader LoadShader(const char *vShaderFile, const char *fShaderFile, const char *gShaderFile, std::string name);
    // retrieves a stored shader
    static Shader GetShader(std::string name);
    // loads (and generates) a texture from file
    static Texture2D LoadTexture(const char *file, bool alpha, const std::string name);
    // retrieves a stored texture
    static Texture2D GetTexture(const std::string& name);
    // properly de-allocates all loaded resources
    static void Clear();
private:
    // private constructor, that is we do not want any actual resource manager objects.
    // Its memnbers and functions should be publicly available (static)
    ResourceManager() {};
    // loads and generates a shader from file
    static Shader loadShaderFromFile(const char *vShaderFile, const char *fShaderFile, const char *gShaderFile = nullptr);
    // load a single texture from file
    static Texture2D loadTextureFromFile(const char *file, bool alpha);
};


#endif // !RESOURCE_MANAGER_H
