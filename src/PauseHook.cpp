#include <Geode/Geode.hpp>
#include <Geode/modify/PauseLayer.hpp>
#include "BotUI.hpp"

using namespace geode::prelude;

class $modify(MFPauseLayer, PauseLayer) {
    void customSetup() {
        PauseLayer::customSetup();

        auto sprite = ButtonSprite::create("MacroFlow");

        auto btn = CCMenuItemSpriteExtra::create(
            sprite,
            this,
            menu_selector(MFPauseLayer::onMacroFlow)
        );

        auto menu = CCMenu::create();
        menu->setPosition({0, 0});
        menu->addChild(btn);
        addChild(menu);

        auto winSize = CCDirector::get()->getWinSize();

        btn->setPosition({winSize.width / 2, 50});
        btn->setScale(0.7f);
    }

    void onMacroFlow(CCObject*) {
        auto ui = BotUI::create(); CCDirector::get()->getRunningScene()->addChild(ui, 999);
    }
};
