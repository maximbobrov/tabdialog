

#include <QtGui>

#include "pages.h"
#include <QListWidget>
#include <QStackedWidget>
#include <QPushButton>
#include <QLayout>
#include <QGroupBox>
#include <QLabel>
#include <QComboBox>
#include <QCheckBox>
#include <QLineEdit>
#include <QSpinBox>
#include <QDateTimeEdit>
#include <QSqlTableModel>
#include <QTableView>
#include <QHeaderView>
#include <QSqlQuery>
#include <QGraphicsEffect>
GenerateFormsPage::GenerateFormsPage(QWidget *parent, commonData *d)
    : QWidget(parent)
{

    data=d;

    //  QFont font;
    //  font.setBold(true);

    data->formParametersGroup = new QGroupBox(tr(""));
    //data->formParametersGroup->setFont(font);
    //   font.setBold(false);

    data->nameLabel = new QLabel(tr("Label:"));
    data->nameEdit = new QLineEdit("label");

    data->keyLabel = new QLabel(tr("AES Key:"));
    data->keyEdit = new QLineEdit(("12345678901234567890123456789012"));

    data->LocNumLabel = new QLabel(tr("Location Number:"));
    data->LocNumEdit = new QLineEdit(("LOCATION NUMBER"));

    data->ValOfRecLabel = new QLabel(tr("Value Of record:"));
    data->ValOfRecEdit = new QLineEdit(("VALUE OF RECORD"));
    data->PercentLabel = new QLabel(tr("Percent of empty:"));
    data->PercentEdit = new QLineEdit(("10"));

    data->FormTypeLabel = new QLabel(tr("Form Type:"));

    data->FormTypeCombo = new QComboBox;

    data->FormTypeCombo->addItem(("1"));
    data->FormTypeCombo->addItem(("2"));


    QGridLayout *packagesLayout = new QGridLayout;

    packagesLayout->setContentsMargins( data->marg, data->marg, data->marg, data->marg );
    // packagesLayout->set;
    packagesLayout->addWidget(data->nameLabel, 0, 0,1,1);
    packagesLayout->addWidget(data->nameEdit, 0, 1,1,1);
    packagesLayout->addWidget(data->keyLabel, 1, 0,1,1);
    packagesLayout->addWidget(data->keyEdit, 1, 1,1,1);

    data->keyEdit->setMinimumWidth(200);
    packagesLayout->addWidget(data->LocNumLabel, 2, 0,1,1);
    packagesLayout->addWidget(data->LocNumEdit, 2, 1,1,1);

    packagesLayout->addWidget(data->ValOfRecLabel, 3, 0,1,1);
    packagesLayout->addWidget(data->ValOfRecEdit, 3, 1,1,1);

    packagesLayout->addWidget(data->FormTypeLabel, 4, 0,1,1);
    packagesLayout->addWidget(data->FormTypeCombo, 4, 1,1,1);
    packagesLayout->addWidget(data->PercentLabel, 5, 0,1,1);
    packagesLayout->addWidget(data->PercentEdit, 5, 1,1,1);


    packagesLayout->setColumnStretch(0, 1);
    packagesLayout->setColumnStretch(1, 20);


    data->num_form_label=new QLabel("111");
    data->total_num_label=new QLabel("111");



    packagesLayout->addWidget(data->num_form_label,6,0,1,2);
    packagesLayout->addWidget(data->total_num_label,7,0,1,2);

    data->num_form_label->setMaximumHeight(20);
    data->total_num_label->setMaximumHeight(20);

    //packagesLayout->addStretch(20);
    data->genButton = new myCoolButton(tr("Generate Forms"));

    QWidget *vpcWidget = new QWidget();
    //myCoolButton *pBtn = new myCoolButton();
   // data->genButton->setParent(vpcWidget);
    QGraphicsDropShadowEffect* effect = new QGraphicsDropShadowEffect();
    effect->setBlurRadius(8); //Adjust accordingly
    effect->setOffset(1,2); //Adjust accordingly

    data->genButton->setGraphicsEffect(effect);
   // vpcWidget->show();



    data->printButton = new myCoolButton(tr("Print Forms"));
    state= new QLabel(" Progress: % ");




    //packagesLayout->addWidget(data->genButton,8,0,1,2);
    packagesLayout->addWidget(state,8,0,1,2);

   // packagesLayout->addWidget(data->printButton,10,0,1,2);

    packagesLayout->setRowStretch(9, 1);




    data->formParametersGroup->setLayout(packagesLayout);


    QGroupBox *previewParametersGroup = new QGroupBox(tr("Preview"));

    QHBoxLayout *previewLayout = new QHBoxLayout;
previewLayout->setContentsMargins( data->marg, data->marg, data->marg, data->marg );

    QTabWidget *tabWidget = new QTabWidget(this);


    QWidget* tab1=new QWidget(this);
    QWidget* tab2=new QWidget(this);

    tabWidget->addTab(tab1, tr("Single Form"));
    tabWidget->addTab(tab2, tr("Pages"));

    ///////////////////
    QGridLayout *prevTab1layout = new QGridLayout;
    prevTab1layout->setContentsMargins( data->marg, data->marg, data->marg, data->marg );
    //myCoolButton *updateButton = new myCoolButton(tr("Update"));
    QLabel* labelLoc=new QLabel("Location number:");
    QLabel* labelForm=new QLabel("Form Type:");
    data->comboloc = new QComboBox;
    //comboloc->addItem(("1"));
    //comboloc->addItem(("2"));

 data->qrtext=new QTextEdit(QString("<b>Qr text output:</b>1234jsdfd   <br> <b>qr2 output</b> dsfkjsdkj"));
    viewer_sing=new myPixmapLabel();
 data->check_empty =new QCheckBox(tr("empty"));
    //connect(updateButton, SIGNAL(clicked()), this, SLOT(update_view_sing()));

    data->comboform = new QComboBox;
    // comboform->addItem(("1"));
    // comboform->addItem(("2"));
    connect(data->comboloc, SIGNAL(currentIndexChanged(QString)), this, SLOT(update_view_sing()));
    connect(data->comboform, SIGNAL(currentIndexChanged(QString)), this, SLOT(update_view_sing()));
     connect(data->LocNumEdit, SIGNAL(textChanged(QString)), this, SLOT(update_view_sing()));
     connect(data->ValOfRecEdit, SIGNAL(textChanged(QString)), this, SLOT(update_view_sing()));
     connect(data->PercentEdit, SIGNAL(textChanged(QString)), this, SLOT(change_percent(QString)));

     connect(data->FormTypeCombo, SIGNAL(currentIndexChanged(QString)), this, SLOT(update_view_sing()));

 connect(data->keyEdit,SIGNAL(textChanged(QString)),this,SLOT(update_key(QString)));

      connect(data->check_empty, SIGNAL(stateChanged(int)), this, SLOT(update_view_sing()));

      prevTab1layout->addWidget(labelForm,0,0,1,1,Qt::AlignRight);

      prevTab1layout->addWidget(data->comboform,0,1);
      prevTab1layout->addWidget(labelLoc,0,2,1,1,Qt::AlignRight);
      prevTab1layout->addWidget(data->comboloc,0,3);
      prevTab1layout->addWidget(data->comboloc,0,3);
      prevTab1layout->addWidget(data->check_empty,0,4);
     // prevTab1layout->addWidget(data->check_form_type,0,5);

      prevTab1layout->addWidget(data->qrtext,1,0,1,6);
      data->qrtext->setMaximumHeight(50);
      prevTab1layout->addWidget(viewer_sing,2,0,10,6);
   // prevTab1layout->addWidget(updateButton,0,5);
    prevTab1layout->setColumnStretch(0, 1);
    prevTab1layout->setColumnStretch(1, 1);
    prevTab1layout->setColumnStretch(2, 1);
    prevTab1layout->setColumnStretch(3, 1);
    prevTab1layout->setColumnStretch(4, 1);
    prevTab1layout->setColumnStretch(5, 1);

    prevTab1layout->setRowStretch(2, 10);
    tab1->setLayout(prevTab1layout);
    //////////////////////////////
    QGridLayout *prevTab2layout = new QGridLayout;
    prevTab2layout->setContentsMargins( data->marg, data->marg, data->marg, data->marg );
    myCoolButton *update2Button = new myCoolButton(tr("Update"));

    myCoolButton *prevButton = new myCoolButton(tr("<<"));
    myCoolButton *nextButton = new myCoolButton(tr(">>"));
    myCoolButton *first = new myCoolButton(tr("|<"));
    myCoolButton *last = new myCoolButton(tr(">|"));
    data->pagesspinbox = new QSpinBox;
    data->pagesspinbox->setPrefix(("page "));
    data->pagesspinbox->setSuffix((" of "));
    // hitsSpinBox->setSpecialValueText(tr("Return only the first result"));
    data->pagesspinbox->setMinimum(1);
    data->pagesspinbox->setMaximum(100);
    data->pagesspinbox->setSingleStep(1);
    connect(nextButton, SIGNAL(clicked(bool)), this, SLOT(next()));
    connect(prevButton, SIGNAL(clicked(bool)), this, SLOT(prev()));
    connect(first, SIGNAL(clicked(bool)), this, SLOT(first()));
    connect(last, SIGNAL(clicked(bool)), this, SLOT(last()));

    connect(data->pagesspinbox, SIGNAL(valueChanged(int)), this, SLOT(render_page(int)));



    slider = new QSlider(Qt::Horizontal,this);
    viewer = new myPixmapLabel(this);
    slider->setMaximum(40);
    slider->setTickInterval(5);
    connect(slider, SIGNAL(valueChanged(int)), this, SLOT(render_page(int)));

    pageLoc=new QLabel("Current Page : 1/15");

    pageLoc->setMinimumHeight(5);



    // prevTab2layout->addWidget(update2Button,0,1,1,1);
    prevTab2layout->addWidget(first,1,0);
    prevTab2layout->addWidget(prevButton,1,1);
     prevTab2layout->addWidget(nextButton,1,2);
     prevTab2layout->addWidget(last,1,3);
    prevTab2layout->addWidget(data->pagesspinbox,1,5,1,1);
    prevTab2layout->addWidget(slider,1,4,1,1);
    prevTab2layout->addWidget(viewer, 0, 0, 1,6);


    // prevTab2layout->addWidget(pageLoc,3,1,Qt::AlignCenter);
    // prevTab2layout->addWidget(updateButton,0,5);


    prevTab2layout->setRowStretch(0, 10);
    tab2->setLayout(prevTab2layout);
    //////////////////////////



    previewLayout->addWidget(tabWidget);
    previewParametersGroup->setLayout(previewLayout);


    QGridLayout *mainLayout = new QGridLayout;
    mainLayout->setContentsMargins( data->marg, data->marg, data->marg, data->marg );
    mainLayout->addWidget(data->formParametersGroup,0,0);
    mainLayout->addWidget(previewParametersGroup,0,1);

    mainLayout->setColumnStretch(0, 1);
    mainLayout->setColumnStretch(1, 3);
    //  mainLayout->addStretch(1);
    setLayout(mainLayout);
    update_view_sing();

}

