#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

public slots:
    // Initialization functions
    void initCANInterface();
    void initMenus();
    void initSignalsSlots();

    // Actions
    void onClose();

    // Workspace
    void loadWorkspace(QString filename = QString());
    void saveWorkspace(QString filename = QString());

protected slots:
    // Display / update functions
    void updateDisplay();
    void updateWindowTitle();

    void showAboutInformation();

    void loadGlobalSettings();
    void saveGlobalSettings();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
