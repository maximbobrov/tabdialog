#include "pages.h"
#include "dialog.h"
#include <QListWidget>
#include <QDebug>
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

void EditTablesPage::selecting1(QModelIndex a)
{

    tableView1->selectRow(a.row());
    data->selected_row1=a.row();
    int rc2=my_database_model2->rowCount();
    for (int i=0;i<rc2;i++)
    {
        if(my_database_model2->data(my_database_model2->index(i,0))==my_database_model1->data(my_database_model1->index(a.row(),0)))
        {

            tableView2->selectRow(i);
            data->selected_row2=i;
        }
    }




}
void EditTablesPage::selecting2(QModelIndex a)
{

    tableView2->selectRow(a.row());
    data->selected_row2=a.row();
    int rc2=my_database_model1->rowCount();
    for (int i=0;i<rc2;i++)
    {
        if(my_database_model1->data(my_database_model1->index(i,0))==my_database_model2->data(my_database_model2->index(a.row(),0)))
        {

            tableView1->selectRow(i);
            data->selected_row1=i;
        }
    }



}
void EditTablesPage::selecting3(QModelIndex a)
{

    tableView3->selectRow(a.row());
    data->selected_row3=a.row();
    QString query=QString(" %1 = \'%2\'").arg(filterCombo4->currentText()).arg(my_database_model3->data(my_database_model3->index(a.row(),0)).toInt());
    qDebug()<<query<<endl;
    my_database_model4->setFilter(query);
    int c=0;
    int rc2=my_database_model4->rowCount();
    for (int i=0;i<rc2;i++)
    {
        if(my_database_model4->data(my_database_model4->index(i,0))==my_database_model3->data(my_database_model3->index(a.row(),0)))
        {
            if(c==0)
            {
                tableView4->selectRow(i);
                data->selected_row4=i;
                c++;
            }
        }
    }



}
void EditTablesPage::selecting4(QModelIndex a)
{

    tableView4->selectRow(a.row());
    data->selected_row4=a.row();
    int rc2=my_database_model3->rowCount();
    for (int i=0;i<rc2;i++)
    {
        if(my_database_model3->data(my_database_model3->index(i,0))==my_database_model4->data(my_database_model4->index(a.row(),0)))
        {

            tableView3->selectRow(i);
            data->selected_row3=i;
        }
    }



}
void EditTablesPage::filter1()
{
    if (filterEdit1->text().length()>0)
    {

        QString query=QString(" %1 = \'%2\'").arg(filterCombo1->currentText()).arg(filterEdit1->text());
        qDebug()<<query<<endl;
        my_database_model1->setFilter(query);
    }else
    {
        my_database_model1->setFilter(QString(""));
    }
    //my_database_model->setSort(2, Qt::DescendingOrder);
    my_database_model1->select();

}
void EditTablesPage::filter2()
{
    if (filterEdit2->text().length()>0)
    {

        QString query=QString(" %1 = \'%2\'").arg(filterCombo2->currentText()).arg(filterEdit2->text());
        qDebug()<<query<<endl;
        my_database_model2->setFilter(query);
    }else
    {
        my_database_model2->setFilter(QString(""));
    }
    //my_database_model->setSort(2, Qt::DescendingOrder);
    my_database_model2->select();

}

void EditTablesPage::filter3()
{
    if (filterEdit3->text().length()>0)
    {

        QString query=QString(" %1 = \'%2\'").arg(filterCombo3->currentText()).arg(filterEdit3->text());
        qDebug()<<query<<endl;
        my_database_model3->setFilter(query);
    }else
    {
        my_database_model3->setFilter(QString(""));
    }
    //my_database_model->setSort(2, Qt::DescendingOrder);
    my_database_model3->select();

}
void EditTablesPage::filter4()
{
    if (filterEdit4->text().length()>0)
    {

        QString query=QString(" %1 = \'%2\'").arg(filterCombo4->currentText()).arg(filterEdit4->text());
        qDebug()<<query<<endl;
        my_database_model4->setFilter(query);
    }else
    {
        my_database_model4->setFilter(QString(""));
    }
    //my_database_model->setSort(2, Qt::DescendingOrder);
    my_database_model4->select();

}

