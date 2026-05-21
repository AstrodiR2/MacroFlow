#pragma once

#include <Geode/Geode.hpp>

using namespace geode::prelude;

class BotUI : public FLAlertLayer {
protected:
    CCLabelBMFont* m_statusLabel = nullptr;
    CCLabelBMFont* m_frameLabel = nullptr;

public:
    static BotUI* create();

    bool init();

    void onRecord(CCObject*);
    void onPlay(CCObject*);
    void onStop(CCObject*);
    void onSave(CCObject*);
    void onLoad(CCObject*);

    void updateLabels();
};
