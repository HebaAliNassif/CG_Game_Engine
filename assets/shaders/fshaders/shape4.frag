#version 330 core

#define PI  3.1415926535897932384626433832795

uniform vec2 translation;
out vec4 frag_color;

void main() {

    // the center of the texture
    vec2 center = vec2(translation.x,translation.y);

    // current pixel location
    vec2 position;

    position.x= gl_FragCoord.x-center.x;
    position.y= gl_FragCoord.y-center.y;

    //outer circle
    float outer = sqrt(pow(position.x,2)+pow(position.y,2));
    if (outer<80)frag_color = vec4(0,1,0,1);

    //inner circle
    float inner = sqrt(pow(position.x,2)+pow(position.y,2));
    if (inner<55)frag_color = vec4(0,0,0,1);

    //45 degree sector
    float angle = atan(position.y/position.x);
    if (angle>=-(0.25*PI) && angle<=0.25*PI && gl_FragCoord.x>center.x) frag_color = vec4(0,0,0,1);

    //vertical bar
    if (position.x>32 && position.x<57 && position.y>-56 && position.y<-5) frag_color = vec4(0,1,0,1);



}
