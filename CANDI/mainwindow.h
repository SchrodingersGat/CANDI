#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <qlist.h>

#include "base_widget.hpp"

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
    void initWidgets();
    void initSignalsSlots();

    // Actions
    void onClose();
    void onLoadWorkspace();
    void onSaveWorkspace();

    void onCanConnect();
    void onCanDisconnect();
    void onCanConfigure();
    void onCanShowStats();


protected slots:
    // Display / update functions
    void updateDisplay();
    void updateWindowTitle();

    void showAboutInformation();

    void loadWorkspace(QString filename = QString());
    void saveWorkspace(QString filename = QString());

    void loadGlobalSettings();
    void saveGlobalSettings();

protected:
    Ui::MainWindow *ui;
    QList<DockManager*> dockedWidgets;

    bool addDockedWidget(DockManager* manager, QAction* action);
    bool addDockedWidget(QWidget* widget, QAction* action);
};

#endif // MAINWINDOW_H
