#include "mainwindow.h"
#include "threadsafebuffer.h"
#include "ui_mainwindow.h"
#include "bufferloader.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    loader_(new BufferLoader()),
    buffer_(new ThreadSafeBuffer()) {
    ui->setupUi(this);
    connect(ui->buttonStart, SIGNAL(clicked()),
            this, SLOT(start()));
    connect(ui->buttonPlay, SIGNAL(clicked()),
            this, SLOT(play()));

    loader_->setBuffer(buffer_);
    //connect(buffer_, SIGNAL(bytesWritten(qint64)), this, SLOT(echo(qint64)));

    player_ = new QMediaPlayer(this, QMediaPlayer::StreamPlayback);
    connect(player_, SIGNAL(mediaStatusChanged(QMediaPlayer::MediaStatus)),
            this, SLOT(respondMediaStatusChange(QMediaPlayer::MediaStatus)));
    connect(player_, SIGNAL(error(QMediaPlayer::Error)),
            this, SLOT(playerError(QMediaPlayer::Error)));
    connect(player_, SIGNAL(bufferStatusChanged(int)),
            this, SLOT(respondBufferChange(int)));
    connect(player_, SIGNAL(stateChanged(QMediaPlayer::State)),
            this, SLOT(respondStateChange(QMediaPlayer::State)));

}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::start() {
    qDebug("MainWindow::start(); Buffering started.");
    loader_->getTimer()->start(5);

    this->play();
}

void MainWindow::play() {
    buffer_->open(ThreadSafeBuffer::ReadOnly);
    QMediaResource* res = new QMediaResource();
    res->setAudioBitRate(16);
    res->setSampleRate(441000);
    res->setDataSize(39379580);
    QMediaContent* content = new QMediaContent(*res);
    player_->setMedia(*content, buffer_);
    player_->play();
}

void MainWindow::respondMediaStatusChange(QMediaPlayer::MediaStatus status) {
    switch (status) {
        case QMediaPlayer::EndOfMedia:
            qDebug("MainWindow::respondMediaStatusChange(); Media status: EndOfMedia");
            break;
        case QMediaPlayer::LoadedMedia:
            qDebug("MainWindow::respondMediaStatusChange(); Media status: LoadedMedia");
            break;
        case QMediaPlayer::StalledMedia:
            qDebug("MainWindow::respondMediaStatusChange(); Media status: StalledMedia");
            break;
        case QMediaPlayer::LoadingMedia:
            qDebug("MainWindow::respondMediaStatusChange(); Media status: LoadingMedia");
            break;
        case QMediaPlayer::UnknownMediaStatus:
            qDebug("MainWindow::respondMediaStatusChange(); Media status: UnknownMediaStatus");
            break;
        case QMediaPlayer::BufferedMedia:
            qDebug("MainWindow::respondMediaStatusChange(); Media status: BufferedMedia");
            break;
        case QMediaPlayer::BufferingMedia:
            qDebug("MainWindow::respondMediaStatusChange(); Media status: BufferingMedia");
            break;
        case QMediaPlayer::InvalidMedia:
            qDebug("MainWindow::respondMediaStatusChange(); Media status: InvalidMedia");
            break;
        default:
            qDebug("MainWindow::respondMediaStatusChange(); Media status; %d", status);
            break;
    }
}

void MainWindow::respondBufferChange(int percentFilled) {
    qDebug() << "MainWindow::respondBufferChange(); Buffer %: " << percentFilled;
}

void MainWindow::playerError(QMediaPlayer::Error error) {
    qDebug() << "MainWindow::playerError(); Error: " << player_->errorString();
}

void MainWindow::respondStateChange(QMediaPlayer::State state) {
    qDebug() << "MainWindow::respondStateChange(); State: " << player_->state();
}
