#ifndef MYSQLTABLEMODEL_H
#define MYSQLTABLEMODEL_H

#include <QObject>
#include <QWidget>
#include <QSqlTableModel>
class mySqlTableModel : public QSqlTableModel
{
    Q_OBJECT

public:
    explicit mySqlTableModel(QObject *parent = Q_NULLPTR, QSqlDatabase db = QSqlDatabase());
    bool setHeaderData(int index, Qt::Orientation orient, const QVariant& val, int role);
    QVariant headerData(int index, Qt::Orientation o, int role = Qt::DisplayRole) const;
   // QVariant headerData(int index, Qt::Orientation o, int role) const

    bool header_checked[4096];

public slots:
    void handle_section_clicked(int indx);
    void uncheck_headers();
    void check_headers();
    void remove_selected();


};

#endif // MYSQLTABLEMODEL_H
