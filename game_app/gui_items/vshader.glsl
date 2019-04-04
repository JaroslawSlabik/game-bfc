#ifdef GL_ES
// Set default precision to medium
precision mediump int;
precision mediump float;
#endif

uniform mat4 u_matrix_projection;
uniform mat4 u_matrix_view;
uniform mat4 u_matrix_model;

attribute vec3 a_position;
attribute vec2 a_texcoord;
attribute vec4 a_base_color;

varying vec2 v_texcoord;
varying vec4 v_base_color;

void main()
{

    // Calculate vertex position in screen space
    //NOTE: That we read the multiplication from right to left
    gl_Position = u_matrix_projection * u_matrix_view * u_matrix_model * vec4(a_position, 1.0);

    // Pass texture coordinate to fragment shader
    // Value will be automatically interpolated to fragments inside polygon faces
    v_texcoord = a_texcoord;
    v_base_color = a_base_color;
    v_base_color = a_base_color;
}
