#include <Geode/Geode.hpp>
#include <Geode/modify/PlayLayer.hpp>
#include <Geode/modify/GJBaseGameLayer.hpp>
#include "ReplaySystem.hpp"

using namespace geode::prelude;

$modify(PlayLayer) {
    bool init(GJGameLevel* level, bool useReplay, bool dontCreateObjects) {
        if (!PlayLayer::init(level, useReplay, dontCreateObjects))
            return false;

        ReplaySystem::get().onLevelStart();
        return true;
    }

    void onQuit() {
        ReplaySystem::get().onLevelEnd();
        PlayLayer::onQuit();
    }

    void levelComplete() {
        ReplaySystem::get().onLevelEnd();
        PlayLayer::levelComplete();
    }
};

$modify(GJBaseGameLayer) {
    void handleButton(bool down, int button, bool isPlayer1) {
        ReplaySystem::get().handleButton(down, button, isPlayer1);
        GJBaseGameLayer::handleButton(down, button, isPlayer1);
    }
};
