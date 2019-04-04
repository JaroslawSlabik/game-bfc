#ifdef GL_ES
// Set default precision to medium
precision mediump int;
precision mediump float;
#endif

uniform sampler2D texture;

varying vec4 v_base_color;

varying vec2 v_texcoord;

void main()
{
    // Set fragment color from texture
    gl_FragColor = texture2D(texture, v_texcoord) * vec4(v_base_color.x / 255.0f, v_base_color.y / 255.0f, v_base_color.z / 255.0f, v_base_color.w / 255.0f);
}
