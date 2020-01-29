#version 150
#extension GL_ARB_explicit_attrib_location : require
// vertex attributes of VAO
layout(location = 0) in vec3 in_Position;
layout(location = 1) in vec3 in_Normal;
layout(location = 2) in vec2 in_Texture_Position;

//Matrix Uniforms as specified with glUniformMatrix4fv
uniform mat4 ModelMatrix;
uniform mat4 ViewMatrix;
uniform mat4 ProjectionMatrix;
uniform mat4 NormalMatrix;

out vec3 pass_Normal;
out vec3 pass_Vertex_Position;
out vec3 pass_Camera_Position;
out vec2 pass_Texture_Position;

void main(void)
{
	gl_Position = (ProjectionMatrix  * ViewMatrix * ModelMatrix) * vec4(in_Position, 1.0);
	
	pass_Normal = (ViewMatrix * vec4(in_Normal, 0.0)).xyz;
	//pass_Normal = (NormalMatrix * vec4(in_Normal, 0.0)).xyz;

	pass_Vertex_Position = ((ViewMatrix * ModelMatrix) * vec4(in_Position, 1.0)).xyz; 
	
	pass_Camera_Position = (inverse(transpose(ViewMatrix)) * vec4(0.0, 0.0, 0.0, 1.0)).xyz;
	//pass_Camera_Position = (ViewMatrix * vec4(0.0, 0.0, 0.0, 1.0)).xyz;

	pass_Texture_Position = in_Texture_Position;
}
