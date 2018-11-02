#include "icosphere.h"

Icosphere::Icosphere(unsigned int level)
{
    // START WITH LEVEL 0 : icosahedron
    // (phi, 1, 0) normalized is (Z,X,N)
    constexpr float X = .525731112119133606f;
    constexpr float Z = .850650808352039932f;
    constexpr float N = 0.f;

    m_vertices.push_back({0.0, 0.5, 0.0});
    m_vertices.push_back({0.5, -0.5, 0.0});
    m_vertices.push_back({-0.5, -0.5, 0.0});

    m_triangles.push_back({0,1,2});
}


