// Thread statuses
#define THS_RUN 0x01
#define THS_READY 0x02
#define THS_WAIT 0x04
#define THS_SUSPEND 0x08
#define THS_WAITSUSPEND 0x0C // THS_WAIT | THS_SUSPEND
#define THS_DORMANT 0x10

typedef struct 
{
    int status;
    void *function;
    void *stack;
    int stackSize;
    void *gpRegister;
    int initialPriority;
    int currentPriority;
    unsigned int attr;
    unsigned int option;
} ThreadParam;
