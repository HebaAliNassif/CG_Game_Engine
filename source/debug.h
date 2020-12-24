
#include <iostream>
#include <iomanip>
#include "glm/glm.hpp"
//For debug
/*
void PrintMatTransform(Transform* T)
{
    std::cout<<"Local to World Matrix\n";
    PrintMat4x4(T->getLocalToWorldMatrix());
    std::cout<<"World to Local Matrix\n";
    PrintMat4x4(T->getWorldToLocalMatrix());
    std::cout<<"getPosition\n";
    PrintVector3(T->getPosition());
    std::cout<<"getLocalPosition\n";
    PrintVector3(T->getLocalPosition());
    std::cout<<"getLocalScale\n";
    PrintVector3(T->getLocalScale());
    std::cout<<"getLossyScale\n";
    PrintVector3(T->getLossyScale());
}
 */
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