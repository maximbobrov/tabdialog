#include "dialog2.h"





Dialog2::Dialog2(QWidget *parent, commonData *d)

{
    data=d;
    //data->comarea= new QComboBox;
    area=new QLineEdit("");
    locat= new QLineEdit("");
    users=new QLineEdit("");
     disk=new QLineEdit("");
   num_area=new QLineEdit("");
     area_l=new QLabel("Area");
     num_area_1=new QLabel("Number of area");
     locat_l=new QLabel("Number of location");
    users_l=new QLabel("Number of users");

     disk_l=new QLabel("Description");
    add_new =new QPushButton("Add");
    edit_new =new QPushButton("Edit");

    QGridLayout *packagesLayout = new QGridLayout;

    // packagesLayout->set;
    packagesLayout->addWidget(num_area_1, 0, 0,1,1);
     packagesLayout->addWidget(num_area, 1, 0,1,3);
     packagesLayout->addWidget(area_l, 2, 0,1,1);
      packagesLayout->addWidget(area, 3, 0,1,3);
    packagesLayout->addWidget(locat_l, 4, 0,1,1);
      packagesLayout->addWidget(locat, 5, 0,1,3);
        packagesLayout->addWidget(users_l, 6, 0,1,1);
          packagesLayout->addWidget(users, 7, 0,1,3);
          packagesLayout->addWidget( disk_l, 9, 0,1,1);
          packagesLayout->addWidget( disk, 10, 0,1,3);

          packagesLayout->addWidget( add_new, 14, 1,1,1);
          packagesLayout->addWidget( edit_new, 15, 1,1,1);
          setLayout(packagesLayout);
           connect(add_new, SIGNAL(clicked()), this, SLOT(update()));
           connect(edit_new, SIGNAL(clicked()), this, SLOT(update_edit()));




}

Dialog2::~Dialog2()
{

}
void Dialog2::my_show()
{
    status=data->status;
    if (status)
    {
        add_new->setVisible(true);
        edit_new->setVisible(false);
        num_area->setText(QString("%1").arg(data->num_area));
       num_area->setEnabled(false);
        area->setEnabled(false);
        locat->setEnabled(false);
        area->setText(data->area);
        locat->setText(QString("%1").arg(data->locat));
        users->setText("");
        disk->setText("");
    }
    if(!status)
    {
     add_new->setVisible(false);
     edit_new->setVisible(true);
     num_area->setText(QString("%1").arg(data->num_area));
      area->setText(data->area);
     num_area->setEnabled(false);
     area->setEnabled(true);
     locat->setEnabled(true);
     locat->setText(QString("%1").arg(data->locat));
     users->setText(QString("%1").arg(data->users));
     disk->setText(data->disk);
     //comm_answer->setText(data->discr);
    }
    this->show();
}
void Dialog2::update()
{
    data->area=area->text();
    data->locat=locat->text().toInt();
    data->users=users->text().toInt();
    data->disk=disk->text();
    //data->comm_answer=comm_answer->text();
    emit add();
this->close();

}
void Dialog2::update_edit()
{
   data->area=area->text();
   data->locat=locat->text().toInt();
    data->users=users->text().toInt();
    data->disk=disk->text();
    //data->comm_answer=comm_answer->text();
    emit edit();
this->close();

}
