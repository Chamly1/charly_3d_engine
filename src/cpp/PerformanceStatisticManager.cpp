#include "PerformanceStatisticManager.hpp"
#include "Renderer.hpp"

namespace Charly {

    static const glm::vec3 STATISTIC_OVERLAY_POSITION(5.f, 595.f, 0.f);
    static const unsigned int CHARACTER_SIZE = 15;

    PerformanceStatisticManager::PerformanceStatisticManager(const std::shared_ptr<Font>& font, const std::shared_ptr<Shader>& textShader)
    : mStatisticText(font, textShader, "frames per second: -\n"
                                       "logic updates per second: -\n"
//                                       "simulation speed: -x\n"
                                       "logic update time: - s\n"
                                       "render time: - s", CHARACTER_SIZE)
    , mStatisticsUpdateTime(0.f)
    , mFramesCounter(0)
    , mLogicUpdatesCounter(0)
    , mLogicUpdateTimeAccumulator(0.f)
    , mRenderTimeAccumulator(0.f) {

        mStatisticText.setPosition(STATISTIC_OVERLAY_POSITION);
    }

    void PerformanceStatisticManager::update(float dt) {
        mStatisticsUpdateTime += dt;

        if (mStatisticsUpdateTime >= 1.f) {
            mLogicUpdatesPerSecond = mLogicUpdatesCounter / mStatisticsUpdateTime;

            snprintf(mStrBuffer, sizeof(mStrBuffer), "frames per second: %f\n"
                                                     "logic updates per second: %f\n"
//                                                     "simulation speed: %fx\n"
                                                     "logic update time: %f s\n"
                                                     "render time: %f s",
                                                     mFramesCounter / mStatisticsUpdateTime,
                                                     mLogicUpdatesPerSecond,
//                                                     mLogicUpdatesPerSecond / mTargetLogicUpdatesPerSecond,
                                                     mLogicUpdateTimeAccumulator / mLogicUpdatesCounter,
                                                     mRenderTimeAccumulator / mFramesCounter);
            mStatisticText.setString(mStrBuffer);

            mStatisticsUpdateTime = 0.f;
            mFramesCounter = 0;
            mLogicUpdatesCounter = 0;
            mLogicUpdateTimeAccumulator = 0.f;
            mRenderTimeAccumulator = 0.f;
        }
    }

    void PerformanceStatisticManager::draw(Renderer& renderer) const {
        renderer.draw(mStatisticText);
    }

    void PerformanceStatisticManager::incrementFramesCounter() {
        ++mFramesCounter;
    }

    void PerformanceStatisticManager::incrementLogicUpdatesCounter() {
        ++mLogicUpdatesCounter;
    }

    void PerformanceStatisticManager::accumulateRenderTime(float time) {
        mRenderTimeAccumulator += time;
    }

    void PerformanceStatisticManager::accumulateUpdateTime(float time) {
        mLogicUpdateTimeAccumulator += time;
    }

}
