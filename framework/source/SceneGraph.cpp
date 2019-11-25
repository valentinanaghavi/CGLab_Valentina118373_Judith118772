#include"SceneGraph.hpp"

SceneGraph::SceneGraph():
    name_{"SceneGraph"},
    root_{}
{};

SceneGraph::SceneGraph(std::string name, std::shared_ptr<Node> root):
    name_{name},
    root_{root}
{};

SceneGraph::~SceneGraph() {
 
}

std::string SceneGraph::getName(){
    return name_;
}

void SceneGraph::setName(std::string name){
    name_ = name;
}

std::shared_ptr<Node> SceneGraph::getRoot(){
    return root_;
}

void SceneGraph::setRoot(std::shared_ptr<Node> root){
    root_ = root;
}

std::string SceneGraph::printGraph(){
    return "print Graph";
}
