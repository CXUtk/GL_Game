#version 330 core
out vec4 f_color;

in vec3 ourColor;
in vec2 TexCoord;

uniform sampler2D ourTexture;

void main()
{
    f_color = texture(ourTexture, TexCoord);
}