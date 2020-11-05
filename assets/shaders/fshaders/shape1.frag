#version 330 core

uniform vec2 translation;
out vec4 frag_color;

void main() {

    // the center of the texture
    vec2 center = vec2(translation.x,translation.y);

    // current pixel location
    vec2 position;
    /*position.x= gl_FragCoord.x-1280.0/2.0;
    position.y= gl_FragCoord.y-720.0/2.0;*/
    position.x= gl_FragCoord.x-center.x;
    position.y= gl_FragCoord.y-center.y;
    //float result = pow((pow(position.x,2)+pow(position.y,2))-5000,3)-(pow(position.x,2)*pow(position.y,3));
    float result = pow(position.x,2)+(pow(position.y-sqrt(abs(position.x)),2));
    if (result<5000)frag_color = vec4(0,1,0,1);

}
