#version 330
varying vec3 vert;

uniform bool wireframe = false;

// V, N, P, lightPos han d'estar al mateix espai de coordenades
// V  vector unitari cap a l'observador
// N  la normal
// P  la posicio
vec4 light(vec3 V, vec3 N, vec3 P, vec3 lightPos) {
        const float shininess = 0.1*128;
        vec3 Ia = vec3(0.1, 0.18725, 0.1745);
        vec3 Id = vec3(0.396, 0.74151, 0.69102);
        vec3 Is = vec3(0.297254, 0.30829, 0.306678);
        N = normalize(N);
        vec3 L = normalize(lightPos - P);
        vec3 R = reflect(-L, N);
        float NdotL = max(0.0, dot(N,L));
        float RdotV = max(0.0, dot(R,V));
        float spec =  pow( RdotV, shininess);
        return vec4(Ia + Id*NdotL + Is*spec, 1.0);
}

vec3 observer = vec3(0, 0, -2); // hardcoded

void main() {
    if (wireframe)
        gl_FragColor = vec4(1.0);
    else {
        vec3 V = normalize(vert - observer);
        vec4 l1 = light(V, vert, vert, vec3(2.0, 2.0, 3.0));
        gl_FragColor = l1;
    }
}
