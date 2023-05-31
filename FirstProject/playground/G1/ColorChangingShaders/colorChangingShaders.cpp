#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>

#include "../OpenGL_Libraries/Include/ReadShaders/ReadShaders.h"

void framebuffer_size_callback(GLFWwindow* window, int width, int height); //resize viewport

void processInput(GLFWwindow* window); //input control

// settings
const unsigned int width = 800;
const unsigned int height = 600;

std::string vertexShaderCode = readShaderFromFile("vertexShader.vert");
const char* vertexShaderSource = vertexShaderCode.c_str();

std::string fragmentShaderCode = readShaderFromFile("fragmentShader.frag");
const char* fragmentShaderSource = fragmentShaderCode.c_str();


int main()
{
    // GLFW Initialization
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    // Window creation
    GLFWwindow* window = glfwCreateWindow(width, height, "OpenGL_Basic_Engine", nullptr, nullptr);
    if (window == nullptr)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);

    // GLAD Initialization
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    // Defining viewport
    glViewport(0, 0, width, height);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    // Build and compile our shader program
    // Vertex shader
    unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, nullptr);
    glCompileShader(vertexShader);
    // Check for shader compile errors
    int success;
    char infoLog[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(vertexShader, 512, nullptr, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
    }

    // Fragment shaders
    unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, nullptr);
    glCompileShader(fragmentShader);
    // Check for shader compile errors
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(fragmentShader, 512, nullptr, infoLog);
        std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
    }

    // Shader programs
    unsigned int shaderProgram = glCreateProgram(); // Creates a program and returns its ID
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);
    // Check for linking errors
    glGetProgramiv(fragmentShader, GL_LINK_STATUS, &success);
    if (!success)
    {
        glGetProgramInfoLog(shaderProgram, 512, nullptr, infoLog);
        std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
    }

    // Delete the shader objects
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);


    // Set up vertex data. Configure vertex attributes
    float vertices[] = {
        -0.9f, -0.5f, 0.0f,  // bottom left 
        -0.45f, 0.5f, 0.0f,  // top left 
        0.0f, -0.5f, 0.0f,  // bottom mid
        0.9f, -0.5f, 0.0f,  // bottom right
        0.45f, 0.5f, 0.0f   // top right
    };

    unsigned int indices[] = {
        0, 1, 2 // Triangle 1
    };

    unsigned int VBO, VAO, EBO; // Buffers
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);
    glGenVertexArrays(1, &VAO);

    // Initialization code for triangle_1 (done once unless your object frequently changes)
    // 1. Bind Vertex Array Object
    glBindVertexArray(VAO);
    // 2. Copy our vertices array into a buffer for OpenGL to use
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    // 3. Load the Element array buffer
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
    // 4. Set our vertex attributes pointers
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glBindVertexArray(0);

    // Render loop
    while (!glfwWindowShouldClose(window))
    {
        // Input
        processInput(window);

        // Rendering commands
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        //Select my shader program
        glUseProgram(shaderProgram);

        // Animation (updaate uniform color)
        float timeValue = glfwGetTime();
        float greenValue = static_cast<float>(sin(timeValue) / 2.0 + 1.0);
        float redValue = static_cast<float>(sin(timeValue) / 2.0 + 1.5);
        float blueValue = static_cast<float>(sin(timeValue) / 1.5 + 0.5);
        int shaderColorLocation = glGetUniformLocation(shaderProgram, "shaderColor");
        glUniform4f(shaderColorLocation, redValue, greenValue, blueValue, 1.0f);

        //5. TRIANGLES! :D
        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, 0);

        // Check and call events and swap buffers
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

void processInput(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}