SetLanguagePage::SetLanguagePage(QWidget *parent,commonData *d)
    : QWidget(parent)
{


    data=d;
    langs.push_back(QString("QtLanguage_en_EN"));
    langs.push_back(QString("QtLanguage_ru_RU"));
    data->langGroup = new QGroupBox(tr("UI Language"));

    data->langLabel = new QLabel(tr("Set:"));
    QComboBox *langCombo = new QComboBox;
    langCombo->addItem(("English"));
    langCombo->addItem(("Russian"));

    connect(data->langCombo, SIGNAL( currentIndexChanged(int)), this, SLOT(translate(int)));




    QHBoxLayout *langLayout = new QHBoxLayout;
    langLayout->addWidget(data->langLabel);
    langLayout->addWidget(langCombo);
    langLayout->addStretch(1);
    QVBoxLayout *configLayout = new QVBoxLayout;
    configLayout->addLayout(langLayout);
    data->langGroup->setLayout(configLayout);

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addWidget(data->langGroup);
    mainLayout->addStretch(1);
    setLayout(mainLayout);
}

void SetLanguagePage::translate(int index)
{

    qDebug()<<"AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA"<<endl;
    qDebug()<<langs[index]<<endl;
    qtLanguageTranslator.load(langs[index]);//QString("QtLanguage_") + QString("ru_RU"));
    // qtLanguageTranslator.load("QtLanguage_" + str, ".");   // Загружаем перевод
    qApp->installTranslator(&qtLanguageTranslator);


    //data->formParametersGroup->setTitle(tr("Form Parameters"));

    data->nameLabel->setText(tr("Label:"));

    data->keyLabel->setText(tr("AES Key:"));

    data->LocNumLabel->setText(tr("Location Number:"));

    data->ValOfRecLabel->setText(tr("Value Of record:"));

    data->FormTypeLabel->setText(tr("Form Type:"));
    data->genButton->setText(tr("Generate Forms"));
    data->printButton->setText(tr("Print Forms"));

    data->langGroup->setTitle(tr("UI Language"));
    data->langLabel->setText(tr("Set:"));


    //data->tablesGroup->setTitle(tr("Table Contents"));
    data->tableLabel1->setText(tr("Query:"));
    data->filterButton1->setText(tr("Filter"));
    data->addButton1->setText(tr("Insert Empty Row"));
    data->remButton1->setText(tr("Remove Row"));

    data->tableLabel2->setText(tr("Query:"));
    data->filterButton2->setText(tr("Filter"));
    data->addButton2->setText(tr("Insert Empty Row"));
    data->remButton2->setText(tr("Remove Row"));

    data->tableLabel3->setText(tr("Query:"));
    data->filterButton3->setText(tr("Filter"));
    data->addButton3->setText(tr("Insert Empty Row"));
    data->remButton3->setText(tr("Remove Row"));

    data->tableLabel4->setText(tr("Query:"));
    data->filterButton4->setText(tr("Filter"));
    data->addButton4->setText(tr("Insert Empty Row"));
    data->remButton4->setText(tr("Remove Row"));

    //data->printGroup->setTitle(tr("Preview:"));
    /* data->openButton->setText(tr("Open"));

           data->nextButton->setText(tr("Next"));

   /*QEvent ev(QEvent::LanguageChange);
   ev.QEvent::LanguageChange;
   QWidget::changeEvent(&ev);


  QWidget *w=(QWidget*)(&langLabel);
  w->setLocale();
  // langLabel->setText(tr(("Set:")));
   langLabel->update();*/

}

