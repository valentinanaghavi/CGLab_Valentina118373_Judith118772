#version 150

in vec2 pass_Texture_Position;

out vec4 out_Color;

uniform sampler2D TextureFragment;
uniform bool Grayscale_Mode;
uniform bool Horizontal_Mirror_Mode;
uniform bool Vertical_Mirror_Mode;
uniform bool Blur_Mode;


void main() {

    vec4 color_from_tex = texture(TextureFragment, pass_Texture_Position);
    out_Color = color_from_tex;

    if(Grayscale_Mode){
        float illuminance = 0.2126 * color_from_tex.r + 0.7152 * color_from_tex.g + 0.0722 * color_from_tex.b ;
        out_Color = vec4(illuminance,illuminance,illuminance, 1.0);
    }

    if(Horizontal_Mirror_Mode){
        // inverting the texture coordinates around the desired axes
        float inverted_Texture_Position = 1 - pass_Texture_Position.x ;
        out_Color = texture(TextureFragment, vec2(inverted_Texture_Position, pass_Texture_Position.y));
    }

    if(Vertical_Mirror_Mode){
        // inverting the texture coordinates around the desired axes
        float inverted_Texture_Position = 1 - pass_Texture_Position.y ;
        out_Color = texture(TextureFragment, vec2(pass_Texture_Position.x , inverted_Texture_Position));
    }

    if(Blur_Mode){
        out_Color = color_from_tex;
    }

}
