#pragma once
#ifndef FINAL_PROJECT_NAMRATAACHARYA2_GAME_BOX_H
#define FINAL_PROJECT_NAMRATAACHARYA2_GAME_BOX_H
#endif //FINAL_PROJECT_NAMRATAACHARYA2_GAME_BOX_H

#include "cinder/gl/gl.h"
#include "ball.h"
#include "paddle.h"

using glm::vec2;

namespace brickbreaker {

    class GameBox {

    public:
        /**
         * Creates game box/screen with balls, paddle, and bricks.
         */
        GameBox();

        /**
         * Displays the game box.
         */
        void Display() const;

        /**
         * Updates the positions and velocities of the ball & paddle.
         */
        void AdvanceOneFrame();

        void CheckWallCollision();

        void CheckPaddleCollision();


    private:

        Ball ball_;
        Paddle paddle_;

        int paddle_left_ = 350; //350 //testing: 330
        int paddle_right_ = 450; //450 //testing: 470
        int paddle_top_ = 650;
        int paddle_bottom_ = 680;

        const int left_wall_ = 100;
        const int right_wall_ = 700;
        const int upper_wall_ = 100;
        const int lower_wall_ = 700;

    };
}