#ifndef OFXHOMEWORKER_H
#define OFXHOMEWORKER_H

#include <QObject>
#include <QThread>

#include "download.h"
#include "preferences.h"

class OfxHomeWorker : public QThread
{
    Q_OBJECT
    virtual void run() override {}
signals:
    void finished();
};

class OfxRequestWorker : public OfxHomeWorker
{
    Q_OBJECT
public:
    explicit OfxRequestWorker(
        const std::string& request, const std::string& url) :
            request_(request), url_(url) {}
    virtual void run() override;
private:
    std::string request_;
    std::string url_;
signals:
    void ofxResponse(const QString&, const QString&, bool);
};

class ValidApiKeyWorker : public OfxHomeWorker
{
    Q_OBJECT
public:
    explicit ValidApiKeyWorker(const QString& api_key) : api_key_(api_key) {}
    virtual void run() override;
private:
    QString api_key_;
signals:
    void apiKeyResponse(const QString&, bool success);
};

class OfxHomeController : public QObject
{
    Q_OBJECT
public:
    // Sends on OFX request. Response is emitted by the
    // ofxResponse(const QString& response, bool success) signal.
    void ofxRequest(
        const Download* download, const std::string& request,
        const std::string& url);

    // Disconnect the ofxResponse signal.
    void cancelOfxRequest(const Download* download);

    void validateApiKey(const Preferences* preferences, const QString& api_key);
private:
    OfxRequestWorker* request_worker_ = nullptr;
    ValidApiKeyWorker* valid_api_key_worker_ = nullptr;
};

#endif // OFXHOMEWORKER_H
