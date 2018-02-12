#ifndef DIALOG1_H
#define DIALOG1_H
#include <QDialog>

#include <QWidget>
#include <QSqlTableModel>
#include <mysqltablemodel.h>
#include <QTableView>
#include <QComboBox>
#include <QLineEdit>
#include <QTranslator>
#include <QLabel>
#include <QGroupBox>
#include <QPushButton>
#include <qgridlayout>
#include "commondata.h"

class Dialog1 : public QDialog
{
    Q_OBJECT

public:

    explicit Dialog1(QWidget *parent = 0,commonData *d=0);
    ~Dialog1();
     commonData *data;
bool status;
 QLineEdit *num_area;
  QLineEdit *area;

  QLabel *num_area_l;
   QLabel *area_l;

   QPushButton * add_new;
   QPushButton * edit_new;

void my_show();

private slots:
   void update();
    void update_edit();

signals:
   void add();
   void edit();
private:

};
#endif // DIALOG1_H
