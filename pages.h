

#ifndef PAGES_H
#define PAGES_H

#include <QWidget>
#include <QSqlTableModel>
#include <mysqltablemodel.h>
#include <QTableView>
#include <QComboBox>
#include <QLineEdit>
#include <QTranslator>
#include <QGroupBox>
#include "QRCodeGenerator.h"
#include "commondata.h"
#include "mypixmaplabel.h"
#include "dialog.h"
#include "dialog1.h"
#include "dialog2.h"
class GenerateFormsPage : public QWidget
{
    Q_OBJECT
public:
    commonData *data;
    GenerateFormsPage(QWidget *parent = 0,commonData *d=0);
    //void  render_page(int page);
    myPixmapLabel* viewer;
    myPixmapLabel* viewer_sing;
    QSlider *slider;
    QLabel* pageLoc;
    QLabel* state;
    int curr_page;


public slots:
    void render_page(int page);
    void update_view_sing();
    void next();
    void prev();
    void first();
    void last();
    void change_percent(QString a);
    void gen_forms();
    void print_forms();

public slots:
    update_key(QString key);
    // void push_open();
};

class SetLanguagePage : public QWidget
{
    Q_OBJECT
public:
    QTranslator qtLanguageTranslator;
    commonData *data;
    std::vector <QString> langs;

    SetLanguagePage(QWidget *parent = 0,commonData *d=0);
public slots:
    void translate(int index);
};

class EditTablesPage : public QWidget
{
    Q_OBJECT
public:
    commonData *data;
    bool sortnumber1;
    bool sortnumber2;
    bool sortnumber3;
    bool sortnumber4;
    Dialog *ui;
    Dialog1 *ui1;
    Dialog2 *ui2;

    EditTablesPage(QWidget *parent = 0,commonData *d=0);
public slots:
    void selecting1(QModelIndex a);
        void selecting2(QModelIndex a);
            void selecting3(QModelIndex a);
                void selecting4(QModelIndex a);
    void check_headers1();
    void uncheck_headers1();
    void remove_selected1();
    void handle_section_clicked(int i);
    void handle_section_clicked3(int i);
    void remove_selected3();
     void remove_selected4();
    void open_win1();
    void open_win11();
    void open_win3();
    void open_win33();
    void filt_all();
    void open_win4();
    void open_win44();
    void filter1();
    void add_row1();
    void update_row1();

    void filter2();
    void add_row2();

    void filter3();
    void add_row3();
    void update_row3();

    void filter4();
    void add_row4();
    void update_row4();

    void remove_row1();
    void remove_row2();
    void remove_row3();
    void remove_row4();

    void change_table1(const QString name);
    void change_table2(const QString name);
    void change_table3(const QString name);
    void change_table4(const QString name);
    void sorting1(int ind);
    void sorting2(int ind);
    void sorting3(int ind);
    void sorting4(int ind);
    void update_data ( const QModelIndex &, const QModelIndex &);

private:
    mySqlTableModel *my_database_model1;
    mySqlTableModel *my_database_model2;
    mySqlTableModel *my_database_model3;
    mySqlTableModel *my_database_model4;


    QTableView  * tableView1;
    QTableView  * tableView2;

    QTableView  * tableView3;
    QTableView  * tableView4;
    QComboBox *filterCombo1;
    QComboBox *filterCombo2;
    QComboBox *filterCombo3;
    QComboBox *filterCombo4;
    QLineEdit *filterEdit1;
    QLineEdit *filterEdit2;
    QLineEdit *filterEdit3;
    QLineEdit *filterEdit4;

};

#include "mypixmaplabel.h"
class PrintAndPreviewPage : public QWidget
{
    Q_OBJECT
public:
    commonData *data;
    PrintAndPreviewPage(QWidget *parent = 0,commonData *d=0);
    // myPixmapLabel* viewer;
    //void  render_page(int page);
public slots:
    //  void push_open();
    // void push_next();
    // void goto_page(int page);
};

#endif
