#ifndef ZCELLDELEGATE_H
#define ZCELLDELEGATE_H

#include <QStyledItemDelegate>
#include <QHash>
#include <QPoint>
#include <Sheet/zcell.h>
class ZCellDelegate : public QStyledItemDelegate
{
    Q_OBJECT
public:
    explicit ZCellDelegate(QObject *parent = 0);
    ~ZCellDelegate();

    //delegate for cell frame.
    void ZAddCellBorder(ZCell *tCell);
    void ZDelCellBorder(ZCell *tCell);

    //delegate for bind var.
    void ZAddBindGeVar(ZCell *cell);
    void ZDelBindGeVar(ZCell *cell);
    void ZAddBindAutoVarLoadEvent(ZCell *cell);
    void ZDelBindAutoVarLoadEvent(ZCell *cell);
    void ZAddBindAutoVarClickEvent(ZCell *cell);
    void ZDelBindAutoVarClickEvent(ZCell *cell);

signals:

public slots:

protected:
    void paint(QPainter *painter, const QStyleOptionViewItem & option, const QModelIndex & index) const;

private:
    //all cells contain in this list need to draw the border.
    QHash<QString,ZCell*> m_borderHash;

    //all cells bind vars in this list need to draw the indicator.
    QHash<QString,ZCell*> m_bindGeVarHash;
    QHash<QString,ZCell*> m_bindAutoVarLoadEventHash;
    QHash<QString,ZCell*> m_bindAutoVarClickEventHash;
};

#endif // ZCELLDELEGATE_H
