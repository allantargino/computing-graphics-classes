#include "openglwidget.h"

OpenGLWidget::OpenGLWidget(QWidget* parent)
    : QOpenGLWidget(parent)
{
}
void OpenGLWidget::initializeGL()
{
    initializeOpenGLFunctions();

    qDebug("OpenGL version : %s", glGetString(GL_VERSION));
    qDebug("GLSL %s", glGetString(GL_SHADING_LANGUAGE_VERSION));

    glEnable(GL_DEPTH_TEST);
}

void OpenGLWidget::resizeGL(int w, int h)
{
    glViewport(0, 0, w, h);
    camera.resizeViewport(w, h);

    update();
}

void OpenGLWidget::paintGL()
{
    glClear ( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
    glClearColor(1,1,1,1);

    if (!model )
        return;

    int shaderProgramID = model -> shaderProgram [model -> shaderIndex ];
    QVector4D ambientProduct = light.ambient*model->material .
    ambient ;
    QVector4D diffuseProduct = light.diffuse*model->material. diffuse ;
    QVector4D specularProduct = light.specular*model -> material.specular ;

    GLuint locLightPosition = glGetUniformLocation ( shaderProgramID , "lightPosition");
    GLuint locAmbientProduct = glGetUniformLocation ( shaderProgramID , "ambientProduct");
    GLuint locDiffuseProduct = glGetUniformLocation ( shaderProgramID , "diffuseProduct");
    GLuint locSpecularProduct = glGetUniformLocation ( shaderProgramID , "specularProduct");
    GLuint locShininess = glGetUniformLocation ( shaderProgramID , "shininess");
    GLuint locProjection = glGetUniformLocation ( shaderProgramID, "projection");
    GLuint locView = glGetUniformLocation ( shaderProgramID , "view");

    glUseProgram(shaderProgramID);

    glUniform4fv(locLightPosition , 1, &( light . position [0]) );
    glUniform4fv(locAmbientProduct , 1, &( ambientProduct [0]) );
    glUniform4fv(locDiffuseProduct , 1, &( diffuseProduct [0]) );
    glUniform4fv(locSpecularProduct , 1, &( specularProduct [0]) );
    glUniform1f(locShininess , model -> material . shininess );
    glUniformMatrix4fv (locProjection, 1, GL_FALSE , camera.projectionMatrix.data());
    glUniformMatrix4fv (locView, 1, GL_FALSE , camera.viewMatrix.data());

    model->drawModel(-1.0f,0.0f,0.0f);

    model->drawModel(1.0f,0.0f,0.0f);
}

void OpenGLWidget::showFileOpenDialog()
{
    QByteArray fileFormat = "off ";
    QString fileName = QFileDialog :: getOpenFileName (this ,
    " Open File ", QDir :: homePath () ,
    QString ("\%1 Files (*.\%2) ").arg( QString ( fileFormat .
    toUpper ())).arg( QString ( fileFormat )), 0
    # ifdef Q_OS_LINUX
    , QFileDialog :: DontUseNativeDialog
    # endif
    );
    int shaderIndex = 0;
    if (! fileName . isEmpty ())
    {
    if ( model )
    shaderIndex = model -> shaderIndex ;
    model = std :: make_shared <Model >( this );
    model -> shaderIndex = shaderIndex ;
    model -> readOFFFile ( fileName );
    emit statusBarMessage ( QString (" Vertices : \%1 , Faces : \%2"
    ).arg(model -> numVertices ).arg(model -> numFaces ));
    }
    update ();
}

void OpenGLWidget::loadSampleModel()
{
    QString fileName = "..\\..\\..\\off-models\\Misc\\bunny.off";
    int shaderIndex = 3;

    if (model)
        shaderIndex = model->shaderIndex;
    model = std::make_shared<Model>(this);
    model->shaderIndex = shaderIndex;
    model->readOFFFile(fileName);
    emit statusBarMessage(QString("Vertices: \%1 , Faces : \%2").arg(model->numVertices).arg(model->numFaces));

    update();
}

void OpenGLWidget::keyPressEvent(QKeyEvent *event)
{
    switch (event->key())
    {
    case Qt::Key_Left:
        camera.MoveCameraLeft();
        break;
    case Qt::Key_Right:
        camera.MoveCameraRight();
        break;
    case Qt::Key_Up:
        camera.MoveCameraUp();
        break;
    case Qt::Key_Down:
        camera.MoveCameraDown();
        break;
    case Qt::Key_1:
        camera.IncreaseDistance();
        break;
    case Qt::Key_2:
        camera.DecreaseDistance();
        break;
    case Qt::Key_Escape:
        qApp->quit();
        break;
    default:
        break;
    }
    update();
}

void OpenGLWidget::changeNearField(QString value){
    camera.nearField = value.toFloat();
    resizeGL(width(), height());
}

void OpenGLWidget::changeFarField(QString value){
    camera.farField = value.toFloat();
    resizeGL(width(), height());
}
