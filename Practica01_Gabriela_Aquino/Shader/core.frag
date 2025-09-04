#version 330 core
in vec3 ourColor;
out vec4 color;

uniform bool useSolidColor;  // true = usar solidColor; false = usar ourColor
uniform vec3 solidColor;     // color fijo (p.ej. rojo, blanco, etc.)

void main()
{
    vec3 c = useSolidColor ? solidColor : ourColor;
    color = vec4(c, 1.0);
}