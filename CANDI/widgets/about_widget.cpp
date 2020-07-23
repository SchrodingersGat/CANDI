#include "about_widget.hpp"
#include "candi_version.h"


AboutWidget::AboutWidget(QWidget *parent) : QDialog(parent)
{
    ui.setupUi(this);

    setWindowTitle(tr("About CANDI"));

    setAttribute(Qt::WA_DeleteOnClose, true);

    // Display application version
    ui.version->setText(getCandiVersion());
    ui.qtVersion->setText(qVersion());

    // TODO: Format and display the build information

    // TODO: Display commit hash

    // Set the URL links
    const QString GITHUB_URL = "github.com/SchrodingersGat/CANDI";

    ui.githubLabel->setTextFormat(Qt::RichText);
    ui.githubLabel->setOpenExternalLinks(true);
    ui.githubLabel->setText("<a href='https://" + GITHUB_URL + "'>" + GITHUB_URL + "</a>");
}


void AboutWidget::showReleaseNotes()
{
    // TODO: Display application release notes (open in system text editor?)
}
