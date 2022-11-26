#pragma once

#include <QPointF>

namespace Utils
{
    class TrigonometricUtils
    {
    public:
        /**
         * @brief Calculate the angle between 2 points
         *
         * @param point1Coordinates xy coordinates of point 1
         * @param point2Coordinates xy coordinates of point 2
         * @return An angle in degrees
         */
        static float calculateAngleBetweenTwoPointsCoordinates(const QPointF &point1Coordinates,
                                                               const QPointF &point2Coordinates);

        /**
         * @brief Calculate the distance between 2 points
         *
         * @param point1Coordinates xy coordinates of point 1
         * @param point2Coordinates xy coordinates of point 2
         * @return The distance
         */
        static float calculateDistanceBetweenTwoPointsCoordinates(const QPointF &point1Coordinates,
                                                                  const QPointF &point2Coordinates);

        /**
         * @brief Rotate a specific angle to a specific rotate angle
         *
         * @param angleDegrees The angle to rotate
         * @param rotateDegrees The degrees to rotate the angle
         * @return The rotated angle
         */
        static float rotateAngle(const float &angleDegrees, const float &rotateDegrees);

    private:
        TrigonometricUtils();
    };
}
