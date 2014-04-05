#include "treeitemconnector.h"

#include "arrowitem.h"
#include "treeviewitem.h"

namespace HeaderIncludeGraph {
namespace Internal {

TreeItemConnector::TreeItemConnector(TreeViewItem *startItem, TreeViewItem *endItem)
    : m_startItem(startItem),
      m_endItem(endItem),
      m_arrowItem(0)
{
    createArrowItem();
}

TreeItemConnector::~TreeItemConnector()
{
    m_arrowItem->setParentItem(0);
    delete m_arrowItem;
}

TreeViewItem *TreeItemConnector::startItem() const
{
    return m_startItem;
}

TreeViewItem *TreeItemConnector::endItem() const
{
    return m_endItem;
}

void TreeItemConnector::update()
{
    m_arrowItem->setStart(calculateStartPoint());
    m_arrowItem->setEnd(calculateEndPoint());
    m_arrowItem->update();
}

void TreeItemConnector::createArrowItem()
{
    if (!m_startItem || !m_endItem)
        return;

    m_arrowItem = new ArrowItem(calculateStartPoint(), calculateEndPoint());
    m_arrowItem->setParentItem(m_startItem);
}

QPointF TreeItemConnector::calculateStartPoint()
{
    const QRectF startRect = m_startItem->sceneBoundingRect();
    const QRectF endRect = m_endItem->sceneBoundingRect();

    if (startRect.top() > endRect.bottom())
        return QPointF(startRect.center().x(), startRect.top());
    else if (startRect.bottom() < endRect.top())
        return QPointF(startRect.center().x(), startRect.bottom());
    else if (startRect.left() > endRect.right())
        return QPointF(startRect.left(), startRect.center().y());
    else
        return QPointF(startRect.right(), startRect.center().y());
}

QPointF TreeItemConnector::calculateEndPoint()
{
    const QRectF startRect = m_startItem->sceneBoundingRect();
    const QRectF endRect = m_endItem->sceneBoundingRect();

    if (startRect.top() > endRect.bottom())
        return QPointF(endRect.center().x(), endRect.bottom());
    else if (startRect.bottom() < endRect.top())
        return QPointF(endRect.center().x(), endRect.top());
    else if (startRect.left() > endRect.right())
        return QPointF(endRect.right(), endRect.center().y());
    else
        return QPointF(endRect.left(), endRect.center().y());
}

} // namespace Internal
} // namespace HeaderIncludeGraph
