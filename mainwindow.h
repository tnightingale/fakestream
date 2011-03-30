#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QThread>
#include <QMediaPlayer>
#include <QDebug>
#include <QByteArray>

namespace Ui {
    class MainWindow;
}

class BufferLoader;
class ThreadSafeBuffer;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    QThread* thread_;
    QMediaPlayer* player_;
    BufferLoader* loader_;
    ThreadSafeBuffer* buffer_;

public slots:
    void start();
    void respondMediaStatusChange(QMediaPlayer::MediaStatus);
    void playerError(QMediaPlayer::Error error);
    void respondBufferChange(int percentFilled);
    void respondStateChange(QMediaPlayer::State state);
    void play();
    void echo(qint64 bytes) { qDebug("ECHO %d", bytes); }
};

#endif // MAINWINDOW_H
