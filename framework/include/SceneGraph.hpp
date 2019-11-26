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

        std::string getName() const;
        std::shared_ptr<Node> getRoot() const;

        std::string printGraph();

    private:

        void setName(std::string const& name);
        void setRoot(std::shared_ptr<Node> const& root);

        std::string name_;
        std::shared_ptr<Node> root_;
};


#endif //SCENEGRAPH_HPP