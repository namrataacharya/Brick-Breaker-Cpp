#pragma once
#ifndef FINAL_PROJECT_NAMRATAACHARYA2_PADDLE_H
#define FINAL_PROJECT_NAMRATAACHARYA2_PADDLE_H
#endif //FINAL_PROJECT_NAMRATAACHARYA2_PADDLE_H

#include "cinder/gl/gl.h"

using glm::vec2;

namespace brickbreaker {

    class Paddle {
    public:

        Paddle();

        /**
         * Creates paddle with specified attributes.
         */
        Paddle(vec2 left_bound, vec2 right_bound);

        void MoveRight();
        void MoveLeft();

        void SetLeftBound(vec2 newLeft);
        void SetRightBound(vec2 newRight);

        vec2 GetLeftBound() const;
        vec2 GetRightBound() const;

        int GetLeft() const;
        int GetRight() const;
        int GetUpper() const;
        int GetLower() const;

    private:

        int shift = 30;
        int length_;

        vec2 left_bound_;
        vec2 right_bound_;

        int left_x_;
        int right_x_;
        int upper_y_;
        int lower_y_;

        int left_wall_ = 100;
        int right_wall_ = 700;

    };

}
