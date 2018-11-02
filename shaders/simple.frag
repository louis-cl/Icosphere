varying vec3 vert;

void main() {
    gl_FragColor = vec4(vec3(0.2 + 0.8*abs(vert.z)), 1.0);
}
