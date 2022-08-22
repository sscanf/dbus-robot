
#ifndef GRADIENTE_H
#define GRADIENTE_H

#include <QtCore>
#include <QQuickPaintedItem>
#include <QPainter>

/*!
 * \brief The Gradiente class
 *
 * Small class that offers horizontal gradient visual items.
 *
 * Normally, QML only allows for vertical gradients, so to get other types on plain QML; some tinkering with rotations and clipping would be needed.
 *
 * This plugins draws rectangular items with horizontal gradient without resorting to that techniques.
 *
 */

class Gradiente : public QQuickPaintedItem
{
    Q_OBJECT
    Q_PROPERTY(QList<QString> colores   READ colores    WRITE setColores    NOTIFY fondoChanged)

Q_PROPERTY(QList<qreal> puntos          READ puntos         WRITE setPuntos         NOTIFY fondoChanged)
Q_PROPERTY(QPointF      puntoInicial    READ puntoInicial   WRITE setPuntoInicial   NOTIFY fondoChanged)
Q_PROPERTY(QPointF      puntoFinal      READ puntoFinal     WRITE setPuntoFinal     NOTIFY fondoChanged)

public:
    void            setColores      (const QList<QString> &cs);
    QList<QString>  colores         () const;
    void            setPuntos       (const QList<qreal> &ps);
    QList<qreal>    puntos          () const;
    void            setPuntoInicial (const QPointF &p);
    void            setPuntoFinal   (const QPointF &p);
    QPointF         puntoInicial    () const;
    QPointF         puntoFinal      () const;

signals:
    void fondoChanged();

public:
    explicit Gradiente(QQuickPaintedItem *parent = 0);
    void     paint(QPainter *painter);

signals:

public slots:

private:
    QList<QString>  m_colores;
    QList<qreal>    m_puntos;
    QPointF         m_pi;
    QPointF         m_pf;

};

#endif // GRADIENTE_H

