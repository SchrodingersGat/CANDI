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
    void onLoadWorkspace();
    void onSaveWorkspace();

    void onCanConnect();
    void onCanDisconnect();


protected slots:
    // Display / update functions
    void updateDisplay();
    void updateWindowTitle();

    void showAboutInformation();

    void loadWorkspace(QString filename = QString());
    void saveWorkspace(QString filename = QString());

    void loadGlobalSettings();
    void saveGlobalSettings();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
