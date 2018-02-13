#include "display.h"

using namespace std;

Display::Display(){
    settings.majorVersion = 3;
    settings.minorVersion = 3;
    settings.depthBits = 24;
}
Display::~Display(){

}
void Display::render(int width, int height){
    sf::RenderWindow window(sf::VideoMode(width, height), "Opengl", sf::Style::Default, settings);
    window.setActive(true);
    
    glewExperimental = true;
    result = glewInit();

    if(result != GLEW_OK){
        cout << endl << "Glew failed to initialize : " << glewGetErrorString(result) << endl;
    }

    float vertices[] = {-0.5,-0.5,0.0,0.0,0.5,0.0,0.5,-0.5,0.0};

    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glGenVertexArrays(2, &vao);
    glBindVertexArray(vao);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (GLvoid*)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, (GLvoid*)0);
    glEnableVertexAttribArray(1);

    string vertexShaderText = loadFileContents("vertex.glsl");
    string fragmentShaderText = loadFileContents("fragment.glsl");

    unsigned int shaderProgram = CreateShaderProgram(vertexShaderText.c_str(), fragmentShaderText.c_str());
    glUseProgram(shaderProgram); 

    while(window.isOpen()){
        sf::Event e;
        while(window.pollEvent(e)){
            if(e.type == sf::Event::Closed)
                window.close();
        }

        glClearColor(0.1f, 0.1f, 0.2f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        glDrawArrays(GL_TRIANGLES, 0, 3);

        window.display();
    }
}

unsigned int Display::CreateShaderProgram(const GLchar* vertexShaderText, const GLchar* fragmentShaderText){
    unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
    unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    unsigned int shaderProgram = glCreateProgram();

    glShaderSource(vertexShader, 1, &vertexShaderText, NULL);
    glCompileShader(vertexShader);

    //Fragment Shader Compile status
    GLint success;
    GLchar infoLog[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if(!success){
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        cerr << endl << "Vertex Shader Compilation failed : \n" << infoLog << endl;
    }

    glShaderSource(fragmentShader, 1, &fragmentShaderText, NULL);
    glCompileShader(fragmentShader);

    //Fragment Shader Compile status
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if(!success){
        glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
        cerr << endl << "Fragment Shader Compilation failed : \n" << infoLog << endl;
    }

    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);

    glLinkProgram(shaderProgram);

    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if(!success){
        glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
        cerr << endl << "Program failed to link : " << endl << infoLog; 
    }


    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    return shaderProgram;
}

std::string Display::loadFileContents(const std::string filepath){
    std::ifstream file(filepath);
    std::stringstream sstream;

    if(!file.is_open())
        std::cout << "\nUnable to open file : " << filepath << endl;
    
    sstream << file.rdbuf();

    return sstream.str();
}