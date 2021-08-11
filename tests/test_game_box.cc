#include <catch2/catch.hpp>
#include <game_box.h>

using brickbreaker::GameBox;
using brickbreaker::Ball;
using glm::vec2;

TEST_CASE("Game set up") {
    SECTION("Initialize ball test") {
        GameBox game = GameBox();

        REQUIRE(game.GetBall().GetVelocity() == vec2(2.5, 2.5));
        REQUIRE(game.GetBall().GetRadius() == 7);
    }
}

TEST_CASE("Post wall collision velocity test") {
    SECTION("Right wall collision") {
        GameBox game = GameBox();

        game.GetBall().SetVelocity(vec2(3, 3));
        game.GetBall().SetPosition(vec2(690, 500));
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

        game.GetBall().SetVelocity(vec2(-3, 3));
        game.GetBall().SetPosition(vec2(200, 150));
        game.AdvanceOneFrame();
        game.AdvanceOneFrame();

        REQUIRE(game.GetBall().GetVelocity() == vec2(3, 3));
    }
}

TEST_CASE("Brick collision tests") {
    SECTION("Right wall brick collision") { //WORKS
        GameBox game = GameBox();

        game.GetBall().SetVelocity(vec2(-3, 3));
        game.GetBall().SetPosition(vec2(657, 200));
        game.AdvanceOneFrame();
        game.AdvanceOneFrame();

        REQUIRE(game.GetBall().GetVelocity() == vec2(3, 3));
    }

    SECTION("Left wall brick collision") {
        GameBox game = GameBox();

        game.GetBall().SetPosition(vec2(142, 200));
        game.GetBall().SetVelocity(vec2(3, 3));
        game.AdvanceOneFrame();
        game.AdvanceOneFrame();

        REQUIRE(game.GetBall().GetVelocity() == vec2(-3, 3));
    }

    SECTION("Upper wall brick collision") {
        GameBox game = GameBox();

        game.GetBall().SetPosition(vec2(250, 142));
        game.GetBall().SetVelocity(vec2(3, 3));
        game.AdvanceOneFrame();
        game.AdvanceOneFrame();

        REQUIRE(game.GetBall().GetVelocity() == vec2(3, -3));
    }

    SECTION("Lower wall brick collision") {
        GameBox game = GameBox();

        game.GetBall().SetPosition(vec2(250, 357));
        game.GetBall().SetVelocity(vec2(3, -3));
        game.AdvanceOneFrame();
        game.AdvanceOneFrame();

        REQUIRE(game.GetBall().GetVelocity() == vec2(3.09, 3.09));
    }
}

TEST_CASE("Speed increase tests") {
    SECTION("Left wall brick collision - speed increase") {
        GameBox game = GameBox();

        game.GetBall().SetPosition(vec2(142, 340));
        game.GetBall().SetVelocity(vec2(3, 3));
        game.AdvanceOneFrame();
        game.AdvanceOneFrame();

        REQUIRE(game.GetBall().GetVelocity() == vec2(-3.09, 3.09));
    }

    SECTION("Lower wall brick collision - speed increase") {
        GameBox game = GameBox();

        game.GetBall().SetPosition(vec2(250, 357));
        game.GetBall().SetVelocity(vec2(3, -3));
        game.AdvanceOneFrame();
        game.AdvanceOneFrame();

        REQUIRE(game.GetBall().GetVelocity() == vec2(3.09, 3.09));
    }
}

TEST_CASE("Paddle collision tests") {
    SECTION("Upper surface collision") {
        GameBox game = GameBox();

        game.GetBall().SetPosition(vec2(363, 642));
        game.GetBall().SetVelocity(vec2(3, 3));
        game.AdvanceOneFrame();
        game.AdvanceOneFrame();

        REQUIRE(game.GetBall().GetVelocity() == vec2(3, -3));

    }

    SECTION("Left wall collision") {
        GameBox game = GameBox();

        game.GetBall().SetPosition(vec2(352, 653));
        game.GetBall().SetVelocity(vec2(3, 3));
        game.AdvanceOneFrame();
        game.AdvanceOneFrame();

        REQUIRE(game.GetBall().GetVelocity() == vec2(-3, 3));
    }

    SECTION("Right wall collision") {
        GameBox game = GameBox();

        game.GetBall().SetPosition(vec2(448, 653));
        game.GetBall().SetVelocity(vec2(-3, 3));
        game.AdvanceOneFrame();
        game.AdvanceOneFrame();

        REQUIRE(game.GetBall().GetVelocity() == vec2(3, 3));
    }
}

TEST_CASE("Life count tests") {
    SECTION("Initial life count") {
        GameBox game = GameBox();
        REQUIRE(game.GetLifeCount() == 3);
    }

    SECTION("Life lost") {
        GameBox game = GameBox();

        game.GetBall().SetPosition(vec2(500, 692));
        game.GetBall().SetVelocity(vec2(3, 3));
        game.AdvanceOneFrame();
        game.AdvanceOneFrame();

        REQUIRE(game.GetLifeCount() == 2);
    }
}

