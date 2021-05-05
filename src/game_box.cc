#include "game_box.h"
#include "cinder/Rand.h"

using glm::vec2;
using std::rand;

namespace brickbreaker {

    GameBox::GameBox() {

        paddle_ = Paddle(vec2 (paddle_left_, paddle_top_),
                            vec2 (paddle_right_, paddle_bottom_));

        int max_strength_level = 4; //# of brick levels
        int bricks_per_row = 7;
        int brick_strength = max_strength_level;

        //takes care of x/row spacing
        double brick_length = double(game_box_length_ - 100) / double(bricks_per_row);

        //takes care of y/column spacing
        double brick_height = double(brick_space_y_) / double(max_strength_level);

        double brick_left;
        double brick_right;
        double brick_upper;
        double brick_lower;

        for (int i = 1; i <= max_strength_level; i++) {
            for (int j = 0; j < bricks_per_row; j++) {

                brick_left = left_wall_ + (j * brick_length) + 50;
                brick_right = brick_left + brick_length - 1;
                brick_upper = upper_wall_ + (i * brick_height);
                brick_lower = brick_upper + brick_height - 1;
                bricks_end_y_ = brick_lower; //used when generating random ball start position

                bricks_.push_back(Brick(brick_left, brick_right, brick_upper, brick_lower, brick_strength));
            }
            brick_strength--;
        }

        RandomStartPosition();

        glm::vec2 position(random_x_, random_y_);
        glm::vec2 velocity(2.5, 2.5);
        ball_ = Ball(position, velocity, 7);

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

        ci::gl::color(ci::Color("cyan"));
        ci::gl::drawSolidRect(ci::Rectf(paddle_.GetLeftBound(), paddle_.GetRightBound()));


        if (!bricks_.empty() && lives_ > 0) {

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

                ci::gl::drawSolidRect(ci::Rectf(brick.GetLeftUpperBound(), brick.GetRightLowerBound()));

                color_multiplier++;
                color_switch++;
            }

        } else {

            ci::gl::drawStringCentered("GAME OVER", vec2((right_wall_ + left_wall_) / 2,
                                                         (upper_wall_ + lower_wall_) / 2), "green",
                                       cinder::Font("Arial", 30));
        }

        ci::gl::color(ci::Color("magenta"));
        ci::gl::drawSolidCircle(ball_.GetPosition(), ball_.GetRadius());
    }

    void GameBox::AdvanceOneFrame() {
        CheckWallCollision();

        if (lives_ > 0 && game_over_ == false) {
            CheckBrickCollision();
            CheckIfLifeLost();
        }

        CheckPaddleCollision();
        ball_.UpdatePosition();
    }

    void GameBox::RandomStartPosition() {
        random_x_ = cinder::randInt(left_wall_ + ball_.GetRadius() + 150,
                                    right_wall_ - ball_.GetRadius() - 150);

        random_y_ = cinder::randInt(bricks_end_y_ + ball_.GetRadius() + 50,
                                    paddle_top_ - ball_.GetRadius() - 100);
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
        if (ball_.GetPosition().x <= paddle_.GetRight() &&
            ball_.GetPosition().x >= paddle_.GetLeft()) {

            //checks if ball hits paddle's upper y surface
            if (ball_.GetPosition().y >= paddle_.GetUpper() - ball_.GetRadius()) {

                //trying to get rid of boundary issue
                ball_.SetPosition(vec2 (ball_.GetPosition().x, paddle_.GetUpper() - ball_.GetRadius()));

                vec2 current_velocity = ball_.GetVelocity() * vec2(1, -1);
                ball_.SetVelocity(current_velocity);
            }
        }

        if (ball_.GetPosition().y <= paddle_.GetLower() &&
            ball_.GetPosition().y >= paddle_.GetUpper()) {

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

                        ball_.IncreaseVelocity();
                    }

                    vec2 current_velocity = ball_.GetVelocity() * vec2(1, -1);
                    ball_.SetVelocity(current_velocity);
                }
            }

            if (ball_.GetPosition().y <= brick.GetLowerWall() &&
                ball_.GetPosition().y >= brick.GetUpperWall()) {

                if ((ball_.GetPosition().x >= brick.GetLeftWall() - ball_.GetRadius() &&
                     ball_.GetPosition().x <= brick.GetRightWall() + ball_.GetRadius())) {

                    vec2 current_velocity = ball_.GetVelocity() * vec2(-1, 1);
                    ball_.SetVelocity(current_velocity);

                    //removes brick from game if hit certain # of times
                    brick.IncreaseHitCount();
                    if (brick.IsDestroyed() == true) {
                        bricks_.erase(bricks_.begin() + current);
                        score_ += brick.GetPointValue();

                        ball_.IncreaseVelocity();
                    }
                }
            }

            current++;
        }
    }

    void GameBox::CheckIfLifeLost() {

        if (ball_.GetPosition().y >= lower_wall_ - ball_.GetRadius()) {
            lives_--;

            if (lives_ > 0) {
                ResetAfterLifeLost();
            }

            if (bricks_.empty()) {
                game_over_ = true;
            }
        }
    }

    void GameBox::ResetAfterLifeLost() {
        RandomStartPosition();
        ball_.SetPosition(vec2(random_x_, random_y_));
    }

    Ball& GameBox::GetBall() {
        return ball_;
    }

    Paddle& GameBox::GetPaddle() {
        return paddle_;
    }

    int GameBox::GetLifeCount() {
        return lives_;
    }

}


