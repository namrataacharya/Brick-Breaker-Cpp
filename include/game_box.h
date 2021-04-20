#pragma once
#ifndef FINAL_PROJECT_NAMRATAACHARYA2_GAME_BOX_H
#define FINAL_PROJECT_NAMRATAACHARYA2_GAME_BOX_H
#endif //FINAL_PROJECT_NAMRATAACHARYA2_GAME_BOX_H

#include "cinder/gl/gl.h"
#include "ball.h"

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


    private:

        Ball ball_;

        const int left_wall_ = 100;
        const int right_wall_ = 700;
        const int upper_wall_ = 100;
        const int lower_wall_ = 700;

    };
}