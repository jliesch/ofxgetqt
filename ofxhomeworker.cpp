#include <iostream>

#include <QDebug>
#include <QThread>

#include "ofxget/ofxget.h"
#include "ofxget/ofxhome.h"
#include "ofxhomeworker.h"

using ofxget::ValidateApiKey;
using std::string;

void OfxHomeController::ofxRequest(
        const Download* download, const ofxget::OfxGetContext& context)
{
    assert(request_worker_ == nullptr);
    request_worker_ = new OfxRequestWorker(context);
    connect(request_worker_, &OfxRequestWorker::finished,
            request_worker_, &QObject::deleteLater);
    connect(request_worker_, &OfxRequestWorker::ofxResponse,
            download, &Download::ofxResponse);
    request_worker_->start();
}

void OfxHomeController::cancelOfxRequest(const Download* download) {
    assert(request_worker_ != nullptr);
    disconnect(request_worker_, &OfxRequestWorker::ofxResponse,
            download, &Download::ofxResponse);
}

void OfxHomeController::validateApiKey(const Preferences* preferences,
                                       const QString &api_key)
{
    assert(valid_api_key_worker_ == nullptr);
    valid_api_key_worker_ = new ValidApiKeyWorker(api_key);
    connect(valid_api_key_worker_, &ValidApiKeyWorker::finished,
            valid_api_key_worker_, &QObject::deleteLater);
    connect(valid_api_key_worker_, &ValidApiKeyWorker::apiKeyResponse,
            preferences, &Preferences::apiKeyResponse);
    valid_api_key_worker_->start();
}

void OfxRequestWorker::run()
{
    string resp;
    try {
        string resp;
        string headers;
        context_.PostRequest();
        if (!context_.is_error()) {
            emit ofxResponse(context_.response().c_str(), headers.c_str(), true);
        } else {
            emit ofxResponse(context_.error_string_.c_str(), headers.c_str(), false);
        }
    } catch(const string& msg) {
        emit ofxResponse(msg.c_str(), "", false);
    }
}

void ValidApiKeyWorker::run()
{
    bool success = ValidateApiKey(api_key_.toStdString());
    emit apiKeyResponse(api_key_, success);
}
