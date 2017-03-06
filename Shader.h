#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <GL/glew.h>


class Shader
{
public:
    GLuint Program;
    GLuint uniformObj;
    // Constructor generates the shader on the fly
    Shader(GLchar* vertexPath, GLchar* fragmentPath);

    void Use();
    GLuint getUniform(GLchar* name);
};
