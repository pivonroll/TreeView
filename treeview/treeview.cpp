#include "treeview.h"

#include <QGraphicsScene>
#include <QGraphicsView>
#include <QVBoxLayout>

#include "treeviewitem.h"
#include "treeviewwindow.h"
#include "treeviewlayout.h"

namespace HeaderIncludeGraph {
namespace Internal {

TreeView::TreeView(QWidget *parent)
    : m_scene(new QGraphicsScene),
      m_root(0)
{
    m_window = new TreeViewWindow(parent);
    m_window->setContentsMargins(0, 0, 0, 0);
    m_window->hide();

    m_view = new QGraphicsView(parent);
    m_window->layout()->addWidget(m_view);
    m_view->setScene(m_scene);

    connect(m_view, SIGNAL(destroyed()), this, SLOT(deleteLater()));
}

void TreeView::setRootItem(TreeViewItem *root)
{
    if (m_root)
        m_scene->removeItem(m_root);
    m_root = root;
    m_scene->addItem(m_root);

    m_root->layout()->updateLayout();

    QRect boundRect = m_scene->itemsBoundingRect().toRect();

    QMargins margins = m_window->layout()->contentsMargins();
    m_window->resize(boundRect.width() + margins.left() + margins.right() + 20,
                   boundRect.height() + margins.top() + margins.bottom() + 20);

}

void TreeView::showView(bool show)
{
    if (show)
        m_window->show();
    else
        m_window->hide();
}

} // namespace Internal
} // namespace HeaderIncludeGraph
