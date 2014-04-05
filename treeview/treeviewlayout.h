#ifndef HEADERINCLUDEGRAPH_INTERNAL_TREEVIEWLAYOUT_H
#define HEADERINCLUDEGRAPH_INTERNAL_TREEVIEWLAYOUT_H

#include <QtGlobal>
#include <QMap>

QT_BEGIN_NAMESPACE
class QRectF;
class QGraphicsScene;
QT_END_NAMESPACE

namespace HeaderIncludeGraph {
namespace Internal {

class TreeViewItem;
class TreeItemConnector;

class TreeViewLayout
{
public:
    TreeViewLayout(TreeViewItem *parentItem);

    void updateLayout();
    void addItemConnection(TreeViewItem *child);

private:    
    void relocateChildren();
    QRectF boundingRectOfSubTrees(const QList<QRectF> &subTreeBoundingRects);
    QRectF subTreeBoundingRect() const;
    QMap<TreeViewItem *, QRectF> collectChildrenBoundingRects() const;
    void positionChild(TreeViewItem *child, const QMap<TreeViewItem *, QRectF> &childBoundingRects);

    bool connectorExists(TreeViewItem *child) const;

    QList<TreeItemConnector *> m_treeItemConnections;
    int H_SPACE_BETWEEN_SUBTREES;
    int W_SPACE_BETWEEN_SIBLINGS;
    TreeViewItem *m_parentItem;
};

} // namespace Internal
} // namespace HeaderIncludeGraph

#endif // HEADERINCLUDEGRAPH_INTERNAL_TREEVIEWLAYOUT_H
