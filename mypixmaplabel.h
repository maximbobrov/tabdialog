#ifndef MYPIXMAPLABEL_H
#define MYPIXMAPLABEL_H

#include <QObject>
#include <QLabel>
#include <QPixmap>
class myPixmapLabel : public QLabel
{
public:

    explicit myPixmapLabel(QWidget* parent = nullptr, Qt::WindowFlags f = Qt::WindowFlags());
    ~myPixmapLabel();
QPixmap pix;
void updatePix();
public slots:
    void setPixmap(const QPixmap& pm);

protected:
    void resizeEvent(QResizeEvent* event) override;

private:
    void updateMargins();



    int pixmapWidth = 0;
    int pixmapHeight = 0;
};

#endif // MYPIXMAPLABEL_H
