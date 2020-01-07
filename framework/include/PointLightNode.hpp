#ifndef POINTLIGHTNODE_HPP
#define POINTLIGHTNODE_HPP

#include<glm/glm.hpp>
#include"Node.hpp"
#include"model.hpp"

class PointLightNode: public Node
{
    public:
    PointLightNode();
    PointLightNode(float lightIntensity, glm::vec3  lightColor);
     ~PointLightNode();

    private:
    float lightIntensity_;
    glm::vec3 lightColor_;

};


#endif //PointLightNode_HPP
