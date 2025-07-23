//Repo created on Feb 15 2024
//TODO:
//1. Make it even executable
//1. Understand GLEW GLU dependency - GLFW wanted only
//3. Change .cpp in to .c
#include <iostream>
#include <chrono>
#include <thread>
#include <string>
#include <cstring>
#include <cstdint>
#include <memory>
#include <vector>
#include <random>

#include <GL/glew.h>
//#include <GL/GLU.h>
#include <GLFW/glfw3.h>

enum EnumType
{
    NMESSAGE,
    NWARNING,
    NERROR
};

typedef struct {
    int x, y;
} POINT;
//Decided to remove plattform-specific code - espacially these from windows.
void PrintNotification(EnumType type, const wchar_t* msg, int MB_Type);

const GLint WIDTH = 800, HEIGHT = 600;
GLuint VAO, VBO, shader;

// Vertex Shader (GLSL)
static const char* vShader = "                                                          \n\
#version 330                                                                            \n\
                                                                                        \n\
layout (location = 0) in vec3 pos;                                                      \n\
                                                                                        \n\
void main()                                                                             \n\
{                                                                                       \n\
                                                                                        \n\
                                                                                        \n\
                                                                                        \n\
    float ScaleFactor = 0.25f;                                                          \n\
    gl_Position = vec4(ScaleFactor * pos.x, ScaleFactor *  pos.y, pos.z, 1.0);          \n\
                                                                                        \n\
                                                                                        \n\
}";                                                      

static const char* fShader = "                                                          \n\
#version 330                                                                            \n\
                                                                                        \n\
out vec4 colour;                                                                        \n\
                                                                                        \n\
void main()                                                                             \n\
{                                                                                       \n\
                                                                                        \n\
                                                                                        \n\
    colour = vec4(1.0, 1.0, 0.0, 1.0);                                                  \n\
                                                                                        \n\
                                                                                        \n\
                                                                                        \n\
}";

// The shader Stuff | theProgram is the mainShader!! 
void AddShader(GLuint theProgram, const char* shaderCode, GLenum shaderType) { 
    GLuint theShader = glCreateShader(shaderType);

    const GLchar* theCode[1];
    theCode[0] = shaderCode;

    GLint codeLength[1];
    codeLength[0] = strlen(shaderCode);

    glShaderSource(theShader, 1, theCode, codeLength);
    glCompileShader(theShader);


    constexpr uint16_t logSize = 1024;

    GLint result = 0;
    GLchar eLog[logSize] = { 0 }; // 128 bytes
    constexpr int bufferSize = 512 + logSize; // Gr��e des Puffers

    glGetShaderiv(theShader, GL_COMPILE_STATUS, &result); // *param = result.
    if (result != 1) {
        glGetShaderInfoLog(theShader, logSize / 8, NULL, eLog); // here ist getshader and not get program.
        wchar_t text[bufferSize];
        memset(text, 0, bufferSize * sizeof(wchar_t));
        swprintf(text, bufferSize, L"Your %d Shader Code (GLSL) compile error!!"
            L"\nYour log is:\n %lc", shaderType, eLog);

        //PrintNotification(NERROR, text, 1);
        return;
    }
    glAttachShader(theProgram, theShader); // "anh�ngen".
    return;
}


// The Program stuff
void CompileShaders() {
    shader = glCreateProgram();
    if (!shader)
        //PrintNotification(NERROR, L"Error creating shader!", 1); return;
    AddShader(shader, vShader, GL_VERTEX_SHADER);
    AddShader(shader, fShader, GL_FRAGMENT_SHADER);

    GLint result = 0;
    constexpr uint16_t logSize = 1024;
    constexpr int bufferSize = 512 + logSize; // Gr��e des Puffers
    GLchar eLog[logSize] = { 0 }; // 128 bytes

    glLinkProgram(shader);
    glGetProgramiv(shader, GL_LINK_STATUS, &result); // *param = result.
    if (!result) { 
        glGetProgramInfoLog(shader, logSize / 8, NULL, eLog);

        wchar_t text[bufferSize];
        memset(text, 0, bufferSize);
        swprintf(text, bufferSize, L"ERROR: linking program failed (1)"
            L"\nYour log is:\n %ls", eLog);

        //PrintNotification(NERROR, text, 1);
        return;
    }

    glValidateProgram(shader); // �berpr�fen bzw. best�tigen.

    glGetProgramiv(shader, GL_VALIDATE_STATUS, &result); // *param = result.
    if (!result) {
        glGetProgramInfoLog(shader, logSize / 8, NULL, eLog);

        wchar_t text[bufferSize];
        memset(text, 0, bufferSize * sizeof(wchar_t));
        swprintf(text, bufferSize, L"ERROR: Validate program failed"
                                   L"\nYour log is:\n %ls", eLog);
        //PrintNotification(NERROR, text, 1); return;
    }
}

