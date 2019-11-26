#include "application_solar.hpp"
#include "window_handler.hpp"

#include "utils.hpp"
#include "shader_loader.hpp"
#include "model_loader.hpp"


#include <glbinding/gl/gl.h>
// use gl definitions from glbinding 
using namespace gl;

//dont load gl bindings from glfw
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/matrix_inverse.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <iostream>

ApplicationSolar::ApplicationSolar(std::string const& resource_path)
 :Application{resource_path}
 ,planet_object{}
 ,m_view_transform{glm::translate(glm::fmat4{}, glm::fvec3{0.0f, 0.0f, 4.0f})}
 ,m_view_projection{utils::calculate_projection_matrix(initial_aspect_ratio)}
{
  initializeSceneGraph();
  initializeGeometry();
  initializeShaderPrograms();
}

ApplicationSolar::~ApplicationSolar() {
  glDeleteBuffers(1, &planet_object.vertex_BO);
  glDeleteBuffers(1, &planet_object.element_BO);
  glDeleteVertexArrays(1, &planet_object.vertex_AO);
}

void ApplicationSolar::render() const {
  // bind shader to upload uniforms
  glUseProgram(m_shaders.at("planet").handle);

  //int counter = 0; // test for planet rendering
  for (auto const& child : scene_graph.getRoot() -> getChildrenList()) {
    
    //counter += 1;
    //std::cout << i -> getName() /*<< counter*/;
      float speed = child -> getSpeed();
      float distance = child -> getDistance();

      glm::fmat4 model_matrix = child -> getLocalTransform();

      model_matrix = glm::rotate(glm::fmat4{}, float(glfwGetTime()) * speed, glm::fvec3{0.0f, 1.0f, 0.0f});//speed
      model_matrix = glm::translate(model_matrix, glm::fvec3{0.0f, 0.0f, - distance}); //distance

      child -> setLocalTransform(model_matrix);

      glUniformMatrix4fv(m_shaders.at("planet").u_locs.at("ModelMatrix"),
                         1, GL_FALSE, glm::value_ptr(model_matrix));

      // extra matrix for normal transformation to keep them orthogonal to surface
      glm::fmat4 normal_matrix = glm::inverseTranspose(glm::inverse(m_view_transform) * model_matrix); 
      glUniformMatrix4fv(m_shaders.at("planet").u_locs.at("NormalMatrix"), 
                         1, GL_FALSE, glm::value_ptr(normal_matrix)); 

      // bind the VAO to draw
      glBindVertexArray(planet_object.vertex_AO);

      // draw bound vertex array using bound shader
      glDrawElements(planet_object.draw_mode, planet_object.num_elements, model::INDEX.type, NULL);
    
    if(child -> getName() == "earth"){
      
      glm::fmat4 model_matrix = child -> getLocalTransform();
      float speed = child -> getSpeed();
      float distance = child -> getDistance();
      model_matrix = glm::rotate(model_matrix, float(glfwGetTime()) * speed, glm::fvec3{0.0f, 1.0f, 0.0f});//speed
      model_matrix = glm::translate(model_matrix, glm::fvec3{0.0f, 0.0f, - distance}); //distance

      //child -> setLocalTransform(model_matrix);
      
      for (auto const& earth_children : child -> getChildrenList()){

        //glm::fmat4 model_matrix_earth_child = child -> getLocalTransform();
        float speed_child = earth_children -> getSpeed();
        float distance_child = earth_children -> getDistance();

        glm::fmat4 model_matrix_earth_child = glm::rotate(model_matrix * earth_children -> getLocalTransform(), float(glfwGetTime()) * speed_child, glm::fvec3{0.0f, 1.0f, 0.0f});//speed
        //model_matrix =                        glm::rotate(model_matrix, float(glfwGetTime())*(child->getParent()->getSpeed()), glm::fvec3{0.0f, 1.0f, 0.0f});
        model_matrix_earth_child = glm::translate(model_matrix, glm::fvec3{0.0f, 0.0f, - distance_child}); //distance
          //                        glm::translate(model_matrix, child->getParent()->getPosition());


        earth_children -> setLocalTransform(model_matrix_earth_child);

        glUniformMatrix4fv(m_shaders.at("planet").u_locs.at("ModelMatrix"),
                         1, GL_FALSE, glm::value_ptr(model_matrix_earth_child));

        // extra matrix for normal transformation to keep them orthogonal to surface
        glm::fmat4 normal_matrix = glm::inverseTranspose(glm::inverse(m_view_transform) * model_matrix_earth_child); 
        glUniformMatrix4fv(m_shaders.at("planet").u_locs.at("NormalMatrix"), 
                          1, GL_FALSE, glm::value_ptr(normal_matrix)); 

        // bind the VAO to draw
        glBindVertexArray(planet_object.vertex_AO);

        // draw bound vertex array using bound shader
        glDrawElements(planet_object.draw_mode, planet_object.num_elements, model::INDEX.type, NULL);

      }
      //child -> getChildrenList();
      //parent data as origin
      // std::shared_ptr<Node> parent = child -> getParent();
      // glm::fmat4 model_matrix = parent -> getLocalTransform();
      // float speed = parent -> getSpeed();
      // float distance = parent -> getDistance();
      // model_matrix = glm::rotate(glm::fmat4{}, float(glfwGetTime()) * speed, glm::fvec3{0.0f, 1.0f, 0.0f});//speed
      // model_matrix = glm::translate(model_matrix, glm::fvec3{0.0f, 0.0f, - distance}); //distance

      // child -> setLocalTransform(model_matrix);

      //child 
      // glm::fmat4 model_matrix_child = child -> getLocalTransform();
      // float speed_child = child -> getSpeed();
      // float distance_child = child -> getDistance();

      // model_matrix_child = glm::rotate(glm::fmat4{}, float(glfwGetTime()) * speed_child, glm::fvec3{0.0f, 1.0f, 0.0f});//speed
      // model_matrix_child = glm::translate(model_matrix_child, glm::fvec3{0.0f, 0.0f, - distance_child}); //distance

      // glUniformMatrix4fv(m_shaders.at("planet").u_locs.at("ModelMatrix"),
      //                    1, GL_FALSE, glm::value_ptr(model_matrix_child));

      // // extra matrix for normal transformation to keep them orthogonal to surface
      // glm::fmat4 normal_matrix = glm::inverseTranspose(glm::inverse(m_view_transform) * model_matrix_child); 
      // glUniformMatrix4fv(m_shaders.at("planet").u_locs.at("NormalMatrix"), 
      //                    1, GL_FALSE, glm::value_ptr(normal_matrix)); 

      // // bind the VAO to draw
      // glBindVertexArray(planet_object.vertex_AO);

      // // draw bound vertex array using bound shader
      // glDrawElements(planet_object.draw_mode, planet_object.num_elements, model::INDEX.type, NULL);

    } //end if


  } //end loop


} //end function

