#include "brick_breaker_app.h"

namespace brickbreaker {

    BrickBreakerApp::BrickBreakerApp() {
        ci::app::setWindowSize(kWindowSize, kWindowSize);
    }

    void BrickBreakerApp::draw() {
        ci::Color background_color("black");
        ci::gl::clear(background_color);

        game_.Display();
    }

    void BrickBreakerApp::update() {
        game_.AdvanceOneFrame();
    }

}  // namespace brickbreaker
