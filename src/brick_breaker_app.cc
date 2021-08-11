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

    void BrickBreakerApp::keyDown(ci::app::KeyEvent event) {
        switch (event.getCode()) {
            case ci::app::KeyEvent::KEY_RIGHT:
                game_.GetPaddle().MoveRight();
                break;

            case ci::app::KeyEvent::KEY_LEFT:
                game_.GetPaddle().MoveLeft();
                break;
        }
    }

}  // namespace brickbreaker
