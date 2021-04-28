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
        int bricks_per_row = 7; //10

        //takes care of x/row spacing
        double brick_length = double(game_box_length_ - 100) / double(bricks_per_row);

        //takes care of y/column spacing
        //int brick_height = brick_space_y / max_strength_level;
        double brick_height = double(brick_space_y) / double(max_strength_level);

        /*
        int brick_left;
        int brick_right;
        int brick_upper;
        int brick_lower;
         */

        double brick_left;
        double brick_right;
        double brick_upper;
        double brick_lower;


        for (int i = 1; i <= max_strength_level; i++) {
            for (int j = 0; j < bricks_per_row; j++) {

                brick_left = left_wall_ + (j * brick_length) + 50;
                brick_right = brick_left + brick_length;
                brick_upper = upper_wall_ + (i * brick_height);
                brick_lower = brick_upper + brick_height;

                /*
                brick_left = double(left_wall_ + (j * brick_length));
                brick_right = double(brick_left + brick_length);
                brick_upper = upper_wall_ + (i * brick_height); //(i - 1)
                brick_lower = brick_upper + brick_height;
                 */
                /*
                if (j == 0) {
                    brick_left = double(left_wall_ + (j * brick_length));
                    brick_right = double(brick_left + brick_length);
                    brick_upper = upper_wall_ + (i * brick_height); //(i - 1)
                    brick_lower = brick_upper + brick_height;

                } else {
                    brick_left = double(left_wall_ + (j * brick_length)); // + 1;
                    brick_right = double(brick_left + brick_length);
                    brick_upper = upper_wall_ + (i * brick_height); //(i - 1)
                    brick_lower = brick_upper + brick_height; // + 1;
                }
                 */

                // FIX STRENGTH ASSIGNMENT, INCORRECT!
                // i = strength (1 thru 4)
                bricks_.push_back(Brick(brick_left, brick_right, brick_upper, brick_lower, i)); //incorrect i value

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

        int color_switch = 0;
        int color_spacer = 255 / bricks_.size();
        int color_multiplier = 0;

        for(const Brick &brick : bricks_) {

            /*
            if (color_switch % 2 == 0) {
                //ci::gl::color(ci::Color("yellow"));

                ci::gl::color(ci::Color8u(255 - (color_multiplier * color_spacer),
                                          178, (color_multiplier * color_spacer)));

                ci::gl::color(ci::Color8u(255 - (color_multiplier * color_spacer),
                                          178,
                                          (color_multiplier * color_spacer)));
                //green: (color_multiplier * color_spacer)


            } else {
                //ci::gl::color(ci::Color("green"));
                //ci::gl::color(ci::Color8u(255, 178, 112));

                ci::gl::color(ci::Color8u(255 - (color_multiplier * color_spacer),
                                          178, (color_multiplier * color_spacer)));

                ci::gl::color(ci::Color8u(255 - (color_multiplier * color_spacer),
                                          178,
                                          (color_multiplier * color_spacer) / 2));

            }*/
            if (color_switch % 2 == 0) {
                ci::gl::color(ci::Color8u(220, // / 2, // - (color_multiplier * color_spacer),
                                          0, (color_multiplier * color_spacer)));

            } else {
                ci::gl::color(ci::Color8u(220, // - (color_multiplier * color_spacer),
                                          75, (color_multiplier * color_spacer)));

            }

            /*
            ci::gl::color(ci::Color8u(255, // - (color_multiplier * color_spacer),
                                      178, (color_multiplier * color_spacer)));*/

            //ci::gl::drawStrokedRect(ci::Rectf(brick.GetLeftUpperBound(), brick.GetRightLowerBound()));
            ci::gl::drawSolidRect(ci::Rectf(brick.GetLeftUpperBound(), brick.GetRightLowerBound()));

            color_multiplier++;
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

    void GameBox::CheckBrickCollision() { // FIX THIS

        for (Brick &brick : bricks_) {
            if (ball_.GetPosition().x >= brick.GetLeftWall() &&
                ball_.GetPosition().x <= brick.GetRightWall()) {

                //checks if ball hits brick upper/lower wall
                if (ball_.GetPosition().y == brick.GetLowerWall() + ball_.GetRadius()||
                    ball_.GetPosition().y == brick.GetUpperWall() - ball_.GetRadius()) {

                    vec2 current_velocity = ball_.GetVelocity() * vec2(1, -1);
                    ball_.SetVelocity(current_velocity);

                }
            }

            if (ball_.GetPosition().y >= brick.GetLowerWall() &&
                ball_.GetPosition().y <= brick.GetUpperWall()) {

                //checks if ball hits brick left/right side wall
                if (ball_.GetPosition().x == brick.GetLeftWall() - ball_.GetRadius() ||
                    ball_.GetPosition().x == brick.GetRightWall() + ball_.GetRadius()) {

                    vec2 current_velocity = ball_.GetVelocity() * vec2(-1, 1);
                    ball_.SetVelocity(current_velocity);

                }
            }


            /*
            if (ball_.GetPosition().y <= upper_wall_ + ball_.GetRadius() ||
                ball_.GetPosition().y >= lower_wall_ - ball_.GetRadius()) {

                vec2 current_velocity = ball_.GetVelocity() * vec2(1, -1);
                ball_.SetVelocity(current_velocity);
            }
             */


        }
    }

    Ball& GameBox::GetBall() {
        return ball_;
    }

    Paddle& GameBox::GetPaddle() {
        return paddle_;
    }

}