void EditTablesPage::update_data ( const QModelIndex &, const QModelIndex &)
{


    // qDebug()<<"DATA CHANGED"<<endl;
    // data->num_form_label->setText();
    data->comboloc->clear();
    data->comboform->clear();
    QSqlQuery * query = new QSqlQuery(data->db);
    query->setForwardOnly(true);
    query->exec( "SELECT number_of_area, location_number, number_of_users FROM locations_table;");

    int total_users=0;
    int total_locs=0;
    while(query->next())
    {
        bool isok;

        int users=query->value(2).toInt(&isok);
        data->comboloc->addItem(QString("Area:")+ QString::number(query->value(0).toInt(&isok))+QString(" Loc:")+ QString::number(query->value(1).toInt(&isok)));
        data->area_loc[total_locs]=query->value(0).toInt(&isok)+query->value(1).toInt(&isok)*10000;

        if (isok) total_users+=users;
        total_locs++;
    }



    QSqlQuery * query_forms = new QSqlQuery(data->db);
    query_forms->setForwardOnly(true);
    query_forms->exec( "SELECT number, description FROM form_type_table;");

    int forms_num=0;
    while(query_forms->next())
    {



        data->comboform->addItem(QString("Number:")+ QString(query_forms->value(0).toString())+QString(" Descr:")+ QString(query_forms->value(1).toString()));
        if (forms_num<100)
        {
            data->forms_numbers[forms_num]=query_forms->value(0).toInt();
            data->forms_names[forms_num]=query_forms->value(1).toString();
        }
        forms_num++;

    }

    data->num_form_label->setText(QString("Locations: %1").arg(total_locs));
    data->total_num_label->setText(QString("Total Forms Number: %1").arg(forms_num*total_users));

    delete query;
    delete query_forms;




}
void EditTablesPage::open_win3()
{

    data->num_area=my_database_model3->rowCount()+1;
    data->status=true;
    ui1->my_show();

}
void EditTablesPage::open_win4()
{
    QModelIndexList selection = tableView3->selectionModel()->selectedIndexes();

    if(selection.count()!=0)
    {
        data->num_area=my_database_model3->data(my_database_model3->index(data->selected_row3,0)).toInt();
        data->area=my_database_model3->data(my_database_model3->index(data->selected_row3,1)).toString();
        /*int rc2=my_database_model3->rowCount();
        for (int i=0;i<rc2;i++)
        {
            if(my_database_model3->data(my_database_model3->index(i,0))==my_database_model4->data(my_database_model4->index(data->selected_row3,0)))
            {
                data->num_area=my_database_model3->data(my_database_model3->index(i,0)).toInt();
                data->area=my_database_model3->data(my_database_model3->index(i,1)).toString();

            }
        }*/
        int k=0;
        int rc1=my_database_model4->rowCount();
        for (int i=0;i<rc1;i++)
        {
            if(my_database_model4->data(my_database_model4->index(i,0))==data->num_area)
            {

                k++;
            }
        }
        data->locat=k+1;


        //data->area=my_database_model3->data(my_database_model3->index(i,1)).toString();
        data->status=true;
        ui2->my_show();
    }



}
void EditTablesPage::open_win33()
{
    int a;
    for(int i=0;i<my_database_model3->rowCount();i++)
    {
        if(my_database_model3->header_checked[i]==true)
        {
            a=i;
        }
    }
    data->num_area=my_database_model3->data(my_database_model3->index(data->selected_row3,0)).toInt();
    data->area=my_database_model3->data(my_database_model3->index(data->selected_row3,1)).toString();



    data->status=false;

    ui1->my_show();


}
void EditTablesPage::open_win44()
{
    int a;
    for(int i=0;i<my_database_model4->rowCount();i++)
    {
        if(my_database_model4->header_checked[i]==true)
        {
            a=i;
        }
    }


    int rc2=my_database_model3->rowCount();
    for (int i=0;i<rc2;i++)
    {
        if(my_database_model3->data(my_database_model3->index(i,0))==my_database_model4->data(my_database_model4->index(data->selected_row4,0)))
        {
            data->area=my_database_model3->data(my_database_model3->index(i,1)).toString();

        }
    }
    data->num_area=my_database_model4->data(my_database_model4->index(data->selected_row4,0)).toInt();
    data->locat=my_database_model4->data(my_database_model4->index(data->selected_row4,1)).toInt();
    data->users=my_database_model4->data(my_database_model4->index(data->selected_row4,2)).toInt();
    data->disk=my_database_model4->data(my_database_model4->index(data->selected_row4,3)).toString();


    data->status=false;

    ui2->my_show();


}
void EditTablesPage::open_win1()
{
    data->num_que=my_database_model1->rowCount()+1;
    data->status=true;
    ui->my_show();
    //ui->show();

}

