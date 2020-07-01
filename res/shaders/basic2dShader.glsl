#shader vertex
#version 410

layout(location = 0) in vec2 position;

void main()
{
    gl_Position = vec4(position, 1.0, 1.0);
}

#shader fragment
#version 410

out vec4 FragColor;

void main()
{
    FragColor = vec4(1.0, 0.0, 0.0, 1.0);
}