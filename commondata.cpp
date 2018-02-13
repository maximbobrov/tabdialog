#include "commondata.h"
#include "aes256.h"
#include <QDebug>
#include <QSqlQuery>


#define MIN(a,b) (((a)<(b))?(a):(b))
#define MAX(a,b) (((a)>(b))?(a):(b))

commonData::commonData(QObject *parent) : QObject(parent)
{


    db_name="database.sqlite";
    open_db();
    percent=0.1;



}

QString commonData::scypher(QString text)
{
 int sizeText =strlen( text.toUtf8().constData());
    aes256_context ctx;
    uint8_t key[32];
    uint8_t buf[16];
    uint8_t acc_buff[1024];
    char  acc_hex[1024];
    int acc_buff_size=0;
    char*  buf2;

    int i,j;
    /* put a test vector */
    j=0;

    //for ( i = 0; i < sizeof(key);i++) key[i] = i;
    //DUMP("key: ", key, sizeof(key));

    for ( i = 0; i < sizeof(key);i++)
    {
        if (i<aes256_key.length())
            key[i] = aes256_key.toLatin1().data()[i];
        else
            key[i]=0;

    }

    aes256_init(&ctx, key);

    for  (i = 0; i < sizeText;i++)
    {
        buf[j] =  (unsigned char)(text.toUtf8().constData()[i]);//text.toLatin1().constData()[i]);
        j++;
        if (j>=16)
        {

            // DUMP("txt: ", buf, sizeof(buf));
            aes256_encrypt_ecb(&ctx, buf);
            //DUMP("enc: ", buf, sizeof(buf));
            for (int k=0;k<16;k++)
            {
                acc_buff[acc_buff_size]=buf[k];
                acc_buff_size++;
            }
            j=0;
        }
    }

    if ((j>0)&&(j<16))
    {
        for (int jj=j;jj<16;jj++)
            buf[jj]=0;

        //DUMP("txt: ",  buf, sizeof(buf));
        aes256_encrypt_ecb(&ctx, buf);
        // DUMP("enc: ", buf, sizeof(buf));
        for (int k=0;k<16;k++)
        {
            acc_buff[acc_buff_size]=buf[k];
            acc_buff_size++;
        }
        j=0;
    }

    sprintf(acc_hex,"");
    for (int i=0;i<acc_buff_size;i++)
    {

        sprintf(acc_hex + strlen(acc_hex),"%02x",acc_buff[i]);
    }
    sizeText=strlen(acc_hex);
    //printf("AAAAAAAAAAAAAAAA %s %d \n",acc_hex,sizeText);
    QString out=to_base64(acc_buff,acc_buff_size);

    return out;
}



