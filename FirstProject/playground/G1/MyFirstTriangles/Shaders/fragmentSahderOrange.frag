#version 330 core
out vec4 FragColor;

in vec4 vertexColorOrange;

void main()
{
    FragColor = vertexColorOrange;
} 