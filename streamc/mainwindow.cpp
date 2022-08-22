#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow) {

    m_pWidget = new QQuickWidget(this);
    //    connect (m_pWidget, SIGNAL (statusChanged(QQuickWidget::Status)), this, SLOT (onStatusChanged(QQuickWidget::Status)));
    m_pWidget->setSource(QUrl(QStringLiteral("qrc:/MainMenu.qml")));
    m_pWidget->setResizeMode(QQuickWidget::SizeRootObjectToView);
    m_pWidget->setFixedWidth(900);
    m_pWidget->setFixedHeight(563);
    setWindowTitle(QStringLiteral("Main Menu"));
    setFixedWidth(900);
    setFixedHeight(563);

    QQuickItem *pItem = m_pWidget->rootObject();
    connect(pItem, SIGNAL(launch(QString)), this, SLOT(onApp(QString)));

    m_pWidgetThreshold = new streamClientWidget(ROBOT_IP, 1235);
    m_pWidgetResult    = new streamClientWidget(ROBOT_IP, 1236);
    m_pWidgetStatus    = new statusWidget();
    m_pWidgetPower     = new powerWidget();
    m_pWidgetIRCamera  = new IRCameraWidget();
    m_pSensorsWidget   = new SensorsWidget();
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::onApp(const QString &app) {
    QWidget *pWidget = nullptr;

    if (app == QLatin1String("speedPannel"))
        pWidget = m_pWidgetStatus;

    if (app == QLatin1String("powerPannel"))
        pWidget = m_pWidgetPower;

    if (app == QLatin1String("cvPannel")) {
        pWidget = m_pWidgetResult;
        onApp(QStringLiteral("thresshold"));
    }

    if (app == QLatin1String("threshold")) {
        pWidget = m_pWidgetThreshold;
    }

    if (app == QLatin1String("ircameraPannel")) {
        pWidget = m_pWidgetIRCamera;
    }

    if (app == QLatin1String("sensorsPannel")) {
        pWidget = m_pSensorsWidget;
    }

    if (pWidget) {
        if (!pWidget->isVisible())
            pWidget->show();
        else
            pWidget->hide();
    }
}
