#include "threadsafebuffer.h"

ThreadSafeBuffer::ThreadSafeBuffer(QObject *parent)
: QBuffer(parent), lock_(new QMutex()), bytesRead_(0) {

}
ThreadSafeBuffer::~ThreadSafeBuffer() {
    lock_->unlock();
    delete lock_;
}

bool ThreadSafeBuffer::isSequential() {
    qDebug("ThreadSafeBuffer::isSequential(); called.");
    return TRUE;
}

qint64 ThreadSafeBuffer::readData(char* data, qint64 maxSize) {
    QMutexLocker locker(lock_);
    qint64 numRead = 0;
    numRead = QBuffer::readData(data, maxSize);
    bytesRead_ += numRead;
    //qDebug("ThreadSafeBuffer::readData(); read %d bytes, total read: %d.", numRead, bytesRead_);

    return numRead;
}

qint64 ThreadSafeBuffer::writeData(const char* data, qint64 maxSize) {
    QMutexLocker locker(lock_);
    return QBuffer::writeData(data, maxSize);
}