#pragma region ManualShit
void MoveX(float& x, float ControllerX) {
    x += ControllerX;
}

void MoveY(float& y, float ControllerY) {
    y += ControllerY;
}

void MoveZ(float& z, float ControllerZ) {
    z += ControllerZ;
}

void rotateY(float& x, float& y, float& z, float theta) {
    float newX = x * cos(theta) + z * sin(theta);
    float newZ = -x * sin(theta) + z * cos(theta);
    x = newX;
    z = newZ;
}

void rotateX(float& x, float& y, float& z, float theta) {
    float newY = y * cos(theta) - z * sin(theta);
    float newZ = y * sin(theta) + z * cos(theta);
    y = newY;
    z = newZ;
}
#pragma endregion ManualShit

void CreateTriangle(POINT cursor) {
    const int resX = 3440;
    const int resY = 1440;

    float angleX = static_cast<float>(cursor.x) / (resX / 200) / 25;
    float angleY = static_cast<float>(cursor.y) / (resY / 200) / 25;

    constexpr int ObjectAmount = 1;
    constexpr int AxisAmount = 3;
    constexpr int vertexAmount = AxisAmount * 3 * ObjectAmount;
    GLsizeiptr DataSize = vertexAmount * sizeof(GLfloat);

    GLfloat vertices[vertexAmount * 2] = {
        -1.0f, -1.0f, 0.0f,
         1.0f, -1.0f, 0.0f,
        -1.0f,  3.0f, 0.0f,

        -1.0f,  1.0f, 0.0f,
         1.0f, -1.0f, 0.0f,
        -1.0f,  2.0f, 0.0f
    };

    static float XTranslation = 0.0f;
    static float YTranslation = 0.0f;
    static float ZTranslation = 0.0f;

    static float XRotation = 0.0f;
    static float YRotation = 0.0f;
    static float ZRotation = 0.0f;

    for (int i = 0; i < vertexAmount; i += 3) {
        float& x = vertices[i];
        float& y = vertices[i + 1];
        float& z = vertices[i + 2];

        MoveX(x, XTranslation);
        MoveY(y, YTranslation);
        MoveZ(z, ZTranslation);

        rotateY(x, y, z, YRotation);
        rotateX(x, y, z, XRotation);

        if (GetAsyncKeyState('D'))
        {
            XTranslation += 0.1f;
        }
        if (GetAsyncKeyState('A'))
        {

            XTranslation -= 0.1f;
        }
        if (GetAsyncKeyState('W'))
        {
            YTranslation += 0.1f;
        }
        if (GetAsyncKeyState('S'))
        {

            YTranslation -= 0.1f;
        }



        if (GetAsyncKeyState(VK_UP))
        {

            XRotation -= 0.05f;
        }
        if (GetAsyncKeyState(VK_DOWN))
        {

            XRotation += 0.05f;
        }


        if (GetAsyncKeyState(VK_RIGHT))
        {

            YRotation -= 0.05f;
        }
        if (GetAsyncKeyState(VK_LEFT))
        {

            YRotation += 0.05f;
        }
    }


    glGenVertexArrays(ObjectAmount, &VAO);
    glBindVertexArray(VAO);

    glGenBuffers(ObjectAmount, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    glBufferData(GL_ARRAY_BUFFER, DataSize , vertices, GL_DYNAMIC_DRAW);

    glVertexAttribPointer(0, AxisAmount, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(0);


    // do something here.

    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    // Just bind it to nothing, instead of deleting it
    /*glDeleteVertexArrays(vertexAmount, &VAO); 
    glDeleteBuffers(vertexAmount, &VBO);*/
}

int main()
{

#pragma region Init

    if (!glfwInit()) {
        //PrintNotification(NERROR,  L"Well, you have badluck! D:\nGLFW initialisation failed!", 1);
        glfwTerminate();
        return 1;
    }

    /*glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); 
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3); 
    
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);*/

    GLFWwindow* mainWindow = glfwCreateWindow(WIDTH, HEIGHT, "Testwindow", NULL, NULL);

    if (!mainWindow) {
        //PrintNotification(NERROR, L"GLFW Window creation failed!", 1);
        glfwTerminate();
        return 1;
    }

    int bufferWidth, bufferHeight;
    glfwGetFramebufferSize(mainWindow, &bufferWidth, &bufferHeight);
    glfwMakeContextCurrent(mainWindow);
    glewExperimental = GL_TRUE;

    if (glewInit()) {
        //PrintNotification(NERROR, L"Well, you have badluck! D:\nGLEW initialisation failed!", 1);
        glfwDestroyWindow(mainWindow);
        glfwTerminate();
        return 1; 
    }



#pragma endregion Init

#pragma region Other
    glViewport(0, 0, bufferWidth, bufferHeight);

    static float r = 0.0f;
    static float g = 0.0f;
    static float b = 0.0f;

    constexpr float SpeedFactor = 1.0 / 1.0f;
    constexpr float OneSecond = 1000; // in Milliseconds
    constexpr long long FrameRate = 120;
    static long long FPS = OneSecond / FrameRate;
    static float DeltaTime = 1.0f / (powf(FPS, 1.0f / SpeedFactor));

    static bool upwards = true;

    std::random_device rd;
    // Erzeugen eines Generators mit rd als Seed
    std::mt19937 gen(rd());
    // Definition eines Verteilungsbereichs (hier: Ganzzahlen von 1 bis 100)
    std::uniform_real_distribution<float> distribution_r(0.0f, 1.0f - r);
    std::uniform_real_distribution<float> distribution_g(0.0f, 1.0f - g);
    std::uniform_real_distribution<float> distribution_b(0.0f, 1.0f - b);

    // Generierung einer Zufallszahl
    float rnd_r = 1.0f, rnd_g = 1.0f, rnd_b = 1.0f;
#pragma endregion Other
    POINT cursor = POINT(0, 0);
    CompileShaders();

    while (!glfwWindowShouldClose(mainWindow)) {
        GetCursorPos(&cursor);
        CreateTriangle(cursor);

        glfwPollEvents();
        //glClearColor(r, g, b, 1.0f);
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

        glClear(GL_COLOR_BUFFER_BIT);
#pragma region GeometryLogic
        glUseProgram(shader);
        glBindVertexArray(VAO);
        // use the shader here:
        glDrawArrays(GL_TRIANGLES, 0 , 3);
        glBindVertexArray(0);
        glUseProgram(0);
#pragma endregion GeometryLogic
        glfwSwapBuffers(mainWindow);
        std::this_thread::sleep_for(std::chrono::milliseconds((FPS)));
#pragma region ColorLogic
        if (upwards) {
            r += (DeltaTime * rnd_r);
            g += (DeltaTime * rnd_g);
            b += (DeltaTime * rnd_b);

            if (r >= 1.0f || g >= 1.0f || b >= 1.0f) {
                upwards = false;
                rnd_r = distribution_r(gen);
                rnd_g = distribution_g(gen);
                rnd_b = distribution_b(gen);
            }
        }
        else {
            r -= (DeltaTime * rnd_r);
            g -= (DeltaTime * rnd_g);
            b -= (DeltaTime * rnd_b);

            if (r <= 0.0f || g <= 0.0f || b <= 0.0f) {
                upwards = true;
            }
        }

#pragma endregion ColorLogic

    }
#pragma endregion MainLoop
//#version 460
    std::cin.get();  return 0;
}
