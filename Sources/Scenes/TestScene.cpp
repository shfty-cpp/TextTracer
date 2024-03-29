#include "TestScene.h"

#include <glm/gtx/transform.hpp>
#include <glm/gtc/constants.hpp>

#include "PlaneObject.h"
#include "ConvexPolyObject.h"
#include "DiscObject.h"
#include "AABBObject.h"
#include "KdTree.h"

const float SUN_ROTATION_PER_SEC = glm::radians(1.0f);

SphereObject* sunSphere;
SphereObject* moonSphere;

const float PI = glm::pi<float>();
const float HALF_PI = glm::half_pi<float>();

TestScene::TestScene()
{
    // STATIC OBJECTS
    // Floor
    PlaneObject* testFloor = new PlaneObject(glm::vec3(0, 5, 0), glm::rotate(glm::half_pi<float>(), glm::vec3(1, 0, 0)), false);
    testFloor->SetColour(glm::vec4(0.5, 0.5, 0.5, 1));
    m_staticObjects.push_back(testFloor);

    // Walls
    ConvexPolyObject* testWallN = new ConvexPolyObject(glm::vec3(0, 50, 40), glm::rotate(PI, glm::vec3(0, 1, 0)), 100.0f, 4, true);
    testWallN->SetColour(glm::vec4(1, 0, 0, 1));
    m_staticObjects.push_back(testWallN);

    ConvexPolyObject* testWallE = new ConvexPolyObject(glm::vec3(60, 50, -20), glm::rotate(-HALF_PI, glm::vec3(0, 1, 0)), 100.0f, 4, true);
    testWallE->SetColour(glm::vec4(1, 1, 0, 1));
    m_staticObjects.push_back(testWallE);

    ConvexPolyObject* testWallS = new ConvexPolyObject(glm::vec3(0, 50, -80), glm::rotate(0.0f, glm::vec3(0, 1, 0)), 100.0f, 4, true);
    testWallS->SetColour(glm::vec4(1, 1, 1, 1));
    m_staticObjects.push_back(testWallS);

    ConvexPolyObject* testWallW = new ConvexPolyObject(glm::vec3(-60, 50, -20), glm::rotate(HALF_PI, glm::vec3(0, 1, 0)), 100.0f, 4, true);
    testWallW->SetColour(glm::vec4(1, 0, 1, 1));
    m_staticObjects.push_back(testWallW);

    // Poly Portal
    ConvexPolyObject* polyPortalIn = new ConvexPolyObject(glm::vec3(-10, 0, -50), glm::rotate(-HALF_PI, glm::vec3(0, 1, 0)), 4.0f, 5, true);
    ConvexPolyObject* polyPortalInOutline = new ConvexPolyObject(glm::vec3(-10, 0, -50), glm::rotate(-HALF_PI, glm::vec3(0, 1, 0)), 5.0f, 5, true);
    ConvexPolyObject* polyPortalOut = new ConvexPolyObject(glm::vec3(10, 0, -50), glm::rotate(HALF_PI, glm::vec3(0, 1, 0)), 4.0f, 5, true);
    ConvexPolyObject* polyPortalOutOutline = new ConvexPolyObject(glm::vec3(10, 0, -50), glm::rotate(HALF_PI, glm::vec3(0, 1, 0)), 5.0f, 5, true);

    polyPortalIn->SetExitPortal(polyPortalOut);
    polyPortalInOutline->GetGeometry()->SetCSGSubtract(polyPortalIn->GetGeometry());

    polyPortalOut->SetExitPortal(polyPortalIn);
    polyPortalOutOutline->GetGeometry()->SetCSGSubtract(polyPortalOut->GetGeometry());

    m_staticObjects.push_back(polyPortalIn);
    m_staticObjects.push_back(polyPortalInOutline);
    m_staticObjects.push_back(polyPortalOut);
    m_staticObjects.push_back(polyPortalOutOutline);

    // Sphere Portal
    SphereObject* spherePortalIn = new SphereObject(glm::vec3(20, 0, -20), glm::rotate(0.0f, glm::vec3(0, 1, 0)), 5.0f, true);
    SphereObject* spherePortalInOutline = new SphereObject(glm::vec3(20, 0, -20), glm::mat4(), 6.0f, true);
    SphereObject* spherePortalOut = new SphereObject(glm::vec3(-20, 0, -20), glm::rotate(PI, glm::vec3(0, 1, 0)), 5.0f, true);
    SphereObject* spherePortalOutOutline = new SphereObject(glm::vec3(-20, 0, -20), glm::mat4(), 6.0f, true);

    spherePortalIn->SetExitPortal(spherePortalOut);

    spherePortalOut->SetExitPortal(spherePortalIn);

    m_staticObjects.push_back(spherePortalIn);
    m_staticObjects.push_back(spherePortalInOutline);
    m_staticObjects.push_back(spherePortalOut);
    m_staticObjects.push_back(spherePortalOutOutline);

    // Disc Portal
    DiscObject* discPortalIn = new DiscObject(glm::vec3(20, 0, -79), glm::rotate(0.0f, glm::vec3(0, 1, 0)), 4.0f, true);
    DiscObject* discPortalInOutline = new DiscObject(glm::vec3(20, 0, -79), glm::rotate(0.0f, glm::vec3(0, 1, 0)), 5.0f, true);
    DiscObject* discPortalOut = new DiscObject(glm::vec3(-20, -15, 39), glm::rotate(PI, glm::vec3(0, 1, 0)), 4.0f, true);
    DiscObject* discPortalOutOutline = new DiscObject(glm::vec3(-20, -15, 39), glm::rotate(PI, glm::vec3(0, 1, 0)), 5.0f, true);

    discPortalIn->SetExitPortal(discPortalOut);
    discPortalInOutline->GetGeometry()->SetCSGSubtract(discPortalIn->GetGeometry());
    discPortalInOutline->SetColour(glm::vec4(1, 0.65, 0, 1));
    discPortalInOutline->Fullbright = true;

    discPortalOut->SetExitPortal(discPortalIn);
    discPortalOutOutline->GetGeometry()->SetCSGSubtract(discPortalOut->GetGeometry());
    discPortalOutOutline->SetColour(glm::vec4(0, 1, 1, 1));
    discPortalOutOutline->Fullbright = true;

    m_staticObjects.push_back(discPortalIn);
    m_staticObjects.push_back(discPortalInOutline);
    m_staticObjects.push_back(discPortalOut);
    m_staticObjects.push_back(discPortalOutOutline);

    // Triangle
    ConvexPolyObject* testTri = new ConvexPolyObject(glm::vec3(-20, 0, 20), glm::rotate(glm::radians(5.0f), glm::vec3(1, 0, 0)), 7.5f, 3, true);
    testTri->SetColour(glm::vec4(0, 0, 1, 1));
    m_staticObjects.push_back(testTri);

    // Pentagon
    ConvexPolyObject* testPent = new ConvexPolyObject(glm::vec3(0, -2.5, -12.5), glm::rotate(-HALF_PI, glm::vec3(1, 0, 0)), 5.0f, 5, true);
    testPent->SetColour(glm::vec4(1, 1, 0, 0.5f));
    m_staticObjects.push_back(testPent);

    // Arrowhead
    std::vector<glm::vec3> arrowheadVertices;
    arrowheadVertices.push_back(glm::vec3(0, -1, 0));
    arrowheadVertices.push_back(glm::vec3(1, 1, 0));
    arrowheadVertices.push_back(glm::vec3(0, 1.5, 0));
    arrowheadVertices.push_back(glm::vec3(-1, 1, 0));
    ConvexPolyObject* arrowhead = new ConvexPolyObject(glm::vec3(-40, -10, -10), glm::rotate(-HALF_PI, glm::vec3(0, 1, 0)), 5.0f, arrowheadVertices, true);
    arrowhead->SetColour(glm::vec4(0, 1, 0, 1));
    m_staticObjects.push_back(arrowhead);

    // Transparent Discs
    DiscObject* transDisc0 = new DiscObject(glm::vec3(40, 0, -10), glm::rotate(0.0f, glm::vec3(0, 1, 0)), 5.0f, true);
    transDisc0->SetColour(glm::vec4(1, 1, 1, 0.2f));
    m_staticObjects.push_back(transDisc0);
    DiscObject* transDisc1 = new DiscObject(glm::vec3(40, 0, -20), glm::rotate(0.0f, glm::vec3(0, 1, 0)), 5.0f, true);
    transDisc1->SetColour(glm::vec4(1, 1, 1, 0.2f));
    m_staticObjects.push_back(transDisc1);
    DiscObject* transDisc2 = new DiscObject(glm::vec3(40, 0, -30), glm::rotate(0.0f, glm::vec3(0, 1, 0)), 5.0f, true);
    transDisc2->SetColour(glm::vec4(1, 1, 1, 0.2f));
    m_staticObjects.push_back(transDisc2);
    DiscObject* transDisc3 = new DiscObject(glm::vec3(40, 0, -40), glm::rotate(0.0f, glm::vec3(0, 1, 0)), 5.0f, true);
    transDisc3->SetColour(glm::vec4(1, 1, 1, 0.2f));
    m_staticObjects.push_back(transDisc3);
    DiscObject* transDisc4 = new DiscObject(glm::vec3(40, 0, -50), glm::rotate(0.0f, glm::vec3(0, 1, 0)), 5.0f, true);
    transDisc4->SetColour(glm::vec4(1, 1, 1, 0.2f));
    m_staticObjects.push_back(transDisc4);

    // Floating Sphere
    SphereObject* testSphere = new SphereObject(glm::vec3(20, 0, 20), glm::mat4(), 5.0f, false);
    testSphere->SetColour(glm::vec4(0.2f, 0.5, 0.2f, 1));
    m_staticObjects.push_back(testSphere);

    // Box
    AABB testBounds(glm::vec3(-40, 0, -40), glm::vec3(-5, -5, -5), glm::vec3(5, 5, 5));
    AABBObject* testAABB = new AABBObject(glm::vec3(-40, 0, -40), glm::mat4(), testBounds);
    testAABB->SetColour(glm::vec4(1.0f, 0.5, 0.2f, 1));
    m_staticObjects.push_back(testAABB);

    // STATIC BOUNDS
    m_staticBounds.SetMin(glm::vec3(-50, -50, -50));
    m_staticBounds.SetMax(glm::vec3(50, 50, 50));

    // STATIC TREE
    initStaticTree();

    // DYNAMIC OBJECTS
    // Celestial Bodies
    sunSphere = new SphereObject(glm::vec3(), glm::mat4(), 500.0f, false);
    sunSphere->SetColour(glm::vec4(1, 1, 0, 1));
    sunSphere->CastShadow = false;
    sunSphere->Fullbright = true;
    m_dynamicObjects.push_back(sunSphere);

    moonSphere = new SphereObject(glm::vec3(), glm::mat4(), 500.0f, false);
    moonSphere->SetColour(glm::vec4(1, 1, 1, 1));
    moonSphere->CastShadow = false;
    moonSphere->Fullbright = true;
    m_dynamicObjects.push_back(moonSphere);

    // DYNAMIC BOUNDS
    m_dynamicBounds.SetMin(glm::vec3(-5500, -5500, -500));
    m_dynamicBounds.SetMax(glm::vec3(5500, 5500, 500));

    // DYNAMIC TREE
    initDynamicTree();
}

TestScene::~TestScene()
{
}

void TestScene::Update(const float deltaTime)
{
    // Move celestial bodies
    float sunRotation = SUN_ROTATION_PER_SEC * deltaTime;

    glm::vec4 norm = glm::vec4(SunNormal.x, SunNormal.y, SunNormal.z, 0);
    norm = glm::normalize(glm::rotate(sunRotation, glm::vec3(0, 0, 1)) * norm);
    SunNormal = glm::vec3(norm.x, norm.y, norm.z);
    sunSphere->SetPosition(-SunNormal * 5000.0f);
    moonSphere->SetPosition(SunNormal * 5000.0f);

    // Update Dynamic Tree
    updateDynamicTree();
}
