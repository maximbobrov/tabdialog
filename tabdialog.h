
#ifndef TABDIALOG_H
#define TABDIALOG_H

#include <QDialog>
#include <QMainWindow>
#include <QListWidget>
#include <QStackedWidget>

#include <QLayout>
#include <QGroupBox>
#include "pages.h"
#include "commondata.h"
#include "mycoolbutton.h"
QT_BEGIN_NAMESPACE
class QDialogButtonBox;
class QFileInfo;
class QTabWidget;
class QListWidget;
class QListWidgetItem;
class QStackedWidget;
QT_END_NAMESPACE

class ValidateTab : public QWidget
{
    Q_OBJECT

public:
    commonData * cData;
    ValidateTab(QWidget *parent = 0,commonData * Data=0);
};

class SettingsTab : public QWidget
{
    Q_OBJECT

public:

    GenerateFormsPage * genpage ;
    EditTablesPage * tablepage;
    commonData * cData;
    myCoolButton *edittab;
    myCoolButton *genf;
    myCoolButton *file;
    myCoolButton *loadForm;
    myCoolButton *formList;
    myCoolButton *genReports;
    myCoolButton *Logs;
    myCoolButton *ActLog;
    myCoolButton *AudLog;
    myCoolButton *Settings;

    /* QPushButton *tab1;
    QPushButton *edit1;
    QPushButton *rem1;
    QPushButton *add1;
    QPushButton *tab2;
    QPushButton *edit2;
    QPushButton *rem_area2;
       QPushButton *rem_loc2;
    QPushButton *add_area2;
       QPushButton *add_loc2;*/
    SettingsTab(QWidget *parent = 0, commonData * Data=0);
public slots:
    void setInvisible();
    void setInvisible1();
    void changePage(QListWidgetItem *current, QListWidgetItem *previous);
    void changePage1();
    void changePage2();
    void changeTab1();
    void changeTab2();
    void file_set();
    void loadForm_set();
    void formList_set();
    void genReports_set();
    void Logs_set();
    void ActLog_set();
    void AudLog_set();
    void Settings_set();

private:
    void createIcons();

    QListWidget *contentsWidget;
    QStackedWidget *pagesWidget;

};

class TabDialog : public QMainWindow
{
    Q_OBJECT

public:
    commonData * cData;
    explicit TabDialog(QWidget *parent = 0);

    ~TabDialog();
private:
    void createActions();
    void createMenus();

    QMenu *fileMenu;
    QMenu *editMenu;

    QMenu *helpMenu;

    QAction *newAct;
    QAction *openAct;
    QAction *saveAct;
    QAction *printAct;
    QAction *exitAct;
    QTabWidget *tabWidget;
    QDialogButtonBox *buttonBox;

};

#endif