void ApplicationSolar::uploadView() {
  // vertices are transformed in camera space, so camera transform must be inverted
  glm::fmat4 view_matrix = glm::inverse(m_view_transform);
  // upload matrix to gpu
  glUniformMatrix4fv(m_shaders.at("planet").u_locs.at("ViewMatrix"),
                     1, GL_FALSE, glm::value_ptr(view_matrix));
}

void ApplicationSolar::uploadProjection() {
  // upload matrix to gpu
  glUniformMatrix4fv(m_shaders.at("planet").u_locs.at("ProjectionMatrix"),
                     1, GL_FALSE, glm::value_ptr(m_view_projection));
}

// update uniform locations
void ApplicationSolar::uploadUniforms() { 
  // bind shader to which to upload unforms
  glUseProgram(m_shaders.at("planet").handle);
  // upload uniform values to new locations
  uploadView();
  uploadProjection();
}

///////////////////////////// intialisation functions /////////////////////////
// load shader sources
void ApplicationSolar::initializeShaderPrograms() {
  // store shader program objects in container
  m_shaders.emplace("planet", shader_program{{{GL_VERTEX_SHADER,m_resource_path + "shaders/simple.vert"},
                                           {GL_FRAGMENT_SHADER, m_resource_path + "shaders/simple.frag"}}});
  // request uniform locations for shader program
  m_shaders.at("planet").u_locs["NormalMatrix"] = -1;
  m_shaders.at("planet").u_locs["ModelMatrix"] = -1;
  m_shaders.at("planet").u_locs["ViewMatrix"] = -1;
  m_shaders.at("planet").u_locs["ProjectionMatrix"] = -1;
}

