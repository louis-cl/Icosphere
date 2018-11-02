#include "icosphere.h"

Icosphere::Icosphere(unsigned int level)
{
    // START WITH LEVEL 0 : icosahedron
    // (phi, 1, 0) normalized is (Z,X,N)
    constexpr float X = .525731112119133606f;
    constexpr float Z = .850650808352039932f;
    constexpr float N = 0.f;

    static const VertexList vertices =
    {
      {-X,N,Z}, {X,N,Z}, {-X,N,-Z}, {X,N,-Z},
      {N,Z,X}, {N,Z,-X}, {N,-Z,X}, {N,-Z,-X},
      {Z,X,N}, {-Z,X, N}, {Z,-X,N}, {-Z,-X, N}
    };

    static const TriangleList triangles =
    {
      {0,4,1},{0,9,4},{9,5,4},{4,5,8},{4,8,1},
      {8,10,1},{8,3,10},{5,3,8},{5,2,3},{2,7,3},
      {7,10,3},{7,6,10},{7,11,6},{11,0,6},{0,1,6},
      {6,1,10},{9,0,11},{9,11,2},{9,2,5},{7,2,11}
    };

    m_vertices = vertices;
    m_triangles = triangles;
}


