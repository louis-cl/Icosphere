#include "oglwidget.h"

OGLWidget::OGLWidget(QWidget *parent)
    : QOpenGLWidget (parent)
    , m_xRot(0)
    , m_yRot(0)
    , m_zRot(0)
    , wireframe(false)
    , m_sphere(4)
    , m_vertex_vbo(QOpenGLBuffer::VertexBuffer)
    , m_index_vbo(QOpenGLBuffer::IndexBuffer)
    , m_program(nullptr)
{
    setFocusPolicy(Qt::StrongFocus); // get keyboard event
}

OGLWidget::~OGLWidget()
{
    cleanup();
}

void OGLWidget::cleanup()
{
    if (m_program == nullptr) return;
    makeCurrent();
    m_vertex_vbo.destroy();
    m_index_vbo.destroy();
    delete m_program;
    m_program = nullptr;
    doneCurrent();
}

void OGLWidget::initializeGL()
{
    initializeOpenGLFunctions();

    // create buffers
    glClearColor(0,0,0,1);
    m_vao.create();
    m_vertex_vbo.create();
    m_index_vbo.create();

    // load shaders
    m_program = new QOpenGLShaderProgram;
    if (!m_program->addShaderFromSourceFile(QOpenGLShader::Vertex, VSPath) ||
            !m_program->addShaderFromSourceFile(QOpenGLShader::Fragment, FSPath)) {
        qDebug() << m_program->log();
        close();
    }
    m_program->bindAttributeLocation("vertex", 0);
    //m_program->bindAttributeLocation("normal", 1);
    m_program->link();
    m_program->bind();

    m_projMatrixLoc = m_program->uniformLocation("projMatrix");
    m_viewMatrixLoc = m_program->uniformLocation("viewMatrix");
    m_modelMatrixLoc = m_program->uniformLocation("modelMatrix");
    m_wireframeLoc = m_program->uniformLocation("wireframe");

    // START VAO
    QOpenGLVertexArrayObject::Binder vaoBinder(&m_vao);

        // VERTEX VBO
    m_vertex_vbo.bind();
    m_vertex_vbo.setUsagePattern(QOpenGLBuffer::StaticDraw);
    m_vertex_vbo.allocate(m_sphere.vertices(),
        static_cast<int>(m_sphere.n_vertices() * sizeof(QVector3D)));

    m_index_vbo.bind();
    m_index_vbo.setUsagePattern(QOpenGLBuffer::StaticDraw);
    m_index_vbo.allocate(m_sphere.indices(),
        static_cast<int>(3 * m_sphere.n_triangles() * sizeof(GLushort)));

    m_program->enableAttributeArray(0);
    m_program->setAttributeBuffer(0, GL_FLOAT, 0, 3, 3*sizeof(GLfloat));

    m_program->release();

    m_world.setToIdentity();
    m_proj.setToIdentity();
    m_camera.setToIdentity();
    m_camera.translate(0, 0, -2);
}

void OGLWidget::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // display only lines
    if (wireframe) glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    else glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

    glClearColor(0.3f,0.3f,0.3f,1.0);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);


    m_world.setToIdentity();
    m_world.rotate(m_xRot / ROT_PRECISION, 1, 0, 0);
    m_world.rotate(m_yRot / ROT_PRECISION, 0, 1, 0);
    m_world.rotate(m_zRot / ROT_PRECISION, 0, 0, 1);

    QOpenGLVertexArrayObject::Binder vaoBinder(&m_vao);
    m_program->bind();

    m_program->setUniformValue(m_projMatrixLoc, m_proj);
    m_program->setUniformValue(m_viewMatrixLoc, m_camera);
    m_program->setUniformValue(m_modelMatrixLoc, m_world);
    m_program->setUniformValue(m_wireframeLoc, wireframe);

    glDrawElements(GL_TRIANGLES,
                   static_cast<int>(3*m_sphere.n_triangles()),
                   GL_UNSIGNED_SHORT,
                   nullptr);

    m_program->release();
}

void OGLWidget::resizeGL(int w, int h)
{
    m_proj.setToIdentity();
    m_proj.perspective(90.0f, GLfloat(w) / h, 0.01f, 100.0f);
}

void OGLWidget::mousePressEvent(QMouseEvent * event)
{
    m_lastPos = event->pos();
}

void OGLWidget::normalizeAngle(int &angle)
{
    constexpr int d = 360 * ROT_PRECISION;
    while (angle < 0) angle += d;
    while (angle > d) angle -= d;
}

void OGLWidget::mouseMoveEvent(QMouseEvent * event)
{
    QPoint D = event->pos() - m_lastPos;
    int dx = D.x();
    int dy = D.y();
    if (event->buttons() & Qt::LeftButton) {
        m_xRot += 8 * dy;
        normalizeAngle(m_xRot);
        m_yRot += 8 * dx;
        normalizeAngle(m_yRot);
        update();
    }
    m_lastPos = event->pos();
}

void OGLWidget::keyPressEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_Space) {
        wireframe = !wireframe;
        update();
    }
}
