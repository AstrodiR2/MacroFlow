#include <Geode/Geode.hpp>
#include <Geode/modify/PauseLayer.hpp>
#include "BotUI.hpp"

using namespace geode::prelude;

class $modify(MFPauseLayer, PauseLayer) {
    void customSetup() {
        PauseLayer::customSetup();

        auto btn = CCMenuItemSpriteExtra::create(
            ButtonSprite::create("MacroFlow", "bigFont.fnt", "GJ_button_01.png"),
            this, menu_selector(MFPauseLayer::onMacroFlow)
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
        BotUI::create()->show();
    }
};
