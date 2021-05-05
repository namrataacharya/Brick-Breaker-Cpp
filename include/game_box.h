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

        /**
         * Generates random x and y values for ball's position vector.
         */
        void RandomStartPosition();

        /**
         * Examines ball position and updates velocity if wall collision is detected.
         */
        void CheckWallCollision();

        /**
         * Examines ball position and updates velocity if paddle collision is detected.
         */
        void CheckPaddleCollision();

        /**
         * Examines ball position and updates velocity if brick collision is detected.
         */
        void CheckBrickCollision();

        /**
         * Determines if player looses a life if ball falls too low.
         */
        void CheckIfLifeLost();

        /**
         * Resets ball position after a life is lost.
         */
        void ResetAfterLifeLost();

        /**
         * Returns ball object that is a part of the game box.
         * @return ball object
         */
        Ball& GetBall();

        /**
         * Returns paddle object that is a part of the game box.
         * @return paddle object
         */
        Paddle& GetPaddle();

        /**
         * Returns the number of lives the player has left.
         * @return the life count of the player.
         */
        int GetLifeCount();


    private:

        Ball ball_;
        Paddle paddle_;
        std::vector<Brick> bricks_;

        bool game_over_ = false;

        int score_ = 0;
        int lives_ = 3;

        double bricks_end_y_;
        int random_x_;
        int random_y_;

        int paddle_left_ = 360;
        int paddle_right_ = 440;
        int paddle_top_ = 650;
        int paddle_bottom_ = 670;

        const int left_wall_ = 100;
        const int right_wall_ = 700;
        const int upper_wall_ = 100;
        const int lower_wall_ = 700;

        int game_box_length_ = right_wall_ - left_wall_;
        int brick_space_y_ = 200;

    };
}