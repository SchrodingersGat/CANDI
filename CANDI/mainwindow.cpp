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
    delete ui;
}


/**
 * @brief MainWindow::initSignalsSlots - Connect various signals and slots
 */
void MainWindow::initSignalsSlots()
{

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
