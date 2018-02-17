/****************************************************************************
**
** Copyright (C) 2012 Nokia Corporation and/or its subsidiary(-ies).
** All rights reserved.
** Contact: Nokia Corporation (qt-info@nokia.com)
**
** This file is part of the examples of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:BSD$
** You may use this file under the terms of the BSD license as follows:
**
** "Redistribution and use in source and binary forms, with or without
** modification, are permitted provided that the following conditions are
** met:
**   * Redistributions of source code must retain the above copyright
**     notice, this list of conditions and the following disclaimer.
**   * Redistributions in binary form must reproduce the above copyright
**     notice, this list of conditions and the following disclaimer in
**     the documentation and/or other materials provided with the
**     distribution.
**   * Neither the name of Nokia Corporation and its Subsidiary(-ies) nor
**     the names of its contributors may be used to endorse or promote
**     products derived from this software without specific prior written
**     permission.
**
** THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
** "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
** LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
** A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
** OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
** SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
** LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
** DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
** THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
** (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
** OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE."
** $QT_END_LICENSE$
**
****************************************************************************/

#include <QtGui>

#include "tabdialog.h"
#include <QListWidget>
#include <QTreeWidget>
#include <QStackedWidget>
#include <QPushButton>
#include <QLayout>
#include <QGroupBox>
#include <QLabel>
#include <QLineEdit>
#include <QCheckBox>
#include <QAction>
#include <QMenuBar>
#include <QSpacerItem>
#include  "pages.h"
#include "commondata.h"
#include <QGraphicsEffect>
//! [0]
//!
//!
//!

TabDialog::TabDialog(QWidget *parent)
{

    //}
    /*TabDialog::TabDialog(const QString &fileName, QWidget *parent)
    : QDialog(parent)
{*/
    //   QFileInfo fileInfo(fileName);

    //menuBar()->add
    // tabWidget = new QTabWidget(this);

    cData=new commonData();

    cData->langCombo = new QComboBox;

    cData->langCombo->addItem(("English"));
    cData->langCombo->addItem(("Russian"));

    /*tabWidget->addTab(new ValidateTab(tabWidget,cData), tr("Validate Forms"));
    tabWidget->addTab(new SettingsTab(tabWidget,cData), tr("Settings"));

    tabWidget->setCurrentIndex(1);*/
    SettingsTab *settingstab=new SettingsTab(0,cData);
    //settingstab->setStyleSheet("background-color: #ffffff");
    /*
//! [1] //! [2]
    buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok
//! [1] //! [3]
                                     | QDialogButtonBox::Cancel);

    connect(buttonBox, SIGNAL(accepted()), this, SLOT(accept()));
    connect(buttonBox, SIGNAL(rejected()), this, SLOT(reject()));*/
    QGroupBox* langGroup = new QGroupBox(tr(""));
    //langGroup->setStyleSheet(" background-color: #669999;");
    //langGroup->setStyleSheet(" border-color: #669999;");
    //langGroup->setStyleSheet(" color: #669999;");
    // langGroup->setFlat(true);
    // langGroup->setStyleSheet( "border: none" );

    langGroup->setContentsMargins(0,0,0,0);
    QLabel* langLabelpic = new QLabel("");
    langLabelpic->setPixmap(QPixmap(":/images/lang_verysmall.png"));

    QLabel* langLabel = new QLabel(tr("UI Language:"));
    langLabel->setStyleSheet("color: #666666");
    QFont font = langLabel->font();
    font.setBold(true);
    font.setPointSize(10);
    langLabel->setFont(font);

    //langLabel->setStyleSheet("font:bold");
    //langLabel->setStyleSheet("font-size: 20");
    //langLabel->setStyleSheet("font-family: Arial");



    QHBoxLayout *langLayout = new QHBoxLayout;

    langLayout->addWidget(langLabelpic);
    langLayout->addWidget(langLabel);
    langLayout->addWidget(cData->langCombo);


    langLayout->setContentsMargins(10, 10, 10, 10);
    langGroup->setLayout(langLayout);

    //langGroup->setObjectName("top_large_navbar");
    QWidget *widget=new QWidget;
    widget->setObjectName("the_central_widget");
    QWidget *widgetup=new QWidget;

    QVBoxLayout *mainLayout = new QVBoxLayout;
    QVBoxLayout *verticalLayout = new QVBoxLayout;
    QHBoxLayout *horizontalLayout = new QHBoxLayout;

    mainLayout->setContentsMargins( cData->marg, cData->marg, cData->marg, cData->marg );
    verticalLayout->setContentsMargins( cData->marg, cData->marg, cData->marg, cData->marg );
    horizontalLayout->setContentsMargins( cData->marg, cData->marg, cData->marg, cData->marg );

    myCoolButton *primaryLoc=new myCoolButton("Primary location");primaryLoc->setObjectName("addnew_Button");
    myCoolButton *exit=new myCoolButton("Exit");exit->setObjectName("exitnew_Button");exit->setFixedWidth(100);
    connect(exit, SIGNAL(clicked(bool)), qApp, SLOT(quit()));

    //widgetup->setMaximumHeight(30);
    widgetup->setObjectName("top_large_navbar");
    widgetup->setLayout(horizontalLayout);
    widgetup->setMaximumHeight(50);
    horizontalLayout->SetMinimumSize;
    horizontalLayout->addWidget(primaryLoc);
    horizontalLayout->addStretch(20);
    // horizontalLayout->addWidget(cData->langCombo);
    horizontalLayout->addWidget(langGroup);
    horizontalLayout->addWidget(exit);
    //horizontalLayout->addStretch(0);
    widget->setLayout(verticalLayout);
    verticalLayout->addWidget(widgetup);
    verticalLayout->addWidget(settingstab);
    mainLayout->setSizeConstraint(QLayout::SetNoConstraint);
    // mainLayout->addLayout(horizontalLayout);
    mainLayout->addWidget(widget);


    //mainLayout->addWidget(buttonBox);
    setLayout(mainLayout);
    setWindowTitle(tr("Form Generator UI"));
    createActions();
    createMenus();


    setCentralWidget(widget);
}
//! [5]


