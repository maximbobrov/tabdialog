#include "dialog.h"


Dialog::Dialog(QWidget *parent, commonData *d)

{
    data=d;
    num_que= new QLineEdit("11");
    que=new QLineEdit("Question1");
     answer=new QLineEdit("22");
     comm_answer=new QLineEdit("Description");
    num_que_l=new QLabel("Number of question");

     que_l=new QLabel("Question");
    answer_l=new QLabel("Value of record");
     comm_answer_l=new QLabel("Description");
    add_new =new myCoolButton("Add");
    edit_new =new myCoolButton("Edit");

    QGridLayout *packagesLayout = new QGridLayout;

    // packagesLayout->set;
    packagesLayout->addWidget(num_que_l, 0, 0,1,1);
      packagesLayout->addWidget(num_que, 1, 0,1,3);
        packagesLayout->addWidget(que_l, 3, 0,1,1);
          packagesLayout->addWidget(que, 4, 0,1,3);
          packagesLayout->addWidget( answer_l, 6, 0,1,1);
          packagesLayout->addWidget( answer, 7, 0,1,3);
          packagesLayout->addWidget( comm_answer_l, 9, 0,1,1);
          packagesLayout->addWidget( comm_answer, 10, 0,1,3);
          packagesLayout->addWidget( add_new, 13, 1,1,1);
          packagesLayout->addWidget( edit_new, 14, 1,1,1);
          setLayout(packagesLayout);
           connect(add_new, SIGNAL(clicked()), this, SLOT(update()));
           connect(edit_new, SIGNAL(clicked()), this, SLOT(update_edit()));




}

Dialog::~Dialog()
{

}
void Dialog::my_show()
{
    status=data->status;
    if (status)
       {
        add_new->setVisible(true);
        edit_new->setVisible(false);
        num_que->setText(QString("%1").arg(data->num_que));
        num_que->setEnabled(false);
        que->setText("");
         answer->setText("");
         comm_answer->setText("");

    }
    if(!status)
    {
      add_new->setVisible(false);
     edit_new->setVisible(true);
     num_que->setText(QString("%1").arg(data->num_que));
     num_que->setEnabled(false);
     que->setText(data->que);
      answer->setText(QString("%1").arg(data->answer));
      comm_answer->setText(data->comm_answer);

    }
    this->show();
}
void Dialog::update()
{

   data->num_que=num_que->text().toInt();
    data->que=que->text();
    data->answer=answer->text().toInt();
    data->comm_answer=comm_answer->text();
    emit add();
this->close();

}
void Dialog::update_edit()
{

   data->num_que=num_que->text().toInt();
    data->que=que->text();
    data->answer=answer->text().toInt();
    data->comm_answer=comm_answer->text();
    emit edit();
this->close();

}
