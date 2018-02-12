#include <QDebug>
#include <QPrinter>
#include <QPainter>
#include <QFileDialog>
#include "pages.h"
#include <poppler-qt5.h>
#include <QPrintDialog>
#include <QApplication>

Poppler::Document* document=NULL;
int curr_page=0;

void GenerateFormsPage::gen_forms()
{

data->gen_forms_array();
    QString fileName = QFileDialog::getSaveFileName((QWidget* )0, "Export PDF", QString(), "*.pdf");

    if (fileName.isEmpty()) return;

    if (QFileInfo(fileName).suffix().isEmpty()) { fileName.append(".pdf"); }

     data->curr_pdf_path=fileName;

    QPrinter printer(QPrinter::PrinterResolution);
    printer.setResolution(300);
    printer.setPageSize(QPrinter::A4);
    printer.setOrientation(QPrinter::Landscape);
    printer.setPageMargins (0,0,0,0,QPrinter::Millimeter);
    printer.setFullPage(false);
    printer.setOutputFileName(fileName);
    printer.setOutputFormat(QPrinter::PdfFormat); //or QPrinter::NativeFormat



    QPainter painter(&printer); // create a painter which will paint 'on printer'.

    painter.setRenderHint(QPainter::Antialiasing, true);
    painter.setRenderHint(QPainter::TextAntialiasing, true);


    qDebug()<<"num="<<data->forms.size()<<endl;
    for (int i=0;i<data->forms.size();i++)
    {

        qDebug()<<"i="<<i<<" "<<data->forms[i].form_type<<" "<<data->forms[i].int_loc_num<<endl;
    }

    for (int ii=0;ii<=(data->forms.size()-1)/4;ii++)
    {

        data->draw_page(painter,data->forms,ii*4,data->forms.size(),0);
       // if (ii!=9)
        if (ii<(data->forms.size()-1)/4)
         {
            printer.newPage();

         }
           if((ii!=data->forms.size()/4) && (ii%10==0))
           {
               state->setText(QString("Progress:")+QString::number(int(ii*400/data->forms.size()))+QString("%"));
               qApp->processEvents();
           }
           if (ii==data->forms.size()/4)
                state->setText(QString("Progress:100%"));
    }
    painter.end();
    //data->openButton->click();
    QString filename=data->curr_pdf_path;

    if (data->curr_pdf_path.isEmpty()) return;
     document = Poppler::Document::load(filename);
    if (!document || document->isLocked()) {
    // ... error message ....
        qDebug()<<"error"<<endl;
    delete document;
    return;
    }else
    {
qDebug()<<"num pages="<<document->numPages();


        data->pagesspinbox->setSuffix(QString(" of %1").arg(document->numPages()-1));
       // hitsSpinBox->setSpecialValueText(tr("Return only the first result"));
        data->pagesspinbox->setMinimum(0);
        data->pagesspinbox->setMaximum(document->numPages()-1);
        data->pagesspinbox->setSingleStep(1);
        data->pagesspinbox->setValue(0);

         curr_page=0;
        qDebug() <<"success"<<endl;

        /*enum RenderHint {
            Antialiasing = 0x00000001,      ///< Antialiasing for graphics
            TextAntialiasing = 0x00000002,  ///< Antialiasing for text
            TextHinting = 0x00000004,       ///< Hinting for text \since 0.12.1
            TextSlightHinting = 0x00000008, ///< Lighter hinting for text when combined with TextHinting \since 0.18
            OverprintPreview = 0x00000010,  ///< Overprint preview \since 0.22
            ThinLineSolid = 0x00000020,     ///< Enhance thin lines solid \since 0.24
            ThinLineShape = 0x00000040,     ///< Enhance thin lines shape. Wins over ThinLineSolid \since 0.24
            IgnorePaperColor = 0x00000080   ///< Do not compose with the paper color \since 0.35
        };*/
document->setRenderHint(Poppler::Document::RenderHint::TextAntialiasing,true);
document->setRenderHint(Poppler::Document::RenderHint::Antialiasing,true);
document->setRenderHint(Poppler::Document::RenderHint::TextHinting,true);
document->setRenderHint(Poppler::Document::RenderHint::ThinLineShape,true);
        if (document == 0) {
        // ... error message ...
        return;
        }
        // Access page of the PDF file
        render_page(0);
        slider->setMinimum(0);
        slider->setMaximum(document->numPages()-1);
        slider->setSingleStep(1);
        slider->setValue(0);
       // delete document;
    }

}
void GenerateFormsPage::next()
{
     render_page(curr_page+1);
}
void GenerateFormsPage::prev()
{
     render_page(curr_page-1);
}
void GenerateFormsPage::first()
{
     render_page(0);
}
void GenerateFormsPage::last()
{
     render_page(document->numPages()-1);
}
void GenerateFormsPage::change_percent(QString a)
{
data->percent=a.toDouble()/100;
}
void GenerateFormsPage::update_view_sing()
{


    QPixmap  map( 1600,1100);
    QPainter painter(&map);
       painter.setBrush(QBrush(Qt::transparent));
       //painter.drawRect(10, 10, 100, 100);


       painter.fillRect(QRectF(0,0,map.width(),map.height()),Qt::white);


       int iii=12345;


       int frmindx=data->comboform->currentIndex();
       int locindx=data->comboloc->currentIndex();


       if (frmindx<0) frmindx=0;
       if (locindx<0) locindx=0;
       qDebug()<<"frmindx="<<frmindx<<" locindx="<<locindx<<endl;

                   QString number = QString("%1").arg(data->area_loc[locindx], 8, 10, QChar('0'));
                   QString ffff = QString("%1").arg(data->forms_numbers[frmindx], 2, 10, QChar('0'));
                    QString series = QString("%1").arg(iii, 5, 10, QChar('0'));
                  // frm.qr_text=global_qr_label+number+series+ffff+"1";


                    //if (!data->check_form_type->isChecked())


       QString qrtextloc=data->nameEdit->text()+number+series+ffff;

       int locc=abs(data->area_loc[locindx]);
       if (data->FormTypeCombo->currentIndex()==1)
       locc=-(locc/10000);

       if (data->check_empty->isChecked())
       {
           locc=0;
           qrtextloc+="1";
       }else
               {
                   qrtextloc+="0";
               }

       QString scyphered=data->scypher(qrtextloc);
       int slen=strlen( qrtextloc.toUtf8().constData());
       data->qrtext->setText(QString("<b>qr-code text:</b> %1 <b> %2 symbols </b> <br> <b>scyphered text:</b> %3 <b> %4 symbols </b>").arg(qrtextloc).arg(slen).arg(scyphered).arg(scyphered.length()));
         data->updateQRImage(qrtextloc,1,2,1);


       data->draw_form( painter, 0, 0, map.width(),map.height(),locc, data->forms_names[frmindx], QString (data->LocNumEdit->text()),QString (data->ValOfRecEdit->text()));

      // painter.end();
    viewer_sing->pix=map;
    viewer_sing->updatePix();
}
GenerateFormsPage::update_key(QString key)
{
    data->aes256_key=key;
    update_view_sing();
}
void GenerateFormsPage::render_page(int page)
{
    curr_page=page;
    Poppler::Page* pdfPage = document->page(page); // Document starts at page 0
    if (pdfPage == 0) {
    // ... error message ...
    return;
    }

qDebug()<<"page="<<data->pagesspinbox->value()<<endl;
    QImage image = pdfPage->renderToImage(100, 100);//, x, y, width, height);
    if (image.isNull()) {
    // ... error message ...
    return;
    }


    QPixmap  map( QPixmap::fromImage(image));

    slider->setValue(page);
    data->pagesspinbox->setValue(page);
    viewer->pix=map;
    viewer->updatePix();
   // pageLoc->setText(QString("Current Page:")+QString::number(page+1)+QString("/")+QString::number(document->numPages()));
    //ui->label->setPixmap(map);
   // ui->label->setScaledContents(true);
   // ui->label->layout()->update();
  //  ui->label->res
    //ui->graphicsView->scene()->addItem(&itm);
   // qDebug()<<image.width()<<" "<<image.height()<<endl;
    // ... use image ...
    // after the usage, the page must be deleted
    delete pdfPage;


}
void GenerateFormsPage::print_forms()
{
data->gen_forms_array();
    QPrinter printer;

    QPrintDialog *dialog = new QPrintDialog(&printer);
    dialog->setWindowTitle("Print Document");

    if (dialog->exec() != QDialog::Accepted)
        return ;

    printer.setResolution(300);
    printer.setPageSize(QPrinter::A4);
    printer.setOrientation(QPrinter::Landscape);
    printer.setPageMargins (0,0,0,0,QPrinter::Millimeter);
    printer.setFullPage(false);

    QPainter painter(&printer); // create a painter which will paint 'on printer'.
    painter.setRenderHint(QPainter::Antialiasing, true);
    painter.setRenderHint(QPainter::TextAntialiasing, true);

    qDebug()<<printer.width()<<" "<<printer.height()<<endl;
    for (int ii=0;ii<=data->forms.size()/4;ii++)
    {
        if (ii!=0)
           printer.newPage();
        data->draw_page(painter,data->forms,ii*4,data->forms.size(),1);
       // if (ii!=9)

    }
    painter.end();
}
