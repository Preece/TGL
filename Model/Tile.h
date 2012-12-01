#ifndef TILE_H
#define TILE_H

class Tile
{
private:
    int originX, originY;
    int collision;

    int x, y;

public:
    Tile();

    void SetPos(int newX, int newY) { x = newX; y = newY; }
    void SetX(int newX) { x = newX; }
    void SetY(int newY) { y = newY; }
    int GetX() { return x; }
    int GetY() { return y; }

    void SetCollision(int newType) { collision = newType; }
    int GetCollision();

    void SetOrigin(int newX, int newY) { originX = newX; originY = newY; }
    void SetXOrigin(int newX) { originX = newX; }
    void SetYOrigin(int newY) { originY = newY; }
    int GetXOrigin() { return originX; }
    int GetYOrigin() { return originY; }

};

#endif // TILE_H
