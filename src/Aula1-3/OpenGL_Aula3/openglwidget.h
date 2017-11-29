#ifndef OPENGLWIDGET_H
#define OPENGLWIDGET_H

#include <memory>
#include <QtOpenGL>
#include <QOpenGLWidget>
#include <QOpenGLExtraFunctions>

class OpenGLWidget : public QOpenGLWidget, protected QOpenGLExtraFunctions
{
    Q_OBJECT
public:
    explicit OpenGLWidget(QWidget *parent = 0);
            ~OpenGLWidget();

    GLuint shaderProgram;

    void createVBOs();
    void createShaders();
    void destroyVBOs();
    void destroyShaders();

    GLuint vao = 0;
    GLuint vbo[3];

protected:
    void initializeGL();
    void resizeGL(int width, int height);
    void paintGL();

};

#endif // OPENGLWIDGET_H
