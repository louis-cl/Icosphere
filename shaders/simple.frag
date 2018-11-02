#version 330
varying vec3 vert;

uniform bool wireframe = false;

void main() {
    if (wireframe)
        gl_FragColor = vec4(1.0);
    else
        gl_FragColor = vec4(vec3(vert.z), 1.0);
}
