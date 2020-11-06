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
    float face = sqrt(pow(position.x,2)+pow(position.y,2));
    if (face<80)frag_color = vec4(1,1,0,1);

    ///draww a shifted circle
    float eye = sqrt(pow(position.x,2)+pow(position.y-45,2));
    if(eye<15) frag_color = vec4(0,0,0,1);


    ////draw mouth by knowing if point is in the sector
    float endAngle= 0.25*PI; ///about 45 degrees but in radian
    float polarradius = sqrt(position.x*position.x+position.y*position.y);
    float Angle = atan(position.y/position.x);
    if (Angle>=-(0.25*PI) && Angle<=endAngle && polarradius<80 && gl_FragCoord.x>center.x) frag_color = vec4(0,0,0,1);

}
