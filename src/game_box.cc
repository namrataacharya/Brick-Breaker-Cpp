#include "game_box.h"

using glm::vec2;

namespace brickbreaker {

    GameBox::GameBox() {

        glm::vec2 position(400, 115);  //(400, 600)
        glm::vec2 velocity(6, 6);  // (3, 3)
        ball_ = Ball(position, velocity, 7);

        paddle_ = Paddle(vec2 (paddle_left_, paddle_top_),
                            vec2 (paddle_right_, paddle_bottom_));

        int max_strength_level = 4; //# of brick levels
        int bricks_per_row = 7; //10
        int brick_strength = max_strength_level;

        //takes care of x/row spacing
        double brick_length = double(game_box_length_ - 100) / double(bricks_per_row);

        //takes care of y/column spacing
        //int brick_height = brick_space_y / max_strength_level;
        double brick_height = double(brick_space_y) / double(max_strength_level);

        double brick_left;
        double brick_right;
        double brick_upper;
        double brick_lower;

        for (int i = 1; i <= max_strength_level; i++) {
            for (int j = 0; j < bricks_per_row; j++) {

                brick_left = left_wall_ + (j * brick_length) + 50; // + 50
                brick_right = brick_left + brick_length - 1; // - 1 was added
                brick_upper = upper_wall_ + (i * brick_height);
                brick_lower = brick_upper + brick_height - 1; // - 1 was added

                /*
                // FIX STRENGTH ASSIGNMENT, INCORRECT!
                // i = strength (1 thru 4)
                //bricks_.push_back(Brick(brick_left, brick_right, brick_upper, brick_lower, i)); //incorrect i value*/
                //bricks_.push_back(Brick(brick_left, brick_right, brick_upper, brick_lower, brick_strength));
                bricks_.push_back(Brick(brick_left, brick_right, brick_upper, brick_lower, 1));
            }
            brick_strength--;
        }
    }

    void GameBox::Display() const {
        ci::gl::color(ci::Color("white"));
        ci::gl::drawStrokedRect(ci::Rectf(vec2(left_wall_, upper_wall_),
                                          vec2(right_wall_, lower_wall_)));

        ///*
        ci::gl::color(ci::Color("magenta"));
        ci::gl::drawSolidCircle(ball_.GetPosition(), ball_.GetRadius());
         //*/

        ci::gl::color(ci::Color("cyan"));
        ci::gl::drawSolidRect(ci::Rectf(paddle_.GetLeftBound(), paddle_.GetRightBound()));

        //draws all bricks
        /*
        int color_switch = 0;
        int color_spacer = 255 / bricks_.size();
        int color_multiplier = 0;*/

        if (bricks_.size() != 0) {

            //draws all bricks
            int color_switch = 0;
            int color_spacer = 255 / bricks_.size();
            int color_multiplier = 0;

            for(const Brick &brick : bricks_) {

                if (color_switch % 2 == 0) {
                    ci::gl::color(ci::Color8u(220,0, (color_multiplier * color_spacer)));

                } else {
                    ci::gl::color(ci::Color8u(220,75, (color_multiplier * color_spacer)));
                }

                /*
                if (brick.IsDestroyed()) {
                    ci::gl::color(ci::Color("black"));
                }*/

                //ci::gl::drawStrokedRect(ci::Rectf(brick.GetLeftUpperBound(), brick.GetRightLowerBound()));
                ci::gl::drawSolidRect(ci::Rectf(brick.GetLeftUpperBound(), brick.GetRightLowerBound()));

                color_multiplier++;
                color_switch++;
            }

        } else {
            ci::gl::drawStringCentered("GAME OVER", vec2((right_wall_ + left_wall_) / 2,
                                                         (upper_wall_ + lower_wall_) / 2), "green",
                                       cinder::Font("Arial", 20));
        }

        /*
        for(const Brick &brick : bricks_) {

            if (color_switch % 2 == 0) {
                ci::gl::color(ci::Color8u(220,0, (color_multiplier * color_spacer)));

            } else {
                ci::gl::color(ci::Color8u(220,75, (color_multiplier * color_spacer)));
            }

            //ci::gl::drawStrokedRect(ci::Rectf(brick.GetLeftUpperBound(), brick.GetRightLowerBound()));
            ci::gl::drawSolidRect(ci::Rectf(brick.GetLeftUpperBound(), brick.GetRightLowerBound()));

            color_multiplier++;
            color_switch++;
        } */
        /*
        ci::gl::color(ci::Color("magenta"));
        ci::gl::drawSolidCircle(ball_.GetPosition(), ball_.GetRadius());*/
    }

