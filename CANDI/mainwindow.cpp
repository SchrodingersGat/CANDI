#include "mainwindow.h"

#include "ui_mainwindow.h"

#include "directory.hpp"
#include "debug.hpp"
#include "candi_version.h"

#include <qcanbus.h>
#include <qfiledialog.h>

#include "widgets/about_widget.hpp"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    DEBUG << "MainWindow() started";

    ui->setupUi(this);

    setDockNestingEnabled(true);

    initMenus();
    initSignalsSlots();
    initCANInterface();

    updateDisplay();

    loadGlobalSettings();
    loadWorkspace(CANDI::defaultWorkspaceFile());

    DEBUG << "MainWindow() complete";
}


MainWindow::~MainWindow()
{
    DEBUG << "~MainWindow() started";

    // TODO: Disconnect the CAN interface

    // TODO: Save the workspace settings

    // TODO: Save global settings

    delete ui;

    DEBUG << "~MainWindow() complete";
}


void MainWindow::onClose()
{
    DEBUG << "MainWindow::onClose()";

    close();
}


/**
 * @brief MainWindow::initSignalsSlots - Connect various signals and slots
 */
void MainWindow::initSignalsSlots()
{
    connect(ui->actionE_xit, SIGNAL(triggered()), this, SLOT(onClose()));
    connect(ui->action_About, SIGNAL(triggered()), this, SLOT(showAboutInformation()));
}


void MainWindow::initCANInterface()
{
    // TODO
}


/**
 * @brief MainWindow::initMenus - Initialize menu items and actions
 */
void MainWindow::initMenus()
{

}


void MainWindow::updateDisplay()
{
    updateWindowTitle();
}


void MainWindow::updateWindowTitle()
{
    QString title = "CANDI v" + getCandiVersion();

    setWindowTitle(title);
}


void MainWindow::showAboutInformation()
{
    AboutWidget *about = new AboutWidget(this);

    about->setWindowModality(Qt::ApplicationModal);

    about->exec();
}


void MainWindow::loadGlobalSettings()
{
    // TODO
}


void MainWindow::saveGlobalSettings()
{
    // TODO
}


void MainWindow::onLoadWorkspace()
{
    loadWorkspace();
}


void MainWindow::loadWorkspace(QString filename)
{
    // No file provided? Ask the user
    if (filename.isEmpty())
    {
        filename = QFileDialog::getOpenFileName(this,
                                                tr("Load workspace file"),
                                                CANDI::workspaceDir(),
                                                "(*.candi_wks)");

        // Still no filename? Exit
        if (filename.isEmpty()) return;
    }
}


void MainWindow::onSaveWorkspace()
{
    saveWorkspace();
}


void MainWindow::saveWorkspace(QString filename)
{
    // No file provided? Ask the user
    if (filename.isEmpty())
    {
        filename = QFileDialog::getSaveFileName(this,
                                                tr("Save workspace file"),
                                                CANDI::workspaceDir(),
                                                "(*.candi_wks)");

        // Still no filename? Exit
        if (filename.isEmpty()) return;
    }

}
