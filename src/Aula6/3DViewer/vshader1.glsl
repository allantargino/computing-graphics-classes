# version 400
layout (location = 0) in vec4 vPosition;
layout ( location = 1) in vec3 normal;

uniform mat4 model;
out vec4 v2fcolor;

void main ()
{
    v2fcolor = vec4(abs(normal),1);
    gl_Position = model * vPosition;
}