void EditTablesPage::check_headers1()
{
    my_database_model1->check_headers();
    my_database_model2->check_headers();


}
void EditTablesPage::uncheck_headers1()
{
    my_database_model1->uncheck_headers();
    my_database_model2->uncheck_headers();
}
void EditTablesPage::remove_selected1()
{

    for(int j=0;j<my_database_model1->rowCount();j++)
    {
        if(my_database_model2->data(my_database_model2->index(j,0))==my_database_model1->data(my_database_model1->index(data->selected_row1,0)))
        {
             my_database_model2->removeRow(j);
        }
    }
my_database_model1->setFilter(QString(""));
my_database_model2->setFilter(QString(""));
    for(int j=0;j<my_database_model2->rowCount();j++)
    {
        if(my_database_model2->data(my_database_model2->index(j,0))>my_database_model1->data(my_database_model1->index(data->selected_row1,0)))
        {

               int a;
               a= my_database_model2->data(my_database_model2->index(j,0)).toInt();
                my_database_model2->setData(my_database_model2->index(j,0), a-1);


        }
    }
    for(int j=0;j<my_database_model1->rowCount();j++)
    {
        if(my_database_model1->data(my_database_model1->index(j,0))>my_database_model1->data(my_database_model1->index(data->selected_row1,0)))
        {

               int a;
               a= my_database_model1->data(my_database_model1->index(j,0)).toInt();
                my_database_model1->setData(my_database_model1->index(j,0), a-1);


        }
    }



     my_database_model1->removeRow(data->selected_row1);
    my_database_model2->submitAll();
    my_database_model2->select();
    my_database_model1->submitAll();
    my_database_model1->select();
}
void EditTablesPage::handle_section_clicked(int i)
{
    my_database_model1->handle_section_clicked(i);
    my_database_model2->handle_section_clicked(i);
}
void EditTablesPage::handle_section_clicked3(int i)
{
    my_database_model3->handle_section_clicked(i);
    if (my_database_model3->header_checked[i]==true)
    {

        QString query=QString(" %1 = \'%2\'").arg(filterCombo4->currentText()).arg(my_database_model3->data(my_database_model3->index(i,0)).toInt());
        qDebug()<<query<<endl;
        my_database_model4->setFilter(query);
    }else
    {
        my_database_model4->setFilter(QString(""));

    }
    //my_database_model->setSort(2, Qt::DescendingOrder);
    my_database_model4->select();


}


