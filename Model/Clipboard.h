#ifndef CLIPBOARD_H
#define CLIPBOARD_H

#include <QObject>

class Clipboard : public QObject
{
    Q_OBJECT
public:
    explicit Clipboard(QObject *parent = 0);
    ~Clipboard();

    void Paste();

signals:
    void PasteTiles(QList<Tile> pasteTiles);

public slots:
    void Copy(QList<Tile> copyTiles);

private:
    QList<Tile> tiles;
};

#endif // CLIPBOARD_H
