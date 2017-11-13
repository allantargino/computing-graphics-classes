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
#include "material.h"

class Model : public QOpenGLExtraFunctions {
public:
    Model(QOpenGLWidget* _glWidget);
    ~Model();

    Material material;
    int shaderIndex ;
    int numShaders ;
    std::vector<GLuint> shaderProgram ;
    void createNormals();

    std::unique_ptr<QVector4D[]> vertices;
    std::unique_ptr<unsigned int[]> indices;
    std::unique_ptr<QVector3D[]> normals;

    QOpenGLWidget* glWidget;
    unsigned int numVertices;
    unsigned int numFaces;

    GLuint vao = 0;
    GLuint vboVertices = 0;
    GLuint vboIndices = 0;
    GLuint vboNormals = 0;

    void createVBOs();
    void createShaders();
    void destroyVBOs();
    void destroyShaders();

    void readOFFFile(const QString& fileName);
    void drawModel(float x, float y, float z);

    QMatrix4x4 modelMatrix;
    QVector3D midPoint;
    double invDiag;
};
#endif // MODEL_H