TabDialog::~TabDialog()
{
    // delete ui;
}


void TabDialog::createActions()
{
    newAct = new QAction(tr("&New"), this);
    newAct->setShortcuts(QKeySequence::New);
    newAct->setStatusTip(tr("Create a new file"));
    // connect(newAct, &QAction::triggered, this, &MainWindow::newFile);

    openAct = new QAction(tr("&Open..."), this);
    openAct->setShortcuts(QKeySequence::Open);
    openAct->setStatusTip(tr("Open an existing file"));
    // connect(openAct, &QAction::triggered, this, &MainWindow::open);

    saveAct = new QAction(tr("&Save"), this);
    saveAct->setShortcuts(QKeySequence::Save);
    saveAct->setStatusTip(tr("Save the document to disk"));
    // connect(saveAct, &QAction::triggered, this, &MainWindow::save);

    printAct = new QAction(tr("&Print..."), this);
    printAct->setShortcuts(QKeySequence::Print);
    printAct->setStatusTip(tr("Print the document"));
    // connect(printAct, &QAction::triggered, this, &MainWindow::print);

    exitAct = new QAction(tr("&Exit"), this);
    exitAct->setShortcuts(QKeySequence::Quit);
    exitAct->setStatusTip(tr("Exit the application"));
    connect(exitAct, &QAction::triggered, this, &QWidget::close);


}

void TabDialog::createMenus()
{
    /* fileMenu = menuBar()->addMenu(tr("&File"));
    fileMenu->addAction(newAct);
    fileMenu->addAction(openAct);
    fileMenu->addAction(saveAct);
    fileMenu->addAction(printAct);
    fileMenu->addSeparator();
    fileMenu->addAction(exitAct);

    helpMenu = menuBar()->addMenu(tr("&Help"));
    //helpMenu->addAction(aboutAct);
    //helpMenu->addAction(aboutQtAct);*/


    // myCoolButton* button= new myCoolButton(this);

    // button->setText("sssss");


    /* QGroupBox* langGroup = new QGroupBox(tr(""));

    // langGroup->setFlat(true);
    // langGroup->setStyleSheet( "border: none" );

    langGroup->setContentsMargins(0,0,0,0);
    QLabel* langLabelpic = new QLabel("");
    langLabelpic->setPixmap(QPixmap(":/images/lang_verysmall.png"));

    QLabel* langLabel = new QLabel(tr("UI Language:"));



    QHBoxLayout *langLayout = new QHBoxLayout;
    langLayout->addWidget(langLabelpic);
    langLayout->addWidget(langLabel);
    langLayout->addWidget(cData->langCombo);

    langLayout->setContentsMargins(0, 0, 0, 0);
    langGroup->setLayout(langLayout);


    menuBar()->setCornerWidget(langGroup);*/


}
//! [7]
ValidateTab::ValidateTab(QWidget *parent, commonData *Data)
    : QWidget(parent)
{
    cData=Data;
}
//! [7]

