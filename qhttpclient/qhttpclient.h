#ifndef QHTTPCLIENT_H
#define QHTTPCLIENT_H

#include "internal/curlengine.h"
#include <QTimer>
class CurlEngine;

class QHttpClient : public QObject
{
    Q_OBJECT

public:
    explicit QHttpClient(QObject* parent = nullptr);
    ~QHttpClient();

    void setMaxRetries(int retries);
    void setRetryDelay(int milliseconds);

public slots:
    void get(const QUrl& url);

signals:
    void finished(const QByteArray& data);
    void failed(const QString& error, int attempt);

private slots:
    void attemptRequest();

private:
    QUrl m_url;
    int m_maxRetries;
    int m_retryDelayMs;
    int m_currentAttempt;

    CurlEngine* m_engine;
};

#endif // QHTTPCLIENT_H
