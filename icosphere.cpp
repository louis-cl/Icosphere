#include "icosphere.h"

Icosphere::Icosphere(unsigned int level)
{
    // (phi, 1, 0) normalized is (Z,X,N)
    //constexpr float X = .525731112119133606f;
    //constexpr float Z = .850650808352039932f;
    //constexpr float N = 0.f;
    m_vertices.append(QVector3D(0.0, 0.5, 0.0));
    m_vertices.append(QVector3D(0.5, -0.5, 0.0));
    m_vertices.append(QVector3D(-0.5, -0.5, 0.0));

    m_indices.append(0);
    m_indices.append(1);
    m_indices.append(2);
}


