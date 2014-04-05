#include <QApplication>

#include "treeview/treeview.h"
#include "treeview/treeviewitem.h"

using namespace HeaderIncludeGraph::Internal;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    TreeView *view = new TreeView;

    TreeViewItem *item1 = new TreeViewItem;
    TreeViewItem *item2 = new TreeViewItem;
    TreeViewItem *item3 = new TreeViewItem;
    TreeViewItem *item4 = new TreeViewItem;
    TreeViewItem *item5 = new TreeViewItem;
    TreeViewItem *item6 = new TreeViewItem;
    TreeViewItem *item7 = new TreeViewItem;
    TreeViewItem *item8 = new TreeViewItem;

    item1->setDisplayText("fdsfsdfsdfsdfs");
    item1->setToolTip("rade car");

    item2->setDisplayText("wqeqeq");
    item2->setToolTip(item2->displayText());

    item3->setDisplayText("tererter");
    item3->setToolTip(item3->displayText());

    item4->setDisplayText("uyutut");
    item4->setToolTip(item4->displayText());

    item5->setDisplayText("uiiyuouioui");
    item5->setToolTip(item5->displayText());

    item6->setDisplayText("sdasdasd");
    item6->setToolTip(item6->displayText());

    item7->setDisplayText("cxvxvcx");
    item7->setToolTip(item7->displayText());

    item8->setDisplayText("jhjghjgjg");
    item8->setToolTip(item8->displayText());

    item4->addChildItem(item6);
    item4->addChildItem(item7);
    item4->addChildItem(item8);

    item2->addChildItem(item4);
    item2->addChildItem(item5);

    item1->addChildItem(item2);
    item1->addChildItem(item3);

    view->setRootItem(item1);
    view->showView(true);

    return a.exec();
}
