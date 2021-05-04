#include "ball.h"
#include "cinder/gl/gl.h"

using glm::vec2;

namespace brickbreaker {

    Ball::Ball() {}

    Ball::Ball(vec2 position, vec2 velocity, double radius) {
        position_ = position;
        velocity_ = velocity;
        radius_ = radius;
    }

    void Ball::SetVelocity(vec2 newVelocity) {
        velocity_ = newVelocity;
    }

    void Ball::SetPosition(vec2 newPosition) {
        position_ = newPosition;
    }

    vec2 Ball::GetVelocity() const {
        return velocity_;
    }

    vec2 Ball::GetPosition() const {
        return position_;
    }

    double Ball::GetRadius() const {
        return radius_;
    }

    void Ball::UpdatePosition() {
        position_ += velocity_;
    }

    void Ball::IncreaseVelocity() {
        velocity_ = velocity_ * vec2(1.03, 1.03);
    }

}