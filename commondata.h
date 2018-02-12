#ifndef COMMONDATA_H
#define COMMONDATA_H

#include <QObject>
#include <QPainter>
#include "aes256.h"
#include "QRCodeGenerator.h"
#include <QImage>
#include <QSqlDatabase>
#include <QLabel>
#include <QGroupBox>
#include <QPushButton>
#include <QLineEdit>
#include <QComboBox>
#include <QSpinBox>
#include <QTextEdit>
#include <QCheckBox>

struct FORM
{
    QString form_type;
     QString loc_num;
    int int_loc_num;
    QString val_of_rec;
    QString qr_text;
};

class commonData : public QObject
{
    Q_OBJECT
public:
    explicit commonData(QObject *parent = 0);
    void updateQRImage(QString text, int scypher, int index,int invert);
      QString scypher(QString text);
    QString to_base64(unsigned char * in,int buffsize);
    void draw_number(QPainter &painter, int x, int y, int d, int val);
    void draw_label(QPainter &painter, int x, int y, int h, int w, int fontsize, QString lbl);
    void draw_form(QPainter &painter, int X0, int Y0, int W,int H,int int_loc_num, QString form_type, QString loc_num,QString val_of_rec);

    void draw_page(QPainter &painter,std::vector <FORM>& form_arr,int istart,int iend,int invert);

    void gen_forms_array();
    QComboBox* comboloc;

    QComboBox* comboform;
    double percent;
    int area_loc[1000];
    int forms_numbers[100];
    int num_que;
    int selected_row1;
    int selected_row2;
    int selected_row3;
    int selected_row4;

    QString que;
    int num_area;
    int answer;
    QString area;
    int locat;
    int users;
    QString disk;
    QString comm_answer;

    QString forms_names[100];
    std::vector<FORM> forms;
    QString text_for_qr;
    QString form;
    QString loc;
    QString val;
    QString global_val_name;
    QString global_loc_name;
    QString global_qr_label;
    int global_form_model;
    QString aes256_key;
    CQR_Encode qrEncode;
    QImage eI;
QComboBox *langCombo;
    QLineEdit *nameEdit;
     QLineEdit *keyEdit;
    QLineEdit *LocNumEdit;
     QLineEdit *ValOfRecEdit;
     QLineEdit *PercentEdit;
    QComboBox *FormTypeCombo;

    QLabel* num_form_label;
    QLabel* PercentLabel;
    QLabel* total_num_label;

    QString curr_pdf_path;
    QSpinBox *pagesspinbox;

    //////////////Database:
    void init_db();
    void open_db();
    QString db_name;
    QSqlDatabase db;
    ////////translatable

    QGroupBox *formParametersGroup;// = new QGroupBox(tr("Form Parameters"));

    QLabel *nameLabel;// = new QLabel(tr("Label:"));

    QLabel *keyLabel;// = new QLabel(tr("AES Key:"));

    QLabel *LocNumLabel;// = new QLabel(tr("Location Number:"));

    QLabel *ValOfRecLabel ;//= new QLabel(tr("Value Of record:"));

    QLabel *FormTypeLabel;// = new QLabel(tr("Form Type:"));
    QPushButton *genButton;// = new QPushButton(tr("Generate Forms"));
    QPushButton *printButton;// = new QPushButton(tr("Print Forms"));
    //
    QGroupBox *langGroup;//= new QGroupBox(tr("UI Language"));
    QLabel *langLabel; //new QLabel(tr("Set:"));

    //
    QGroupBox *tablesGroup;// = new QGroupBox(tr("Table Contents"));
    QLabel *tableLabel1;
    QLabel *tableLabel2;// = new QLabel(tr("Query:"));
    QLabel *tableLabel3;
    QLabel *tableLabel4;

    QPushButton *filterButton1;// = new QPushButton(tr("Filter"));
    QPushButton *addButton1;
    bool status;
    QPushButton *editButton1;// = new QPushButton(tr("Insert Empty Row"));
    QPushButton *remButton1;
    QPushButton *checkallButton1;// = new QPushButton(tr("Remove Row"));
    QPushButton *uncheckallButton1;
    //
    QPushButton *filterButton2;// = new QPushButton(tr("Filter"));
    QPushButton *addButton2;// = new QPushButton(tr("Insert Empty Row"));
    QPushButton *remButton2;// = new QPushButton(tr("Remove Row"));
    QPushButton *checkallButton2;// = new QPushButton(tr("Remove Row"));
    QPushButton *uncheckallButton2;
    //
    QPushButton *editButton3;
    QPushButton *filterButton3;// = new QPushButton(tr("Filter"));
    QPushButton *addButton3;// = new QPushButton(tr("Insert Empty Row"));
    QPushButton *remButton3;// = new QPushButton(tr("Remove Row"));
    QPushButton *checkallButton3;// = new QPushButton(tr("Remove Row"));
    QPushButton *uncheckallButton3;
    //
    QPushButton *editButton4;
    QPushButton *filterButton4;// = new QPushButton(tr("Filter"));
    QPushButton *addButton4;// = new QPushButton(tr("Insert Empty Row"));
    QPushButton *remButton4;// = new QPushButton(tr("Remove Row"));
    QPushButton *checkallButton4;// = new QPushButton(tr("Remove Row"));
    QPushButton *uncheckallButton4;
    //
    QGroupBox *printGroup;// = new QGroupBox(tr("Preview:"));
    QPushButton *openButton;// = new QPushButton(tr("Open"));

    QPushButton *nextButton;// = new QPushButton(tr("Next"));
    QTextEdit* qrtext;

    QCheckBox * check_form_type;
    QCheckBox * check_empty;

signals:

public slots:
};

#endif // COMMONDATA_H
