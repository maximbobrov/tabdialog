#include "dialog1.h"





Dialog1::Dialog1(QWidget *parent, commonData *d)

{
    data=d;
    num_area= new QLineEdit("11");
    area=new QLineEdit("Question1");
    num_area_l=new QLabel("Number of area");
    area_l=new QLabel("Area");
    add_new =new QPushButton("Add");
    edit_new =new QPushButton("Edit");
    QGridLayout *packagesLayout = new QGridLayout;

    packagesLayout->addWidget(num_area_l, 0, 0,1,1);
      packagesLayout->addWidget(num_area, 1, 0,1,3);
        packagesLayout->addWidget(area_l, 3, 0,1,1);
          packagesLayout->addWidget(area, 4, 0,1,3);
          //packagesLayout->addWidget( answer_l, 6, 0,1,1);
          //packagesLayout->addWidget( answer, 7, 0,1,3);
          //packagesLayout->addWidget( comm_answer_l, 9, 0,1,1);
          //packagesLayout->addWidget( comm_answer, 10, 0,1,3);
          packagesLayout->addWidget( add_new, 13, 1,1,1);
          packagesLayout->addWidget( edit_new, 14, 1,1,1);
          setLayout(packagesLayout);
           connect(add_new, SIGNAL(clicked()), this, SLOT(update()));
           connect(edit_new, SIGNAL(clicked()), this, SLOT(update_edit()));




}

Dialog1::~Dialog1()
{

}
void Dialog1::my_show()
{
    status=data->status;
    if (status)
       {
        add_new->setVisible(true);
        edit_new->setVisible(false);
        num_area->setText(QString("%1").arg(data->num_area));
        num_area->setEnabled(false);
        area->setText("");
         //answer->setText("");
         //comm_answer->setText("");

    }
    if(!status)
    {
      add_new->setVisible(false);
     edit_new->setVisible(true);
     num_area->setText(QString("%1").arg(data->num_area));
     area->setText(data->area);
     // answer->setText(QString("%1").arg(data->answer));
      //comm_answer->setText(data->comm_answer);

    }
    this->show();
}
void Dialog1::update()
{

   data->num_area=num_area->text().toInt();
    data->area=area->text();
    //data->answer=answer->text().toInt();
    //data->comm_answer=comm_answer->text();
    emit add();
this->close();

}
void Dialog1::update_edit()
{

   data->num_area=num_area->text().toInt();
    data->area=area->text();
   // data->answer=answer->text().toInt();
    //data->comm_answer=comm_answer->text();
    emit edit();
this->close();

}
