#include"PointLightNode.hpp"

PointLightNode::PointLightNode()
{}

PointLightNode::PointLightNode(float lightIntensity, glm::vec3  lightColor):
    lightIntensity_{lightIntensity},
    lightColor_{lightColor} 
{}

PointLightNode::~PointLightNode() 
{}
