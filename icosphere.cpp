#include "icosphere.h"
#include <unordered_map>

Icosphere::Icosphere(unsigned int level)
    : m_level(level)
{
    icosahedron(); // level 0
    for (unsigned int i = 0; i < level; ++i)
        subdivide();
}

void Icosphere::icosahedron()
{
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

void Icosphere::subdivide() {
    // create 4 triangles from 1 triangle by midpoint of edges

    // reserve more memory
    size_t N = m_vertices.size();
    size_t T = m_triangles.size();
    m_vertices.reserve(N + 3*T/2); // add 3 vertices by face, counted twice
    m_triangles.reserve(4*T); // each triangle is turned into 4

    std::unordered_map<Edge, Index, Edge_hash> edge2mid;

    for (size_t i = 0; i < T; ++i) {
        Triangle &t = m_triangles[i];

        // midpoints generation
        Triangle midpoints; // this will be the middle face

        for (unsigned char j = 0; j < 3; ++j) {
            // get jth midpoint
            Edge e(t[j], t[(j+1)%3]);
            auto search = edge2mid.find(e);
            if (search != edge2mid.end()) { // already did it
                midpoints[j] = search->second;
            } else { // have to create it
                Vertex mid = (m_vertices[e.first] + m_vertices[e.second])/2;
                mid.normalize(); // sphere approx !!
                edge2mid[e] = midpoints[j] = static_cast<Index>(m_vertices.size());
                m_vertices.push_back(mid);
            }
        }

        Index p1 = t[0];
        Index p2 = t[1];
        Index p3 = t[2];
        Index q1 = midpoints[0]; // mid of p1,p2
        Index q2 = midpoints[1]; // mid of p2,p3
        Index q3 = midpoints[2]; // mid of p3,p1
        // face creation
        m_triangles.push_back({p1,q1,q3});
        m_triangles.push_back({q1,p2,q2});
        m_triangles.push_back({q3,q2,p3});

        // delete the old face and put the middle one
        t = midpoints;
    }
}
