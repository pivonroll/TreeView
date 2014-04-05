#include "treeviewlayout.h"

#include <QGraphicsScene>

#include "treeviewitem.h"
#include "treeitemconnector.h"

namespace HeaderIncludeGraph {
namespace Internal {

TreeViewLayout::TreeViewLayout(TreeViewItem *parentItem)
    : m_parentItem(parentItem)
{
    H_SPACE_BETWEEN_SUBTREES = 60;
    W_SPACE_BETWEEN_SIBLINGS = 10;
}

void TreeViewLayout::updateLayout()
{
    if (m_parentItem && m_parentItem->scene())
        relocateChildren();

    foreach (TreeItemConnector *connector, m_treeItemConnections) {
        if (connector)
            connector->update();
    }
}

void TreeViewLayout::addItemConnection(TreeViewItem *child)
{
    if (connectorExists(child))
        return;

    TreeItemConnector *connector = new TreeItemConnector(m_parentItem, child);
    m_treeItemConnections.append(connector);
}

void TreeViewLayout::relocateChildren()
{
    QMap<TreeViewItem *, QRectF> childItemsBoundingRects = collectChildrenBoundingRects();
    QMapIterator<TreeViewItem *, QRectF> it(childItemsBoundingRects);

    while (it.hasNext()) {
        it.next();

        if (it.key()) {
            positionChild(it.key(), childItemsBoundingRects);

            if (it.key()->layout())
                it.key()->layout()->updateLayout();
        }
    }
}

QRectF TreeViewLayout::boundingRectOfSubTrees(const QList<QRectF> &subTreeBoundingRects)
{
    QListIterator<QRectF> listIt(subTreeBoundingRects);
    QRectF boundRct;

    bool isFirst = true;

    while (listIt.hasNext()) {
        QRectF rect = listIt.next();

        if (boundRct.height() < rect.height())
            boundRct.setHeight(rect.height());

        if (isFirst)
            boundRct = rect;
        else
            boundRct.setWidth(boundRct.width() + rect.width() + W_SPACE_BETWEEN_SIBLINGS);

        isFirst = false;
    }

    return boundRct;
}

QRectF TreeViewLayout::subTreeBoundingRect() const
{
    QRectF childItemsBoundingRect;
    QList<QGraphicsItem *> children = m_parentItem->childItems();
    QRectF boundRect = m_parentItem->boundingRect();

    bool isFirst = true;
    foreach (QGraphicsItem *item, children) {
        TreeViewItem *treeViewItemChild = dynamic_cast<TreeViewItem *>(item);

        if (!treeViewItemChild)
            continue;

        QRectF subTreeRect = treeViewItemChild->layout()->subTreeBoundingRect();

        if (isFirst) {
            isFirst = false;
            childItemsBoundingRect = subTreeRect;
            childItemsBoundingRect.setHeight(boundRect.height() + childItemsBoundingRect.height() + H_SPACE_BETWEEN_SUBTREES);
        }
        else
            childItemsBoundingRect.setWidth(childItemsBoundingRect.width() + subTreeRect.width() + W_SPACE_BETWEEN_SIBLINGS);
    }

    return childItemsBoundingRect.united(boundRect);

}

QMap<TreeViewItem *, QRectF> TreeViewLayout::collectChildrenBoundingRects() const
{
    QList<QGraphicsItem *> children = m_parentItem->childItems();
    QMap<TreeViewItem *, QRectF> childItemsBoundingRects;

    foreach (QGraphicsItem *item, children) {
        TreeViewItem *treeViewItemChild = dynamic_cast<TreeViewItem *>(item);

        if (treeViewItemChild && treeViewItemChild->layout())
            childItemsBoundingRects[treeViewItemChild] = treeViewItemChild->layout()->subTreeBoundingRect();
    }

    return childItemsBoundingRects;
}

void TreeViewLayout::positionChild(TreeViewItem *child, const QMap<TreeViewItem *, QRectF> &childBoundingRects)
{
    QRectF boundRect = boundingRectOfSubTrees(childBoundingRects.values());
    qreal fromRight = 0;

    QMapIterator<TreeViewItem *, QRectF> it(childBoundingRects);

    while (it.hasNext()) {
        it.next();

        if (it.key() == child)
            break;

        QRectF rect = it.value();
        fromRight += rect.width() + W_SPACE_BETWEEN_SIBLINGS;
    }

    QRectF childBoundRect = childBoundingRects[child];
    fromRight += (childBoundRect.width() - child->boundingRect().width())/2;

    qreal moveX = fromRight - boundRect.center().x();
    qreal destX = m_parentItem->boundingRect().center().x() + moveX;
    qreal destY = m_parentItem->boundingRect().bottom() + H_SPACE_BETWEEN_SUBTREES;

    QPointF translation = m_parentItem->mapToScene(QPointF(destX, destY)) - child->sceneBoundingRect().topLeft();
    child->setTransform(QTransform().translate(translation.x(), translation.y()), true);
}

bool TreeViewLayout::connectorExists(TreeViewItem *child) const
{
    foreach (TreeItemConnector *connector, m_treeItemConnections) {
        if (connector && connector->startItem() == m_parentItem && connector->endItem() == child) {
            return true;
        }
    }
    return false;
}

} // namespace Internal
} // namespace HeaderIncludeGraph
