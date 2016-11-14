struct ControlPanel {
    unsigned long long panelUID:56;
    unsigned long long isRegistered:1;
    unsigned long long isLinked:1;
    unsigned long long panelVersion:5;
    unsigned long long:0;
    byte firmwareVersionNum:5;
    byte firmwareRevisionNum:3;
};

struct Tag {
    unsigned long tagUID;
    unsigned long scanTime;
    unsigned int patternID:7;
    unsigned int activeState:1;
    unsigned int storageCategory:1;
    unsigned int foodCategory:3;
    unsigned int cookedCategory:2;
    unsigned int needsUpdate:1;
    unsigned int :0;
};
