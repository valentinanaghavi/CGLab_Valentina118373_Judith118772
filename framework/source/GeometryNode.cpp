#include"GeometryNode.hpp"

GeometryNode::GeometryNode():
    geometry_{}
{}

GeometryNode::GeometryNode(model geometry):
    geometry_{geometry}
{}

GeometryNode::~GeometryNode() {
 
}

model GeometryNode::getGeometry(){
    return geometry_;
}

void GeometryNode::setGeometry(model geometry){
    geometry_ = geometry;
}

void GeometryNode::setSpeed(float speed){
    speed_ = speed;
}
float GeometryNode::getSpeed(){
    return speed_;
}

void GeometryNode::setDistance(float distance){
    distance_ = distance;
}
float GeometryNode::getDistance(){
    return distance_;
}

void GeometryNode::setSize(float size){
    size_ = size;
}
float GeometryNode::getSize(){
    return size_;
}


