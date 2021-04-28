#include "brick.h"
#include "cinder/gl/gl.h"

namespace brickbreaker {

    Brick::Brick() {}

    Brick::Brick(int strength) {
        strength_ = strength;
    }

    /*
    Brick::Brick(int left_wall, int right_wall, int upper_wall, int lower_wall, int strength) {
        left_wall_ = left_wall;
        right_wall_ = right_wall;
        upper_wall_ = upper_wall;
        lower_wall_ = lower_wall;
        strength_ = strength;

        left_bound_ = vec2(left_wall_, upper_wall_);
        right_bound_ = vec2(right_wall_, lower_wall_);
    }*/

    Brick::Brick(double left_wall, double right_wall, double upper_wall, double lower_wall, double strength) {
        left_wall_ = left_wall;
        right_wall_ = right_wall;
        upper_wall_ = upper_wall;
        lower_wall_ = lower_wall;
        strength_ = strength;

        left_bound_ = vec2(left_wall_, upper_wall_);
        right_bound_ = vec2(right_wall_, lower_wall_);
    }

    /*
    int Brick::GetLeftWall() {
        return left_wall_;
    }

    int Brick::GetRightWall() {
        return right_wall_;
    }

    int Brick::GetUpperWall() {
        return upper_wall_;
    }

    int Brick::GetLowerWall() {
        return lower_wall_;
    }*/

    double Brick::GetLeftWall() {
        return left_wall_;
    }

    double Brick::GetRightWall() {
        return right_wall_;
    }

    double Brick::GetUpperWall() {
        return upper_wall_;
    }

    double Brick::GetLowerWall() {
        return lower_wall_;
    }

    vec2 Brick::GetLeftUpperBound() const {
        return left_bound_;
    }

    vec2 Brick::GetRightLowerBound() const {
        return right_bound_;
    }

    int Brick::GetHitCount() {
        return hit_count_;
    }

    void Brick::IncreaseHitCount() {
        hit_count_++;

        if (hit_count_ >= strength_) {
            is_destroyed_ = true;
        }
    }

    bool Brick::IsDestroyed() {
        return is_destroyed_; //fix implementation, incomplete
    }

}