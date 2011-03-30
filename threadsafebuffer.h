#ifndef THREADSAFEBUFFER_H
#define THREADSAFEBUFFER_H

#include <QBuffer>
#include <QMutexLocker>
#include <QMutex>

class ThreadSafeBuffer : public QBuffer
{
    Q_OBJECT
private:
    QMutex* lock_;
    qint64 bytesRead_;
public:
    explicit ThreadSafeBuffer(QObject *parent = 0);
    ~ThreadSafeBuffer();
    bool isSequential();

protected:
    qint64 readData(char* data, qint64 maxSize);
    qint64 writeData(const char* data, qint64 maxSize);
};

#endif // THREADSAFEBUFFER_H
