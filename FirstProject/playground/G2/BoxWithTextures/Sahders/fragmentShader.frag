#version 330 core
out vec4 FragColor;

in vec3 shaderColor;
in vec2 texCoord;

uniform sampler2D container_texture;
uniform sampler2D emoji_texture;

uniform float mixValue;

void main()
{
    FragColor = mix(texture(container_texture, texCoord), texture(emoji_texture, vec2(-texCoord.x,texCoord.y)), mixValue);
}