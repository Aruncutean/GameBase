#version 100
precision mediump float;  // Precizia medie pentru variabilele float (obligatoriu în ES 2.0)

varying vec2 TexCoord;  // Coordonatele texturii primite din vertex shader

uniform sampler2D texture1;  // Uniform pentru textura

void main()
{
    // Aplica textura la coordonatele date
    gl_FragColor = texture2D(texture1, TexCoord);
}
