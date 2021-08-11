#include "paddle.h"
#include "cinder/gl/gl.h"

using glm::vec2;

namespace brickbreaker {

    Paddle::Paddle() {}

    Paddle::Paddle(vec2 left_bound, vec2 right_bound) {
        left_bound_ = left_bound;
        right_bound_ = right_bound;

        left_x_ = left_bound.x;
        right_x_ = right_bound.x;

        upper_y_ = left_bound.y;
        lower_y_ = right_bound.y;

        length_ = right_x_ - left_x_;
    }

    void Paddle::MoveRight() {
        right_bound_ += vec2 (shift, 0);
        left_bound_ += vec2 (shift, 0);

        //make sure paddle is within game box
        if (right_bound_.x >= right_wall_) {
            right_bound_ = vec2 (right_wall_, upper_y_);
            left_bound_ = vec2  (right_wall_ - length_, lower_y_);
        }

        right_x_ = right_bound_.x;
        lower_y_ = right_bound_.y;
        left_x_ = left_bound_.x;
        upper_y_ = left_bound_.y;
    }

    void Paddle::MoveLeft() {
        right_bound_ += vec2 (-shift, 0);
        left_bound_ += vec2 (-shift, 0);

        //make sure paddle is within game box
        if (left_bound_.x <= left_wall_) {
            right_bound_ = vec2 (left_wall_ + length_, upper_y_);
            left_bound_ = vec2  (left_wall_, lower_y_);
        }

        right_x_ = right_bound_.x;
        lower_y_ = right_bound_.y;
        left_x_ = left_bound_.x;
        upper_y_ = left_bound_.y;
    }

    vec2 Paddle::GetLeftBound() const {
        return left_bound_;
    }

    vec2 Paddle::GetRightBound() const {
        return right_bound_;
    }


    int Paddle::GetLeft() const {
        return left_x_;
    }

    int Paddle::GetRight() const {
        return right_x_;
    }

    int Paddle::GetUpper() const {
        return upper_y_;
    }

    int Paddle::GetLower() const {
        return lower_y_;
    }

}