//
// Created by Namrata Acharya on 4/19/21.
//
#pragma once
#ifndef FINAL_PROJECT_NAMRATAACHARYA2_GAME_BOX_H
#define FINAL_PROJECT_NAMRATAACHARYA2_GAME_BOX_H
#endif //FINAL_PROJECT_NAMRATAACHARYA2_GAME_BOX_H

#include "cinder/gl/gl.h"

namespace brickbreaker {

    class GameBox {

    public:
        /**
         * Creates container and desired number of particles within container.
         * @param the number of particles to be added to the container.
         */
        GameBox();

        /**
         * Displays the container walls and the current positions of the particles.
         */
        void Display() const;

        /**
         * Updates the positions and velocities of all particles (based on the rules
         * described in the assignment documentation).
         */
        void AdvanceOneFrame();

    };
}