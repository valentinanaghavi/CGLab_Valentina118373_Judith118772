#include"SceneGraph.hpp"

SceneGraph::SceneGraph():
    name_{"SceneGraph"},
    root_{}
{}

SceneGraph::SceneGraph(std::string name, std::shared_ptr<Node> root):
    name_{name},
    root_{root}
{}

SceneGraph::SceneGraph(std::string name, std::shared_ptr<GeometryNode> g_root):
    name_{name},
    g_root_{g_root}
{}

SceneGraph::SceneGraph(std::string name, std::shared_ptr<PointLightNode> l_root):
    name_{name},
    l_root_{l_root}
{}

SceneGraph::~SceneGraph() {
 
}

std::string SceneGraph::getName() const {
    return name_;
}

void SceneGraph::setName(std::string const& name){
    name_ = name;
}

std::shared_ptr<Node> SceneGraph::getRoot() const {
    return root_;
}

void SceneGraph::setRoot(std::shared_ptr<Node> const& root){
    root_ = root;
}

std::string SceneGraph::printGraph(){
    return "print Graph";
}
