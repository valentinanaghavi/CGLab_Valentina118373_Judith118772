#ifndef CAMERANODE_HPP
#define CAMERANODE_HPP

#include<string>
#include<list>
#include<memory>

#include<glm/glm.hpp>
#include"Node.hpp"

class CameraNode: public Node
{
    public:
        CameraNode();
        ~CameraNode();

        bool getPerspective();

        bool getEnabled();
        void setEnabled(bool isEnabled);

        glm::mat4 getProjectionMatrix();
        void setProjectionMatrix(glm::mat4 projectionMatrix);


    private:
        bool isPerspective_;
        bool isEnabled_;
        glm::mat4 projectionMatrix_;



};


#endif //CAMERANODE_HPP