void ApplicationSolar::initializeSceneGraph() {

  model planet_model = model_loader::obj(m_resource_path + "models/sphere.obj", model::NORMAL);

  auto root = std::make_shared<Node>();


  
/*   GeometryNode mercury (planet_model);
  auto mercury_holder = std::make_shared<Node>(mercury);
  mercury_holder -> setName("mercury");
  mercury_holder -> setParent(root);
  mercury_holder -> setDistance(4.5f); //distance to origin
  mercury_holder -> setSpeed(0.6f); //rotation speed
  root -> addChildren(mercury_holder);

  GeometryNode venus (planet_model);
  auto venus_holder = std::make_shared<Node>(venus);
  venus_holder -> setName("venus");
  venus_holder -> setParent(root);
  venus_holder -> setDistance(8.5f); //distance to origin
  venus_holder -> setSpeed(0.5f); //rotation speed
  root -> addChildren(venus_holder);

  GeometryNode mars (planet_model);
  auto mars_holder = std::make_shared<Node>(mars);
  mars_holder -> setName("mars");
  mars_holder -> setParent(root);
  mars_holder -> setDistance(15.0f); //distance to origin
  mars_holder -> setSpeed(0.4f); //rotation speed
  root -> addChildren(mars_holder);

  GeometryNode jupiter (planet_model);
  auto jupiter_holder = std::make_shared<Node>(jupiter);
  jupiter_holder -> setName("jupiter");
  jupiter_holder -> setParent(root);
  jupiter_holder -> setDistance(20.0f); //distance to origin
  jupiter_holder -> setSpeed(0.25f); //rotation speed
  root -> addChildren(jupiter_holder);

  GeometryNode saturn (planet_model);
  auto saturn_holder = std::make_shared<Node>(saturn);
  saturn_holder -> setName("saturn");
  saturn_holder -> setParent(root);
  saturn_holder -> setDistance(26.0f); //distance to origin
  saturn_holder -> setSpeed(0.2f); //rotation speed
  root -> addChildren(saturn_holder);

  GeometryNode uranus (planet_model);
  auto uranus_holder = std::make_shared<Node>(uranus);
  uranus_holder -> setName("uranus");
  uranus_holder -> setParent(root);
  uranus_holder -> setDistance(33.0f); //distance to origin
  uranus_holder -> setSpeed(0.15f); //rotation speed
  root -> addChildren(uranus_holder);

  GeometryNode neptun (planet_model);
  auto neptun_holder = std::make_shared<Node>(neptun);
  neptun_holder -> setName("neptun");
  neptun_holder -> setParent(root);
  neptun_holder -> setDistance(40.0f); //distance to origin
  neptun_holder -> setSpeed(0.1f); //rotation speed
  root -> addChildren(neptun_holder); */

  GeometryNode sun (planet_model);
  auto sun_holder = std::make_shared<Node>(sun);
  sun_holder -> setName("sun");
  sun_holder -> setParent(root);
  sun_holder -> setDistance(0.0f); //distance to origin
  sun_holder -> setSpeed(0.1f); //rotation speed
  root -> addChildren(sun_holder);

  GeometryNode earth (planet_model);
  auto earth_holder = std::make_shared<Node>(earth);
  earth_holder -> setName("earth");
  earth_holder -> setParent(root);
  earth_holder -> setDistance(20.0f); //distance to origin
  earth_holder -> setSpeed(0.45f); //r0fotation speed
  root -> addChildren(earth_holder);
  
  GeometryNode moon (planet_model);
  auto moon_holder = std::make_shared<Node>(moon);
  moon_holder -> setName("moon");
  moon_holder -> setParent(earth_holder);
  moon_holder -> setDistance(2.0f); //distance to origin
  moon_holder -> setSpeed(2.0f); //rotation speed
  earth_holder  -> addChildren(moon_holder);




  //CameraNode camera ();
  auto camera = std::make_shared<CameraNode>();
  camera -> setParent(root);
  camera -> setName("camera");
  root -> addChildren(camera);

  SceneGraph sceneGraph_tmp{"SolarSystem", root};
  scene_graph = sceneGraph_tmp;
}

