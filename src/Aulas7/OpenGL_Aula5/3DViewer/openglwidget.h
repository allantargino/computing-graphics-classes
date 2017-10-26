#ifndef OPENGLWIDGET_H
#define OPENGLWIDGET_H

#include <QWidget>
#include <QOpenGLWidget>
#include <QOpenGLExtraFunctions>
#include "memory.h"
#include "model.h"
#include "light.h"

class OpenGLWidget : public QOpenGLWidget, protected QOpenGLExtraFunctions {
    Q_OBJECT

public:
    OpenGLWidget(QWidget* parent = 0);
    std::shared_ptr<Model> model = nullptr;
    float angle;
    float X;
    float Y;
    float Z;

    Light light ;
    QMatrix4x4 projectionMatrix ;
    QMatrix4x4 viewMatrix ;

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
    void rotateObject(int value);
    void AxisXChecked(bool checked);
    void AxisYChecked(bool checked);
    void AxisZChecked(bool checked);

    void changeShader (int);

};
#endif // OPENGLWIDGET_H
