
#include "base_widget.hpp"


void BaseWidget::loadSettings(QSettings &settings)
{
    Q_UNUSED(settings);
}


void BaseWidget::saveSettings(QSettings &settings)
{
    Q_UNUSED(settings);
}


void BaseWidget::updateDisplay()
{

}


void BaseWidget::refresh()
{
    if (isVisible()) updateDisplay();
}


DockManager::DockManager(const QString &title, QWidget *widget, QWidget *parent, Qt::WindowFlags flags) :
    QDockWidget(title, parent, flags)
{
    setObjectName(title);
    setWidget(widget);

    // Prevent deletion when the widget closes
    setAttribute(Qt::WA_DeleteOnClose, false);

    DEBUG << "creating new DockManager -" << title;
}


DockManager::~DockManager()
{
    DEBUG << "destroying DockManager -" << objectName();
}


BaseWidget* DockManager::getWidget()
{
    return dynamic_cast<BaseWidget*>(widget());
}


void DockManager::refresh()
{
    if (isVisible())
    {
        auto *widget = getWidget();

        if (widget) widget->refresh();
    }
}


void DockManager::closeEvent(QCloseEvent *event)
{
    Q_UNUSED(event);

    if (toggleAction && toggleAction->isCheckable())
    {
        toggleAction->blockSignals(true);
        toggleAction->setChecked(false);
        toggleAction->blockSignals(false);
    }
}


void DockManager::setToggleAction(QAction *action)
{
    // If an action is already assigned, unassign it
    if (toggleAction)
    {
        disconnect(toggleAction, SIGNAL(toggled(bool)), this, SLOT(setVisible(bool)));
    }

    if (action && action->isCheckable())
    {
        toggleAction = action;
        connect(action, SIGNAL(toggled(bool)), this, SLOT(setVisible(bool)));

        setVisible(action->isChecked());

        updateActionState();
    }
}


void DockManager::updateActionState()
{
    if (toggleAction)
    {
        toggleAction->blockSignals(true);
        toggleAction->setChecked(isVisible());
        toggleAction->blockSignals(false);
    }
}
