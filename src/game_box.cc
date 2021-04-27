#include "game_box.h"

using glm::vec2;

namespace brickbreaker {

    GameBox::GameBox() {

        glm::vec2 position(400, 600);
        glm::vec2 velocity(3, 3);
        ball_ = Ball(position, velocity, 10);

        paddle_ = Paddle(vec2 (paddle_left_, paddle_top_),
                            vec2 (paddle_right_, paddle_bottom_));

        int max_strength_level = 4; //# of brick levels
        int bricks_per_row = 10;

        //takes care of x/row spacing
        int brick_length = game_box_length_ / bricks_per_row;
        int end_x_prev_brick;

        //takes care of y/column spacing
        int brick_height = brick_space_y / max_strength_level;

        for (int i = 1; i <= max_strength_level; i++) {
            for (int j = 0; j < bricks_per_row; j++) {
                //Brick();
                bricks_.push_back(Brick(i)); //i = strength (1 thru 4)
            }
        }

    }

    void GameBox::Display() const {
        ci::gl::color(ci::Color("white"));
        ci::gl::drawStrokedRect(ci::Rectf(vec2(left_wall_, upper_wall_),
                                          vec2(right_wall_, lower_wall_)));

        ci::gl::color(ci::Color("magenta"));
        ci::gl::drawSolidCircle(ball_.GetPosition(), ball_.GetRadius());

        ci::gl::color(ci::Color("cyan"));
        ci::gl::drawSolidRect(ci::Rectf(paddle_.GetLeftBound(), paddle_.GetRightBound()));

        //draws all bricks
        /*
        for(int i = 0; i < bricks_.size(); i++) {
            if (i % 2 == 0) {
                ci::gl::color(ci::Color("yellow"));
                ci::gl::drawStrokedRect(ci::Rectf(vec2(left_wall_, upper_wall_),
                                                  vec2(right_wall_, lower_wall_)));

            } else {
                ci::gl::color(ci::Color("green"));
                ci::gl::drawStrokedRect(ci::Rectf(vec2(left_wall_, upper_wall_),
                                                  vec2(right_wall_, lower_wall_)));
            }
        }*/
        int color_switch = 0;
        for(const Brick &brick : bricks_) {
            if (color_switch % 2 == 0) {
                ci::gl::color(ci::Color("yellow"));
                /*
                ci::gl::drawStrokedRect(ci::Rectf(vec2(left_wall_, upper_wall_),
                                                  vec2(right_wall_, lower_wall_)));*/

            } else {
                ci::gl::color(ci::Color("green"));
                /*
                ci::gl::drawStrokedRect(ci::Rectf(vec2(left_wall_, upper_wall_),
                                                  vec2(right_wall_, lower_wall_)));*/
            }
            ci::gl::drawStrokedRect(ci::Rectf(brick.GetLeftUpperBound(), brick.GetRightLowerBound()));
            color_switch++;
        }
    }

    void GameBox::AdvanceOneFrame() {
        CheckWallCollision();
        CheckPaddleCollision();
        CheckBrickCollision(); // new, just added

        ball_.UpdatePosition();
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

    void GameBox::CheckBrickCollision() {} // FIX THIS

    Ball& GameBox::GetBall() {
        return ball_;
    }

    Paddle& GameBox::GetPaddle() {
        return paddle_;
    }

}