//! [8]
SettingsTab::SettingsTab(QWidget *parent,commonData *Data)
    : QWidget(parent)
{

    cData=Data;

    contentsWidget = new QListWidget;
    contentsWidget->setViewMode(QListView::ListMode);//QListView::IconMode);
    contentsWidget->setIconSize(QSize(96/2, 84/2));
    contentsWidget->setMovement(QListView::Static);
    contentsWidget->setMaximumWidth(160);
    contentsWidget->setMinimumWidth(160);
    contentsWidget->setSpacing(0);

    // commonData* Data=new commonData(this);

    pagesWidget = new QStackedWidget;

    pagesWidget->setObjectName("pages_widget");
    genpage =new GenerateFormsPage(this,cData);
    tablepage= new EditTablesPage(this,cData);
    QWidget *empty=new QWidget;


    pagesWidget->addWidget(tablepage);
    pagesWidget->addWidget(genpage);
    pagesWidget->addWidget(empty);
    pagesWidget->setStyleSheet("background-color: #ffffff");
    genpage->setStyleSheet("background-color: #ffffff;border-color: grey;    border-width: 1px; border-style: solid; border-radius: 3px;");
    tablepage->setStyleSheet("background-color: #ffffff");
    genpage->update_view_sing();


    // pagesWidget->addWidget(new SetLanguagePage(this,cData));

    // pagesWidget->addWidget(new PrintAndPreviewPage(this,cData));


    createIcons();
    contentsWidget->setCurrentRow(0);

    //  connect(closeButton, SIGNAL(clicked()), this, SLOT(close()));
    edittab= new myCoolButton(tr("Edit Database │ ▼"));edittab->setObjectName("addButton");
    edittab->setIcon(QIcon(":/images/edit_white.png"));


    edittab->setFixedWidth(180);
    edittab->activate();
    genf= new myCoolButton(tr("Generate Forms"));genf->setObjectName("addButton");
    genf->setIcon(QIcon(":/images/table-edit-icon.png"));
    genf->setFixedWidth(180);
    genf->setMinimumHeight(35);
    genf->deactivate();
    file=new myCoolButton(tr(" File │ ►"));file->setObjectName("menuButton");
    loadForm=new myCoolButton(tr("Load Forms"));loadForm->setObjectName("addButton");
    formList=new myCoolButton(tr("Form List"));formList->setObjectName("addButton");

    genReports=new myCoolButton(tr(" Generate reports"));genReports->setObjectName("menuButton");
    Logs=new myCoolButton(tr(" Logs │ ►"));Logs->setObjectName("menuButton");
    ActLog=new myCoolButton(tr("Act log"));ActLog->setObjectName("addButton");
    AudLog=new myCoolButton(tr("Aud log"));AudLog->setObjectName("addButton");
    Settings=new myCoolButton(tr(" Settings │ ►"));Settings->setObjectName("menuButton");
    file->setFixedWidth(180);
    loadForm->setFixedWidth(180);
    formList->setFixedWidth(180);
    genReports->setFixedWidth(180);
    Logs->setFixedWidth(180);
    ActLog->setFixedWidth(180);
    AudLog->setFixedWidth(180);
    Settings->setFixedWidth(180);
    QSize a;
    a.setHeight(15);
    a.setWidth(15);
    edittab->setIconSize(a);
    genf->setIconSize(a);

    cData->tab1= new myCoolButton("—  Form type and answer");cData->tab1->setObjectName("menuButton");

    cData->edit1= new myCoolButton("Edit"); cData->edit1->setObjectName("editnew_Button");cData->edit1->setFixedWidth(150);
    cData->tab1->setFixedWidth(180);
    cData->add1= new myCoolButton("Add new"); cData->add1->setObjectName("addnew_Button");cData->add1->setFixedWidth(150);
    cData->rem1= new myCoolButton("Remove"); cData->rem1->setObjectName("removenew_Button");cData->rem1->setFixedWidth(150);
    cData->tab2= new myCoolButton("—  Location and area"); cData->tab2->setObjectName("menuButton");
    cData->tab2->setFixedWidth(180);
    cData->edit2= new myCoolButton("Edit"); cData->edit2->setObjectName("editnew_Button");cData->edit2->setFixedWidth(150);
    cData->rem_area2= new myCoolButton("Remove area"); cData->rem_area2->setObjectName("removenew_Button");cData->rem_area2->setFixedWidth(150);
    cData->rem_loc2= new myCoolButton("Remove location"); cData->rem_loc2->setObjectName("removenew_Button");cData->rem_loc2->setFixedWidth(150);
    cData->add_area2= new myCoolButton("Add new area"); cData->add_area2->setObjectName("addnew_Button");cData->add_area2->setFixedWidth(150);
    cData->add_loc2= new myCoolButton("Add new location"); cData->add_loc2->setObjectName("addnew_Button");cData->add_loc2->setFixedWidth(150);

    cData->genff= new myCoolButton("Generate form"); cData->genff->setObjectName("addnew_Button");cData->genff->setFixedWidth(150);
    cData->printforms= new myCoolButton("Print form"); cData->printforms->setObjectName("editnew_Button");cData->printforms->setFixedWidth(150);
    cData->filterButton1->setObjectName("filternew_Button");
    cData->filterButton4->setObjectName("filternew_Button");

    pagesWidget->setCurrentIndex(2);
    QGridLayout *gridLayout = new QGridLayout;

    QVBoxLayout *verticalLayout = new QVBoxLayout;
    QHBoxLayout *horizontalLayout = new QHBoxLayout;


    gridLayout->setContentsMargins( cData->marg, cData->marg, cData->marg, cData->marg );
    verticalLayout->setContentsMargins( cData->marg, cData->marg, cData->marg, cData->marg );
    horizontalLayout->setContentsMargins( 10, 10, 10, 10 );
    pagesWidget->setContentsMargins( 0, 0, 0, 0 );
    QWidget * widUp= new QWidget;

    QWidget * left_navbar= new QWidget(this);

    /* QGraphicsDropShadowEffect* effect = new QGraphicsDropShadowEffect();
    effect->setBlurRadius(10); //Adjust accordingly
    effect->setOffset(0,2); //Adjust accordingly*/

    // this->setGraphicsEffect(effect);
    //verticalLayout->addWidget(contentsWidget);
    verticalLayout->addWidget(file);
    verticalLayout->addWidget(loadForm);
    verticalLayout->addWidget(formList);
    verticalLayout->addWidget(genReports);
    verticalLayout->addWidget(Logs);
    verticalLayout->addWidget(ActLog);
    verticalLayout->addWidget(AudLog);
    verticalLayout->addWidget(Settings);





    verticalLayout->addWidget(genf);
    verticalLayout->addWidget(edittab);
    verticalLayout->addWidget(cData->tab1);
    /* verticalLayout->addWidget(cData->edit1);
    verticalLayout->addWidget(cData->add1);
    verticalLayout->addWidget(cData->rem1);*/
    verticalLayout->addWidget(cData->tab2);
    /* verticalLayout->addWidget(cData->edit2);
    verticalLayout->addWidget(cData->add_area2);
    verticalLayout->addWidget(cData->add_loc2);
    verticalLayout->addWidget(cData->rem_area2);
    verticalLayout->addWidget(cData->rem_loc2);*/



    left_navbar->setLayout(verticalLayout);
    left_navbar->setObjectName("left_navbar");

    horizontalLayout->addWidget(cData->add1);
    horizontalLayout->addWidget(cData->edit1);
    horizontalLayout->addWidget(cData->rem1);

    horizontalLayout->addWidget(cData->add_area2);
    horizontalLayout->addWidget(cData->add_loc2);
    horizontalLayout->addWidget(cData->edit2);
    horizontalLayout->addWidget(cData->rem_area2);
    horizontalLayout->addWidget(cData->rem_loc2);
    horizontalLayout->addWidget(cData->genff);
    horizontalLayout->addWidget(cData->printforms);
    //horizontalLayout->addWidget(cData->tableLabel1);
    horizontalLayout->addWidget(cData->filterCombo1);
    horizontalLayout->addWidget(cData->filterEdit1);
    horizontalLayout->addWidget(cData->filterButton1);
    horizontalLayout->addWidget(cData->filterCombo4);
    horizontalLayout->addWidget(cData->filterEdit4);
    horizontalLayout->addWidget(cData->filterButton4);//data->filterButton1->setObjectName("filterButton");
    horizontalLayout->addStretch(20);
    loadForm->setVisible(false);
    formList->setVisible(false);
    ActLog->setVisible(false);
    AudLog->setVisible(false);
    edittab->setVisible(false);
    genf->setVisible(false);
    cData->tab1->setVisible(false);
    cData->tab2->setVisible(false);
    cData-> edit1->setVisible(false);
    cData->add1->setVisible(false);
    cData->rem1->setVisible(false);
    cData->edit2->setVisible(false);
    cData->rem_area2->setVisible(false);
    cData->rem_loc2->setVisible(false);
    cData->add_area2->setVisible(false);
    cData->add_loc2->setVisible(false);
    cData->genff->setVisible(false);
    cData->printforms->setVisible(false);
    cData->filterCombo1->setVisible(false);
    cData->filterEdit1->setVisible(false);
    cData->filterButton1->setVisible(false);
    cData->filterCombo4->setVisible(false);
    cData->filterEdit4->setVisible(false);
    cData->filterButton4->setVisible(false);


    verticalLayout->addStretch();
    widUp->setLayout(horizontalLayout);
    widUp->setObjectName("top_small_navbar");
    widUp->setMaximumHeight(50);
    widUp->setMaximumWidth(5000);

    gridLayout->addWidget(left_navbar,0,0,2,1);

    gridLayout->setContentsMargins( cData->marg, cData->marg, cData->marg, cData->marg );

    //gridLayout->setc
    gridLayout->addWidget(widUp,0,1,1,1);
    gridLayout->addWidget(pagesWidget,1,1,1,1);
    //gridLayout->setSpacing(1);

    //horizontalLayout->addLayout(verticalLayout);
    //horizontalLayout->addWidget(pagesWidget, 1);

    //QHBoxLayout *buttonsLayout = new QHBoxLayout;
    //buttonsLayout->addStretch(1);
    //buttonsLayout->addWidget(closeButton);

    /* QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addLayout(horizontalLayout);
    mainLayout->addStretch(1);
    mainLayout->addSpacing(12);
    mainLayout->addLayout(buttonsLayout);*/
    setLayout(gridLayout);
    connect(file,
            SIGNAL(clicked(bool)),
            this, SLOT(file_set()));
    connect(genReports,
            SIGNAL(clicked(bool)),
            this, SLOT(genReports_set()));
    connect(Logs,
            SIGNAL(clicked(bool)),
            this, SLOT(Logs_set()));
    connect(ActLog,
            SIGNAL(clicked(bool)),
            this, SLOT(ActLog_set()));
    connect(AudLog,
            SIGNAL(clicked(bool)),
            this, SLOT(AudLog_set()));
    connect(loadForm,
            SIGNAL(clicked(bool)),
            this, SLOT(loadForm_set()));
    connect(formList,
            SIGNAL(clicked(bool)),
            this, SLOT(formList_set()));

    connect(Settings,
            SIGNAL(clicked(bool)),
            this, SLOT(Settings_set()));
    connect(edittab,
            SIGNAL(clicked(bool)),
            this, SLOT(changePage1()));
    connect(genf,
            SIGNAL(clicked(bool)),
            this, SLOT(changePage2()));
    connect(cData->tab1,
            SIGNAL(clicked(bool)),
            this, SLOT(changeTab1()));
    connect(cData->tab2,
            SIGNAL(clicked(bool)),
            this, SLOT(changeTab2()));
    connect(cData->add1, SIGNAL(clicked()), tablepage, SLOT(open_win1()));
    connect(cData->edit1, SIGNAL(clicked()),  tablepage, SLOT(open_win11()));
    connect(cData->rem1, SIGNAL(clicked()),  tablepage, SLOT(remove_selected1()));
    connect(cData->add_area2, SIGNAL(clicked()), tablepage, SLOT(open_win3()));
    connect(cData->rem_area2, SIGNAL(clicked()),  tablepage, SLOT(remove_selected3()));
    connect(cData->add_loc2, SIGNAL(clicked()), tablepage, SLOT(open_win4()));
    connect(cData->edit2, SIGNAL(clicked()), tablepage, SLOT(open_win44()));
    connect(cData->rem_loc2, SIGNAL(clicked()),  tablepage, SLOT(remove_selected4()));
    connect(cData->genff, SIGNAL(clicked()),genpage , SLOT(gen_forms()));
    connect(cData->printforms, SIGNAL(clicked()), genpage, SLOT(print_forms()));


    //  edittab->setText(tr("Edit Database │ ▼"));


}

