#ifndef ABOUT_WIDGET_HPP
#define ABOUT_WIDGET_HPP

#include <qdialog.h>

#include "ui_about.h"

class AboutWidget : public QDialog
{
    Q_OBJECT

public:
    AboutWidget(QWidget *parent = nullptr);

public slots:
    void showReleaseNotes();

protected:
    Ui::aboutForm ui;
};

#endif // ABOUT_HPP
