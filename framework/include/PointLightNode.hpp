#ifndef POINTLIGHTNODE_HPP
#define POINTLIGHTNODE_HPP

#include<glm/glm.hpp>
#include"Node.hpp"
#include"model.hpp"

class PointLightNode: public Node
{
    public:
    PointLightNode();
    PointLightNode(float lightIntensity, glm::fvec3  lightColor);
     ~PointLightNode();

    float getLightIntensity();
    glm::fvec3 getLightColor();

    protected:
    float lightIntensity_;
    glm::fvec3 lightColor_;

};


#endif //PointLightNode_HPP
