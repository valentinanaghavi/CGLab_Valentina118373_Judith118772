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

    private:

    model geometry_;

};


#endif //GEOMETRYNODE_HPP