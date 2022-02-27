#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QCommandLineParser>
#include <QQmlContext>
#include <pthread.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>

void *pthread(void *arg) {
    int   fd;
    QObject *pObject= (QObject *) arg;
    const char *file = "/tmp/zoscreen";
    mkfifo(file, 0x666);
    char message[80];

    for (;;) {
        fd = open(file, O_RDONLY);
        memset(message, 0, sizeof(message));
        int size = read(fd, message, 80);
        Q_UNUSED (size)
        QMetaObject::invokeMethod(pObject , "setText", Q_ARG(QVariant, message));
        close(fd);
        usleep(1000);
    }
}

int main(int argc, char *argv[])
{
    pthread_t ptHandler;
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QGuiApplication app(argc, argv);

    const QUrl url(QStringLiteral("qrc:/main.qml"));
    QQmlApplicationEngine engine;

    engine.load(url);
    pthread_create(&ptHandler, NULL, &pthread, (void *)engine.rootObjects().at(0));
    return app.exec();
}
