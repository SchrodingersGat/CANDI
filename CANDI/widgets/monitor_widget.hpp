#ifndef MONITOR_WIDGET_HPP
#define MONITOR_WIDGET_HPP

#include "ui_can_viewer.h"

#include "base_widget.hpp"

class CANMonitorWidget : public BaseWidget
{
    Q_OBJECT

public:
    CANMonitorWidget(QWidget *parent = nullptr);

public slots:
    virtual void updateDisplay() override;

protected:
    Ui::can_monitor ui;
};

#endif // MONITOR_WIDGET_HPP
