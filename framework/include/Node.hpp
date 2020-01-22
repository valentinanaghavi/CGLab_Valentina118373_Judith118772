#ifndef NODE_HPP
#define NODE_HPP

#include<string>
#include<list>
#include<memory>
#include<algorithm>
#include <iostream>
#include<glm/glm.hpp>
#include "pixel_data.hpp"

//super class
class Node
{
    public:
        Node();
        ~Node();

        std::shared_ptr<Node> getParent();
        void setParent(std::shared_ptr<Node> parent);

        std::shared_ptr<Node> getChildren(std::string name);
        std::list<std::shared_ptr<Node>> getChildrenList();

        void setName(std::string name);
        std::string getName();
        std::string getPath();
        int getDepth();
        
        glm::mat4 getLocalTransform();
        void setLocalTransform(glm::mat4 matrix_in);

        glm::mat4 getWorldTransform();
        void setWorldTransform(glm::mat4 matrix_in);

        void addChildren(std::shared_ptr<Node> child);
        std::shared_ptr<Node> removeChildren(std::string name);

        void setSpeed(float speed);
        float getSpeed();

        void setDistance(float distance);
        float getDistance();

        void setSize(float size);
        float getSize();

        void setPlanetColor(glm::vec3 const& color);
        glm::vec3 getPlanetColor() const; 

        float getLightIntensity() const;
        void setLightIntensity(float const& light_intensity);

        glm::fvec3 getLightColor() const;
        void setLightColor(glm::fvec3 const& light_color);

        pixel_data getTexture() const;
        void setTexture(pixel_data const& planet_texture);

    protected:
    
        std::shared_ptr<Node> parent_;
        std::list<std::shared_ptr<Node>>children_;
        std::string name_;
        std::string path_;
        int depth_;
        glm::mat4 localTransform_;
        glm::mat4 worldTransform_;

        float speed_;
        float distance_;
        float size_;
        glm::fvec3 planetColor_;
        float light_intensity_;
        glm::fvec3 light_color_;
        pixel_data planet_texture_;
};


#endif //NODE_HPP