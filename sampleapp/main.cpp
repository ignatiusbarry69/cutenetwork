#include <QCoreApplication>
#include <QTimer>
#include <QDebug>
#include "../qhttpclient/qhttpclient.h"

int main(int argc, char *argv[])
{
    QCoreApplication app(argc, argv);

    QHttpClient* client = new QHttpClient(&app);
    client->setMaxRetries(3);
    client->setRetryDelay(1500);

    int loopCount = 0;
    QTimer* looper = new QTimer(&app);
    QObject::connect(looper, &QTimer::timeout, [&]() {
        qDebug() << "test async loop #" << loopCount++;
        if (loopCount >= 100) {
            looper->stop();
        }
    });
    looper->start(100); // every 100 ms

    QObject::connect(client, &QHttpClient::finished, [&](const QByteArray& data) {
        qDebug() << "Request succeeded:";
        qDebug().nospace() << data.constData();
        app.quit();
    });

    QObject::connect(client, &QHttpClient::failed, [&](const QString& error, int attempt) {
        qDebug() << "Request failed after" << attempt << "attempt(s):";
        qDebug() << error;
        app.quit();
    });

    client->get(QUrl("https://api.etix.co.id/s3/banner"));

    return app.exec();
}
