#shader vertex
#version 330 core

layout(location = 0) in vec4 position;

void main()
{
   gl_Position = position;
};

#shader fragment
#version 330 core

layout(location = 0) out vec4 color;

uniform vec4 u_Color; //u_ prefix ids a uniform. two things that matter is type of uniform and the name

void main()
{
   color = u_Color;
};