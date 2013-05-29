#include "ConvexPolyObject.h"
#include "Ray.h"

// PUBLIC
ConvexPolyObject::ConvexPolyObject(const glm::vec3& position, const glm::mat4& rotation, const float scale, const int sides, const bool twoSided)
{
    m_geometry = new ConvexPolyGeometry();
    SetSides(sides);
    SetPosition(position);
    SetRotation(rotation);
    SetScale(scale);
    SetTwoSided(twoSided);
    SetColour(glm::vec4(1, 0, 0, 1));
}

ConvexPolyObject::ConvexPolyObject(const glm::vec3& position, const glm::mat4& rotation, const float scale, const std::vector<glm::vec3>& vertices, const bool twoSided)
{
    m_geometry = new ConvexPolyGeometry();
    SetObjectVertices(vertices);
    SetPosition(position);
    SetRotation(rotation);
    SetScale(scale);
    SetTwoSided(twoSided);
    SetColour(glm::vec4(1, 0, 0, 1));
}

// PRIVATE

