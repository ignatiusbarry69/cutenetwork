#ifndef CURLENGINE_H
#define CURLENGINE_H

#include "curl/curl.h"
#include <QObject>
#include <QByteArray>
#include <QUrl>



class CurlEngine : public QObject
{
    Q_OBJECT

public:
    explicit CurlEngine(QObject* parent = nullptr);
    ~CurlEngine();

    bool performGet(const QUrl& url);
    QByteArray responseData() const;
    QString errorString() const;

private:
    static size_t writeCallback(char* ptr, size_t size, size_t nmemb, void* userdata);

    CURL* m_curl;
    QByteArray m_buffer;
    QString m_error;
};

#endif // CURLENGINE_H