EditTablesPage::EditTablesPage(QWidget *parent,commonData *d)
    : QWidget(parent)
{




    data=d;
    ui=new Dialog(this,data);
    ui1=new Dialog1(this,data);
    ui2=new Dialog2(this,data);

    //data->tablesGroup = new QGroupBox(tr("Table Contents"));

    if (!data->db.open()) {
        qDebug() << "cannot open the database";
        return ;
    }
    QTabWidget*  tabEdit= new QTabWidget;
data->tableStack = new QStackedWidget;
    QWidget *tab1=new QWidget;
      //QWidget *lol=new QWidget;
    QWidget *tab2=new QWidget;


    data->tableStack->addWidget(tab1);
    data->tableStack->addWidget(tab2);

  // tabEdit->addTab(tab1, tr("Form types and answers"));
    //tabEdit->addTab(tab2, tr("Locations and areas"));


    my_database_model1=new mySqlTableModel(this,data->db);
    my_database_model1->setTable("form_type_table");
    my_database_model1->select();
    my_database_model1->setEditStrategy(mySqlTableModel::OnFieldChange);
    my_database_model2=new mySqlTableModel(this,data->db);
    my_database_model2->setTable("value_of_record_table");
    my_database_model2->select();
    my_database_model2->setEditStrategy(mySqlTableModel::OnFieldChange);

    connect(my_database_model1, SIGNAL( dataChanged ( const QModelIndex &, const QModelIndex &) ), this, SLOT(update_data( const QModelIndex &, const QModelIndex &)));
    connect(my_database_model2, SIGNAL( dataChanged ( const QModelIndex &, const QModelIndex &) ), this, SLOT(update_data( const QModelIndex &, const QModelIndex &)));
   // connect(tabEdit, SIGNAL( currentChanged(int)) , this, SLOT(update_button( int)));

    tableView1=new QTableView(this);
    tableView1->setModel(my_database_model1);

    //tableView1->setShowGrid(false);

    //tableView1->setCornerButtonEnabled(false);

    tableView1->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    tableView1->verticalHeader()->hide();
    tableView2=new QTableView(this);
    tableView2->setModel(my_database_model2);

    tableView2->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    tableView2->verticalHeader()->hide();

    my_database_model3=new mySqlTableModel(this,data->db);
    my_database_model3->setTable("geographic_area_table");
    my_database_model3->select();
    my_database_model3->setEditStrategy(mySqlTableModel::OnFieldChange);
    my_database_model4=new mySqlTableModel(this,data->db);
    my_database_model4->setTable("locations_table");
    my_database_model4->select();
    my_database_model4->setEditStrategy(mySqlTableModel::OnFieldChange);

    connect(my_database_model3, SIGNAL( dataChanged ( const QModelIndex &, const QModelIndex &) ), this, SLOT(update_data( const QModelIndex &, const QModelIndex &)));
    connect(my_database_model4, SIGNAL( dataChanged ( const QModelIndex &, const QModelIndex &) ), this, SLOT(update_data( const QModelIndex &, const QModelIndex &)));

    tableView3=new QTableView(this);
    tableView3->setModel(my_database_model3);
    tableView3->verticalHeader()->hide();

    tableView3->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    tableView4=new QTableView(this);
    tableView4->setModel(my_database_model4);
    tableView4->verticalHeader()->hide();

    tableView4->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    // tableView->setSelectionMode(QAbstractItemView::SingleSelection);
    //ui->tableView->show();
    /*QComboBox *tableCombo=new QComboBox();
    tableCombo->addItem("form_type_table");
    tableCombo->addItem("value_of_record_table");
    tableCombo->addItem("geographic_area_table");
    tableCombo->addItem("locations_table");*/
     tableView1->setEditTriggers(QAbstractItemView::NoEditTriggers);
     tableView2->setEditTriggers(QAbstractItemView::NoEditTriggers);
    tableView3->setEditTriggers(QAbstractItemView::NoEditTriggers);
     tableView4->setEditTriggers(QAbstractItemView::NoEditTriggers);
     //tableView3->setSelectionModel();
 connect(tableView1->verticalHeader(), SIGNAL(sectionClicked(int)), this,SLOT (handle_section_clicked(int)));
 connect(tableView2->verticalHeader(), SIGNAL(sectionClicked(int)), this,SLOT (handle_section_clicked(int)));
 connect(tableView3->verticalHeader(), SIGNAL(sectionClicked(int)), this,SLOT (handle_section_clicked3(int)));
 connect(tableView4->verticalHeader(), SIGNAL(sectionClicked(int)), my_database_model4,SLOT (handle_section_clicked(int)));
  connect(tableView1->horizontalHeader(), SIGNAL(sectionClicked(int)), this,SLOT (sorting1(int)));
    connect(tableView2->horizontalHeader(), SIGNAL(sectionClicked(int)), this,SLOT (sorting2(int)));
      connect(tableView3->horizontalHeader(), SIGNAL(sectionClicked(int)), this,SLOT (sorting3(int)));
        connect(tableView4->horizontalHeader(), SIGNAL(sectionClicked(int)), this,SLOT (sorting4(int)));
   connect(tableView1, SIGNAL(clicked(QModelIndex)), this,SLOT (selecting1(QModelIndex)));
    connect(tableView2, SIGNAL(clicked(QModelIndex)), this,SLOT (selecting2(QModelIndex)));
     connect(tableView3, SIGNAL(clicked(QModelIndex)), this,SLOT (selecting3(QModelIndex)));
      connect(tableView4, SIGNAL(clicked(QModelIndex)), this,SLOT (selecting4(QModelIndex)));
       connect(tableView4, SIGNAL(doubleClicked(QModelIndex)), this,SLOT (filt_all()));


    //connect(tableCombo, SIGNAL(currentIndexChanged( QString)), this, SLOT(change_table(QString)));

    data->tableLabel1 = new QLabel(tr("Query:"));
    data->filterCombo1 = new QComboBox;
    data->tableLabel2 = new QLabel(tr("Query:"));
    data->filterCombo2 = new QComboBox;
    data->tableLabel3 = new QLabel(tr("Query:"));
    data->filterCombo3 = new QComboBox;
    data->tableLabel4 = new QLabel(tr("Query:"));
    data->filterCombo4 = new QComboBox;

    qDebug()<<"col count "<<my_database_model1->columnCount()<<endl;
    for (int i=0;i<my_database_model1->columnCount();i++)
        data->filterCombo1->addItem(my_database_model1->headerData(i, Qt::Horizontal).toString());

    qDebug()<<"col count "<<my_database_model2->columnCount()<<endl;
    for (int i=0;i<my_database_model2->columnCount();i++)
        data->filterCombo2->addItem(my_database_model2->headerData(i, Qt::Horizontal).toString());

    qDebug()<<"col count "<<my_database_model3->columnCount()<<endl;
    for (int i=0;i<my_database_model3->columnCount();i++)
        data->filterCombo3->addItem(my_database_model3->headerData(i, Qt::Horizontal).toString());

    qDebug()<<"col count "<<my_database_model4->columnCount()<<endl;
    for (int i=0;i<my_database_model4->columnCount();i++)
        data->filterCombo4->addItem(my_database_model4->headerData(i, Qt::Horizontal).toString());


    data->filterEdit1= new QLineEdit;
    data->filterEdit2 = new QLineEdit;
    data->filterEdit3 = new QLineEdit;
    data->filterEdit4 = new QLineEdit;


    data->filterButton1 = new myCoolButton(tr("Filter"));
    data->addButton1 = new myCoolButton(tr("Add new question"));
    data->editButton1 = new myCoolButton(tr("Edit"));
    data->remButton1 = new myCoolButton(tr("Remove Row"));
     data->checkallButton1 = new myCoolButton(tr("Check All"));
     data->uncheckallButton1= new myCoolButton(tr("Uncheck All"));;

    data->filterButton2 = new myCoolButton(tr("Filter"));
    data->addButton2 = new myCoolButton(tr("Insert Empty Row"));
    data->remButton2 = new myCoolButton(tr("Remove Row"));
    data->checkallButton2 = new myCoolButton(tr("Check All"));
    data->uncheckallButton2= new myCoolButton(tr("Uncheck All"));;

    data->filterButton3 = new myCoolButton(tr("Filter"));
    data->addButton3 = new myCoolButton(tr("Add new area"));
    data->editButton3 = new myCoolButton(tr("Edit area"));
    data->remButton3 = new myCoolButton(tr("Remove Row"));
    data->checkallButton3 = new myCoolButton(tr("Check All"));
    data->uncheckallButton3= new myCoolButton(tr("Uncheck All"));;

    data->filterButton4 = new myCoolButton(tr("Filter"));
    data->addButton4 = new myCoolButton(tr("Add new location"));
    data->editButton4 = new myCoolButton(tr("Edit location"));
    data->remButton4 = new myCoolButton(tr("Remove Row"));
    data->checkallButton4 = new myCoolButton(tr("Check All"));
    data->uncheckallButton4= new myCoolButton(tr("Uncheck All"));;

    connect(data->filterButton1, SIGNAL(clicked()), this, SLOT(filter1()));
   // connect(data->addButton1, SIGNAL(clicked()), this, SLOT(open_win1()));
    //connect(data->editButton1, SIGNAL(clicked()), this, SLOT(open_win11()));

    connect(ui, SIGNAL(add()), this, SLOT(add_row1()));
    connect(ui, SIGNAL(edit()), this, SLOT(update_row1()));

   // connect(ui, SIGNAL(edit()), this, SLOT(update_row2()));
   // connect(data->remButton1, SIGNAL(clicked()), this, SLOT(remove_selected1()));
    connect(data->checkallButton1, SIGNAL(clicked()), this, SLOT(check_headers1()));
    connect(data->uncheckallButton1, SIGNAL(clicked()), this, SLOT(uncheck_headers1()));

   /* connect(data->filterButton2, SIGNAL(clicked()), this, SLOT(filter2()));
    connect(data->addButton2, SIGNAL(clicked()), this, SLOT(add_row2()));
    connect(data->remButton2, SIGNAL(clicked()),  my_database_model2, SLOT(remove_selected()));
    connect(data->checkallButton2, SIGNAL(clicked()), my_database_model2, SLOT(check_headers()));
    connect(data->uncheckallButton2, SIGNAL(clicked()), my_database_model2, SLOT(uncheck_headers()));*/

    connect(data->filterButton3, SIGNAL(clicked()), this, SLOT(filter3()));
    //connect(data->addButton3, SIGNAL(clicked()), this, SLOT(open_win3()));
    //connect(data->editButton3, SIGNAL(clicked()), this, SLOT(open_win33()));
    connect(ui1, SIGNAL(add()), this, SLOT(add_row3()));
    connect(ui1, SIGNAL(edit()), this, SLOT(update_row3()));
    //connect(data->remButton3, SIGNAL(clicked()),  this, SLOT(remove_selected3()));
    connect(data->checkallButton3, SIGNAL(clicked()), my_database_model3, SLOT(check_headers()));
    connect(data->uncheckallButton3, SIGNAL(clicked()), my_database_model3, SLOT(uncheck_headers()));

    connect(data->filterButton4, SIGNAL(clicked()), this, SLOT(filter4()));
   // connect(data->addButton4, SIGNAL(clicked()), this, SLOT(open_win4()));
    //connect(data->editButton4, SIGNAL(clicked()), this, SLOT(open_win44()));
    connect(ui2, SIGNAL(add()), this, SLOT(add_row4()));
    connect(ui2, SIGNAL(edit()), this, SLOT(update_row4()));
    //connect(data->remButton4, SIGNAL(clicked()),  this, SLOT(remove_selected4()));
    connect(data->checkallButton4, SIGNAL(clicked()), my_database_model4, SLOT(check_headers()));
    connect(data->uncheckallButton4, SIGNAL(clicked()), my_database_model4, SLOT(uncheck_headers()));


    QGridLayout *langLayout1 = new QGridLayout;

     langLayout1->setContentsMargins( data->marg, data->marg, data->marg, data->marg );
    /*langLayout1->addWidget(data->tableLabel1,0,0);
    langLayout1->addWidget(filterCombo1,0,1);
    langLayout1->addWidget(filterEdit1,0,2);
    langLayout1->addWidget(data->filterButton1,0,3); data->filterButton1->setObjectName("filterButton");
    langLayout1->addWidget(data->checkallButton1,0,4);data->checkallButton1->setObjectName("checkButton");
    langLayout1->addWidget(data->uncheckallButton1,0,5);data->uncheckallButton1->setObjectName("uncheckButton");*/
    //langLayout1->addStretch(20);
    //QSpacerItem
    //langLayout1->addWidget(data->addButton1,1,0);data->addButton1->setObjectName("addButton");
    //langLayout1->addWidget(data->editButton1,1,1);data->editButton1->setObjectName("editButton");
    //langLayout1->addWidget(data->remButton1,1,2);data->remButton1->setObjectName("remButton");
    //langLayout1->addStretch(1);

    /*QHBoxLayout *langLayout2 = new QHBoxLayout;
    langLayout2->addWidget(data->tableLabel2);

    langLayout2->addWidget(filterCombo2);
    langLayout2->addWidget(filterEdit2);
    langLayout2->addWidget(data->filterButton2);
    langLayout2->addWidget(data->checkallButton2);
    langLayout2->addWidget(data->uncheckallButton2);

    langLayout2->addStretch(20);
    //QSpacerItem
    langLayout2->addWidget(data->addButton2);
    langLayout2->addWidget(data->remButton2);
    langLayout2->addStretch(1);*/

    QGridLayout *langLayout3 = new QGridLayout;
    langLayout3->setContentsMargins( data->marg, data->marg, data->marg, data->marg );
    /*langLayout3->addWidget(data->tableLabel3,0,0);

    langLayout3->addWidget(filterCombo3,0,1);
    langLayout3->addWidget(filterEdit3,0,2);
    langLayout3->addWidget(data->filterButton3,0,3); data->filterButton3->setObjectName("top_small_navbar_Button");
    langLayout3->addWidget(data->checkallButton3,0,4);data->checkallButton3->setObjectName("checkButton");
    langLayout3->addWidget(data->uncheckallButton3,0,5);data->uncheckallButton3->setObjectName("uncheckButton");*/

   // langLayout3->addStretch(20);
    //QSpacerItem
   // langLayout3->addWidget(data->addButton3,1,0);data->addButton3->setObjectName("addButton");
    //langLayout3->addWidget(data->editButton3);
   // langLayout3->addWidget(data->remButton3,1,1);data->remButton3->setObjectName("remButton");
   // langLayout3->addStretch(1);

    QGridLayout *langLayout4 = new QGridLayout;
    langLayout4->setContentsMargins( data->marg, data->marg, data->marg, data->marg );
    /*langLayout4->addWidget(data->tableLabel4,0,0);

    langLayout4->addWidget(filterCombo4,0,1);
    langLayout4->addWidget(filterEdit4,0,2);
    langLayout4->addWidget(data->filterButton4,0,3); data->filterButton4->setObjectName("filterButton");
    langLayout4->addWidget(data->checkallButton4,0,4);data->checkallButton4->setObjectName("checkButton");
    langLayout4->addWidget(data->uncheckallButton4,0,5);data->uncheckallButton4->setObjectName("uncheckButton");*/

  //  langLayout4->addStretch(20);
    //QSpacerItem
   // langLayout4->addWidget(data->addButton4,1,0);data->addButton4->setObjectName("addButton");
    //langLayout4->addWidget(data->editButton4,1,1);data->editButton4->setObjectName("editButton");
    //langLayout4->addWidget(data->remButton4,1,2);data->remButton4->setObjectName("remButton");
    //langLayout4->addStretch(1);

    QGridLayout *configLayout1 = new QGridLayout;
    configLayout1->setContentsMargins( data->marg, data->marg, data->marg, data->marg );
    configLayout1->addLayout(langLayout1, 0, 0);
    //configLayout1->addLayout(langLayout2, 0, 1);
    // packagesLayout->addWidget(nameEdit, 0, 1);
    configLayout1->addWidget(tableView1, 1, 0,1,1);
    configLayout1->addWidget(tableView2, 1, 1,1,1);

    tab1->setLayout(configLayout1);

    QGridLayout *configLayout2 = new QGridLayout;
    configLayout2->setContentsMargins( data->marg, data->marg, data->marg, data->marg );
     configLayout2->addLayout(langLayout3, 0, 0);
     configLayout2->addLayout(langLayout4, 0, 1);
    // packagesLayout->addWidget(nameEdit, 0, 1);
    configLayout2->addWidget(tableView3, 1, 0,1,1);
    configLayout2->addWidget(tableView4, 1, 1,1,1);

   tab2->setLayout(configLayout2);

    tableView1->show();
    tableView2->show();
    tableView3->show();
    tableView4->show();

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->setContentsMargins( data->marg, data->marg, data->marg, data->marg );
    // mainLayout->addWidget(tableCombo);
    //mainLayout->addWidget(tabEdit);
    mainLayout->addWidget(data->tableStack);
    //mainLayout->addWidget(data->tablesGroup);
    //  mainLayout->addStretch(1);
    setLayout(mainLayout);

    QModelIndex indx;
    update_data ( indx, indx);

}




