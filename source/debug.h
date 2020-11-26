
#include <iostream>
#include <iomanip>
#include "glm/glm.hpp"
//For debug
void PrintVector3(glm::vec3 vex)
{
    std::cout<<vex.x<<"  "<<vex.y<<"  "<<vex.z<<"\n";
}
void PrintMat4x4(glm::mat4 mat)
{
    std::cout<<std::setw(10)<<mat[0][0]<<std::setw(10)<<mat[0][1]<<std::setw(10)<<mat[0][2]<<std::setw(10)<<mat[0][3]<<std::setw(10)<<"\n";
    std::cout<<std::setw(10)<<mat[1][0]<<std::setw(10)<<mat[1][1]<<std::setw(10)<<mat[1][2]<<std::setw(10)<<mat[1][3]<<std::setw(10)<<"\n";
    std::cout<<std::setw(10)<<mat[2][0]<<std::setw(10)<<mat[2][1]<<std::setw(10)<<mat[2][2]<<std::setw(10)<<mat[2][3]<<std::setw(10)<<"\n";
    std::cout<<std::setw(10)<<mat[3][0]<<std::setw(10)<<mat[3][1]<<std::setw(10)<<mat[3][2]<<std::setw(10)<<mat[3][3]<<std::setw(10)<<"\n";

}