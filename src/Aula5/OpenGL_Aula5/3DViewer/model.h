#ifndef MODEL_H
#define MODEL_H

#include <QtOpenGL>
#include <QOpenGLWidget>
#include <QOpenGLExtraFunctions>
#include <QTextStream>
#include <QFile>
#include <fstream>
#include <limits>
#include <iostream>
#include <memory>

class Model : public QOpenGLExtraFunctions {
public:
    Model(QOpenGLWidget* _glWidget);
    ~Model();

    std::unique_ptr<QVector4D[]> vertices;
    std::unique_ptr<unsigned int[]> indices;

    QOpenGLWidget* glWidget;
    unsigned int numVertices;
    unsigned int numFaces;

    GLuint vao = 0;
    GLuint vboVertices = 0;
    GLuint vboIndices = 0;
    GLuint shaderProgram = 0;

    void createVBOs();
    void createShaders();
    void destroyVBOs();
    void destroyShaders();
    void readOFFFile(const QString& fileName);
    void drawModel(float angle, float X, float Y, float Z);

    QMatrix4x4 modelMatrix;
    QVector3D midPoint;
    double invDiag;
};
#endif // MODEL_H
