#ifndef CLIPBOARD_H
#define CLIPBOARD_H

struct TileData;

class Clipboard : public QObject
{
	Q_OBJECT

public:
	Clipboard();
	~Clipboard();

	void Paste();
	
public slots:
	void Copy(QList<TileData> copyTiles);
	

signals:
	void PasteTiles(QList<TileData> pasteTiles);


private:
	QList<TileData> tiles;
};

#endif
