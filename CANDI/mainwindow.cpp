#include "mainwindow.h"

#include "ui_mainwindow.h"

#include "directory.hpp"
#include "debug.hpp"
#include "candi_version.h"
#include "candi_interface.hpp"

#include <qcanbus.h>
#include <qfiledialog.h>

#include "widgets/about_widget.hpp"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    DEBUG << "MainWindow() started";

    // Ensure any user directories are available
    CANDI::createSettingsDirectories();

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

    CANDI_Interface::instance()->disconnect();

    saveWorkspace(CANDI::defaultWorkspaceFile());

    saveGlobalSettings();

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

    connect(ui->action_Load_Workspace, SIGNAL(triggered()), this, SLOT(onLoadWorkspace()));
    connect(ui->action_Save_Workspace, SIGNAL(triggered()), this, SLOT(onSaveWorkspace()));
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
    QString title;

    auto interface = CANDI_Interface::instance();

    if (interface->isConnected())
    {
        title = tr("CAN connected");
    }
    else
    {
        title = tr("Disconnected");
    }

    setWindowTitle(title);
}


void MainWindow::onCanConnect()
{
    auto interface = CANDI_Interface::instance();

    // Ignore if already connected
    if (interface->isConnected()) return;

    // TODO - What to do with result of connection?
    bool result = interface->connect();
}


void MainWindow::onCanDisconnect()
{
    auto interface = CANDI_Interface::instance();

    // Ignore if already disconnected
    if (!interface->isConnected()) return;

    interface->disconnect();
}


void MainWindow::showAboutInformation()
{
    AboutWidget *about = new AboutWidget(this);

    about->setWindowModality(Qt::ApplicationModal);

    about->exec();
}


void MainWindow::loadGlobalSettings()
{
    QSettings settings(CANDI::globalSettingsFile(), QSettings::IniFormat);

    CANDI_Interface::instance()->loadSettings(settings);
}


void MainWindow::saveGlobalSettings()
{
    QSettings settings(CANDI::globalSettingsFile(), QSettings::IniFormat);

    CANDI_Interface::instance()->saveSettings(settings);
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

    QFile f(filename);

    // Ignore if the file does not exist..
    if (!f.exists()) return;

    QSettings workspace(filename, QSettings::IniFormat);

    workspace.beginGroup("workspace");

    // Workspace geometry
    if (workspace.contains("geometry"))
    {
        QVariant geom = workspace.value("geometry");
        restoreGeometry(geom.toByteArray());
    }

    if (workspace.contains("state"))
    {
        QVariant st = workspace.value("state");
        restoreState(st.toByteArray());
    }

    workspace.endGroup();  // "workspace"

    workspace.beginGroup("windows");

    workspace.endGroup();  // "windows"
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

    QSettings workspace(filename, QSettings::IniFormat);

    workspace.clear();

    // Save application information
    workspace.beginGroup("application");
    workspace.setValue("version", getCandiVersion());
    workspace.endGroup();  // "application"

    workspace.beginGroup("workspace");
    workspace.setValue("geometry", saveGeometry());
    workspace.setValue("state", saveState());
    workspace.endGroup();  // "workspace"

    workspace.beginGroup("windows");
    // TODO - Save settings for each sub-window
    workspace.endGroup();  // "windows"
}
