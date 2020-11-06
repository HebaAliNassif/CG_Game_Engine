#version 330 core

uniform vec2 translation;
out vec4 frag_color;

void main() {

    // the center of the texture
    vec2 center = vec2(translation.x,translation.y);

    vec2 position;

    position.x= gl_FragCoord.x-center.x;
    position.y= gl_FragCoord.y-center.y;

    float result=pow(position.x,2)+pow((position.y+40-sqrt(abs(70*position.x))),2)-6000;

    if (result<600)frag_color = vec4(1,0,0,1);

}
