#ifndef HEADERINCLUDEGRAPH_ARROWITEM_H
#define HEADERINCLUDEGRAPH_ARROWITEM_H

#include <QGraphicsItem>
#include <QPen>

namespace HeaderIncludeGraph {
namespace Internal {

class ArrowItem : public QGraphicsItem
{
public:
    ArrowItem(const QPointF &start, const QPointF &end);

    // QGraphicsItem interface
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

    void setStart(const QPointF &pointInSceneCoords);
    void setEnd(const QPointF &pointInSceneCoords);

private:
    void updateEndArrows();

    QPointF m_start;
    QPointF m_end;
    QRectF m_boundingRect;
    QLineF m_firstArrowEnd;
    QLineF m_secondArrowEnd;
    QPen m_pen;
};

} // namespace Internal
} // namespace HeaderIncludeGraph

#endif // HEADERINCLUDEGRAPH_ARROWITEM_H
