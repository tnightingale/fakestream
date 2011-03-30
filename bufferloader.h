#ifndef BUFFERLOADER_H
#define BUFFERLOADER_H

#include <QObject>
#include <QThread>
#include <QTimer>
#include <QByteArray>
#include <QFile>
#include <QIODevice>

class ThreadSafeBuffer;
class BufferLoader : public QObject {
    Q_OBJECT
private:
    int totalBytesLoaded_;
    QTimer* timer_;
    QFile* source_;
    ThreadSafeBuffer* streamBuffer_;
public:
    explicit BufferLoader(QObject *parent = 0);

    void setBuffer(ThreadSafeBuffer* buffer) { streamBuffer_ = buffer; }
    QTimer* getTimer() { return timer_; }
    ThreadSafeBuffer* getBuffer() { return streamBuffer_; }

signals:
    void bufferLoaded();

public slots:
    void fillBuffer();

};

#endif // BUFFERLOADER_H
