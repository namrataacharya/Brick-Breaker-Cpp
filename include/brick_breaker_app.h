#pragma once
#ifndef FINAL_PROJECT_NAMRATAACHARYA2_BRICK_BREAKER_APP_H
#define FINAL_PROJECT_NAMRATAACHARYA2_BRICK_BREAKER_APP_H
#endif //FINAL_PROJECT_NAMRATAACHARYA2_BRICK_BREAKER_APP_H

#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"
#include "game_box.h"

namespace brickbreaker {

/**
 * An app for the game Brick Breaker.
 */
    class BrickBreakerApp : public ci::app::App {
    public:
        BrickBreakerApp();

        void draw() override;
        void update() override;
        void keyDown(ci::app::KeyEvent event) override;

        const int kWindowSize = 800;
        const int kMargin = 100;

    private:
        GameBox game_ = GameBox();
    };

}  // namespace brickbreaker