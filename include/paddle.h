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
         * @param left_bound - vector holding left and upper surface bounds.
         * @param right_bound - vector holding right and lower surface bounds.
         */
        Paddle(vec2 left_bound, vec2 right_bound);

        /**
         * Moves the paddle to the right.
         */
        void MoveRight();

        /**
         * Moves the paddle to the left.
         */
        void MoveLeft();

        /**
         * Returns the vector representing the paddle's left bound.
         * @return vector that holds the left and upper surface bounds.
         */
        vec2 GetLeftBound() const;

        /**
         * Returns the vector representing the paddle's right bound.
         * @return vector that holds the right and lower surface bounds.
         */
        vec2 GetRightBound() const;

        /**
         * Returns the x value representing paddle's left bound.
         * @return x value of the left bound.
         */
        int GetLeft() const;

        /**
         * Returns the x value representing paddle's right bound.
         * @return x value of the right bound.
         */
        int GetRight() const;

        /**
         * Returns the y value representing paddle's upper bound.
         * @return y value of the upper bound.
         */
        int GetUpper() const;

        /**
         * Returns the y value representing paddle's lower bound.
         * @return y value of the lower bound.
         */
        int GetLower() const;

    private:

        int shift = 40;
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
