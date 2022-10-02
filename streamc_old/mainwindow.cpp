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
    connect(pItem, SIGNAL(launch(QString)), this, SLOT(onApp(const QString &)));

    m_pWidgetThreshold = new streamClientWidget(QStringLiteral(ROBOT_IP), 1235);
    m_pWidgetResult    = new streamClientWidget(QStringLiteral(ROBOT_IP), 1236);
    m_pWidgetPower     = new powerWidget(this);
    m_pWidgetIRCamera  = new IRCameraWidget(this);
    m_pWidgetStatus    = new statusWidget(this);
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::onApp(const QString &app) {
    QWidget *pWidget = nullptr;

    if (app == QStringLiteral("speedPannel"))
        pWidget = m_pWidgetStatus;

    if (app == QStringLiteral("powerPannel"))
        pWidget = m_pWidgetPower;

    if (app == QStringLiteral("cvPannel")) {
        pWidget = m_pWidgetResult;
        onApp("thresshold");
    }

    if (app == QStringLiteral("threshold")) {
        pWidget = m_pWidgetThreshold;
    }

    if (app == QStringLiteral("ircameraPannel")) {
        pWidget = m_pWidgetIRCamera;
    }

    if (pWidget) {
        if (!pWidget->isVisible())
            pWidget->show();
        else
            pWidget->hide();
    }
}
