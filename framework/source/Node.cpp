#include"Node.hpp"

Node::Node():
    parent_{},
    children_{},
    name_{},
    path_{},
    depth_{},
    localTransform_{},
    worldTransform_{}
{}

Node::~Node() {
 
}

std::shared_ptr<Node> Node::getParent(){
    return parent_;
}

void Node::setParent(std::shared_ptr<Node> parent){
    parent_ = parent;
}

std::shared_ptr<Node> Node::getChildren(std::string name){
   // auto list -> getChildrenlist;
    for(auto const& child : this -> getChildrenList()){
        if(child -> getName() == name){
            return child;
        }
    }
    return nullptr;

    //lambda function to get children
    // auto it = std::find_if(children_.begin(), children_.end(), [name](const std::shared_ptr<Node> child) 
    // {return child -> getName() == name;});

}

std::list<std::shared_ptr<Node>> Node::getChildrenList(){
    return children_;
}

void Node::setName(std::string name){
    name_ = name;
}

std::string Node::getName(){
    return name_;
}

std::string Node::getPath(){
    return path_;
}

int Node::getDepth(){
    return depth_;
}

glm::mat4 Node::getLocalTransform(){
    return localTransform_;
}

void Node::setLocalTransform(glm::mat4 matrix_in){
    localTransform_ = matrix_in;
}

glm::mat4 Node::getWorldTransform(){
    return worldTransform_;
}

void Node::setWorldTransform(glm::mat4 matrix_in){
    worldTransform_ = matrix_in;
}

void Node::addChildren(std::shared_ptr<Node> child){
    children_.push_back(child);
}

std::shared_ptr<Node> Node::removeChildren(std::string name){
    std::shared_ptr<Node> child = getChildren(name);
    children_.remove(child);
    return child;
}



void Node::setSpeed(float speed){
    speed_ = speed;
}
float Node::getSpeed(){
    return speed_;
}

void Node::setDistance(float distance){
    distance_ = distance;
}
float Node::getDistance(){
    return distance_;
}

void Node::setSize(float size){
    size_ = size;
}
float Node::getSize(){
    return size_;
}

void Node::setPlanetColor(glm::fvec3 const& color){
    planetColor_ = color;
}
glm::fvec3 Node::getPlanetColor() const {
    return planetColor_;
}

float Node::getLightIntensity() const{
    return light_intensity_;
}
void Node::setLightIntensity(float const& light_intensity){
    light_intensity_ = light_intensity;
}

glm::fvec3 Node::getLightColor() const{
    return light_color_;
}
void Node::setLightColor(glm::fvec3 const& light_color){
    light_color_ = light_color;
}

