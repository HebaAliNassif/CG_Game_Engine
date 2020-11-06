#version 330 core

uniform vec2 translation;
out vec4 frag_color;
void main() {
    const float PI=3.14159265359;
    // the center of the texture
    vec2 center = vec2(translation.x,translation.y);
    // current pixel location
    vec2 position;
    position.x= gl_FragCoord.x-center.x;
    position.y= gl_FragCoord.y-center.y;
    float result = pow(position.x,2)+pow(position.y,2);
    if (result < 7000)frag_color =vec4(1,1,1,1);
    // To draw eyes of smile face
    float result1 =  pow(position.x+35,2)+pow(position.y-30,2);
    float result2 =  pow(position.x-35,2)+pow(position.y-30,2);
    if (result1<100 || result2 < 100)frag_color = vec4(0,0,0,1);
  // To draw mouth of smile face
    float end = -2*PI;
    float polarradius = sqrt(position.x*position.x+position.y*position.y);
    float angle= atan(position.y/position.x);
    if (angle <=5*PI && angle >=end && polarradius<50 && polarradius > 40&& gl_FragCoord.y < center.y)frag_color = vec4(0,0,0,1);

}