void SettingsTab::createIcons()
{

    QFont font;
    font.setBold(true);


    /*QListWidgetItem *configButton = new QListWidgetItem(contentsWidget);
    configButton->setIcon(QIcon(":/images/lang_small.png"));
    configButton->setFont(font);
    configButton->setText(tr("Set Language"));
    configButton->setTextAlignment(Qt::AlignCenter);
    configButton->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);*/
    /* QTreeWidget *tree=new QTreeWidget;
   tree->setColumnCount(1);


QTreeWidgetItem *item1=new QTreeWidgetItem;
QTreeWidgetItem *item2=new QTreeWidgetItem;
item1->setText(0,"Edit Database");
item1->setIcon(0,QIcon(":/images/table-edit-icon.png"));
item2->setText(0,"Generate forms");
item2->setIcon(0,QIcon(":/images/gen.png"));
tree->addTopLevelItem(item1);
tree->addTopLevelItem(item2);*/


    /* QListWidgetItem *updateButton = new QListWidgetItem(contentsWidget);
    updateButton->setIcon(QIcon(":/images/table-edit-icon.png"));
    updateButton->setText(tr("Edit Database"));
    updateButton->setFont(font);
    updateButton->setTextAlignment(Qt::AlignCenter);
    updateButton->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);



    QListWidgetItem *genb = new QListWidgetItem(contentsWidget);
    genb->setIcon(QIcon(":/images/gen.png"));
    genb->setText(tr("Generate Forms"));
    genb->setFont(font);
    genb->setTextAlignment(Qt::AlignCenter);
    genb->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);*/

    /*  QListWidgetItem *queryButton = new QListWidgetItem(contentsWidget);
    queryButton->setIcon(QIcon(":/images/preview.png"));
    queryButton->setText(tr("Preview & Print"));
    queryButton->setFont(font);
    queryButton->setTextAlignment(Qt::AlignCenter);
    queryButton->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);*/



    /* connect(contentsWidget,
            SIGNAL(currentItemChanged(QListWidgetItem*,QListWidgetItem*)),
            this, SLOT(changePage(QListWidgetItem*,QListWidgetItem*)));*/

}

