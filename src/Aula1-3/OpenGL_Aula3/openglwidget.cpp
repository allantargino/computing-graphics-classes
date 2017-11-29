#include "openglwidget.h"

OpenGLWidget::OpenGLWidget(QWidget *parent) : QOpenGLWidget(parent)
{

}

OpenGLWidget ::~OpenGLWidget()
{
    destroyVBOs();
    destroyShaders();
}


void OpenGLWidget::initializeGL(){
    initializeOpenGLFunctions ();

    qDebug (" OpenGL version : %s", glGetString ( GL_VERSION ));
    qDebug (" GLSL %s", glGetString ( GL_SHADING_LANGUAGE_VERSION ));

    createShaders ();
    createVBOs ();
}


void OpenGLWidget::resizeGL(int width, int height){
    glViewport(0, 0, width, height);
}

void OpenGLWidget::paintGL(){
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glClearColor (0 ,0 ,0 ,1);

    glUseProgram (shaderProgram);
    //glBindVertexArray (vao);
    //glDrawElements (GL_TRIANGLES ,2 * 3, GL_UNSIGNED_INT ,0);

    glEnable(GL_POINT_SPRITE);
    glEnable(GL_VERTEX_PROGRAM_POINT_SIZE);

    glDrawArrays(GL_POINTS, 0, 3);
}

void OpenGLWidget::toggleBackgroundColor ( bool changeBColor ){
    makeCurrent ();
    if (changeBColor)
        glClearColor (0 ,0 ,0 ,1);
    else
        glClearColor (1 ,1 ,1 ,1);
    update ();
}


void OpenGLWidget::createShaders()
{
    makeCurrent ();
    destroyShaders ();
    QString vertexShaderFile (":/shaders/vshader1.glsl");
    QString fragmentShaderFile (":/shaders/fshader1.glsl");

    QFile vs( vertexShaderFile );
    QFile fs( fragmentShaderFile );

    vs. open ( QFile :: ReadOnly | QFile :: Text );
    fs. open ( QFile :: ReadOnly | QFile :: Text );

    QTextStream streamVs (& vs), streamFs (& fs);

    QString qtStringVs = streamVs . readAll ();
    QString qtStringFs = streamFs . readAll ();

    std :: string stdStringVs = qtStringVs . toStdString ();
    std :: string stdStringFs = qtStringFs . toStdString ();

    // Create an empty vertex shader handle
    GLuint vertexShader = 0;
    vertexShader = glCreateShader( GL_VERTEX_SHADER );

    // Send the vertex shader source code to GL
    const GLchar * source = stdStringVs . c_str ();
    glShaderSource( vertexShader , 1, &source , 0);

    // Compile the vertex shader
    glCompileShader( vertexShader );
    GLint isCompiled = 0;
    glGetShaderiv( vertexShader , GL_COMPILE_STATUS , & isCompiled );
    if (isCompiled==GL_FALSE)
    {
        GLint maxLength = 0;
        glGetShaderiv ( vertexShader , GL_INFO_LOG_LENGTH , &
        maxLength );
        // The maxLength includes the NULL character
        std :: vector <GLchar > infoLog ( maxLength );
        glGetShaderInfoLog( vertexShader , maxLength , & maxLength , &
        infoLog [0]) ;
        qDebug ("%s", & infoLog [0]) ;
        glDeleteShader( vertexShader );
        return ;
    }

    // Create an empty fragment shader handle
    GLuint fragmentShader = 0;
    fragmentShader = glCreateShader ( GL_FRAGMENT_SHADER );
    // Send the fragment shader source code to GL
    // Note that std :: string ’s . c_str is NULL character terminated .
    source = stdStringFs . c_str ();
    glShaderSource ( fragmentShader , 1, &source , 0);
    // Compile the fragment shader
    glCompileShader ( fragmentShader );
    glGetShaderiv ( fragmentShader , GL_COMPILE_STATUS , & isCompiled );
    if (isCompiled==GL_FALSE)
    {
        GLint maxLength = 0;
        glGetShaderiv ( fragmentShader , GL_INFO_LOG_LENGTH , &
        maxLength );
        std :: vector <GLchar > infoLog ( maxLength );
        glGetShaderInfoLog ( fragmentShader , maxLength , & maxLength ,
        & infoLog [0]) ;
        qDebug ("%s", & infoLog [0]) ;
        glDeleteShader ( fragmentShader );
        glDeleteShader ( vertexShader );
        return ;
    }

    shaderProgram = glCreateProgram();
    // Attach our shaders to our program
    glAttachShader( shaderProgram , vertexShader );
    glAttachShader ( shaderProgram , fragmentShader );
    // Link our program
    glLinkProgram( shaderProgram );
    // Note the different functions here : glGetProgram * instead of glGetShader *.
    GLint isLinked = 0;
    glGetProgramiv( shaderProgram , GL_LINK_STATUS , ( int *)& isLinked );
    if ( isLinked == GL_FALSE )
    {
        GLint maxLength = 0;
        glGetProgramiv ( shaderProgram , GL_INFO_LOG_LENGTH , &
        maxLength );
        // The maxLength includes the NULL character
        std :: vector <GLchar > infoLog ( maxLength );
        glGetProgramInfoLog ( shaderProgram , maxLength , & maxLength ,
        & infoLog [0]) ;
        qDebug ("%s", & infoLog [0]) ;
        glDeleteProgram ( shaderProgram );
        glDeleteShader ( vertexShader );
        glDeleteShader ( fragmentShader );
        return ;
    }

    glDetachShader( shaderProgram , vertexShader );
    glDetachShader ( shaderProgram , fragmentShader );
    glDeleteShader( vertexShader );
    glDeleteShader ( fragmentShader );
    vs.close ();
    fs.close ();
}

