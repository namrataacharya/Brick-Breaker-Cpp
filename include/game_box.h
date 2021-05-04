#pragma once
#ifndef FINAL_PROJECT_NAMRATAACHARYA2_GAME_BOX_H
#define FINAL_PROJECT_NAMRATAACHARYA2_GAME_BOX_H
#endif //FINAL_PROJECT_NAMRATAACHARYA2_GAME_BOX_H

#include "cinder/gl/gl.h"
#include "ball.h"
#include "paddle.h"
#include "brick.h"

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

        void RandomStartPosition();

        void CheckWallCollision();

        void CheckPaddleCollision();

        void CheckBrickCollision();

        void CheckIfLifeLost();

        void ResetAfterLifeLost();

        Ball& GetBall();

        Paddle& GetPaddle();


    private:

        Ball ball_;
        Paddle paddle_;
        std::vector<Brick> bricks_;

        bool game_over_ = false;

        int score_ = 0;
        int lives_ = 10;
        double bricks_end_y_;
        int random_x_;
        int random_y_;

        int paddle_left_ = 360; //350
        int paddle_right_ = 440; //450
        int paddle_top_ = 650; //660
        int paddle_bottom_ = 670; //680

        const int left_wall_ = 100;
        const int right_wall_ = 700;
        const int upper_wall_ = 100;
        const int lower_wall_ = 700;

        int game_box_length_ = right_wall_ - left_wall_;
        int brick_space_y = 200;

    };
}