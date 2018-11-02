#ifndef ICOSPHERE_H
#define ICOSPHERE_H

#include <QVector>
#include <QVector3D>
#include <QtOpenGL>

class Icosphere
{
public:
    Icosphere(unsigned int level);
    const QVector3D *vertices() const {
        return m_vertices.constData();
    }
    const GLushort *indices() const {
        return m_indices.constData();
    }
    int n_vertices() const {
        return m_vertices.size();
    }
    int n_indices() const {
        return m_indices.size();
    }
private:
    QVector<QVector3D> m_vertices;
    QVector<GLushort> m_indices;
};

#endif
