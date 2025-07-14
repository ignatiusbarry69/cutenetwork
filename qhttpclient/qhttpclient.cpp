#include "qhttpclient.h"


QHttpClient::QHttpClient(QObject* parent)
    : QObject(parent),
      m_maxRetries(0),
      m_retryDelayMs(1000),
      m_currentAttempt(0),
      m_engine(new CurlEngine(this))
{
}

QHttpClient::~QHttpClient()
{
}

void QHttpClient::setMaxRetries(int retries)
{
    m_maxRetries = retries;
}

void QHttpClient::setRetryDelay(int milliseconds)
{
    m_retryDelayMs = milliseconds;
}

void QHttpClient::get(const QUrl& url)
{
    if (!url.isValid()) {
        emit failed(QStringLiteral("Invalid URL"), 0);
        return;
    }

    m_url = url;
    m_currentAttempt = 0;
    QTimer::singleShot(0, this, SLOT(attemptRequest()));
}

void QHttpClient::attemptRequest()
{
    printf("attempt request\n");

    ++m_currentAttempt;

    bool success = m_engine->performGet(m_url);
    if (success) {
        emit finished(m_engine->responseData());
    } else {
        if (m_currentAttempt < m_maxRetries) {
            QTimer::singleShot(m_retryDelayMs, this, SLOT(attemptRequest()));
        } else {
            emit failed(m_engine->errorString(), m_currentAttempt);
        }
    }
}
