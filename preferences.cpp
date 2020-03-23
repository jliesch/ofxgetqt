#include <QDebug>


#include "ofxhomeworker.h"
#include "preferences.h"
#include "ui_preferences.h"

Preferences::Preferences(QSettings* settings, OfxGet* ofx_get, QWidget *parent) :
    QDialog(parent),
    ui_(new Ui::Preferences),
    settings_(settings),
    ofx_get_(ofx_get)
{
    ui_->setupUi(this);
    ui_->showFailingInstitutions->setChecked(settings_->value(
        "showFailingInstitutions", QVariant(true)).toBool());
    ui_->sendInstitutionData->setChecked(settings_->value(
        "sendInstitutionData", QVariant(false)).toBool());
    QString api_key = settings_->value("apiKey", QVariant("")).toString();
    if (api_key.size() > 0) {
        ui_->apiKey->setText(api_key);
        changedApiKey(api_key);
    } else {
        ui_->sendInstitutionData->setEnabled(false);
    }
    ui_->apiKey->setCursorPosition(0);
    ui_->apiKey->setFocus();

    connect(ui_->apiKey,
            SIGNAL(textChanged(const QString&)),
            this,
            SLOT(changedApiKey(const QString&)));
    connect(this, &QDialog::accepted,
            this, &Preferences::save);
}

Preferences::~Preferences()
{
    delete ui_;
}

void Preferences::changedApiKey(const QString& api_key) {
    if (api_key.size() == 0) {
        ui_->apiIcon->setPixmap(QPixmap(""));
        return;
    }
    OfxHomeController controller;
    controller.validateApiKey(this, api_key);
}

void Preferences::apiKeyResponse(const QString& api_key, bool success) {
    (void) api_key;  // Remove warning.
    valid_api_key_ = success;
    ui_->sendInstitutionData->setEnabled(success);
    if (success) {
        ui_->apiIcon->setPixmap(QPixmap(":/icons/check-icon.png"));
    } else {
        ui_->apiIcon->setPixmap(QPixmap(":/icons/x-icon.png"));
    }
}

void Preferences::save() {
    bool changedShowFailing =
        settings_->value("showFailingInstitutions", QVariant(true)).toBool() !=
        ui_->showFailingInstitutions->isChecked();
    settings_->setValue(
        "showFailingInstitutions", ui_->showFailingInstitutions->isChecked());
    if (changedShowFailing) {
        ofx_get_->rebuildList("");
    }

    if (valid_api_key_) {
        settings_->setValue("apiKey", ui_->apiKey->text());
        settings_->setValue(
            "sendInstitutionData", ui_->sendInstitutionData->isChecked());
    } else {
        settings_->setValue("apiKey", "");
        settings_->setValue("sendInstitutionData", false);
    }
}
