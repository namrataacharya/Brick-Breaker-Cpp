#include "game_box.h"

using glm::vec2;

namespace brickbreaker {

    GameBox::GameBox() {

        glm::vec2 position(400, 600);
        glm::vec2 velocity(3, 3);
        ball_ = Ball(position, velocity, 10);

        paddle_ = Paddle(vec2 (paddle_left_, paddle_top_),
                            vec2 (paddle_right_, paddle_bottom_) );

    }

    void GameBox::Display() const {
        ci::gl::color(ci::Color("white"));
        ci::gl::drawStrokedRect(ci::Rectf(vec2(left_wall_, upper_wall_),
                                          vec2(right_wall_, lower_wall_)));

        ci::gl::color(ci::Color("magenta"));
        ci::gl::drawSolidCircle(ball_.GetPosition(), ball_.GetRadius());

        ci::gl::color(ci::Color("cyan"));
        ci::gl::drawSolidRect(ci::Rectf(paddle_.GetLeftBound(), paddle_.GetRightBound()));
    }

    void GameBox::AdvanceOneFrame() {
        //CheckPaddleCollision();
        CheckWallCollision();
        CheckPaddleCollision();
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

    Ball& GameBox::GetBall() {
        return ball_;
    }

    Paddle& GameBox::GetPaddle() {
        return paddle_;
    }

}
