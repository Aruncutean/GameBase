#version 100

attribute vec3 aPos;  // Poziția vertex-ului
attribute vec2 aTexCoord;  // Coordonatele de textură

varying vec2 TexCoord;  // Transmitem coordonatele de textură la fragment shader

uniform mat4 model;  // Matricea model
uniform mat4 view;   // Matricea view
uniform mat4 projection;  // Matricea de proiecție

void main()
{
    // Calculăm poziția finală a vertex-ului
    gl_Position = projection * view * model * vec4(aPos, 1.0);
    TexCoord = aTexCoord;  // Pasăm coordonatele de textură la fragment shader
}
