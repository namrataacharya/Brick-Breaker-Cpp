//
// Created by Namrata Acharya on 4/19/21.
//
/*
#pragma once
#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"
 */
#include "brick_breaker_app.h"


namespace brickbreaker {

    BrickBreakerApp::BrickBreakerApp() {
        ci::app::setWindowSize(kWindowSize, kWindowSize);
    }

    void BrickBreakerApp::draw() {
        ci::Color background_color("black");
        ci::gl::clear(background_color);

        //container_.Display();
        game_.Display();
    }

    void BrickBreakerApp::update() {
        //container_.AdvanceOneFrame();
        game_.AdvanceOneFrame();
    }

}  // namespace brickbreaker
