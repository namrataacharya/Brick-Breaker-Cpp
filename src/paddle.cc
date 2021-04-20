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
    }

    void Paddle::SetLeftBound(vec2 newLeft) {
        left_bound_ = newLeft;
    }

    void Paddle::SetRightBound(vec2 newRight) {
        right_bound_ = newRight;
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





    /*
    Paddle::Paddle(vec2 position) {
        position_ = position;
    }

    void Paddle::SetPosition(vec2 newPosition) {
        position_ = newPosition;
    }

    vec2 Paddle::GetPosition() const {
        return position_;
    }
     */

    /*
    void Paddle::UpdatePosition() {
        position_ += velocity_;
    }
     */

}