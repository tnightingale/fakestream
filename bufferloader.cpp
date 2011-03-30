#include "bufferloader.h"
#include "threadsafebuffer.h"

BufferLoader::BufferLoader(QObject *parent)
: QObject(parent), totalBytesLoaded_(0), timer_(new QTimer(this)), streamBuffer_(NULL)
{
    //source_ = new QFile("C:\\Users\\Public\\Music\\Sample Music\\Kalimba.mp3");
    //source_ = new QFile("C:\\Users\\Public\\Music\\Sample Music\\test.wav");
    //source_ = new QFile("C:\\Users\\Public\\Music\\Sample Music\\The Suburbs.wav");
    source_ = new QFile("C:\\Users\\Public\\Music\\Sample Music\\08 - Heart of the City (Ain't No Love).wav");
    source_->open(QIODevice::ReadOnly);

    connect(timer_, SIGNAL(timeout()),
            this, SLOT(fillBuffer()));
}

void BufferLoader::fillBuffer() {
    static int count = 0;
    count++;

    QByteArray data = source_->read(1024);

    streamBuffer_->open(ThreadSafeBuffer::Append);
    totalBytesLoaded_ += streamBuffer_->write(data);
    streamBuffer_->open(ThreadSafeBuffer::ReadOnly);
    //streamBuffer_->close();

    if (count % 1000 == 0) {
        qDebug("BufferLoader::fillBuffer; current: %d, Available: %d", totalBytesLoaded_, streamBuffer_->bytesAvailable());
    }

    if (data.size() == 0) {
        qDebug("BufferLoader::fillBuffer(); Buffer size: %d, Total loaded: %d, Available: %d", streamBuffer_->data().size(), totalBytesLoaded_, streamBuffer_->bytesAvailable());
        disconnect(timer_, SIGNAL(timeout()), this, SLOT(fillBuffer()));
        emit bufferLoaded();
    }
}
