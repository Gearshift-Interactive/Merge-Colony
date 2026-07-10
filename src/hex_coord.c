#include "hex_coord.h"

bool HexEqual(HexCoord a, HexCoord b)
{
    return (a.x == b.x && a.y == b.y);
}
bool HexIsNeighbour(HexCoord a, HexCoord b)
{
    if (HexEqual(HexNeighbourTop(a), b)) return true;
    if (HexEqual(HexNeighbourBottom(a), b)) return true;
    if (HexEqual(HexNeighbourTopRight(a), b)) return true;
    if (HexEqual(HexNeighbourBottomRight(a), b)) return true;
    if (HexEqual(HexNeighbourTopLeft(a), b)) return true;
    if (HexEqual(HexNeighbourBottomLeft(a), b)) return true;
    return false;
}
HexCoord HexNeighbourTop(HexCoord origin)
{
    return (HexCoord) {
        .x = origin.x,
        .y = origin.y - 1
    };
}
HexCoord HexNeighbourBottom(HexCoord origin)
{
    return (HexCoord) {
        .x = origin.x,
        .y = origin.y + 1
    };
}
HexCoord HexNeighbourTopRight(HexCoord origin)
{
    if (origin.x % 2 == 0)
        return (HexCoord) {
            .x = origin.x + 1,
            .y = origin.y
        };
    else
        return (HexCoord) {
            .x = origin.x + 1,
            .y = origin.y - 1
        };
}
HexCoord HexNeighbourBottomRight(HexCoord origin)
{
    if (origin.x % 2 == 0)
        return (HexCoord) {
            .x = origin.x + 1,
            .y = origin.y + 1
        };
    else
        return (HexCoord) {
            .x = origin.x + 1,
            .y = origin.y
        };
}
HexCoord HexNeighbourTopLeft(HexCoord origin)
{
    if (origin.x % 2 == 0)
        return (HexCoord) {
            .x = origin.x - 1,
            .y = origin.y
        };
    else
        return (HexCoord) {
            .x = origin.x - 1,
            .y = origin.y - 1
        };
}
HexCoord HexNeighbourBottomLeft(HexCoord origin)
{
    if (origin.x % 2 == 0)
        return (HexCoord) {
            .x = origin.x - 1,
            .y = origin.y + 1
        };
    else
        return (HexCoord) {
            .x = origin.x - 1,
            .y = origin.y
        };
}