void SettingsTab::changePage(QListWidgetItem *current, QListWidgetItem *previous)
{
    if (!current)
        current = previous;

    pagesWidget->setCurrentIndex(contentsWidget->row(current));


}
void SettingsTab::changePage1()
{
    genf->deactivate();




    if (cData->tab1->isVisible()==false)
    {
        pagesWidget->setCurrentIndex(0);
        cData->tableStack->setCurrentIndex(0);
        setInvisible1();
        cData->tab1->activate2();
        cData->tab1->setVisible(true);
        cData->tab2->setVisible(true);
        cData-> edit1->setVisible(true);
        cData->add1->setVisible(true);
        cData->rem1->setVisible(true);
        cData->edit2->setVisible(false);
        cData->rem_area2->setVisible(false);
        cData->rem_loc2->setVisible(false);
        cData->add_area2->setVisible(false);
        cData->add_loc2->setVisible(false);
        cData->filterCombo1->setVisible(true);
        cData->filterEdit1->setVisible(true);
        cData->filterButton1->setVisible(true);
        cData->filterCombo4->setVisible(false);
        cData->filterEdit4->setVisible(false);
        cData->filterButton4->setVisible(false);

        edittab->setText(tr("Edit Database │ ▼"));


    }else
    {
        pagesWidget->setCurrentIndex(2);
        setInvisible1();
        cData->tab1->setVisible(false);
        cData->tab2->setVisible(false);

        //edittab->deactivate();
        edittab->setText(tr("Edit Database │ ►"));
    }
    edittab->activate1();



}
void SettingsTab::changePage2()
{
    setInvisible1();
    edittab->deactivate();
    pagesWidget->setCurrentIndex(1);
    genf->activate1();

    //edittab->setText(tr("Edit Database"));
    //edittab->deactivate();

    edittab->setVisible(true);
    genf->setVisible(true);
    cData->genff->setVisible(true);
    cData->printforms->setVisible(true);
    cData-> edit1->setVisible(false);
    cData->add1->setVisible(false);
    cData->rem1->setVisible(false);
    cData->edit2->setVisible(false);
    cData->rem_area2->setVisible(false);
    cData->rem_loc2->setVisible(false);
    cData->add_area2->setVisible(false);
    cData->add_loc2->setVisible(false);


}
void SettingsTab::changeTab1()
{

    cData->tab1->activate2();
    cData->tab2->deactivate();
    pagesWidget->setCurrentIndex(0);
    cData->tableStack->setCurrentIndex(0);
    cData-> edit1->setVisible(true);
    cData->add1->setVisible(true);
    cData->rem1->setVisible(true);
    cData->edit2->setVisible(false);
    cData->rem_area2->setVisible(false);
    cData->rem_loc2->setVisible(false);
    cData->add_area2->setVisible(false);
    cData->add_loc2->setVisible(false);
    cData->genff->setVisible(false);
    cData->printforms->setVisible(false);
    cData->filterCombo1->setVisible(true);
    cData->filterEdit1->setVisible(true);
    cData->filterButton1->setVisible(true);
    cData->filterCombo4->setVisible(false);
    cData->filterEdit4->setVisible(false);
    cData->filterButton4->setVisible(false);


}
void SettingsTab::changeTab2()
{

    cData->tab1->deactivate();
    cData->tab2->activate2();
    pagesWidget->setCurrentIndex(0);
    cData->tableStack->setCurrentIndex(1);
    cData-> edit1->setVisible(false);
    cData->add1->setVisible(false);
    cData->rem1->setVisible(false);
    cData->edit2->setVisible(true);
    cData->rem_area2->setVisible(true);
    cData->rem_loc2->setVisible(true);
    cData->add_area2->setVisible(true);
    cData->add_loc2->setVisible(true);
    cData->genff->setVisible(false);
    cData->printforms->setVisible(false);
    cData->filterCombo1->setVisible(false);
    cData->filterEdit1->setVisible(false);
    cData->filterButton1->setVisible(false);
    cData->filterCombo4->setVisible(true);
    cData->filterEdit4->setVisible(true);
    cData->filterButton4->setVisible(true);

}
void SettingsTab::file_set()
{
    //setInvisible();

    pagesWidget->setCurrentIndex(2);

    if (loadForm->isVisible()==false)
    {
        setInvisible();
        loadForm->setVisible(true);
        formList->setVisible(true);
        file->setText(tr(" File │ ▼"));


    }else
    {
        setInvisible();

        file->setText(tr(" File │ ►"));;
        file->deactivate();
    }
    file->activate();

}
void SettingsTab::loadForm_set()
{
    loadForm->activate1();
    formList->deactivate();
}
void SettingsTab::formList_set()
{
    formList->activate1();
    loadForm->deactivate();
}
void SettingsTab::genReports_set()
{
    pagesWidget->setCurrentIndex(2);
    setInvisible();
    genReports->activate();

}
void SettingsTab::Logs_set()
{
    pagesWidget->setCurrentIndex(2);
    if (ActLog->isVisible()==false)
    {
        setInvisible();
        ActLog->setVisible(true);
        AudLog->setVisible(true);
        Logs->setText(tr(" Logs │ ▼"));


    }else
    {
        setInvisible();

        Logs->setText(tr(" Logs │ ►"));;
        Logs->deactivate();
    }
    Logs->activate();
}
void SettingsTab::ActLog_set()
{
    ActLog->activate1();
    AudLog->deactivate();
}
void SettingsTab::AudLog_set()
{
    AudLog->activate1();
    ActLog->deactivate();
}
void SettingsTab::Settings_set()
{
    pagesWidget->setCurrentIndex(2);
    if (edittab->isVisible()==false)
    {
        setInvisible();
        edittab->setVisible(true);
        genf->setVisible(true);
        //cData->tab1->setVisible(true);
        //cData->tab2->setVisible(true);
        Settings->setText(tr(" Settings │ ▼"));


    }else
    {
        setInvisible();

        Settings->setText(tr(" Settings │ ►"));;
        Settings->deactivate();
    }
    Settings->activate();
}
void SettingsTab::setInvisible()
{


    loadForm->setVisible(false);
    formList->setVisible(false);
    ActLog->setVisible(false);
    AudLog->setVisible(false);
    edittab->setVisible(false);
    genf->setVisible(false);
    cData->tab1->setVisible(false);
    cData->tab2->setVisible(false);
    cData-> edit1->setVisible(false);
    cData->add1->setVisible(false);
    cData->rem1->setVisible(false);
    cData->edit2->setVisible(false);
    cData->rem_area2->setVisible(false);
    cData->rem_loc2->setVisible(false);
    cData->add_area2->setVisible(false);
    cData->add_loc2->setVisible(false);
    cData->genff->setVisible(false);
    cData->printforms->setVisible(false);
    cData->filterCombo1->setVisible(false);
    cData->filterEdit1->setVisible(false);
    cData->filterButton1->setVisible(false);
    cData->filterCombo4->setVisible(false);
    cData->filterEdit4->setVisible(false);
    cData->filterButton4->setVisible(false);
    edittab->setText("Edit Database │ ►");

    file->setText(" File │ ►");

    Logs->setText(" Logs │ ►");

    // Settings->setText(" Settings │ ►");
    edittab->deactivate();

    genf->deactivate();
    file->deactivate();
    Logs->deactivate();
    Settings->deactivate();
    genReports->deactivate();
    cData->tab1->deactivate();
    cData->tab2->deactivate();
    formList->deactivate();
    loadForm->deactivate();
    AudLog->deactivate();
    ActLog->deactivate();

}
void SettingsTab::setInvisible1()
{


    loadForm->setVisible(false);
    formList->setVisible(false);
    ActLog->setVisible(false);
    AudLog->setVisible(false);
    //edittab->setVisible(false);
    //genf->setVisible(false);
    cData->tab1->setVisible(false);
    cData->tab2->setVisible(false);
    cData-> edit1->setVisible(false);
    cData->add1->setVisible(false);
    cData->rem1->setVisible(false);
    cData->edit2->setVisible(false);
    cData->rem_area2->setVisible(false);
    cData->rem_loc2->setVisible(false);
    cData->add_area2->setVisible(false);
    cData->add_loc2->setVisible(false);
    cData->genff->setVisible(false);
    cData->printforms->setVisible(false);
    cData->filterCombo1->setVisible(false);
    cData->filterEdit1->setVisible(false);
    cData->filterButton1->setVisible(false);
    cData->filterCombo4->setVisible(false);
    cData->filterEdit4->setVisible(false);
    cData->filterButton4->setVisible(false);
    edittab->setText("Edit Database │ ►");

    file->setText(" File │ ►");

    Logs->setText(" Logs │ ►");

    //Settings->setText(" Settings │ ►");
    edittab->deactivate();
    genf->deactivate();
    file->deactivate();
    Logs->deactivate();
    //Settings->deactivate();
    genReports->deactivate();
    cData->tab1->deactivate();
    cData->tab2->deactivate();

}

//! [8]


