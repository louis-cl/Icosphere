attribute vec3 vertex;


uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat4 projMatrix;

varying vec3 vert;

void main() {
    vec4 v_model = modelMatrix * vec4(vertex, 1.0);
    vert = v_model.xyz;
    gl_Position = projMatrix * viewMatrix * v_model;
}
