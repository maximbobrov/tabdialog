
#include <poppler-qt5.h>
#include "pages.h"
#include <QDebug>
//Poppler::Document* document=NULL;
//int curr_page=0;


/*void PrintAndPreviewPage::render_page(int page)
{
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


    viewer->pix=map;
    viewer->updatePix();
    //ui->label->setPixmap(map);
   // ui->label->setScaledContents(true);
   // ui->label->layout()->update();
  //  ui->label->res
    //ui->graphicsView->scene()->addItem(&itm);
   // qDebug()<<image.width()<<" "<<image.height()<<endl;
    // ... use image ...
    // after the usage, the page must be deleted
    delete pdfPage;


}*/

/*void PrintAndPreviewPage::push_open()
{
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


        data->pagesspinbox->setSuffix(QString(" of %1").arg(document->numPages()));
       // hitsSpinBox->setSpecialValueText(tr("Return only the first result"));
        data->pagesspinbox->setMinimum(1);
        data->pagesspinbox->setMaximum(document->numPages());
        data->pagesspinbox->setSingleStep(1);
        data->pagesspinbox->setValue(1);

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
        };
document->setRenderHint(Poppler::Document::RenderHint::TextAntialiasing,true);
document->setRenderHint(Poppler::Document::RenderHint::Antialiasing,true);
document->setRenderHint(Poppler::Document::RenderHint::TextHinting,true);
document->setRenderHint(Poppler::Document::RenderHint::ThinLineShape,true);
        if (document == 0) {
        // ... error message ...
        return;
        }
        // Access page of the PDF file
        render_page(1);
       // delete document;
    }
}
*/


/*void PrintAndPreviewPage::push_next()
{

    //qDebug()<<"mw= "<<ui->label->minimumWidth()<<" mh="<<ui->label->minimumHeight()<<" "<<ui->label->width()<<" "<<ui->label->height()<<endl;
    if (document!=NULL)
    {
        if (curr_page<document->numPages()-1)
            curr_page++;

        render_page(curr_page);
    }
}*/
/*void PrintAndPreviewPage::goto_page(int page)
{
    if (document!=NULL)
    {

qDebug()<<"ffff"<<page<<endl;
        render_page(page);
    }

}*/
