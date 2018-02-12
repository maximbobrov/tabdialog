
#ifndef TABDIALOG_H
#define TABDIALOG_H

#include <QDialog>
#include <QMainWindow>
#include <QListWidget>
#include <QStackedWidget>
#include <QPushButton>
#include <QLayout>
#include <QGroupBox>
#include "pages.h"
#include "commondata.h"
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
    SettingsTab(QWidget *parent = 0, commonData * Data=0);
public slots:
    void changePage(QListWidgetItem *current, QListWidgetItem *previous);

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
