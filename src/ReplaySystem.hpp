#pragma once
#include <Geode/Geode.hpp>
#include <vector>
#include <string>

using namespace geode::prelude;

enum class BotState {
    Idle,
    Recording,
    Playing
};

struct InputFrame {
    int frame;
    bool down;
    int button;
    bool isPlayer1;
};

class ReplaySystem {
public:
    static ReplaySystem& get();

    void handleButton(bool down, int button, bool isPlayer1);
    void onLevelStart();
    void onLevelEnd();

    void startRecording();
    void stopRecording();
    void startPlaying();
    void stopPlaying();

    bool saveReplay(const std::string& name);
    bool loadReplay(const std::string& name);

    BotState getState() const { return m_state; }
    int getCurrentFrame() const { return m_frame; }
    std::string getReplayDir() const;

private:
    BotState m_state = BotState::Idle;
    std::vector<InputFrame> m_inputs;
    int m_frame = 0;
    int m_playbackIndex = 0;
};
