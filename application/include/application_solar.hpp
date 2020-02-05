#ifndef APPLICATION_SOLAR_HPP
#define APPLICATION_SOLAR_HPP

#include <vector>

#include "application.hpp"
#include "model.hpp"
#include "structs.hpp"

#include "SceneGraph.hpp"
#include "Node.hpp"
#include "GeometryNode.hpp"
#include "CameraNode.hpp"
#include "PointLightNode.hpp"
#include "texture_loader.hpp"
#include "pixel_data.hpp"

// gpu representation of model
class ApplicationSolar : public Application {
 public:
  // allocate and initialize objects
  ApplicationSolar(std::string const& resource_path);
  // free allocated objects
  ~ApplicationSolar();

  // react to key input
  void keyCallback(int key, int action, int mods);
  //handle delta mouse movement input
  void mouseCallback(double pos_x, double pos_y);
  //handle resizing
  void resizeCallback(unsigned width, unsigned height);

  // draw all objects
  void render() const;
  void renderPlanets(glm::fmat4 model_matrix, glm::fvec3 planet_color, float light_intensity, glm::fvec3 light_color, texture_object texture) const;
  void renderStars() const;

  void loadTextures();
  void initializeTextures();
  void initializeQuad();
  void initializeFramebuffer();
  void initializeSceneGraph();
  void initializeStars();

 protected:
  void initializeShaderPrograms();
  void initializeGeometry();
  

  
  // update uniform values
  void uploadUniforms();
  // upload projection matrix
  void uploadProjection();
  // upload view matrix
  void uploadView();

  // cpu representation of model
  model_object planet_object;

  // cpu representation of model
  model_object star_object;
  model_object quad_object;
  texture_object texture_object_value;
  
  texture_object rb_framebuffer;
  texture_object tex_framebuffer;
  texture_object fbo_framebuffer;

  SceneGraph scene_graph;
  SceneGraph scene_light;
  // load pixel data to model object (texture)
  std::vector<texture_object> texture_object_container;
  // load png to pixel data
  std::vector<pixel_data> texture_pixel_data_container;

  // camera transform matrix
  glm::fmat4 m_view_transform;
  // camera projection matrix
  glm::fmat4 m_view_projection;
  
};

#endif