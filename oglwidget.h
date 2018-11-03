#ifndef OGLWIDGET_H
#define OGLWIDGET_H

#include <QWidget>
#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <QOpenGLBuffer>
#include <QOpenGLShaderProgram>
#include <QOpenGLVertexArrayObject>
#include <QMatrix4x4>
#include <QMouseEvent>
#include <QKeyEvent>

#include "icosphere.h"

class OGLWidget: public QOpenGLWidget, protected QOpenGLFunctions
{
public:
    OGLWidget(QWidget *parent = nullptr);
    ~OGLWidget() override;
    const QString VSPath = ":/shaders/simple.vert";
    const QString FSPath = ":/shaders/simple.frag";
    constexpr static int ROT_PRECISION = 16; // points per degree

public slots:
    void cleanup();

protected:
    void initializeGL() override;
    void resizeGL(int w, int h) override;
    void paintGL() override;

    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void keyPressEvent(QKeyEvent *event) override;

private:
    static void normalizeAngle(int &angle);
    // rotation euler angles
    int m_xRot, m_yRot, m_zRot;
    // last click position
    QPoint m_lastPos;
    // display wireframe
    bool wireframe;

    // data
    void loadSphere();
    Icosphere m_sphere;

    // opengl objects
    QOpenGLVertexArrayObject m_vao;
    QOpenGLBuffer m_vertex_vbo;
    QOpenGLBuffer m_index_vbo;
    QOpenGLShaderProgram *m_program;

    // uniform locations
    int m_projMatrixLoc;
    int m_viewMatrixLoc;
    int m_modelMatrixLoc;

    int m_wireframeLoc;

    // P, V, M matrices
    QMatrix4x4 m_proj, m_camera, m_world;
};

#endif // OGLWIDGET_H
