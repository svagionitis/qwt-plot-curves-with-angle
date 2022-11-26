#include "TrigonometricUtils.h"

#include <QDebug>

namespace Utils
{
    float TrigonometricUtils::calculateAngleBetweenTwoPointsCoordinates(const QPointF &point1Coordinates,
                                                                        const QPointF &point2Coordinates)
    {
        qDebug() << "point1Coordinates: " << point1Coordinates << " point2Coordinates: " << point2Coordinates;

        return (float)(atan2(point1Coordinates.y() - point2Coordinates.y(),
                             point1Coordinates.x() - point2Coordinates.x()) *
                       (180 / M_PI));
    }

    float TrigonometricUtils::calculateDistanceBetweenTwoPointsCoordinates(const QPointF &point1Coordinates,
                                                                           const QPointF &point2Coordinates)
    {
        qDebug() << "point1Coordinates: " << point1Coordinates << " point2Coordinates: " << point2Coordinates;

        return (float)sqrt(pow(point1Coordinates.y() - point2Coordinates.y(), 2) +
                           pow(point1Coordinates.x() - point2Coordinates.x(), 2));
    }

    float TrigonometricUtils::rotateAngle(const float &angleDegrees, const float &rotateDegrees)
    {
        qDebug() << "angleDegrees: " << angleDegrees << " rotateDegrees: " << rotateDegrees;

        auto rotateAngleDegrees = (float)fmod((angleDegrees + rotateDegrees), 360.0f);

        return rotateAngleDegrees;
    }
}
