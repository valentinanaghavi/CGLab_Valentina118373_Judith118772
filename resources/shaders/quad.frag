#version 150

in vec2 pass_Texture_Position;

out vec4 out_Color;

uniform sampler2D TextureFragment;


void main() {

    vec4 color_from_tex = texture(TextureFragment, pass_Texture_Position);
    out_Color = color_from_tex;

}
