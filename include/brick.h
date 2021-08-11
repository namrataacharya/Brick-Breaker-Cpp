#pragma once
#ifndef FINAL_PROJECT_NAMRATAACHARYA2_BRICK_H
#define FINAL_PROJECT_NAMRATAACHARYA2_BRICK_H
#endif //FINAL_PROJECT_NAMRATAACHARYA2_BRICK_H

#include "cinder/gl/gl.h"

using glm::vec2;

namespace brickbreaker {
    class Brick {

    public:

        /**
         * Default constructor.
         */
        Brick();

        /**
         * Constructor that takes in the brick strength.
         * @param the strength of the brick.
         */
        Brick(int strength);

        /**
         * Constructor that takes in and sets multiple values for the brick.
         * @param left_wall - the x value representing the brick's left wall.
         * @param right_wall -the x value representing the brick's right wall.
         * @param upper_wall -the y value representing the brick's upper wall.
         * @param lower_wall -the y value representing the brick's lower wall.
         * @param strength - the number of hits required to destroy the brick.
         */
        Brick(double left_wall, double right_wall, double upper_wall, double lower_wall, double strength);

        /**
         * Returns the x value representing the brick's left wall.
         * @return x value of the brick's left wall.
         */
        double GetLeftWall();

        /**
         * Returns the x value representing the brick's right wall.
         * @return x value of the brick's right wall.
         */
        double GetRightWall();

        /**
         * Returns the y value representing the brick's upper wall.
         * @return y value of the brick's upper wall.
         */
        double GetUpperWall();

        /**
         * Returns the y value representing the brick's lower wall.
         * @return y value of the brick's lower wall.
         */
        double GetLowerWall();

        /**
         * Returns the vector holding brick's left and upper wall.
         * @return vector representing brick's left and upper wall.
         */
        vec2 GetLeftUpperBound() const;

        /**
         * Returns the vector holding brick's right and lower wall.
         * @return vector representing brick's right and lower wall.
         */
        vec2 GetRightLowerBound() const;

        /**
         * Increases the brick's hit count by 1 every time there is a brick collision.
         */
        void IncreaseHitCount();

        /**
         * Returns a bool that shows whether the brick has been destroyed or not
         * @return bool true or false if the brick is destroyed or not
         */
        bool IsDestroyed();

        /**
         * Returns an int value that represents the number of points the brick is worth.
         * @return point value of the brick.
         */
        int GetPointValue();


    private:

        double left_wall_;
        double right_wall_;
        double upper_wall_;
        double lower_wall_;

        vec2 left_bound_;
        vec2 right_bound_;

        int strength_;
        int hit_count_ = 0;
        int points_;

        bool is_destroyed_ = false;

    };
}