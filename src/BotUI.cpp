#include "BotUI.hpp"
#include "ReplaySystem.hpp"

BotUI* BotUI::create() {
    auto ret = new BotUI();
    if (ret->initAnchored(280, 200, "GJ_square01.png")) {
        ret->autorelease();
        return ret;
    }
    delete ret;
    return nullptr;
}

bool BotUI::setup() {
    setTitle("MacroFlow");

    auto& rs = ReplaySystem::get();

    m_statusLabel = CCLabelBMFont::create("Idle", "bigFont.fnt");
    m_statusLabel->setScale(0.5f);
    m_statusLabel->setPosition({140, 155});
    m_mainLayer->addChild(m_statusLabel);

    m_frameLabel = CCLabelBMFont::create("Frames: 0", "goldFont.fnt");
    m_frameLabel->setScale(0.4f);
    m_frameLabel->setPosition({140, 138});
    m_mainLayer->addChild(m_frameLabel);

    auto menu = CCMenu::create();
    menu->setPosition({0, 0});
    m_mainLayer->addChild(menu);

    auto recordBtn = CCMenuItemSpriteExtra::create(
        ButtonSprite::create("Record", "bigFont.fnt", "GJ_button_01.png"),
        this, menu_selector(BotUI::onRecord)
    );
    recordBtn->setPosition({70, 100});
    menu->addChild(recordBtn);

    auto playBtn = CCMenuItemSpriteExtra::create(
        ButtonSprite::create("Play", "bigFont.fnt", "GJ_button_02.png"),
        this, menu_selector(BotUI::onPlay)
    );
    playBtn->setPosition({140, 100});
    menu->addChild(playBtn);

    auto stopBtn = CCMenuItemSpriteExtra::create(
        ButtonSprite::create("Stop", "bigFont.fnt", "GJ_button_06.png"),
        this, menu_selector(BotUI::onStop)
    );
    stopBtn->setPosition({210, 100});
    menu->addChild(stopBtn);

    auto saveBtn = CCMenuItemSpriteExtra::create(
        ButtonSprite::create("Save", "bigFont.fnt", "GJ_button_04.png"),
        this, menu_selector(BotUI::onSave)
    );
    saveBtn->setPosition({100, 55});
    menu->addChild(saveBtn);

    auto loadBtn = CCMenuItemSpriteExtra::create(
        ButtonSprite::create("Load", "bigFont.fnt", "GJ_button_04.png"),
        this, menu_selector(BotUI::onLoad)
    );
    loadBtn->setPosition({180, 55});
    menu->addChild(loadBtn);

    return true;
}

void BotUI::updateLabels() {
    auto& rs = ReplaySystem::get();
    switch (rs.getState()) {
        case BotState::Idle:      m_statusLabel->setString("Idle"); break;
        case BotState::Recording: m_statusLabel->setString("Recording..."); break;
        case BotState::Playing:   m_statusLabel->setString("Playing..."); break;
    }
    auto frameStr = fmt::format("Frames: {}", rs.getCurrentFrame());
    m_frameLabel->setString(frameStr.c_str());
}

void BotUI::onRecord(CCObject*) {
    ReplaySystem::get().startRecording();
    updateLabels();
    onClose(nullptr);
}

void BotUI::onPlay(CCObject*) {
    ReplaySystem::get().startPlaying();
    updateLabels();
    onClose(nullptr);
}

void BotUI::onStop(CCObject*) {
    ReplaySystem::get().stopRecording();
    ReplaySystem::get().stopPlaying();
    updateLabels();
}

void BotUI::onSave(CCObject*) {
    ReplaySystem::get().saveReplay("macro");
    FLAlertLayer::create("MacroFlow", "Macro saved!", "OK")->show();
}

void BotUI::onLoad(CCObject*) {
    ReplaySystem::get().loadReplay("macro");
    updateLabels();
    FLAlertLayer::create("MacroFlow", "Macro loaded!", "OK")->show();
}
