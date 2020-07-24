
#include "monitor_widget.hpp"


CANMonitorWidget::CANMonitorWidget(QWidget *parent) : BaseWidget("CANMonitor", parent)
{
    ui.setupUi(this);

    setWindowTitle(tr("CAN Monitor"));
}


void CANMonitorWidget::updateDisplay()
{
    // TODO
}