void OpenGLWidget::destroyShaders(){
    makeCurrent();
    glDeleteProgram(shaderProgram);
}

void OpenGLWidget::createVBOs(){
    makeCurrent ();
    destroyVBOs ();

    GLuint VAO;
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    // Position data
    const GLfloat pointPos[] = {
        -0.5f, -0.5f, 0.0f,
        0.5f,  -0.5f, 0.0f,
        0.0f,   0.5f, 0.0f,
    };

    // Color data
    const GLfloat pointCol[] = {
        1.0f, 0.0f, 0.0f,
        0.0f, 1.0f, 0.0f,
        0.0f, 0.0f, 1.0f
    };


    glGenBuffers(2, VBO);

    // VBO for position data
    glBindBuffer(GL_ARRAY_BUFFER, VBO[0]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(pointPos), pointPos, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);
    glEnableVertexAttribArray(0);

    // VBO for color data
    glBindBuffer(GL_ARRAY_BUFFER, VBO[1]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(pointCol), pointCol, GL_STATIC_DRAW);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, NULL);
    glEnableVertexAttribArray(1);
}

void OpenGLWidget::destroyVBOs()
{
    makeCurrent ();

    glDeleteBuffers(1, & vboVertices );
    glDeleteBuffers (1, & vboColors );
    glDeleteBuffers (1, & vboIndices );
    glDeleteVertexArrays (1, &vao);

    vboVertices = 0;
    vboIndices = 0;
    vboColors = 0;
    vao = 0;
}


void OpenGLWidget::toggleDiagonal( bool changeDiagonal )
{
    makeCurrent ();
    glBindBuffer ( GL_ELEMENT_ARRAY_BUFFER , vboIndices );
    unsigned int * indices = ( unsigned int *)glMapBufferRange(
    GL_ELEMENT_ARRAY_BUFFER , 0, 2 * 3 * sizeof ( unsigned int),
    GL_MAP_WRITE_BIT );

    if(changeDiagonal){
        indices [0] = 0; indices [1] = 1; indices [2] = 3;
        indices [3] = 1; indices [4] = 2; indices [5] = 3;
    }else{
        indices [0] = 0; indices [1] = 1; indices [2] = 2;
        indices [3] = 0; indices [4] = 2; indices [5] = 3;
    }

    glUnmapBuffer ( GL_ELEMENT_ARRAY_BUFFER );
    update ();
}

void OpenGLWidget::changeColor(int color){
    qDebug ("Color was changed to: %d", color);
    float convertedColor = color/255.0;
    qDebug ("Color was changed to: %f", convertedColor);

    makeCurrent ();
    glBindBuffer(GL_ARRAY_BUFFER , vboColors);
    float* colors = (float*)glMapBufferRange(GL_ARRAY_BUFFER, 0, 16 * sizeof (float), GL_MAP_WRITE_BIT);

    colors[0] = convertedColor;
    colors[1] = convertedColor;
    colors[2] = convertedColor;

    glUnmapBuffer (GL_ARRAY_BUFFER);
    update ();
}
