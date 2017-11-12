#ifndef OPENGLWIDGET_H
#define OPENGLWIDGET_H

#include <QWidget>
#include <QOpenGLWidget>
#include <QOpenGLExtraFunctions>
#include "memory.h"
#include "model.h"
#include "light.h"
#include "camera.h"

class OpenGLWidget : public QOpenGLWidget, protected QOpenGLExtraFunctions {
    Q_OBJECT

public:
    OpenGLWidget(QWidget* parent = 0);
    std::shared_ptr<Model> model = nullptr;

    Light light;
    Camera camera;

protected:
    void initializeGL();
    void resizeGL(int width, int height);
    void paintGL();

    void keyPressEvent(QKeyEvent *event);

signals:
    void statusBarMessage(QString);

public slots:
    void showFileOpenDialog();
    void loadSampleModel();
    void changeNearField(QString value);
    void changeFarField(QString value);

};
#endif // OPENGLWIDGET_H