PrintAndPreviewPage::PrintAndPreviewPage(QWidget *parent,commonData *d)
    : QWidget(parent)
{


    data=d;
    data->printGroup = new QGroupBox(tr("Preview:"));


    // viewer = new myPixmapLabel(this);

    //data->openButton = new myCoolButton(tr("Open"));

    // data->nextButton = new myCoolButton(tr("Next"));

    //connect(data->openButton, SIGNAL(clicked()), this, SLOT(push_open()));
    // connect(data->nextButton, SIGNAL(clicked()), this, SLOT(push_next()));


    /*  data->pagesspinbox = new QSpinBox;
    data->pagesspinbox->setPrefix(("page "));
    data->pagesspinbox->setSuffix((" of "));
   // hitsSpinBox->setSpecialValueText(tr("Return only the first result"));
    data->pagesspinbox->setMinimum(1);
    data->pagesspinbox->setMaximum(100);
    data->pagesspinbox->setSingleStep(1);*/

    connect(data->pagesspinbox, SIGNAL(valueChanged(int)), this, SLOT(goto_page(int)));


    QHBoxLayout *topLayout = new QHBoxLayout;

    // topLayout->addWidget(data->openButton);
    topLayout->addStretch(20);
    // topLayout->addWidget(data->nextButton);
    //topLayout->addWidget(data->pagesspinbox);

    QGridLayout *groupLayout = new QGridLayout;
    groupLayout->addLayout(topLayout, 0, 0);
    // groupLayout->addWidget(viewer, 1, 0,1,2);

    data->printGroup->setLayout(groupLayout);

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addWidget(data->printGroup);
    setLayout(mainLayout);

    /* QGroupBox *packagesGroup = new QGroupBox(tr("Look for packages"));

   /* QLabel *nameLabel = new QLabel(tr("Name:"));
    QLineEdit *nameEdit = new QLineEdit;

    QLabel *dateLabel = new QLabel(tr("Released after:"));
    QDateTimeEdit *dateEdit = new QDateTimeEdit(QDate::currentDate());

    QCheckBox *releasesCheckBox = new QCheckBox(tr("Releases"));
    QCheckBox *upgradesCheckBox = new QCheckBox(tr("Upgrades"));

    QSpinBox *hitsSpinBox = new QSpinBox;
    hitsSpinBox->setPrefix(tr("Return up to "));
    hitsSpinBox->setSuffix(tr(" results"));
    hitsSpinBox->setSpecialValueText(tr("Return only the first result"));
    hitsSpinBox->setMinimum(1);
    hitsSpinBox->setMaximum(100);
    hitsSpinBox->setSingleStep(10);

    myCoolButton *startQueryButton = new myCoolButton(tr("Start query"));

    QGridLayout *packagesLayout = new QGridLayout;
    packagesLayout->addWidget(nameLabel, 0, 0);
    packagesLayout->addWidget(nameEdit, 0, 1);
    packagesLayout->addWidget(dateLabel, 1, 0);
    packagesLayout->addWidget(dateEdit, 1, 1);
    packagesLayout->addWidget(releasesCheckBox, 2, 0);
    packagesLayout->addWidget(upgradesCheckBox, 3, 0);
    packagesLayout->addWidget(hitsSpinBox, 4, 0, 1, 2);
    packagesGroup->setLayout(packagesLayout);

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addWidget(packagesGroup);
    mainLayout->addSpacing(12);
    mainLayout->addWidget(startQueryButton);
    mainLayout->addStretch(1);
    setLayout(mainLayout);
    */
}
