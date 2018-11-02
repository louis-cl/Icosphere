#ifndef ICOSPHERE_H
#define ICOSPHERE_H

#include <QVector3D>
#include <QtOpenGL>
#include <vector>

class Icosphere
{
public:
    using Index = GLushort;
    struct Triangle {
        Index index[3];
    };
    using TriangleList = std::vector<Triangle>;
    using VertexList = std::vector<QVector3D>;

    Icosphere(unsigned int level);
    const QVector3D *vertices() const {
        return &m_vertices[0];
    }
    const Index *indices() const {
        return &m_triangles[0].index[0];
    }
    unsigned long n_vertices() const {
        return m_vertices.size();
    }
    unsigned long n_triangles() const {
        return m_triangles.size();
    }
private:
    VertexList m_vertices;
    TriangleList m_triangles;
};

#endif
