#include"GeometryNode.hpp"

GeometryNode::GeometryNode():
    geometry_{}
{}

GeometryNode::~GeometryNode() {
 
}

model GeometryNode::getGeometry(){
    return geometry_;
}

void GeometryNode::setGeometry(model geometry){
    geometry_ = geometry;
}


