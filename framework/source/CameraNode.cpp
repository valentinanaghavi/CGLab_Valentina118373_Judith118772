#include"CameraNode.hpp"

CameraNode::CameraNode():
    isPerspective_{true},
    isEnabled_{true},
    projectionMatrix_{}
{}

CameraNode::~CameraNode() {
 
}

bool CameraNode::getPerspective(){
    return isPerspective_;
}

bool CameraNode::getEnabled(){
    return isEnabled_;
}

void CameraNode::setEnabled(bool isEnabled){
    isEnabled_ = isEnabled;
}

glm::mat4 CameraNode::getProjectionMatrix(){
    return projectionMatrix_;
}

void CameraNode::setProjectionMatrix(glm::mat4 projectionMatrix){
    projectionMatrix_ = projectionMatrix;
}