void EditTablesPage::open_win11()
{
    int a;
    for(int i=0;i<my_database_model1->rowCount();i++)
    {
        if(my_database_model1->header_checked[i]==true)
        {
            a=i;
        }
    }
    data->que=my_database_model1->data(my_database_model1->index(data->selected_row1,1)).toString();

    int rc2=my_database_model2->rowCount();
    for (int i=0;i<rc2;i++)
    {
        if(my_database_model2->data(my_database_model2->index(i,0))==my_database_model1->data(my_database_model1->index(data->selected_row1,0)))
        {
            data->num_que=my_database_model2->data(my_database_model2->index(i,0)).toInt();
            data->answer=my_database_model2->data(my_database_model2->index(i,1)).toInt();
            data->comm_answer=my_database_model2->data(my_database_model2->index(i,2)).toString();

        }
    }

    data->status=false;

    ui->my_show();
    //ui->show();

}
void EditTablesPage::add_row1()
{
    //my_database_model->insertRows(my_database_model->rowCount(), 1);

    // QString qs;


    int rc1=my_database_model1->rowCount();
    QVariant qv1(rc1+1);



    my_database_model1->insertRow(rc1);


    my_database_model1->setData(my_database_model1->index(rc1,0), data->num_que);
    my_database_model1->setData(my_database_model1->index(rc1,1), data->que);


    my_database_model1->submitAll();

    int rc2=my_database_model2->rowCount();
    QVariant qv2(rc2+1);

    my_database_model2->insertRow(rc2);
    my_database_model2->setData(my_database_model2->index(rc2,0), data->num_que);
    my_database_model2->setData(my_database_model2->index(rc2,1), data->answer);
    my_database_model2->setData(my_database_model2->index(rc2,2), data->comm_answer);


    my_database_model2->submitAll();

    //  my_database_model->select();
}
void EditTablesPage::update_row1()
{
    //my_database_model->insertRows(my_database_model->rowCount(), 1);

    // QString qs;
    int a;
    for(int i=0;i<my_database_model1->rowCount();i++)
    {
        if(my_database_model1->header_checked[i]==true)
        {
            a=i;
        }
    }


    /* QModelIndexList selection = tableView1->selectionModel()->selectedIndexes();


    for(int i=0; i< selection.count(); i++)
    {
        QModelIndex index = selection.at(i);
        if(my_database_model1->header_checked[i]==0)
        {*/
    int rc2=my_database_model2->rowCount();
    for (int i=0;i<rc2;i++)
    {
        if(my_database_model2->data(my_database_model2->index(i,0))==my_database_model1->data(my_database_model1->index(data->selected_row1,0)))
        {
            my_database_model2->setData(my_database_model2->index(i,0), data->num_que);
            my_database_model2->setData(my_database_model2->index(i,1), data->answer);
            my_database_model2->setData(my_database_model2->index(i,2), data->comm_answer);
            my_database_model2->submitAll();
            my_database_model2->select();
        }
    }
    my_database_model1->header_checked[a]=false;
    my_database_model1->setData(my_database_model1->index(data->selected_row1,0), data->num_que);
    my_database_model1->setData(my_database_model1->index(data->selected_row1,1), data->que);
    my_database_model1->submitAll();
    my_database_model1->select();


    /*QModelIndexList selection = tableView1->selectionModel()->selectedIndexes();

    for(int i=0; i< selection.count(); i++)
    {
        QModelIndex index = selection.at(i);
        if(my_database_model1->header_checked[i]==0)
            my_database_model1->removeRows(index.row(), 1);
    }
    my_database_model1->submitAll();
    my_database_model1->select();*/

}
void EditTablesPage::update_row3()
{
    int a;
    for(int i=0;i<my_database_model3->rowCount();i++)
    {
        if(my_database_model3->header_checked[i]==true)
        {
            a=i;
        }
    }



    my_database_model3->header_checked[a]=false;


    my_database_model3->setData(my_database_model1->index(data->selected_row3,0), data->num_area);
    my_database_model3->setData(my_database_model1->index(data->selected_row3,1), data->area);
    my_database_model3->submitAll();
    my_database_model3->select();




}
void EditTablesPage::update_row4()
{
    int a;
    for(int i=0;i<my_database_model4->rowCount();i++)
    {
        if(my_database_model4->header_checked[i]==true)
        {
            a=i;
        }
    }



    my_database_model4->header_checked[a]=false;
    int rc=my_database_model3->rowCount();

    // my_database_model4->setData(my_database_model4->index(data->selected_row4,0), data->num_area);
    // my_database_model4->setData(my_database_model4->index(data->selected_row4,1), data->locat);
    my_database_model3->setData(my_database_model3->index(data->selected_row3,1), data->area);
    qDebug()<<"lol"<<my_database_model3->data(my_database_model3->index(data->selected_row3,1));
    my_database_model4->setData(my_database_model4->index(data->selected_row4,2), data->users);
    my_database_model4->setData(my_database_model4->index(data->selected_row4,3), data->disk);
    my_database_model4->submitAll();
    my_database_model4->select();



}
void EditTablesPage::add_row2()
{
    //my_database_model->insertRows(my_database_model->rowCount(), 1);

    // QString qs;

    int rc2=my_database_model2->rowCount();
    QVariant qv2(rc2+1);

    my_database_model2->insertRow(rc2);
    my_database_model2->setData(my_database_model2->index(rc2,0), qv2);

    my_database_model2->submitAll();

    int rc1=my_database_model1->rowCount();
    QVariant qv1(rc1+1);

    my_database_model1->insertRow(rc1);
    my_database_model1->setData(my_database_model1->index(rc1,0), qv1);

    my_database_model1->submitAll();

    //  my_database_model->select();
}
void EditTablesPage::add_row3()
{
    int rc=my_database_model3->rowCount();
        my_database_model3->insertRow(rc);
        //my_database_model3->setData(my_database_model3->index(rc,0), qv);
        my_database_model3->setData(my_database_model3->index(rc,0), data->num_area);
        my_database_model3->setData(my_database_model3->index(rc,1), data->area);

        my_database_model3->submitAll();
         tableView3->selectRow(rc);

    //  my_database_model->select();
}
void EditTablesPage::filt_all()
{
    my_database_model4->setFilter(QString(""));
}
void EditTablesPage::add_row4()
{
    int rc=my_database_model4->rowCount();

    my_database_model4->insertRow(rc);
    //my_database_model3->setData(my_database_model3->index(rc,0), qv);
    my_database_model4->setData(my_database_model4->index(rc,0), data->num_area);
    my_database_model4->setData(my_database_model4->index(rc,1), data->locat);
    my_database_model4->setData(my_database_model4->index(rc,2), data->users);
    my_database_model4->setData(my_database_model4->index(rc,3), data->disk);

    my_database_model4->submitAll();
    tableView4->selectRow(rc);


}
void EditTablesPage::sorting1(int ind)
{
    //int rc=columnCount();
    if (sortnumber1)
    {
        my_database_model1->setSort(ind,Qt::AscendingOrder);
        sortnumber1=false;
         my_database_model1->select();
        my_database_model1->submitAll();


    }
    else
    {
        my_database_model1->setSort(ind,Qt::DescendingOrder);
        sortnumber1=true;
        my_database_model1->submitAll();
        my_database_model1->select();
    }

}
void EditTablesPage::sorting2(int ind)
{
    //int rc=columnCount();
    if (sortnumber2)
    {
        my_database_model2->setSort(ind,Qt::AscendingOrder);
        sortnumber2=false;
        my_database_model2->submitAll();
        my_database_model2->select();
    }
    else
    {
        my_database_model2->setSort(ind,Qt::DescendingOrder);
        sortnumber2=true;
        my_database_model2->submitAll();
        my_database_model2->select();
    }


}
void EditTablesPage::sorting3(int ind)
{
    //int rc=columnCount();
    if (sortnumber3)
    {
        my_database_model3->setSort(ind,Qt::AscendingOrder);
        sortnumber3=false;
        my_database_model3->select();
        my_database_model3->submitAll();

    }
    else
    {
        my_database_model3->setSort(ind,Qt::DescendingOrder);
        sortnumber3=true;
        my_database_model3->select();
        my_database_model3->submitAll();

    }

}
void EditTablesPage::sorting4(int ind)
{
    //int rc=columnCount();
    if (sortnumber4)
    {
        my_database_model4->setSort(ind,Qt::AscendingOrder);
        sortnumber4=false;
        my_database_model4->submitAll();
        my_database_model4->select();
    }
    else
    {
        my_database_model4->setSort(ind,Qt::DescendingOrder);
        sortnumber4=true;
        my_database_model4->submitAll();
        my_database_model4->select();
    }

}
void EditTablesPage::remove_selected3()
{


    for(int j=0;j<my_database_model4->rowCount();j++)
    {
        if(my_database_model4->data(my_database_model4->index(j,0))==my_database_model3->data(my_database_model3->index(data->selected_row3,0)))
        {
             my_database_model4->removeRow(j);
        }
    }
my_database_model4->setFilter(QString(""));
    for(int j=0;j<my_database_model4->rowCount();j++)
    {
         //qDebug()<<"lolol="<<my_database_model4->data(my_database_model4->index(j,0)).toInt()<<";lol="<<my_database_model3->data(my_database_model3->index(data->selected_row3,0)).toInt();
        if(my_database_model4->data(my_database_model4->index(j,0))>my_database_model3->data(my_database_model3->index(data->selected_row3,0)))
        {

               int a;
               a= my_database_model4->data(my_database_model4->index(j,0)).toInt();
                my_database_model4->setData(my_database_model4->index(j,0), a-1);


        }
    }


    for(int j=0;j<my_database_model3->rowCount();j++)
    {
        if(my_database_model3->data(my_database_model3->index(j,0))>my_database_model3->data(my_database_model3->index(data->selected_row3,0)))
        {
            int a;
            a= my_database_model3->data(my_database_model3->index(j,0)).toInt();
             my_database_model3->setData(my_database_model3->index(j,0), a-1);
        }
    }


     my_database_model3->removeRow(data->selected_row3);
    my_database_model3->submitAll();
    my_database_model3->select();
    my_database_model4->submitAll();
    my_database_model4->select();

}
void EditTablesPage::remove_selected4()
{
my_database_model4->setFilter(QString(""));
    for(int j=0;j<my_database_model4->rowCount();j++)
    {
        if(my_database_model4->data(my_database_model4->index(j,0))==my_database_model4->data(my_database_model4->index(data->selected_row4,0)))
        {
            if(my_database_model4->data(my_database_model4->index(j,1))>my_database_model4->data(my_database_model4->index(data->selected_row4,1)))
            {
                int a;
                a= my_database_model4->data(my_database_model4->index(j,1)).toInt();
                 my_database_model4->setData(my_database_model4->index(j,1), a-1);

            }
        }
    }
     my_database_model4->removeRow(data->selected_row4);


    my_database_model4->submitAll();
    my_database_model4->select();

}
void EditTablesPage::remove_row1()
{

    QModelIndexList selection = tableView1->selectionModel()->selectedIndexes();

    for(int i=0; i< selection.count(); i++)
    {
        QModelIndex index = selection.at(i);
        if(my_database_model1->header_checked[i]==0)
            my_database_model1->removeRows(index.row(), 1);
    }
    my_database_model1->submitAll();
    my_database_model1->select();
}
void EditTablesPage::remove_row2()
{

    QModelIndexList selection = tableView2->selectionModel()->selectedIndexes();

    for(int i=0; i< selection.count(); i++)
    {
        QModelIndex index = selection.at(i);
        my_database_model2->removeRows(index.row(), 1);
    }
    my_database_model2->submitAll();
    my_database_model2->select();
}
void EditTablesPage::remove_row3()
{

    QModelIndexList selection = tableView3->selectionModel()->selectedIndexes();

    for(int i=0; i< selection.count(); i++)
    {
        QModelIndex index = selection.at(i);
        my_database_model3->removeRows(index.row(), 1);
    }
    my_database_model3->submitAll();
    my_database_model3->select();
}
void EditTablesPage::remove_row4()
{

    QModelIndexList selection = tableView4->selectionModel()->selectedIndexes();

    for(int i=0; i< selection.count(); i++)
    {
        QModelIndex index = selection.at(i);
        my_database_model4->removeRows(index.row(), 1);
    }
    my_database_model4->submitAll();
    my_database_model4->select();
}

