#ifndef _ROOM_H
#define _ROOM_H
struct floorData {
    int ceiling=0, floor=0; // 1 = it exists.
};
class room {
public:
    room();
private:
    floorData floors[];
};
#endif
