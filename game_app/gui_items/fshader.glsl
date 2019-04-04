#ifdef GL_ES
// Set default precision to medium
precision mediump int;
precision mediump float;
#endif

uniform sampler2D u_texture;
//NOTE: jeśli textura jest załadowana to u_no_texture = vec4(0.0,0.0,0.0,0.0) w przeciwnym razie u_no_texture = vec4(1.0,1.0,1.0,1.0)
uniform vec4 u_no_texture;
uniform float u_font;

varying vec4 v_base_color;

varying vec2 v_texcoord;

void main()
{
    vec4 baseColor = vec4(v_base_color.r / 255.0f, v_base_color.g / 255.0f, v_base_color.b / 255.0f, v_base_color.a / 255.0f);

    if(u_font == 1.0)
    {
        float font = texture2D(u_texture, v_texcoord).r;
        vec4 sampled = vec4(1.0, 1.0, 1.0, font);
        gl_FragColor = baseColor * sampled;
    }
    else
    {
        vec4 texel = texture2D(u_texture, v_texcoord);
        texel = clamp(texel + u_no_texture, 0.0, 1.0);
        texel *= baseColor;
        gl_FragColor = texel;
    }
}
