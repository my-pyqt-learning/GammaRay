/*
  remoteviewwidget.h

  This file is part of GammaRay, the Qt application inspection and
  manipulation tool.

  Copyright (C) 2015 Klarälvdalens Datakonsult AB, a KDAB Group company, info@kdab.com
  Author: Anton Kreuzkamp <anton.kreuzkamp@kdab.com>
  Author: Volker Krause <volker.krause@kdab.com>

  Licensees holding valid commercial KDAB GammaRay licenses may use this file in
  accordance with GammaRay Commercial License Agreement provided with the Software.

  Contact info@kdab.com if any conditions of this licensing are not clear to you.

  This program is free software; you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 2 of the License, or
  (at your option) any later version.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef GAMMARAY_REMOTEVIEWWIDGET_H
#define GAMMARAY_REMOTEVIEWWIDGET_H

#include "gammaray_ui_export.h"

#include <QWidget>

namespace GammaRay {

/** Widget showing remote screen content and providing both visual inspection
 *  capabilities as well as input redirection.
 *
 *  Can be sub-classed to support e.g. custom element decoration.
 */
class GAMMARAY_UI_EXPORT RemoteViewWidget : public QWidget
{
    Q_OBJECT
public:
    explicit RemoteViewWidget(QWidget *parent = Q_NULLPTR);

    enum InteractionMode {
        ViewInteraction, ///< panning, zooming, etc
        Measuring,
        InputRedirection,
        ElementPicking,
        NoInteraction ///< use this for disabling all built-in interaction if you are adding custom interaction modes
    };
    void setInteractionMode(InteractionMode mode);

public slots:
    void setImage(const QImage &image);
    void setZoom(double zoom);
    void zoomIn();
    void zoomOut();
    void fitToView();

protected:
    void paintEvent(QPaintEvent *event) Q_DECL_OVERRIDE;
    void resizeEvent(QResizeEvent *event) Q_DECL_OVERRIDE;
    void mousePressEvent(QMouseEvent *event) Q_DECL_OVERRIDE;
    void mouseReleaseEvent(QMouseEvent *event) Q_DECL_OVERRIDE;
    void mouseMoveEvent(QMouseEvent *event) Q_DECL_OVERRIDE;
    void wheelEvent(QWheelEvent *event) Q_DECL_OVERRIDE;
    void keyPressEvent(QKeyEvent *event) Q_DECL_OVERRIDE;
    void keyReleaseEvent(QKeyEvent *event) Q_DECL_OVERRIDE;

private:
    void drawRuler(QPainter *p);
    void drawMeasureOverlay(QPainter *p);
    // translate from view coordinates to source coordinates
    QPoint mapToSource(QPoint pos);

    // size of the content area, ie. excluding the rulers
    int contentWidth() const;
    int contentHeight() const;

    // size of the rulers
    int horizontalRulerHeight() const;
    int verticalRulerWidth() const;

private:
    QImage m_sourceImage;
    QBrush m_backgroundBrush;
    QVector<double> m_zoomLevels;
    double m_zoom;
    int m_x; // view translation before zoom
    int m_y;
    InteractionMode m_interactionMode;
    QPoint m_mouseDownPosition; // semantics depend on interaction mode
    QPoint m_currentMousePosition; // in view coordinates
    bool m_mouseDown;
};

}

#endif // GAMMARAY_REMOTEVIEWWIDGET_H