#ifndef COMPUTER_GRAPHICS_PROJECT_GAME_SCENE_UTILITIES_H
#define COMPUTER_GRAPHICS_PROJECT_GAME_SCENE_UTILITIES_H

#include <transform.h>
namespace CGEngine {

    enum Direction {
        Front,
        RIGHT,
        Back,
        LEFT
    };
    typedef std::tuple<bool, Direction, glm::vec3> Collision;

    static Direction VectorDirection(glm::vec3 target) {
        glm::vec3 compass[] = {
                glm::vec3(0.0f, 0.0f, -1.0f),    // front
                glm::vec3(1.0f, 0.0f, 0.0f),    // right
                glm::vec3(0.0f, 0.0f, 1.0f),    // back
                glm::vec3(-1.0f, 0.0f, 0.0f)    // left
        };
        float max = 0.0f;
        unsigned int best_match = -1;
        for (unsigned int i = 0; i < 4; i++) {
            float dot_product = glm::dot(glm::normalize(target), compass[i]);
            if (dot_product > max) {
                max = dot_product;
                best_match = i;
            }
        }
        return (Direction) best_match;
    }

    static Collision  CheckCollision(CGEngine::Transform *one, CGEngine::Transform *two) // AABB - Circle collision
    {
        // get center point circle first
        glm::vec3 center(one->getPosition().x, 0.6f, one->getPosition().z);

        // calculate AABB info (center, half-extents)
        glm::vec3 aabb_half_extents(2.2f / 2.0f, 0.6f, 2.2f / 2.0f);
        glm::vec3 aabb_center(two->getPosition());

        // get difference vector between both centers
        glm::vec3 difference = center - aabb_center;
        glm::vec3 clamped = glm::clamp(difference, -aabb_half_extents, aabb_half_extents);

        // add clamped value to AABB_center and we get the value of box closest to circle
        glm::vec3 closest = aabb_center + clamped;

        // retrieve vector between center circle and closest point AABB and check if length <= radius
        difference = closest - center;
        // return glm::length(difference) < 0.65f;
        if (glm::length(difference) <= 0.7f)
            return std::make_tuple(true, VectorDirection(difference), difference);
        else
            return std::make_tuple(false, Front, glm::vec3(0.0f, 0.0f, 0.0f));
    }
    static bool  CheckCollisionWithEnemy(CGEngine::Transform *one, CGEngine::Transform *two) // Circle collision - Circle collision
    {
        // get center point circle first
        glm::vec3 center1(one->getPosition().x, 0.6f, one->getPosition().z);

        // get center point circle first
        glm::vec3 center2(two->getPosition().x, 0.6f, two->getPosition().z);

        float distance = glm::distance(center1, center2);
        return distance <(0.6+ (0.9f/2.0f));

    }

    static bool  CheckCollisionWithPowerUp(CGEngine::Transform *one, CGEngine::Transform *two) // Circle collision - Circle collision
    {
        // get center point circle first
        glm::vec3 center1(one->getPosition().x, 0.6f, one->getPosition().z);

        // get center point circle first
        glm::vec3 center2(two->getPosition().x, 0.6f, two->getPosition().z);

        float distance = glm::distance(center1, center2);
        return distance <(0.6+ (0.6f/2.0f));

    }

}
#endif //COMPUTER_GRAPHICS_PROJECT_GAME_SCENE_UTILITIES_H
