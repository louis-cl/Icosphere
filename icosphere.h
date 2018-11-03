#ifndef ICOSPHERE_H
#define ICOSPHERE_H

#include <QVector3D>
#include <QtOpenGL>
#include <vector>
#include <array>

class Icosphere
{
public:
    using Index = GLushort;
    using Vertex = QVector3D;

    Icosphere(unsigned int level);
    const Vertex *vertices() const {
        return &m_vertices[0];
    }
    const Index *indices() const {
        return &m_triangles[0][0];
    }
    unsigned long n_vertices() const {
        return m_vertices.size();
    }
    unsigned long n_triangles() const {
        return m_triangles.size();
    }
private:
    using Triangle = std::array<Index, 3>;
    struct Edge : public std::pair<Index,Index> {
        Edge(Index a, Index b) {
            if (b > a) std::swap(a,b);
            first = a;
            second = b;
        }
    };
    // for done edges store the index of the midpoint vertex
    struct Edge_hash {
        std::size_t operator () (const Edge &p) const {
            auto h1 = std::hash<Index>{}(p.first);
            auto h2 = std::hash<Index>{}(p.second);
            return h1 ^ h2;
        }
    };

    using TriangleList = std::vector<Triangle>;
    using VertexList = std::vector<Vertex>;

    void icosahedron();
    void subdivide();
    VertexList m_vertices;
    TriangleList m_triangles;
};

#endif
