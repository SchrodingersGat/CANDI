#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "debug.hpp"
#include "candi_version.h"

#include "widgets/about_widget.hpp"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    DEBUG << "MainWindow() started";

    ui->setupUi(this);

    initMenus();

    initSignalsSlots();

    updateDisplay();

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


void MainWindow::loadWorkspace(QString filename)
{

}


void MainWindow::saveWorkspace(QString filename)
{

}
