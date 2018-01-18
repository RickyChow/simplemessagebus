#define EVENT_MESSAGE_PARAM_DATA \
EVENT_MESSAGE_DEF( TestEvent,\
    int                intValue;\
    std::string        test; \
                                )\
EVENT_MESSAGE_DEF( SignStatus,\
    int signId; \
    std::string  signName; \
    int status; \
    int messageId; \
    )\