// load models
void ApplicationSolar::initializeGeometry() {
  model planet_model = model_loader::obj(m_resource_path + "models/sphere.obj", model::NORMAL);

  // generate vertex array object
  glGenVertexArrays(1, &planet_object.vertex_AO);
  // bind the array for attaching buffers
  glBindVertexArray(planet_object.vertex_AO);

  // generate generic buffer
  glGenBuffers(1, &planet_object.vertex_BO);
  // bind this as an vertex array buffer containing all attributes
  glBindBuffer(GL_ARRAY_BUFFER, planet_object.vertex_BO);
  // configure currently bound array buffer
  glBufferData(GL_ARRAY_BUFFER, sizeof(float) * planet_model.data.size(), planet_model.data.data(), GL_STATIC_DRAW);

  // activate first attribute on gpu
  glEnableVertexAttribArray(0);
  // first attribute is 3 floats with no offset & stride
  glVertexAttribPointer(0, model::POSITION.components, model::POSITION.type, GL_FALSE, planet_model.vertex_bytes, planet_model.offsets[model::POSITION]);
  // activate second attribute on gpu
  glEnableVertexAttribArray(1);
  // second attribute is 3 floats with no offset & stride
  glVertexAttribPointer(1, model::NORMAL.components, model::NORMAL.type, GL_FALSE, planet_model.vertex_bytes, planet_model.offsets[model::NORMAL]);

   // generate generic buffer
  glGenBuffers(1, &planet_object.element_BO);
  // bind this as an vertex array buffer containing all attributes
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, planet_object.element_BO);
  // configure currently bound array buffer
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, model::INDEX.size * planet_model.indices.size(), planet_model.indices.data(), GL_STATIC_DRAW);

  // store type of primitive to draw
  planet_object.draw_mode = GL_TRIANGLES;
  // transfer number of indices to model object 
  planet_object.num_elements = GLsizei(planet_model.indices.size());
}

///////////////////////////// callback functions for window events ////////////
// handle key input
void ApplicationSolar::keyCallback(int key, int action, int mods) {
  //zoom in
  if (key == GLFW_KEY_W  && (action == GLFW_PRESS || action == GLFW_REPEAT)) {
    m_view_transform = glm::translate(m_view_transform, glm::fvec3{0.0f, 0.0f, -0.1f});
    uploadView();
  }
  //zoom out
  else if (key == GLFW_KEY_S  && (action == GLFW_PRESS || action == GLFW_REPEAT)) {
    m_view_transform = glm::translate(m_view_transform, glm::fvec3{0.0f, 0.0f, 0.1f});
    uploadView();
  }
  //up
  else if (key == GLFW_KEY_UP  && (action == GLFW_PRESS || action == GLFW_REPEAT)) {
    m_view_transform = glm::translate(m_view_transform, glm::fvec3{0.0f, -0.1f, 0.0f});
    uploadView();
  }
  //down
  else if (key == GLFW_KEY_DOWN  && (action == GLFW_PRESS || action == GLFW_REPEAT)) {
    m_view_transform = glm::translate(m_view_transform, glm::fvec3{0.0f, 0.1f, 0.0f});
    uploadView();
  }
  //left
  else if (key == GLFW_KEY_LEFT  && (action == GLFW_PRESS || action == GLFW_REPEAT)) {
    m_view_transform = glm::translate(m_view_transform, glm::fvec3{0.1f, 0.0f, 0.0f});
    uploadView();
  }
  //right
  else if (key == GLFW_KEY_RIGHT  && (action == GLFW_PRESS || action == GLFW_REPEAT)) {
    m_view_transform = glm::translate(m_view_transform, glm::fvec3{-0.1f, 0.0f, 0.0f});
    uploadView();
  }

}

//handle delta mouse movement input
void ApplicationSolar::mouseCallback(double pos_x, double pos_y) {
  // mouse handling
  //left
  if(pos_x > 0){
    m_view_transform = glm::translate(m_view_transform, glm::fvec3{-0.1f, 0.0f, 0.0f});
    uploadView();
  }
  //right
  if(pos_x < 0){
    m_view_transform = glm::translate(m_view_transform, glm::fvec3{0.1f, 0.0f, 0.0f});
    uploadView();
  }
  //down
  if(pos_y > 0){
    m_view_transform = glm::translate(m_view_transform, glm::fvec3{0.0f, 0.1f, 0.0f});
    uploadView();
  }
  //up
  if(pos_y < 0){
    m_view_transform = glm::translate(m_view_transform, glm::fvec3{0.0f, -0.1f, 0.0f});
    uploadView();
  }

  
  
}

//handle resizing
void ApplicationSolar::resizeCallback(unsigned width, unsigned height) {
  // recalculate projection matrix for new aspect ration
  m_view_projection = utils::calculate_projection_matrix(float(width) / float(height));
  // upload new projection matrix
  uploadProjection();
}


// exe entry point
int main(int argc, char* argv[]) {
  Application::run<ApplicationSolar>(argc, argv, 3, 2);
}