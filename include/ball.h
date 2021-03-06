#pragma once

#include "cinder/gl/gl.h"

#ifndef FINAL_PROJECT_NAMRATAACHARYA2_BALL_H
#define FINAL_PROJECT_NAMRATAACHARYA2_BALL_H
#endif //FINAL_PROJECT_NAMRATAACHARYA2_BALL_H

using glm::vec2;

namespace brickbreaker {

    class Ball {
    public:

        Ball();

        /**
         * Creates ball with specified attributes.
         * @param position - the ball's starting position.
         * @param velocity - the ball's intitial velocity.
         * @param radius - the ball's radius.
         */
        Ball(vec2 position, vec2 velocity, double radius);

        /**
         * Changes and sets the ball's velocity.
         * @param newVelocity - the ball's starting position.
         */
        void SetVelocity(vec2 newVelocity);

        /**
         * Changes and sets the ball's position.
         * @param newPosition - the ball's starting position.
         */
        void SetPosition(vec2 newPosition);

        /**
         * Returns the ball's current velocity.
         * @return vector representing ball's velocity.
         */
        vec2 GetVelocity() const;

        /**
         * Returns the ball's current position.
         * @return vector representing ball's position.
         */
        vec2 GetPosition() const;

        /**
         * Returns the ball's radius.
         * @return double representing ball's radius.
         */
        double GetRadius() const;

        /**
         * Updates the ball's position based on its velocity and current position.
         */
        void UpdatePosition();

        /**
         * Increase the ball's speed by changing the velocity.
         */
        void IncreaseVelocity();

    private:
        vec2 position_;
        vec2 velocity_;
        double radius_;

    };

}
