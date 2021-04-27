#pragma once
#ifndef FINAL_PROJECT_NAMRATAACHARYA2_BRICK_H
#define FINAL_PROJECT_NAMRATAACHARYA2_BRICK_H
#endif //FINAL_PROJECT_NAMRATAACHARYA2_BRICK_H

#include "cinder/gl/gl.h"

using glm::vec2;

namespace brickbreaker {
    class Brick {

    public:

        Brick();
        Brick(int strength);

        Brick(int left_wall, int right_wall, int upper_wall, int lower_wall, int strength);

        int GetLeftWall();
        int GetRightWall();
        int GetUpperWall();
        int GetLowerWall();

        vec2 GetLeftUpperBound() const;
        vec2 GetRightLowerBound() const;

        int GetHitCount();

        void IncreaseHitCount();

        //true if brick is destroyed by ball (after certain # of hits)
        bool IsDestroyed();


    private:

        int left_wall_;
        int right_wall_;
        int upper_wall_;
        int lower_wall_;

        vec2 left_bound_;
        vec2 right_bound_;

        int strength_;
        int hit_count_;

        bool is_destroyed_ = false;

    };
}