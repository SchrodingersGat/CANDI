#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "candi_version.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    initMenus();

    initSignalsSlots();

    updateDisplay();
}


MainWindow::~MainWindow()
{
    // TODO: Disconnect the CAN interface

    // TODO: Save the workspace settings

    // TODO: Save global settings

    delete ui;
}


void MainWindow::onClose()
{
    close();
}


/**
 * @brief MainWindow::initSignalsSlots - Connect various signals and slots
 */
void MainWindow::initSignalsSlots()
{
    connect(ui->actionE_xit, SIGNAL(triggered()), this, SLOT(onClose()));
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


void MainWindow::loadWorkspace(QString filename)
{

}


void MainWindow::saveWorkspace(QString filename)
{

}