void EditTablesPage::change_table1(const QString name)
{

    my_database_model1->setTable(name);
    filterEdit1->setText(QString(""));
    filter1();
    filterCombo1->clear();

    qDebug()<<"col count "<<my_database_model1->columnCount()<<endl;

    for (int i=0;i<my_database_model1->columnCount();i++)
        filterCombo1->addItem(my_database_model1->headerData(i, Qt::Horizontal).toString());


}
void EditTablesPage::change_table2(const QString name)
{

    my_database_model2->setTable(name);
    filterEdit2->setText(QString(""));
    filter2();
    filterCombo2->clear();

    qDebug()<<"col count "<<my_database_model2->columnCount()<<endl;

    for (int i=0;i<my_database_model2->columnCount();i++)
        filterCombo2->addItem(my_database_model2->headerData(i, Qt::Horizontal).toString());


}
void EditTablesPage::change_table3(const QString name)
{

    my_database_model3->setTable(name);
    filterEdit3->setText(QString(""));
    filter3();
    filterCombo3->clear();

    qDebug()<<"col count "<<my_database_model3->columnCount()<<endl;

    for (int i=0;i<my_database_model3->columnCount();i++)
        filterCombo3->addItem(my_database_model3->headerData(i, Qt::Horizontal).toString());


}
void EditTablesPage::change_table4(const QString name)
{

    my_database_model4->setTable(name);
    filterEdit4->setText(QString(""));
    filter4();
    filterCombo4->clear();

    qDebug()<<"col count "<<my_database_model4->columnCount()<<endl;

    for (int i=0;i<my_database_model4->columnCount();i++)
        filterCombo4->addItem(my_database_model4->headerData(i, Qt::Horizontal).toString());


}
