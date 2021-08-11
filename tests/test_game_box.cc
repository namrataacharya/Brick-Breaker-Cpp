#include <catch2/catch.hpp>
#include <game_box.h>

using brickbreaker::GameBox;
using brickbreaker::Ball;

using glm::vec2;


TEST_CASE("Game set up") {
    SECTION("Initialize ball test") {
        GameBox game = GameBox();

        REQUIRE(game.GetBall().GetVelocity() == vec2(3, 3));
        REQUIRE(game.GetBall().GetPosition() == vec2(400, 600));
        REQUIRE(game.GetBall().GetRadius() == 10);
    }
}

TEST_CASE("Post wall collision velocity test") {
    SECTION("Right wall collision") {
        GameBox game = GameBox();

        game.GetBall().SetPosition(vec2(690, 400));
        game.AdvanceOneFrame();
        game.AdvanceOneFrame();

        REQUIRE(game.GetBall().GetVelocity() == vec2(-3, 3));
    }

    SECTION("Left wall collision") {
        GameBox game = GameBox();

        game.GetBall().SetPosition(vec2(110, 400));
        game.GetBall().SetVelocity(vec2(-3, 3));
        game.AdvanceOneFrame();
        game.AdvanceOneFrame();

        REQUIRE(game.GetBall().GetVelocity() == vec2(3, 3));
    }

    SECTION("Upper wall collision") {
        GameBox game = GameBox();

        game.GetBall().SetPosition(vec2(400, 110));
        game.GetBall().SetVelocity(vec2(3, -3));
        game.AdvanceOneFrame();
        game.AdvanceOneFrame();

        REQUIRE(game.GetBall().GetVelocity() == vec2(3, 3));
    }

    SECTION("Lower wall collision") {
        GameBox game = GameBox();

        game.GetBall().SetPosition(vec2(200, 690));
        game.AdvanceOneFrame();
        game.AdvanceOneFrame();

        REQUIRE(game.GetBall().GetVelocity() == vec2(3, -3));
    }
}
