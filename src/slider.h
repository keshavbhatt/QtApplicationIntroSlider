#ifndef SLIDER_H
#define SLIDER_H

#include <QWidget>
#include <QDebug>
#include <QTimer>
#include <QLabel>
#include <QPropertyAnimation>
#include <QFile>
#include <QPushButton>
#include <QDesktopServices>

namespace Ui {
class Slider;
}

class Slider : public QWidget
{
    Q_OBJECT

public:
    explicit Slider(QWidget *parent = nullptr);
    ~Slider();
public slots:
        void start();
        void stop();
        void reset();
protected slots:
        void closeEvent(QCloseEvent *event);
private slots:
    void createSlide(QString html, int index);
    void loadSlides();
    void next();
    void prev();
    void changeSlide(int index);
    void uncheckAllNavBtn();
    void on_stop_clicked();
    void progressBarUpdate();
    void updateStopButton();

private:
    Ui::Slider *ui;
    QTimer *timer = nullptr;
    QStringList slideData;
    int currentIndex;
    int total;
    int duration;
    QPropertyAnimation *animation = nullptr;
    bool progressbar;
};

class Slide : public QLabel
{
    Q_OBJECT
public:
    Slide(QWidget *parent = nullptr) : QLabel(parent)
    {
        this->setTextInteractionFlags(Qt::LinksAccessibleByMouse);
        this->setAlignment(Qt::AlignCenter);
    }
};

#endif // SLIDER_H