QString commonData::to_base64(unsigned char * in,int buffsize)
{

    char base64_chars[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

    QString res("");

    int i = 0;
    int j = 0;
    char char_array_3[1024];
    char char_array_4[1024];
    int in_len = buffsize;
    int pos = 0;

    while (in_len--)
    {
        char_array_3[i++] = in[pos++];
        if (i == 3)
        {
            char_array_4[0] = (char_array_3[0] & 0xfc) >> 2;
            char_array_4[1] = ((char_array_3[0] & 0x03) << 4) + ((char_array_3[1] & 0xf0) >> 4);
            char_array_4[2] = ((char_array_3[1] & 0x0f) << 2) + ((char_array_3[2] & 0xc0) >> 6);
            char_array_4[3] = char_array_3[2] & 0x3f;

            for (i = 0; (i <4) ; i++)
                res+= base64_chars[char_array_4[i]];
            i = 0;
        }
    }

    if (i>0)
    {
        for (j = i; j < 3; j++)
            char_array_3[j] = 0;

        char_array_4[0] = (char_array_3[0] & 0xfc) >> 2;
        char_array_4[1] = ((char_array_3[0] & 0x03) << 4) + ((char_array_3[1] & 0xf0) >> 4);
        char_array_4[2] = ((char_array_3[1] & 0x0f) << 2) + ((char_array_3[2] & 0xc0) >> 6);
        char_array_4[3] = char_array_3[2] & 0x3f;

        for (j = 0; (j < i + 1); j++)
            res += base64_chars[char_array_4[j]];

        while ((i++ < 3))
            res += '=';

    }


    return res;

}

void commonData::updateQRImage(QString text, int scypher, int index,int invert)
{
    int sizeText =strlen( text.toUtf8().constData());//text.size();
    qDebug()<<"text_size="<<sizeText<<endl;
   // ui->labelSizeText->setText( QString::number( sizeText ) );

    int levelIndex = index;
    int versionIndex = 0;
    bool bExtent = true;
    int maskIndex = -1;
    bool successfulEncoding=false;

    if (scypher==1)
    {
        /////adding the aes crypting:
        aes256_context ctx;
        uint8_t key[32];
        uint8_t buf[16];
        uint8_t acc_buff[1024];
        char  acc_hex[1024];
        int acc_buff_size=0;
        char*  buf2;

        int i,j;
        /* put a test vector */
        j=0;

        //for ( i = 0; i < sizeof(key);i++) key[i] = i;
        //DUMP("key: ", key, sizeof(key));

        for ( i = 0; i < sizeof(key);i++)
        {
            if (i<aes256_key.length())
                key[i] = aes256_key.toLatin1().data()[i];
            else
                key[i]=0;

        }

        aes256_init(&ctx, key);

        for  (i = 0; i < sizeText;i++)
        {
            buf[j] =  (unsigned char)(text.toUtf8().constData()[i]);//text.toLatin1().constData()[i]);
            j++;
            if (j>=16)
            {

                // DUMP("txt: ", buf, sizeof(buf));
                aes256_encrypt_ecb(&ctx, buf);
                //DUMP("enc: ", buf, sizeof(buf));
                for (int k=0;k<16;k++)
                {
                    acc_buff[acc_buff_size]=buf[k];
                    acc_buff_size++;
                }
                j=0;
            }
        }

        if ((j>0)&&(j<16))
        {
            for (int jj=j;jj<16;jj++)
                buf[jj]=0;

            //DUMP("txt: ",  buf, sizeof(buf));
            aes256_encrypt_ecb(&ctx, buf);
            // DUMP("enc: ", buf, sizeof(buf));
            for (int k=0;k<16;k++)
            {
                acc_buff[acc_buff_size]=buf[k];
                acc_buff_size++;
            }
            j=0;
        }

        sprintf(acc_hex,"");
        for (int i=0;i<acc_buff_size;i++)
        {

            sprintf(acc_hex + strlen(acc_hex),"%02x",acc_buff[i]);
        }
        sizeText=strlen(acc_hex);
        //printf("AAAAAAAAAAAAAAAA %s %d \n",acc_hex,sizeText);
        QString out=to_base64(acc_buff,acc_buff_size);
        qDebug()<<sizeText<<" "<<acc_buff_size<<" "<<out.size()<<" contains: "<<out<<endl;
        buf2=(char*)(acc_hex);



        aes256_done(&ctx);
        /////////////////////////////eo crypting
        buf2=(char*)(acc_hex);
        //  successfulEncoding = qrEncode.EncodeData( levelIndex, versionIndex, bExtent, maskIndex, buf2,acc_buff_size );
        successfulEncoding = qrEncode.EncodeData( levelIndex, versionIndex, bExtent, maskIndex,out.toLatin1().data(),out.size() );
    }
    else
    successfulEncoding = qrEncode.EncodeData( levelIndex, versionIndex, bExtent, maskIndex, text.toLatin1().data(),sizeText );
    if ( !successfulEncoding )
    {
      qDebug()<<"QR gen problem";
        return;
    }

    int qrImageSize = qrEncode.m_nSymbleSize;


    int encodeImageSize = qrImageSize + ( QR_MARGIN * 2 );
    QImage encodeImage( encodeImageSize, encodeImageSize, QImage::Format_Mono );


    int back=0;
    int fig=1;
            if (invert==1)
            {
                back=1;
                fig=0;
            }


        encodeImage.fill(back );

        for ( int i = 0; i < qrImageSize; i++ )
            for ( int j = 0; j < qrImageSize; j++ )
                if ( qrEncode.m_byModuleData[i][j] )
                    encodeImage.setPixel( i + QR_MARGIN, j + QR_MARGIN, fig );



        for ( int i = 0; i <  encodeImageSize; i++ )
            for ( int j = 0; j <  encodeImageSize; j++ )
                if((i==0)||(j==0)||(i== encodeImageSize-1)||(j== encodeImageSize-1))
                    encodeImage.setPixel( i , j , fig );



        eI=encodeImage;

}




void commonData::draw_number( QPainter &painter, int x, int y, int d, int val)
{

    QRect  rect;



    rect.setRect(x+2 , y+2, d-2,d-2 );




    painter.drawEllipse(rect);
    //painter.setPen(Qt::white);
    float coeff;

    if (val<10) coeff=1.2*1.2;
    if (val>=10) coeff=1.4*1.2;
    if (val>=100) coeff=1.75*1.2;

    QFont font("Tahoma",d/coeff);
    font.setPixelSize(d/coeff);
    painter.setFont(font);
    painter.drawText(rect, Qt::AlignCenter, QString::number(val));

}

void commonData::draw_label( QPainter &painter, int x, int y, int h, int w, int fontsize, QString lbl)
{

    QRect  rect;

    int margin=20;

    rect.setRect(x+margin*0.5 , y+margin*0.5, h-margin,w-margin );




    painter.drawRect(rect);

    QFont font("Tahoma",fontsize);
    font.setPixelSize(fontsize);

    painter.setFont(font);
    painter.drawText(rect, Qt::AlignCenter, lbl);

}



void commonData::draw_form(QPainter &painter, int X0, int Y0, int W,int H,int int_loc_num, QString form_type, QString loc_num,QString val_of_rec)
{


    static int pow10[10] = {
        1, 10, 100, 1000, 10000,
        100000, 1000000, 10000000, 100000000, 1000000000
    };
    int YFORM,YLOC,YVAL;

    YFORM=2*H/10; YLOC=H/10; YVAL=H/10;

    YFORM=eI.width()*5+16;

    QPen pen(Qt::black, 4.0, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin);

    painter.setBrush(Qt::NoBrush);//QColor(240, 58, 87));

    painter.setPen(pen);

    draw_label(painter,X0 , Y0, W/2-YFORM,YFORM,YVAL/2,form_type);
    draw_label(painter,X0 , Y0+YFORM, W/2, YLOC,YVAL/2,loc_num);
    draw_label(painter,X0 , Y0+YFORM+YLOC, W/2, H-YFORM-YLOC,YVAL/2,QString(""));
    draw_label(painter,X0+W/2 , Y0, W/2, YVAL,YVAL/2,val_of_rec);
    draw_label(painter,X0+W/2 , Y0+YVAL, W/2, H-YVAL,YVAL/2,QString(""));


    //QPen pen2(Qt::black, 1.5, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin);
    QPen pen2(Qt::black, 3, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin);
    painter.setPen(pen2);

    QPen pen_white(Qt::white, 3, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin);
    QBrush brush_black(Qt::black);
   // painter.setPen(pen2);

    // QImage im = eI.scaled(YFORM-3,YFORM-3,Qt::KeepAspectRatio,Qt::SmoothTransformation);

    QImage im = eI.scaled(eI.width()*5,eI.height()*5,Qt::KeepAspectRatio,Qt::FastTransformation);
    // eI.scaled(1000,Qt::KeepAspectRatio);

    painter.drawImage(X0+W/2-YFORM+8,Y0+8,im);

    if (int_loc_num==0)
    {
        brush_black=QBrush(Qt::NoBrush);
     pen_white=pen2;
    }

int aloc=abs(int_loc_num);
if (int_loc_num>0)
{
    for (int i=0;i<10;i++)
        for (int j=0;j<8;j++)
        {

            if (((aloc/pow10[j])%10)==i)
            {
                    painter.setPen(pen_white);
                    //QColor(240, 58, 87));
                    painter.setBrush(brush_black);

            }
            else
            {
                painter.setPen(pen2);
                painter.setBrush(Qt::NoBrush);
              //  painter.setBrush(brush_black);//QColor(240, 58, 87));
             }
            int dd=(W-60.0)/20.0;
            int ww=(H-YLOC-40.0)/10.0;
            draw_number(painter,X0+20+(i)*dd,Y0+20+YFORM+YLOC+(j)*ww,dd*0.8,i);

        }
}else
{
    for (int i=0;i<10;i++)
        for (int j=0;j<8;j++)
        {

            if (aloc==10*j+i+1)
            {
                    painter.setPen(pen_white);
                 painter.setBrush(brush_black);


            }
            else
            {
                painter.setPen(pen2);
                 painter.setBrush(Qt::NoBrush);//QColor(240, 58, 87));
             }
            int dd=(W-60.0)/20.0;
            int ww=(H-YLOC-40.0)/10.0;
            draw_number(painter,X0+20+(i)*dd,Y0+20+YFORM+YLOC+(j)*ww,dd*0.8,10*j+i+1);

        }
}



    for (int i=0;i<10;i++)
        for (int j=0;j<10;j++)
        {
            int dd=(W-60.0)/20.0;
            int ww=(H-YVAL-20.0)/10.0;
            draw_number(painter,X0+20+W/2+(i)*dd,Y0+30+YVAL+(j)*ww,dd*0.8,10*j+i+1);

        }

}


void commonData::draw_page(QPainter &painter,std::vector <FORM>& form_arr,int istart,int iend,int qr_invert)
{
    int qr_type=2;
    int loc_int;

    static float coords[4][4]={{72,70,1600,1100},
                             {214.5+1600,70,1600,1100},
                               {72,209+1100,1600,1100},
                             {214.5+1600,209+1100,1600,1100}
                             };
    for (int i=istart;i<MIN(iend,istart+4);i++)
    {
    text_for_qr=form_arr[i].qr_text;
    form=form_arr[i].form_type;
    loc=form_arr[i].loc_num;
    val=form_arr[i].val_of_rec;
    loc_int=form_arr[i].int_loc_num;
    updateQRImage(text_for_qr,1,qr_type,qr_invert);
    draw_form(painter,coords[i-istart][0],coords[i-istart][1],coords[i-istart][2],coords[i-istart][3],loc_int,form,loc,val);
    }

    painter.setPen(QPen(Qt::black, 1.5, Qt::DashDotLine, Qt::RoundCap));
    painter.drawLine(0, 1239.5, 4000, 1239.5);

    painter.drawLine(1743, 0, 1743, 3000);


}


void commonData::gen_forms_array()
{
    QSqlQuery * query_forms = new QSqlQuery(db);
    query_forms->setForwardOnly(true);
    query_forms->exec( "SELECT number, description FROM form_type_table;");


    std::vector<QString> forms_list;
    std::vector<int> forms_numbers;
    int forms_num=0;
    while(query_forms->next())
     {
        bool isok;

        forms_numbers.push_back(query_forms->value(0).toInt());
         forms_list.push_back(/*query_forms->value(0).toString()+" "+*/query_forms->value(1).toString());
         forms_num++;
     }

    qDebug()<<"fnum="<<forms_num<<endl;
    std::vector<int> num_of_users;

    QSqlQuery * query_locations = new QSqlQuery(db);
    query_locations->setForwardOnly(true);
    query_locations->exec( "SELECT location_number, number_of_users, number_of_area  FROM locations_table;");


    std::vector<int> loc_nums;
    std::vector<int> area_nums;
    //int forms_num=0;
    while(query_locations->next())
     {
        bool isok;

         num_of_users.push_back(query_locations->value(1).toInt());
         loc_nums.push_back(query_locations->value(0).toInt());
         area_nums.push_back(query_locations->value(2).toInt());

     }

    forms.clear();

    aes256_key=keyEdit->text();
    global_loc_name=LocNumEdit->text();//"LOCATION NUMBER";
    global_val_name=ValOfRecEdit->text();//"VALUE_OF_RECORD";
    global_qr_label=nameEdit->text();//"QR_LABEL";
    global_form_model=FormTypeCombo->currentIndex();
    int iii=0;
    for (int i=0;i<loc_nums.size();i++)
    {
        for (int k=0;k<forms_num;k++)
        {
                 for(int j=0;j<num_of_users[i];j++)
            {
                iii++;
                FORM frm;

                frm.form_type=forms_list[k];
                if (global_form_model==0)
                    frm.int_loc_num=loc_nums[i]+area_nums[i]*10000;
                else
                    frm.int_loc_num=-loc_nums[i]+area_nums[i]*10000;
                frm.loc_num=global_loc_name;//QString(lic_nums[i]);
                frm.val_of_rec=global_val_name;
                QString number = QString("%1").arg(loc_nums[i], 8, 10, QChar('0'));
                QString ffff = QString("%1").arg(forms_numbers[k], 2, 10, QChar('0'));
                 QString series = QString("%1").arg(iii, 5, 10, QChar('0'));
                frm.qr_text=global_qr_label+number+series+ffff+"1";

                forms.push_back(frm);



            }
        }
        for (int k=0;k<forms_num;k++)
        {
             for(int j=0;j<(num_of_users[i]*percent);j++)
            {
                iii++;
                FORM frm;

                frm.form_type=forms_list[k];
                if (global_form_model==0)
                    frm.int_loc_num=0;
                else
                    frm.int_loc_num=0;
                frm.loc_num=global_loc_name;//QString(lic_nums[i]);
                frm.val_of_rec=global_val_name;
                QString number = QString("%1").arg(loc_nums[i], 8, 10, QChar('0'));
                QString ffff = QString("%1").arg(forms_numbers[k], 2, 10, QChar('0'));
                 QString series = QString("%1").arg(iii, 5, 10, QChar('0'));
                frm.qr_text=global_qr_label+number+series+ffff+"0";

                forms.push_back(frm);



            }
        }
    }


    //data->num_form_label->setText(QString("%1").arg(total_users));

    delete query_forms;
    delete query_locations;

}

void commonData::init_db()
{
    QSqlDatabase dbase = QSqlDatabase::addDatabase("QSQLITE");
    dbase.setDatabaseName("my_db.sqlite");
    if (!dbase.open()) {
        qDebug() << "Что-то пошло не так!";
        //return -1;
    }


    QSqlQuery a_query=QSqlQuery(dbase);
    // DDL query
    QString str = "CREATE TABLE form_type_table ("
                  "number integer, "
                  "description VARCHAR(255));";
    bool b = a_query.exec(str);
    // DML
    QString str_insert = "INSERT INTO form_type_table(number, description) "
                         "VALUES (%1, '%2');";
    str = str_insert.arg("1")
            .arg("description1");
    b = a_query.exec(str);

  ///////////////////////////
    str = "CREATE TABLE value_of_record_table ("
          "form_type integer, "
          "value_of_record integer, "
          "meaning VARCHAR(255));";
    b = a_query.exec(str);

    // DML
    str_insert = "INSERT INTO value_of_record_table(form_type, value_of_record, meaning) "
                 "VALUES (%1, %2, '%3');";
    str = str_insert.arg(1).arg(2).arg("meaining1");
    b = a_query.exec(str);


  /////////////////////////////////
    str = "CREATE TABLE geographic_area_table ("
          "number integer, "
          "name VARCHAR(255));";
    b = a_query.exec(str);

    // DML
    str_insert = "INSERT INTO geographic_area_table(number,name) "
                 "VALUES (%1, '%2');";
    str = str_insert.arg(1).arg("name1");
    b = a_query.exec(str);

    ///////////////////////////////////

    str = "CREATE TABLE locations_table ("
          "number_of_area integer, "
            "location_number integer, "
            "number_of_users integer, "
          "description VARCHAR(255));";
    b = a_query.exec(str);

    // DML
    str_insert = "INSERT INTO locations_table(number_of_area,location_number,number_of_users,description) "
                 "VALUES (%1,%2,%3, '%4');";
    str = str_insert.arg(1).arg(2).arg(3).arg("desc1");
    b = a_query.exec(str);
    dbase.close();

}

void commonData::open_db()
{
    db = QSqlDatabase::addDatabase("QSQLITE");
          db.setDatabaseName(db_name);


}
