#ifndef PREFERENCES_H
#define PREFERENCES_H

#include <QDialog>
#include <QSettings>

#include "ofxget_widget.h"

namespace Ui {
class Preferences;
}

class Preferences : public QDialog
{
    Q_OBJECT

public:
    explicit Preferences(QSettings* settings, OfxGet* ofx_get, QWidget *parent = 0);
    ~Preferences();

public slots:
    void changedApiKey(const QString&);
    void apiKeyResponse(const QString&, bool success);
    void save();

private:
    bool valid_api_key_ = false;
    Ui::Preferences *ui_;
    QSettings* settings_;  // not owned.
    OfxGet* ofx_get_;  // not owned.
};

#endif // PREFERENCES_H
