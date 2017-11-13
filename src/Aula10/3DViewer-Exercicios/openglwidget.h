#ifndef OPENGLWIDGET_H
#define OPENGLWIDGET_H

#include <QWidget>
#include <QOpenGLWidget>
#include <QOpenGLExtraFunctions>
#include "memory.h"
#include "model.h"
#include "light.h"
#include "camera.h"
#include "trackball.h"

class OpenGLWidget : public QOpenGLWidget, protected QOpenGLExtraFunctions
{
    Q_OBJECT

  public:
    OpenGLWidget(QWidget *parent = 0);
    std::shared_ptr<Model> model = nullptr;

    Light light;
    Camera camera;

    void mouseMoveEvent(QMouseEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    QTimer timer;

    TrackBall trackBall;

  protected:
    void initializeGL();
    void resizeGL(int width, int height);
    void paintGL();

  signals:
    void statusBarMessage(QString);
    void enableComboShaders(bool);

  public slots:
    void showFileOpenDialog();
    void loadSampleModel();

    void changeShader(int);

    void animate();
};
#endif // OPENGLWIDGET_H
