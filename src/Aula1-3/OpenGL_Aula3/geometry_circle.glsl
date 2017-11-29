#version 400

layout (points) in;
layout (line_strip) out;
//layout (points) out;
layout (max_vertices = 100) out;

in vec3 vs_color[];
out vec3 fs_color;

void main()
{
    int i;
    for(i = 0;i < gl_in.length();i++)
    {
        fs_color = vs_color[i];
        //gl_PointSize = 20.0;
        gl_Position = gl_in[i].gl_Position;
        //EmitVertex();

        float radius = 0.5;
        //float divisions = 5;
        //float angle = 360 / divisions;

        float x = gl_Position.x;
        float y = gl_Position.y;
        float z = gl_Position.z;

        for(float j = 0; j <= 6.28 ; j+=0.628)  //generate vertices at positions on the circumference from 0 to 2*pi
        {
            gl_PointSize = 3.0;
            gl_Position = gl_Position + vec4(x+ radius*cos(j), y + radius*sin(j), z, 1.0);   //circle parametric equation
            EmitVertex();
        }

        EndPrimitive();
    }
    //EndPrimitive();
}
