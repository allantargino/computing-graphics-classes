# version 400
layout (location = 0) in vec4 vPosition;

uniform mat4 model;
out vec4 v2fcolor;

void main ()
{
    gl_Position = model * vPosition ;
    float position = gl_Position.y + 1;
    float r = position * 0.5;
    float g = position * 0.5;
    float b = position * 0.5;
    v2fcolor = vec4 (r, g, b, 1);
}
