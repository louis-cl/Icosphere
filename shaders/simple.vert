attribute vec4 vertex;

uniform mat4 projMatrix;
uniform mat4 mvMatrix;
uniform mat3 normalMatrix;

void main() {
    gl_Position = projMatrix * mvMatrix * vertex;
}
