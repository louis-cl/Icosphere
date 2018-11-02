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
        {1,4,0},{4,9,0},{4,5,9},{8,5,4},{1,8,4},
        {1,10,8},{10,3,8},{8,3,5},{3,2,5},{3,7,2},
        {3,10,7},{10,6,7},{6,11,7},{6,0,11},{6,1,0},
        {10,1,6},{11,0,9},{2,11,9},{5,2,9},{11,2,7}
    };

    m_vertices = vertices;
    m_triangles = triangles;
}


