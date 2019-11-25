#ifndef SCENEGRAPH_HPP
#define SCENEGRAPH_HPP

#include<string>

#include"Node.hpp"

class SceneGraph
{
    public:
        SceneGraph();
        SceneGraph(std::string name, std::shared_ptr<Node> root);
        ~SceneGraph();

        std::string getName();
        std::shared_ptr<Node> getRoot();

        std::string printGraph();

    private:

        void setName(std::string name);
        void setRoot(std::shared_ptr<Node> root);

        std::string name_;
        std::shared_ptr<Node> root_;
};


#endif //SCENEGRAPH_HPP