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

    float texture_x = pass_Texture_Position.x;
    float texture_y = pass_Texture_Position.y;

    if(Horizontal_Mirror_Mode){
        // inverting the texture coordinates around the desired axes
        float inverted_Texture_Position = 1 - pass_Texture_Position.x ;
        texture_x = inverted_Texture_Position;

        //out_Color = texture(TextureFragment, vec2(inverted_Texture_Position, pass_Texture_Position.y)); 
    }

    if(Vertical_Mirror_Mode){
        // inverting the texture coordinates around the desired axes
        float inverted_Texture_Position = 1 - pass_Texture_Position.y ;
        texture_y = inverted_Texture_Position;
        
        //out_Color = texture(TextureFragment, vec2(pass_Texture_Position.x , inverted_Texture_Position)); 
    }
    
    out_Color = texture(TextureFragment, vec2(texture_x, texture_y));

    if(Blur_Mode){
        out_Color = out_Color;
    }

    if(Grayscale_Mode){
        float illuminance = 0.2126 * out_Color.r + 0.7152 * out_Color.g + 0.0722 * out_Color.b ;
        out_Color = vec4(illuminance,illuminance,illuminance, 1.0);
    }

}
