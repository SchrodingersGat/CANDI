#ifndef BASE_WIDGET_HPP
#define BASE_WIDGET_HPP

#include <qwidget.h>
#include <qsettings.h>
#include <qdockwidget.h>
#include <QCloseEvent>
#include <QAction>

#include "debug.hpp"


/**
 * @brief The BaseWidget class is a wrapper QWidget that provides some common functions
 */
class BaseWidget : public QWidget
{
    Q_OBJECT

public:
    BaseWidget(QString name, QWidget *parent = nullptr) : QWidget(parent)
    {
        setObjectName(name);
    }

    virtual ~BaseWidget() {}

    virtual void loadSettings(QSettings& settings);
    virtual void saveSettings(QSettings& settings);

public slots:
    void refresh();

protected:
    virtual void updateDisplay();
};


class DockManager : public QDockWidget
{
    Q_OBJECT

public:
    DockManager(const QString& title, QWidget* widget, QWidget* parent, Qt::WindowFlags flags = Qt::WindowFlags());
    virtual ~DockManager();

    void setToggleAction(QAction* action);

public slots:
    void refresh();
    void updateActionState();

protected:
    void closeEvent(QCloseEvent* event) override;

    QAction* toggleAction = nullptr;
    BaseWidget* getWidget();
};

#endif // BASE_WIDGET_HPP
