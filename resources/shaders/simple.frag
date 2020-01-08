#version 150

in vec3 pass_Normal;
in vec3 pass_Vertex_Position;
in vec3 pass_Camera_Position;

out vec4 out_Color;

uniform vec3 planetcolor;
uniform float lightintensity; //ambient
uniform vec3 lightcolor; //for diffuse and ambient

const vec3 lightposition = vec3(0.0, 0.0, 0.0);
const vec3 specularcolor = vec3(1.0, 1.0, 1.0);

void main() {
  //out_Color = vec4(abs(normalize(pass_Normal)), 1.0);
  //out_Color = vec4(planetcolor, 1.0);

  //Blinn-Phong
  //https://de.wikipedia.org/wiki/Blinn-Beleuchtungsmodell

  vec3 L = normalize(lightposition - pass_Vertex_Position); // light direction
  vec3 V = normalize(pass_Camera_Position - pass_Vertex_Position); //view direction
  vec3 N = normalize(pass_Normal);

  vec3 halfway_direction = normalize(L + V);

  float k_a = 0.2; // says how much of ambient light is reflected
  float k_d = 0.3; // diffuse reflection coefficient
  float k_s = 1.0; // specular reflection coefficient
  float shininess = 16.0; 

  vec3 ambient =  k_a * lightintensity * lightcolor;
  vec3 diffuse =  k_d * lightintensity * (max(dot(N,L),0.0)) * lightcolor;
  vec3 specular = k_s * pow(max(dot(halfway_direction, N), 0.0), shininess) * specularcolor ;

  vec3 blinn_phong_color =  planetcolor + diffuse * planetcolor + specular;//planetcolor * normalize(lightintensity) + diffuse * planetcolor + specular;
  out_Color = vec4(blinn_phong_color, 1.0);
  //out_Color = vec4(planetcolor, 1.0);
}
