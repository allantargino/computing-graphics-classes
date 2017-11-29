#version 400

layout (points) in;
layout (points) out;
layout (max_vertices = 1) out;

in vec3 vs_color[];
out vec3 fs_color;

void main()
{
    int i;
    for(i = 0;i < gl_in.length();i++)
    {
        fs_color = vs_color[i];
        gl_PointSize = 20.0;
        gl_Position = gl_in[i].gl_Position;
        EmitVertex();
    }
    EndPrimitive();
}