    void GameBox::AdvanceOneFrame() {
        CheckWallCollision();
        /*
        if (!bricks_.empty()) {
            CheckBrickCollision();
        }*/
        CheckBrickCollision();
        CheckPaddleCollision();
        ball_.UpdatePosition();
        /*
        if (frame_count_ == 50) {
            ball_.IncreaseVelocity();
            frame_count_ = 0;
        }

        frame_count_++;
         */
    }

    void GameBox::CheckWallCollision() {
        if (ball_.GetPosition().x >= right_wall_ - ball_.GetRadius() ||
            ball_.GetPosition().x <= left_wall_ + ball_.GetRadius()) {

            vec2 current_velocity = ball_.GetVelocity() * vec2(-1, 1);
            ball_.SetVelocity(current_velocity);
        }

        if (ball_.GetPosition().y <= upper_wall_ + ball_.GetRadius() ||
            ball_.GetPosition().y >= lower_wall_ - ball_.GetRadius()) {

            vec2 current_velocity = ball_.GetVelocity() * vec2(1, -1);
            ball_.SetVelocity(current_velocity);
        }
    }

    void GameBox::CheckPaddleCollision() {

        //checks if ball within paddle's x range
        if (ball_.GetPosition().x < paddle_.GetRight() &&
            ball_.GetPosition().x > paddle_.GetLeft()) {

            //checks if ball hits paddle's upper y surface
            if (ball_.GetPosition().y >= paddle_.GetUpper() - ball_.GetRadius()) {

                //trying to get rid of boundary issue
                ball_.SetPosition(vec2 (ball_.GetPosition().x, paddle_.GetUpper() - ball_.GetRadius()));

                vec2 current_velocity = ball_.GetVelocity() * vec2(1, -1);
                ball_.SetVelocity(current_velocity);
            }
        }
    }

    void GameBox::CheckBrickCollision() {

        int current = 0;

        for (Brick &brick : bricks_) {
            if (ball_.GetPosition().x >= brick.GetLeftWall() &&
                ball_.GetPosition().x <= brick.GetRightWall()) {

                //checks if ball hits brick upper/lower wall
                if ((ball_.GetPosition().y <= brick.GetLowerWall() + ball_.GetRadius() && //OG: ||
                    ball_.GetPosition().y >= brick.GetUpperWall() - ball_.GetRadius())) { //&& brick.IsDestroyed() == false

                    /*
                    brick.IncreaseHitCount();
                    if (brick.IsDestroyed() == false) {
                        vec2 current_velocity = ball_.GetVelocity() * vec2(1, -1);
                        ball_.SetVelocity(current_velocity);
                    }*/
                    brick.IncreaseHitCount();
                    if (brick.IsDestroyed() == true) {
                        bricks_.erase(bricks_.begin() + current);
                    }

                    vec2 current_velocity = ball_.GetVelocity() * vec2(1, -1);
                    ball_.SetVelocity(current_velocity);

                    std::cout << "upper / lower wall HIT" << std::endl;

                    //removes brick from game if hit certain # of times
                    /*
                    brick.IncreaseHitCount();
                    if (brick.IsDestroyed() == true) {
                        bricks_.erase(bricks_.begin() + current);
                    }
                     //*/
                }
            }

            if (ball_.GetPosition().y <= brick.GetLowerWall() &&
                ball_.GetPosition().y >= brick.GetUpperWall()) {

                //checks if ball hits brick left/right side wall
                if ((ball_.GetPosition().x >= brick.GetLeftWall() - ball_.GetRadius() &&
                    ball_.GetPosition().x <= brick.GetRightWall() + ball_.GetRadius())) { // && brick.IsDestroyed() == false

                    /*
                    brick.IncreaseHitCount();
                    if (brick.IsDestroyed() == false) {
                        vec2 current_velocity = ball_.GetVelocity() * vec2(1, -1);
                        ball_.SetVelocity(current_velocity);
                    }
                     */

                    vec2 current_velocity = ball_.GetVelocity() * vec2(-1, 1);
                    ball_.SetVelocity(current_velocity);

                    std::cout << "side wall HIT" << std::endl;

                    //removes brick from game if hit certain # of times
                    ///*
                    brick.IncreaseHitCount();
                    if (brick.IsDestroyed() == true) {
                        bricks_.erase(bricks_.begin() + current);
                    }
                     //*/
                }
            }

            current++;
        }
    }

    Ball& GameBox::GetBall() {
        return ball_;
    }

    Paddle& GameBox::GetPaddle() {
        return paddle_;
    }

}


