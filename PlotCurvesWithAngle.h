#pragma once

#include <QwtPlotCurve>
#include <QwtPlotGraphicItem>
#include <QwtPlotShapeItem>

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
         * @param doBrush A flag to use brush. FIXME: It's not working properly
         * @param doReplot A flag to do a replot and repaint. Default is false.
         */
        static void plotTwoLineCurvesTwoPoints(QwtPlot *plot, QwtPlotCurve **plotCurve1, QwtPlotCurve **plotCurve2,
                                               const QPointF &point1Coordinates, const QPointF &point2Coordinates,
                                               QwtSymbol *symbol1, QwtSymbol *symbol2,
                                               Qt::GlobalColor color1, Qt::GlobalColor color2,
                                               bool doBrush, bool doReplot = false);

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

        /**
         * @brief Load an SVG image as rendered (it is scaled) at the center of the plot
         *
         * @param plot The Qwt plot
         * @param graphicItem The graphic item of the svg on the plot. Called by reference in order to modify it.
         * @param fileName The filename to the svg image
         * @param doReplot A flag to do a replot and repaint. Default is false.
         */
        static void loadSVGRendered(QwtPlot *plot, QwtPlotGraphicItem **graphicItem,
                                    const QString &fileName, bool doReplot = false);

        /**
         * @brief Load an image as pixmap (it is not scaled) at the center of the plot
         *
         * @param plot The Qwt plot
         * @param fileName The filename to the image
         * @param doReplot A flag to do a replot and repaint. Default is false.
         */
        static void loadImagePixmap(QwtPlot *plot, const QString &fileName, bool doReplot = false);

        /**
         * @brief Plot a circle with specific radius at the center of the graph
         *
         * @param plot The Qwt plot
         * @param circleItem The shape item of the circle on the plot. Called by reference in order to modify it.
         * @param radius The radius of the circle
         * @param doReplot A flag to do a replot and repaint. Default is false.
         */
        static void plotCircle(QwtPlot *plot, QwtPlotShapeItem **circleItem, const float &radius, bool doReplot = false);

        /**
         * @brief Plot an arc with specific radius, start and span angles at the center of the graph
         *
         * @param plot The Qwt plot
         * @param arcItem The shape item of the arc on the plot. Called by reference in order to modify it.
         * @param radius The radius of the arc
         * @param startAngle The start angle of the arc
         * @param spanAngle The span angle of the arc
         * @param doReplot A flag to do a replot and repaint. Default is false.
         */
        static void plotArc(QwtPlot *plot, QwtPlotShapeItem **arcItem, const float &radius,
                            const int &startAngle, const int &spanAngle, bool doReplot = false);

    private:
        PlotCurvesWithAngle();
    };
}
