#ifndef TEXTTRACER_H
#define TEXTTRACER_H

#include "Camera.h"
#include "Raytracer.h"

class TextTracer
{
public:
    TextTracer();
    ~TextTracer();

    void Update(const int worldClock);
    void Draw();
    bool IsKeyDown(const char key);

    const float FOV = 3.141f / 4; // 45 Degrees
    const float MIN_TIMESTEP = 0.05f;
#ifdef LOW_RES
    const int WIDTH = 32;
    const int HEIGHT = 24;
#else
    const int WIDTH = 64;
    const int HEIGHT = 48;
#endif // LOW_RES
    static const int HUD_HEIGHT = 5;

private:
    Framebuffer* m_framebuffer;
    Camera* m_camera;
    Raytracer* m_raytracer;

    glm::vec4 m_dayColour = glm::vec4(0, 1, 1, 1);
    glm::vec4 m_nightColour = glm::vec4(0, 0, 0.5, 1);

    float m_cameraAngleX = 0;
    float m_cameraAngleY = 0;

    float m_deltaTime = 0;
    int m_prevWorldClock = 0;
};

#endif // TEXTTRACER_H
