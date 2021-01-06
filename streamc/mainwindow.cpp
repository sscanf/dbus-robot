#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{

    m_pWidget = new QQuickWidget (this);
//    connect (m_pWidget, SIGNAL (statusChanged(QQuickWidget::Status)), this, SLOT (onStatusChanged(QQuickWidget::Status)));
    m_pWidget->setSource (QUrl ("qrc:/MainMenu.qml"));
    m_pWidget->setResizeMode(QQuickWidget::SizeRootObjectToView);
    m_pWidget->setFixedWidth(900);
    m_pWidget->setFixedHeight(563);
    setWindowTitle("Main Menu");
    setFixedWidth(900);
    setFixedHeight(563);


    QQuickItem *pItem = m_pWidget->rootObject();
    connect (pItem, SIGNAL (launch(QString)), this, SLOT (onApp(QString)));

    m_pWidgetThreshold = new streamClientWidget("192.168.0.1",1235);
    m_pWidgetResult = new streamClientWidget("192.168.0.1",1236);
    m_pWidgetStatus = new statusWidget();
    m_pWidgetPower = new powerWidget();
    m_pWidgetIRCamera = new IRCameraWidget();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::onApp(QString app)
{
    QWidget *pWidget=nullptr;

    if (app == "speedPannel")
        pWidget = m_pWidgetStatus;

    if (app == "powerPannel")
        pWidget = m_pWidgetPower;

    if (app == "cvPannel") {
        pWidget = m_pWidgetResult;
        onApp("thresshold");
    }

    if (app == "threshold") {
        pWidget = m_pWidgetThreshold;
    }

    if (app == "ircameraPannel") {
        pWidget = m_pWidgetIRCamera;
    }

    if (pWidget) {
        if (!pWidget->isVisible())
            pWidget->show();
        else
            pWidget->hide();
    }
}
