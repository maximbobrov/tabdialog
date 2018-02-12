#include "mypixmaplabel.h"


myPixmapLabel::myPixmapLabel(QWidget* parent, Qt::WindowFlags f) : QLabel(parent, f)
{
}

myPixmapLabel::~myPixmapLabel()
{
}

void myPixmapLabel::updatePix()
{
    if (!pix.isNull())
    {

        QSize size=(this->size());
        size.setWidth(this->size().width()-10);
         size.setHeight(this->size().height()-10);
    QLabel::setPixmap(pix.scaled(size, Qt::KeepAspectRatio, Qt::SmoothTransformation));
}


}

void myPixmapLabel::setPixmap(const QPixmap& pm)
{
    pixmapWidth = pm.width();
    pixmapHeight = pm.height();

    updateMargins();
    QLabel::setPixmap(pm);
}

void myPixmapLabel::resizeEvent(QResizeEvent* event)
{
  //  updateMargins();


      QLabel::resizeEvent(event);

  updatePix();

}

void myPixmapLabel::updateMargins()
{
    if (pixmapWidth <= 0 || pixmapHeight <= 0)
        return;

    int w = this->width();
    int h = this->height();

    if (w <= 0 || h <= 0)
        return;

    if (w * pixmapHeight > h * pixmapWidth)
    {
        int m = (w - (pixmapWidth * h / pixmapHeight)) / 2;
        setContentsMargins(m, 0, m, 0);
    }
    else
    {
        int m = (h - (pixmapHeight * w / pixmapWidth)) / 2;
        setContentsMargins(0, m, 0, m);
    }
}
