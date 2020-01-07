#include"PointLightNode.hpp"

PointLightNode::PointLightNode()
{}

PointLightNode::PointLightNode(float lightIntensity, glm::fvec3  lightColor):
    lightIntensity_{lightIntensity},
    lightColor_{lightColor} 
{}

PointLightNode::~PointLightNode() 
{}

float PointLightNode::getLightIntensity(){
    return lightIntensity_;
}

glm::fvec3 PointLightNode::getLightColor(){
    return lightColor_;
}
