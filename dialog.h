#ifndef DIALOG_H
#define DIALOG_H

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


class Dialog : public QDialog
{
    Q_OBJECT

public:

    explicit Dialog(QWidget *parent = 0,commonData *d=0);
    ~Dialog();
     commonData *data;
bool status;
 QLineEdit *num_que;
  QLineEdit *que;
  QLineEdit *answer;
   QLineEdit *comm_answer;
  QLabel *num_que_l;
   QLabel *que_l;
   QLabel *answer_l;
   QLabel *comm_answer_l;
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

#endif // DIALOG_H
