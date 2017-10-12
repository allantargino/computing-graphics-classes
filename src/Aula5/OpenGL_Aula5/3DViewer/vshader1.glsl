# version 400
layout ( location = 0) in vec4 vPosition;

uniform mat4 model;
out vec4 v2fcolor;

void main ()
{
    gl_Position = model * vPosition ;
    float gray = ( gl_Position .y + 1) *0.5;
    v2fcolor = vec4 ( gray ,gray ,gray ,1);
}
