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


        //void SetPosition(vec2 newPosition);
        void SetLeftBound(vec2 newLeft);
        void SetRightBound(vec2 newRight);

        /**
         * Returns the paddle's current position.
         * @return vector representing ball's position.
         */
        //vec2 GetPosition() const;
        vec2 GetLeftBound() const;
        vec2 GetRightBound() const;

        /**
         * Updates the ball's position based on its velocity and current position.
         */
        //void UpdatePosition();


        int GetLeft() const;
        int GetRight() const;
        int GetUpper() const;
        int GetLower() const;




    private:
        //vec2 position_;

        vec2 left_bound_;
        vec2 right_bound_;

        int left_x_;
        int right_x_;
        int upper_y_;
        int lower_y_;



    };

}
