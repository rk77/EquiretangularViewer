#version 330

layout (location = 0) in vec3 position;
out vec3 TexCoord0;
uniform mat4 model;
uniform mat4 view;
uniform mat4 project;

void main()
{
    //gl_Position = model * vec4(position, 1.0f);
    gl_Position = project * view * vec4(position, 1.0f);
    //gl_Position = project * view * model * vec4(position, 1.0f);
    //gl_Position = vec4(position, 1.0f);
    TexCoord0 = position;
}
