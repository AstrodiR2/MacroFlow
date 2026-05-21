#include "ReplaySystem.hpp"
#include <Geode/modify/PlayLayer.hpp>
#include <fstream>
#include <filesystem>

ReplaySystem& ReplaySystem::get() {
    static ReplaySystem instance;
    return instance;
}

std::string ReplaySystem::getReplayDir() const {
    auto dir = Mod::get()->getSaveDir() / "replays";
    std::filesystem::create_directories(dir);
    return dir.string();
}

void ReplaySystem::onLevelStart() {
    m_frame = 0;
    m_playbackIndex = 0;

    if (m_state == BotState::Recording) {
        m_inputs.clear();
    }
}

void ReplaySystem::onLevelEnd() {
    if (m_state == BotState::Playing) {
        stopPlaying();
    }
}

void ReplaySystem::handleButton(bool down, int button, bool isPlayer1) {
    if (m_state == BotState::Recording) {
        m_inputs.push_back({ m_frame, down, button, isPlayer1 });
    } else if (m_state == BotState::Playing) {
        // playback handled in frame step
    }

    m_frame++;
}

void ReplaySystem::startRecording() {
    m_inputs.clear();
    m_state = BotState::Recording;
    log::info("MacroFlow: Recording started");
}

void ReplaySystem::stopRecording() {
    m_state = BotState::Idle;
    log::info("MacroFlow: Recording stopped, {} frames", m_inputs.size());
}

void ReplaySystem::startPlaying() {
    m_playbackIndex = 0;
    m_state = BotState::Playing;
    log::info("MacroFlow: Playback started");
}

void ReplaySystem::stopPlaying() {
    m_state = BotState::Idle;
    log::info("MacroFlow: Playback stopped");
}

bool ReplaySystem::saveReplay(const std::string& name) {
    auto path = getReplayDir() + "/" + name + ".mf";
    std::ofstream file(path, std::ios::binary);
    if (!file) return false;

    uint32_t count = m_inputs.size();
    file.write(reinterpret_cast<const char*>(&count), sizeof(count));

    for (auto& input : m_inputs) {
        file.write(reinterpret_cast<const char*>(&input), sizeof(InputFrame));
    }

    log::info("MacroFlow: Saved replay to {}", path);
    return true;
}

bool ReplaySystem::loadReplay(const std::string& name) {
    auto path = getReplayDir() + "/" + name + ".mf";
    std::ifstream file(path, std::ios::binary);
    if (!file) return false;

    m_inputs.clear();

    uint32_t count;
    file.read(reinterpret_cast<char*>(&count), sizeof(count));

    for (uint32_t i = 0; i < count; i++) {
        InputFrame frame;
        file.read(reinterpret_cast<char*>(&frame), sizeof(InputFrame));
        m_inputs.push_back(frame);
    }

    log::info("MacroFlow: Loaded replay from {}", path);
    return true;
}
