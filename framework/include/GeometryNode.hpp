#ifndef GEOMETRYNODE_HPP
#define GEOMETRYNODE_HPP

#include<string>
#include<list>
#include<memory>

#include<glm/glm.hpp>

#include"Node.hpp"
#include"model.hpp"

class GeometryNode: public Node
{
    public:
        GeometryNode();
        GeometryNode(model geometry);
        ~GeometryNode();

        model getGeometry();
        void setGeometry(model geometry);

        void setSpeed(float speed);
        float getSpeed();

        void setDistance(float distance);
        float getDistance();

        void setSize(float size);
        float getSize();

    private:

    model geometry_;

    float speed_;
    float distance_;
    float size_;


};


#endif //GEOMETRYNODE_HPP