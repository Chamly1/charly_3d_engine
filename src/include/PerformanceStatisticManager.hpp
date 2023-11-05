#ifndef CHARLY_3D_ENGINE_PERFORMANCESTATISTICMANAGER_HPP
#define CHARLY_3D_ENGINE_PERFORMANCESTATISTICMANAGER_HPP

#include "Text.hpp"

namespace Charly {

    class PerformanceStatisticManager {
    private:
        Text mStatisticText;
        char mStrBuffer[1000];

        float mLogicUpdatesPerSecond;

        float mStatisticsUpdateTime;
        int mFramesCounter;
        int mLogicUpdatesCounter;
        float mLogicUpdateTimeAccumulator;
        float mRenderTimeAccumulator;

    public:

        PerformanceStatisticManager(const std::shared_ptr<Font>& font, const std::shared_ptr<Shader>& textShader);
        /**
         * Update statistics. Update happen one time per second.
         *
         * @param dt delta time.
         */
        void update(float dt);
        void draw(const glm::mat4& viewMatrix, const glm::mat4& projectionMatrix) const;
        /**
         * Increment frame counter which use to calculate FPS and render time. Call it once per every general render call.
         */
        void incrementFramesCounter();
        /**
         * Increment frame counter which use to calculate logic update per second, simulation speed and logic update time.
         * Call it once per every general update call.
         */
        void incrementLogicUpdatesCounter();
        /**
         * Accumulate render time which use to calculate render time. Call it for every general render call.
         *
         * @param time time that general render call take.
         */
        void accumulateRenderTime(float time);
        /**
         * Accumulate logic update time which use to calculate update time. Call it for every general update call.
         *
         * @param time time that general update call take.
         */
        void accumulateUpdateTime(float time);

    };

}

#endif //CHARLY_3D_ENGINE_PERFORMANCESTATISTICMANAGER_HPP
