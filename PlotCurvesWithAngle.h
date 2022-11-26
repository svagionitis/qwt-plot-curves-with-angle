#pragma once

#include <QwtPlotCurve>

namespace PlotCurves
{
    class PlotCurvesWithAngle
    {
    public:
        constexpr static const float MinAngleBetweenCurves = 0.0;
        constexpr static const float MaxAngleBetweenCurves = 360.0;
        constexpr static const float MinAngleRotateCurves = 0.0;
        constexpr static const float MaxAngleRotateCurves = 360.0;

        /**
         * @brief Plot a line curve from a single point (the other point is (0,0))
         *
         * @param plot The Qwt plot
         * @param plotCurve The curve to plot. Called by reference in order to modify it.
         * @param positionCoordinates The coordinates of the point where the line will be plotted
         * @param symbol A symbol at the end of the line
         * @param color A color for the line
         * @param doReplot A flag to do a replot and repaint. Default is false.
         */
        static void plotLineCurveSinglePoint(QwtPlot *plot, QwtPlotCurve **plotCurve,
                                             const QPointF &positionCoordinates,
                                             QwtSymbol *symbol, Qt::GlobalColor color, bool doReplot = false);

        /**
         * @brief Plot 2 line curves given 2 points (the other point is (0,0))
         *
         * FIXME: Can we use one plotcurve to plot these two line curves???
         *
         * @param plot The Qwt plot
         * @param plotCurve1 The curve to plot for point 1. Called by reference in order to modify it.
         * @param plotCurve2 The curve to plot for point 2. Called by reference in order to modify it.
         * @param point1Coordinates xy coordinates of point 1
         * @param point2Coordinates xy coordinates of point 2
         * @param symbol1 A symbol at the end of the line 1
         * @param symbol2 A symbol at the end of the line 2
         * @param color1 A color for the line 1
         * @param color2 A color for the line 2
         * @param doReplot A flag to do a replot and repaint. Default is false.
         */
        static void plotTwoLineCurvesTwoPoints(QwtPlot *plot, QwtPlotCurve **plotCurve1, QwtPlotCurve **plotCurve2,
                                               const QPointF &point1Coordinates, const QPointF &point2Coordinates,
                                               QwtSymbol *symbol1, QwtSymbol *symbol2,
                                               Qt::GlobalColor color1, Qt::GlobalColor color2, bool doReplot = false);

        /**
         * @brief Plot a line curve given an angle from x axis and the distance of the line
         *
         * If the distance is 0.0, then no line will be plotted
         * If the distance is negative, the line will be plotted from the oposite direction
         *
         * @param plot The Qwt plot
         * @param plotCurve The curve to plot. Called by reference in order to modify it.
         * @param degreesFromXAxis The angle of the line from x axis
         * @param distance The distance of the line
         * @param symbol A symbol at the end of the line
         * @param color A color for the line
         * @param doReplot A flag to do a replot and repaint. Default is false.
         */
        static void plotLineCurveDegreesFromXAxis(QwtPlot *plot, QwtPlotCurve **plotCurve,
                                                  const float &degreesFromXAxis, const float &distance,
                                                  QwtSymbol *symbol, Qt::GlobalColor color, bool doReplot = false);

        /**
         * @brief Plot the 2 line curves given the angle between them
         *
         * @param plot The Qwt plot
         * @param plotCurve1 The curve to plot for point 1. Called by reference in order to modify it.
         * @param plotCurve2 The curve to plot for point 2. Called by reference in order to modify it.
         * @param angle The angle between the 2 line curves in degrees
         * @param xAxisAngle The angle from the x axis in degrees. Default is 0 degrees
         */
        static void plotTwoLineCurvesWithAngle(QwtPlot *plot, QwtPlotCurve **plotCurve1, QwtPlotCurve **plotCurve2,
                                               const float &angle, const float &xAxisAngle = 0);

    private:
        PlotCurvesWithAngle();
    };
}
