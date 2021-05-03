#include "game_box.h"

using glm::vec2;

namespace brickbreaker {

    GameBox::GameBox() {

        glm::vec2 position(400, 115);  //(400, 600)
        glm::vec2 velocity(3, 3);  // (3, 3)
        ball_ = Ball(position, velocity, 7);

        paddle_ = Paddle(vec2 (paddle_left_, paddle_top_),
                            vec2 (paddle_right_, paddle_bottom_));

        int max_strength_level = 4; //# of brick levels
        int bricks_per_row = 7; //10 //7 -> (current)
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
                bricks_.push_back(Brick(brick_left, brick_right, brick_upper, brick_lower, brick_strength));
                //bricks_.push_back(Brick(brick_left, brick_right, brick_upper, brick_lower, 2));
            }
            brick_strength--;
        }
    }

    void GameBox::Display() const {
        ci::gl::color(ci::Color("cyan"));
        ci::gl::drawStrokedRect(ci::Rectf(vec2(left_wall_, upper_wall_),
                                          vec2(right_wall_, lower_wall_)));


        ci::gl::drawString("Score: " + std::to_string(score_), vec2((left_wall_),
                                                     (upper_wall_ / 2)), "cyan",
                                   cinder::Font("Arial", 20));

        ci::gl::drawString("Lives: " + std::to_string(lives_), vec2((right_wall_ - 65),
                                                                    (upper_wall_ / 2)), "cyan",
                           cinder::Font("Arial", 20));

        /*
        ci::gl::color(ci::Color("magenta"));
        ci::gl::drawSolidCircle(ball_.GetPosition(), ball_.GetRadius());
         */

        ci::gl::color(ci::Color("cyan"));
        ci::gl::drawSolidRect(ci::Rectf(paddle_.GetLeftBound(), paddle_.GetRightBound()));

        //draws all bricks
        /*
        int color_switch = 0;
        int color_spacer = 255 / bricks_.size();
        int color_multiplier = 0;*/

        if (!bricks_.empty() && lives_ > 0) {

            /*
            ci::gl::drawStringCentered("Score: " + std::to_string(score_), vec2((left_wall_),
                                                                                (upper_wall_ / 2)), "white",
                                       cinder::Font("Arial", 20)); */

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

                //ci::gl::drawStrokedRect(ci::Rectf(brick.GetLeftUpperBound(), brick.GetRightLowerBound()));
                ci::gl::drawSolidRect(ci::Rectf(brick.GetLeftUpperBound(), brick.GetRightLowerBound()));

                color_multiplier++;
                color_switch++;
            }

        } else {
            ci::gl::drawStringCentered("GAME OVER", vec2((right_wall_ + left_wall_) / 2,
                                                         (upper_wall_ + lower_wall_) / 2), "green",
                                       cinder::Font("Arial", 30));
            /*
            ci::gl::drawStringCentered("Score: " + std::to_string(score_),
                                       vec2((right_wall_ + left_wall_) / 2,
                                            ((upper_wall_ + lower_wall_) / 2) + 20), "green",
                                       cinder::Font("Arial", 20));
                                       */
        }

        ///*
        ci::gl::color(ci::Color("magenta"));
        ci::gl::drawSolidCircle(ball_.GetPosition(), ball_.GetRadius());
        //*/
    }

    void GameBox::AdvanceOneFrame() {
        CheckWallCollision();
        if (lives_ > 0) { //added
            CheckBrickCollision();
            CheckIfLifeLost();
        }
        //CheckBrickCollision();
        CheckPaddleCollision();
        //CheckIfLifeLost(); //new
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
        if (ball_.GetPosition().x <= paddle_.GetRight() && //OG: <
            ball_.GetPosition().x >= paddle_.GetLeft()) { //OG: >

            //checks if ball hits paddle's upper y surface
            if (ball_.GetPosition().y >= paddle_.GetUpper() - ball_.GetRadius()) {

                //trying to get rid of boundary issue
                ball_.SetPosition(vec2 (ball_.GetPosition().x, paddle_.GetUpper() - ball_.GetRadius()));

                vec2 current_velocity = ball_.GetVelocity() * vec2(1, -1);
                ball_.SetVelocity(current_velocity);
            }
        }

        if (ball_.GetPosition().y <= paddle_.GetLower() && //OG: <=
            ball_.GetPosition().y >= paddle_.GetUpper()) { //OG: >=

            if ((ball_.GetPosition().x >= paddle_.GetLeft() - ball_.GetRadius() &&
                 ball_.GetPosition().x <= paddle_.GetRight() + ball_.GetRadius())) {

                vec2 current_velocity = ball_.GetVelocity() * vec2(-1, 1);
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
                if ((ball_.GetPosition().y <= brick.GetLowerWall() + ball_.GetRadius() &&
                    ball_.GetPosition().y >= brick.GetUpperWall() - ball_.GetRadius())) {

                    brick.IncreaseHitCount();
                    if (brick.IsDestroyed() == true) {
                        bricks_.erase(bricks_.begin() + current);
                        score_ += brick.GetPointValue();

                        //ball_.IncreaseVelocity();
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
                    ball_.GetPosition().x <= brick.GetRightWall() + ball_.GetRadius())) {

                    vec2 current_velocity = ball_.GetVelocity() * vec2(-1, 1);
                    ball_.SetVelocity(current_velocity);

                    std::cout << "side wall HIT" << std::endl;

                    //removes brick from game if hit certain # of times
                    ///*
                    brick.IncreaseHitCount();
                    if (brick.IsDestroyed() == true) {
                        bricks_.erase(bricks_.begin() + current);
                        score_ += brick.GetPointValue();

                        //ball_.IncreaseVelocity();
                    }
                     //*/
                }
            }

            current++;
        }
    }

    void GameBox::CheckIfLifeLost() {

        // if (ball_.GetPosition().y >= paddle_bottom_) {
        if (ball_.GetPosition().y >= lower_wall_ - ball_.GetRadius()) {
            lives_--;

            if (lives_ > 0) {
                ResetAfterLifeLost();
            }
            //ResetAfterLifeLost();
        }
    }

    void GameBox::ResetAfterLifeLost() {

        //glm::vec2 position(400, 115);  //(400, 600)
        ball_.SetPosition(vec2(400, 115));

    }

    Ball& GameBox::GetBall() {
        return ball_;
    }

    Paddle& GameBox::GetPaddle() {
        return paddle_;
    }

}


