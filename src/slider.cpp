#include "slider.h"
#include "ui_slider.h"
#include <QShortcut>

Slider::Slider(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Slider)
{
    ui->setupUi(this);
    /*  Set Global variables here
     *  total        = total numbers of slides in resource.
     *  currentIndex = index where the slider will start, this updates with time set in timeout
     *  progeressbar = show slide timer based progressbar on top.
     *  duration     = duration of slide while auto playback
    */
    total = 8;
    currentIndex = 0;
    duration = 10000;
    progressbar = false;

    ui->progressBar->setMinimum(0);
    ui->progressBar->setMaximum(100);

    if(progressbar== false){
        ui->progressBar->hide();
    }

    connect(ui->next,SIGNAL(clicked()),this,SLOT(next()));
    connect(ui->prev,SIGNAL(clicked()),this,SLOT(prev()));
    connect(ui->skip,SIGNAL(clicked(bool)),this,SLOT(close()));

    timer = new QTimer (this);
    timer->setInterval(duration);
    connect(timer,SIGNAL(timeout()),this,SLOT(next()));

    loadSlides();
}



Slider::~Slider()
{
    delete ui;
}

void Slider::closeEvent(QCloseEvent *event)
{
    reset();
    QWidget::closeEvent(event);
}

void Slider::start()
{
    changeSlide(0);
    timer->start();
}

void Slider::loadSlides()
{
    for (int i = 0; i < total; i++)
    {
        QFile file(":/slides/"+QString::number(i)+".html");
        file.open(QIODevice::ReadOnly);
        createSlide(file.readAll(),i);
        file.close();
    }
}

void Slider::progressBarUpdate()
{
    if(progressbar){
        animation = new QPropertyAnimation(ui->progressBar, "value");
        animation->setDuration(duration);
        animation->setStartValue(ui->progressBar->minimum());
        animation->setEndValue(ui->progressBar->maximum());
        animation->start(QPropertyAnimation::DeleteWhenStopped);
    }
}

void Slider::stop()
{
    timer->stop();
    updateStopButton();
    progressBarUpdate();
    if(animation!=nullptr){
       animation->stop();
    }
}

void Slider::reset()
{
    currentIndex = 0;
    changeSlide(currentIndex);
    stop();
}

void Slider::updateStopButton()
{
    if(timer->isActive()){
        ui->stop->setToolTip("Stop");
        ui->stop->setIcon(QIcon(":/icons/stop-line.png"));
    }
    if(timer->isActive()==false){
        ui->stop->setToolTip("Play");
        ui->stop->setIcon(QIcon(":/icons/play-line.png"));
    }
}

void Slider::next()
{
    timer->stop();
    if(currentIndex>=total-1){
        stop();
    }else{
        changeSlide(++currentIndex);
        timer->start();
    }
    updateStopButton();
}

void Slider::prev()
{
    timer->stop();
    if(currentIndex==0){
        currentIndex = total-1;
        changeSlide(currentIndex);
    }else{
        changeSlide(--currentIndex);
        timer->start();
    }
    updateStopButton();
}

void Slider::changeSlide(int index)
{
    //hide all in view
    for (int i = 0; i < ui->view->count(); ++i){
      QWidget *widget = ui->view->itemAt(i)->widget();
      if (widget != NULL){
        widget->setVisible(false);
      }
    }
    //show requested slide
    Slide *slide = this->findChild<Slide*>("slide_"+QString::number(index));
    ui->view->addWidget(slide);
    slide->show();
    uncheckAllNavBtn();
    QPushButton *navBtn = this->findChild<QPushButton*>("navBtn_"+QString::number(index));
    navBtn->setChecked(true);
    progressBarUpdate();
}

void Slider::createSlide(QString html,int index){
    Slide *slide = new Slide(this);
    slide->setObjectName("slide_"+QString::number(index));
    slide->hide();
    slide->setText(html);
    connect(slide,&Slide::linkActivated,[=](QString link){
        if(link=="start"){
            this->close();
        }else{
            QDesktopServices::openUrl(QUrl(link));
        }
    });
    //make button without name
    QPushButton *navBtn = new QPushButton("",this);
    navBtn->setCheckable(true);
    navBtn->setFixedSize(12,12);
    //uncomment to make buttons circular
    //navBtn->setStyleSheet("border-radius:"+QString::number(navBtn->width()/2));
    navBtn->setObjectName("navBtn_"+QString::number(index));
    connect(navBtn,&QPushButton::clicked,[=](){
       uncheckAllNavBtn();
       navBtn->setChecked(true);
       changeSlide(index);
       currentIndex = index;
       stop();// stop auto slider if user clicks button to navigate
    });
    ui->navDots->addWidget(navBtn);
}

void Slider::uncheckAllNavBtn(){
    foreach (QPushButton*btn, this->findChildren<QPushButton*>()) {
        btn->setChecked(false);
    }
}

void Slider::on_stop_clicked()
{
    if(timer->isActive()){
        if(animation !=nullptr){
            animation->stop();
        }
        timer->stop();
    }else if(timer->isActive()==false){
        progressBarUpdate();
        timer->start();
    }
    updateStopButton();
}
