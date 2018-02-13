#pragma once

#include <iostream>
#include <SFML/Graphics.hpp>
#include <GL/glew.h>
#include <string>
#include <sstream>
#include <fstream>

class Display{
    private:
        sf::ContextSettings settings;
        GLenum result;
        GLuint vbo;
        GLuint vao;
    public:
        Display();
        void render(int width, int height);
        unsigned int CreateShaderProgram(const GLchar* vertexShaderText, const GLchar* fragmentShaderText);
        std::string loadFileContents(const std::string filepath);
        ~Display();
};