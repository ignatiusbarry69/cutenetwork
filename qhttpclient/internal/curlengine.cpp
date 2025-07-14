#include "curlengine.h"
#include <QDebug>

#include <QCoreApplication>
#include <QFileInfo>

CurlEngine::CurlEngine(QObject* parent)
    : QObject(parent),
      m_curl(curl_easy_init())
{
}

CurlEngine::~CurlEngine()
{
    if (m_curl) {
        curl_easy_cleanup(m_curl);
    }
}

bool CurlEngine::performGet(const QUrl& url)
{
    if (!m_curl || !url.isValid()) {
        m_error = "Invalid CURL handle or URL";
        return false;
    }

    m_buffer.clear();
    m_error.clear();

    // Resolve full path to cacert.pem
    QString caPath = QCoreApplication::applicationDirPath() + "/cacert.pem";
    QFileInfo caFileInfo(caPath);

    if (!caFileInfo.exists()) {
        m_error = "CA file not found: " + caPath;
        qDebug()<<m_error;
        return false;
    }

    curl_easy_setopt(m_curl, CURLOPT_CAINFO, caPath.toUtf8().constData());

    curl_easy_setopt(m_curl, CURLOPT_URL, url.toString(QUrl::FullyEncoded).toUtf8().constData());
    curl_easy_setopt(m_curl, CURLOPT_WRITEFUNCTION, &CurlEngine::writeCallback);
    curl_easy_setopt(m_curl, CURLOPT_WRITEDATA, this);

    CURLcode res = curl_easy_perform(m_curl);
    if (res != CURLE_OK) {
        m_error = QString::fromUtf8(curl_easy_strerror(res));
        return false;
    }

    return true;
}
size_t CurlEngine::writeCallback(char* ptr, size_t size, size_t nmemb, void* userdata)
{
    auto* engine = static_cast<CurlEngine*>(userdata);
    engine->m_buffer.append(ptr, size * nmemb);
    return size * nmemb;
}

QByteArray CurlEngine::responseData() const
{
    return m_buffer;
}

QString CurlEngine::errorString() const
{
    return m_error;
}
