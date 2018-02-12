#include "mysqltablemodel.h"
#include <QPixmap>
#include <QStyle>
#include <QCommonStyle>

mySqlTableModel::mySqlTableModel(QObject *parent, QSqlDatabase db)
{
for (int i=0;i<4096;i++

     )
header_checked[i]=0;
}

bool mySqlTableModel::setHeaderData(int index, Qt::Orientation orient, const QVariant &val, int role)
{

    if(Qt::Vertical != orient)
       return QSqlTableModel::setHeaderData(index, orient, val, role);

    if (role==Qt::CheckStateRole)
       header_checked[index]=val.toBool();
    // storeCheckState(index, val);
     emit headerDataChanged(orient, index, index);
     return true;
}

QVariant mySqlTableModel::headerData(int index, Qt::Orientation o, int role) const
{

    if(Qt::Vertical != o)
        return QSqlTableModel::headerData(index, o, role);

      switch(role)
      {
        case Qt::DecorationRole:
        {
          QCommonStyle style;
          QPixmap p;
          if (header_checked[index]) p= style.standardIcon(QStyle::SP_DialogApplyButton).pixmap(14,14);
          else p= style.standardIcon(QStyle::SP_TitleBarMaxButton).pixmap(12,12);
        //  QStyle::standardPixmap(QStyle::SP_ArrowBack);
          //QPixmap p{12,12};
        //  p.fill(header_checked[index] ? Qt::green : Qt::red);
          return p;
         }
         break;
      //...
      }

      return QSqlTableModel::headerData(index, o, role);
}

void mySqlTableModel::uncheck_headers()
{
     int rc=rowCount();

for (int i=0;i<4096;i++)
{
    header_checked[i]=false;
}
emit headerDataChanged(Qt::Vertical,0,rc-1);
}

void mySqlTableModel::check_headers()
{  int rc=rowCount();
    for (int i=0;i<4096;i++)
    {
        header_checked[i]=true;
    }

    emit headerDataChanged(Qt::Vertical,0,rc-1);
}


void mySqlTableModel::remove_selected()
{

    int rc=rowCount();

    for (int i=rc-1;i>=0;i--)
    {
        if (header_checked[i])
        {
            removeRow(i);
            header_checked[i]=0;

            rc--;
         }


    }
submitAll();
  select();
    uncheck_headers();
}

void mySqlTableModel::handle_section_clicked(int indx)
{
   // QVariant index = QVariant(indx);
      this->setHeaderData(indx
                             , Qt::Vertical
                             , QVariant(!header_checked[indx])
                             , Qt::CheckStateRole);
}
