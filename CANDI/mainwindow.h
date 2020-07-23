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
    void initMenus();
    void initSignalsSlots();

    // Display / update functions
    void updateDisplay();
    void updateWindowTitle();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
