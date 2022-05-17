#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#define bool int
#define true 1
#define false 0
#define A 0
#define B 1
int TRACE = 1;

/* ******************************************************************
  网络（第三层）具有以下特征：
  1. 网络延迟平均有5个时间单位(分布在1~10)，在流水线版本（网络中有其他数据分组）或其他情况下可能更长
  2. 数据分组可能损坏（可能是头或数据部分）或丢失，具体比例由运行参数决定
  3. 数据分组会按照交付的顺序传输（虽然它们有可能丢失）
**********************************************************************/

/* "msg" 是第五层交给第四层的数据单元 */
/* 它包含运输层需要传输的数据（字符数组） */
/* 请勿更改此处定义 */
struct msg
{
    char data[20];
};

/* pkt是从第四层交付给第三层的数据单元 */
/* 请勿更改此处定义 */
struct pkt
{
    int seqnum;
    int acknum;
    int checksum;
    char payload[20];
};

/* 在你编程中会用到以下4个函数接口，请直接使用而不要更改其定义 */
/* 具体使用方法见实验要求 */
void starttimer(int AorB, float increment);
void stoptimer(int AorB);
void tolayer3(int AorB, struct pkt packet);
void tolayer5(int AorB, struct msg message);


/********* 请完成以下7个函数 *********/
#define RTT  15.0            /* 往返时间 */
#define WINDOWSIZE 8         /* 窗口长度，即已被发送但还未被确认的分组的许可序号范围 */
#define FULLBUFFERSIZE 64    /* 缓冲区长度 */
#define SEQSPACE 9           /* 最小序列空间，值应为 WINDOWSIZE+1，引入此常量的目的是方便涉及到溢出的计算 */
#define NOTINUSE (-1)        /* 填充不需要使用的数据项 */

int ComputeChecksum(struct pkt packet)
{
    int checksum = 0;
    int i;

    checksum = packet.seqnum;
    checksum += packet.acknum;
    for (i = 0; i < 20; i++)
        checksum += (int)(packet.payload[i]);

    return checksum;
}

bool IsCorrupted(struct pkt packet)
{
    if (packet.checksum == ComputeChecksum(packet))
        return (false);
    else
        return (true);
}

/********* 发送端A的变量和函数 ************/

static struct pkt buffer[WINDOWSIZE];               /* 等待ACK的分组的数组 */
static int windowfirst, windowlast;                 /* 第早/最晚等待ACK的分组的数组序号（注意是数组序号不是报文序号） */
static int windowcount;                             /* 已发送但正在等待ACK的分组的数量 */
static int A_nextseqnum;                            /* 下一个可发送的分组的序号 */
static struct msg full_buffer[FULLBUFFERSIZE];      /* 缓冲区队列，用来存放窗口已满无法加入时A端第五层交付的数据，注意应先进先出 */
static int full_buffer_first, full_buffer_last;     /* 第早/最晚等待被A接收的数组序号 */
static int full_buffer_counter;                     /* 缓冲区计数器 */

/* 被第五层调用，参数是传往另一端的数据 */
void A_output(struct msg message)
{
    struct pkt sendpkt;
    int i;

    /* 如果窗口未满 */
    if (windowcount < WINDOWSIZE)
    {
        if (TRACE > 1)
            printf("A: 窗口未满，接受来自上层的message!\n");

        /* 为从第五层（上层）接受的msg创建分组 */
        sendpkt.seqnum = A_nextseqnum;
        sendpkt.acknum = NOTINUSE;
        for (i = 0; i < 20; i++)
            sendpkt.payload[i] = message.data[i];
        sendpkt.checksum = ComputeChecksum(sendpkt);

        /* 将分组加入窗口分组数组 */
        /* windowlast will always be 0 for alternating bit; but not for GoBackN */
        windowlast = (windowlast + 1) % WINDOWSIZE;
        buffer[windowlast] = sendpkt;
        windowcount++;

        /* 发送分组 */
        tolayer3(A, sendpkt);
        printf("A: 已将分组 %d 发送至中间层!\n", sendpkt.seqnum);

        /* 一旦窗口中加入分组就开始计时,且由于只有一个计时器，故它用于给最早的已发送但未被确认的分组的计时 */
        if (windowcount == 1)
            starttimer(A, RTT);

        /* 获取下一个序号, 要求能回滚至0而不是让序列号无限增大 */
        A_nextseqnum = (A_nextseqnum + 1) % SEQSPACE;
    }
    /* 如果窗口已满则阻止 */
    else
    {
        if (TRACE > 0)
            printf("A: 窗口已满，将message存入缓冲区等待发送...\n");

        /* 缓冲区未满执行if中步骤，否则不进行其它动作，该msg直接丢弃 */
        if (full_buffer_counter < FULLBUFFERSIZE)
        {
            full_buffer_last = (full_buffer_last + 1) % FULLBUFFERSIZE;
            full_buffer[full_buffer_last] = message;
            full_buffer_counter++;
        }
    }
}

/* 当给A第四层的一个数据分组到达时，被第三层调用 */
void A_input(struct pkt packet)
{
    int ackcount = 0;          /* 此ACK确认的序号大小 */
    int i;

    /* 如果收的ACK未受损 */
    if (!IsCorrupted(packet))
    {
        if (TRACE > 0)
            printf("A: 收到未受损的ACK %d \n", packet.acknum);

        /* 检查收到的分组是新ACK还是重复的ACK */
        if (windowcount != 0)
        {
            int first_seqnum = buffer[windowfirst].seqnum;
            int last_seqnum = buffer[windowlast].seqnum;
            /* 判断为新ACK的条件为：如果基序号小于最晚等待ACK的分组的序号，则ACK序号应介于两者之间； 如果基序号大于最晚等待ACK的分组的序号则相反 */
            if (((first_seqnum <= last_seqnum) && (packet.acknum >= first_seqnum && packet.acknum <= last_seqnum)) ||
                ((first_seqnum > last_seqnum) && (packet.acknum >= first_seqnum || packet.acknum <= last_seqnum)))
            {
                /* 收到的分组是新ACK */
                if (TRACE > 0)
                    printf("A: ACK %d是新ACK\n", packet.acknum);

                /* 累积确认 */
                if (packet.acknum >= first_seqnum)
                    ackcount = packet.acknum + 1 - first_seqnum;
                else
                    ackcount = SEQSPACE - first_seqnum + packet.acknum;

                /* 滑动窗口并接收缓冲区队列第一份msg（如果存在） */
                windowfirst = (windowfirst + ackcount) % WINDOWSIZE;
                windowcount = windowcount - ackcount;
                if (full_buffer_first != (full_buffer_last + 1) % FULLBUFFERSIZE)
                {
                    A_output(full_buffer[full_buffer_first]);
                    full_buffer_first = (full_buffer_first + 1) % FULLBUFFERSIZE;
                    full_buffer_counter--;
                }

                /* 如果收到一个ACK但仍有已发送但未被确认的分组，则定时器中断并重启 */
                stoptimer(A);
                if (windowcount > 0)
                    starttimer(A, RTT);
            }
            /* 收到重复ACK */
            else
                if (TRACE > 0)
                    printf("A: 收到重复ACK！\n");
        }
        else
            printf("A: 收到重复ACK！\n");
    }
    /* 收到受损ACK */
    else
        if (TRACE > 0)
            printf("A: 收到受损ACK！\n");
}

/* 计时器A超时时被调用 */
void A_timerinterrupt(void)
{
    int i;

    if (TRACE > 0)
        printf("A: 超时，重发分组！\n");

    for (i = 0; i < windowcount; i++)
    {

        if (TRACE > 0)
            printf("---A: 重发分组 %d\n", (buffer[(windowfirst + i) % WINDOWSIZE]).seqnum);

        tolayer3(A, buffer[(windowfirst + i) % WINDOWSIZE]);
        if (i == 0)
            starttimer(A, RTT);
    }
}

/* A_init()在A的其他函数前被执行恰好一次 */
/* 初始化A的窗口和序列号 */
void A_init(void)
{
    /* 初始序列号设置为0 */
    A_nextseqnum = 0;
    windowfirst = 0;
    windowlast = -1;   /* 新收到的分组将被放在windowlast+1的位置，当收到第一个来自上层的分组后windowfirst=windowlast=0，所以windowlast初始化为-1 */
    windowcount = 0;
    full_buffer_first = 0;
    full_buffer_last = -1;
    full_buffer_counter = 0;
}

/* 当给B第四层的一个数据分组到达时，被第三层调用*/

static int expectedseqnum; /* 期望收到的下一个分组的序列号 */
static int B_nextseqnum;   /* 下一个B将要发出的分组的序列号 */

void B_input(struct pkt packet)
{
    struct pkt ACKpkt;
    struct msg received_msg;
    int i;

    /* 如果收到的分组未受损且未失序 */
    if ((!IsCorrupted(packet)) && (packet.seqnum == expectedseqnum))
    {
        if (TRACE > 0)
            printf("B: 分组 %d 已正确接收,将对应message发送给上层并回复ACK!\n", packet.seqnum);

        /* 将收到的数据上传给第五层（上层） */
        for (i = 0; i < 20; i++)
            received_msg.data[i] = packet.payload[i];
        tolayer5(B, received_msg);
        expectedseqnum = (expectedseqnum + 1) % SEQSPACE;
    }
    else
    {
        /* 收到的分组受损或失序 */

        if (TRACE > 0)
            printf("B:分组受损或失序！\n");
    }

    /* 创建分组 */
    ACKpkt.acknum = packet.seqnum;        /* ACK序号应等于收到的分组的序号 */
    /* 后面三个语句对于gbn运行并无影响，意义仅为填充数据项 */
    ACKpkt.seqnum = B_nextseqnum;
    B_nextseqnum = (B_nextseqnum + 1) % 2;
    for (i = 0; i < 20; i++)
        ACKpkt.payload[i] = NOTINUSE;

    /* 计算检验和 */
    ACKpkt.checksum = ComputeChecksum(ACKpkt);

    /* 送出分组 */
    tolayer3(B, ACKpkt);
}

/* 计时器B超时时被调用 */
void B_timerinterrupt(void)
{
}

/* B_init()在B的其他函数前被执行恰好一次 */
/* 你可以用它做任意初始化配置 */
void B_init(void)
{
    expectedseqnum = 0;
    B_nextseqnum = 1;
}


/************************ 网络模拟代码部分 *************************
以下代码模拟了第三层及以下的网络环境：
1. 模拟第三四层之间数据分组传输时的丢包和损毁
2. 处理计时器的启动/停止，调用timerinterrupt函数
3. 生成第五层发向第四层的数据

注意：
1. 以下的代码可以不阅读或理解，按照实验要求的功能介绍使用4个接口函数即可
2. 不要直接引用以下定义的任何数据结构
3. 本实验中不需要更改以下代码
******************************************************************/

struct event
{
    float evtime;       /* event time */
    int evtype;         /* event type code */
    int eventity;       /* entity where event occurs */
    struct pkt* pktptr; /* ptr to packet (if any) assoc w/ this event */
    struct event* prev;
    struct event* next;
};
struct event* evlist = NULL; /* the event list */

/* possible events: */
#define TIMER_INTERRUPT 0
#define FROM_LAYER5 1
#define FROM_LAYER3 2

#define OFF 0
#define ON 1

/* int TRACE = 1; */   /* for my debugging */
int nsim = 0;    /* number of messages from 5 to 4 so far */
int nsimmax = 0; /* number of msgs to generate, then stop */
float time = 0.000;
float lossprob;    /* probability that a packet is dropped  */
float corruptprob; /* probability that one bit is packet is flipped */
float lambda;      /* arrival rate of messages from layer 5 */
int ntolayer3;     /* number sent into layer 3 */
int nlost;         /* number lost in media */
int ncorrupt;      /* number corrupted by media*/

void init(int argc, char** argv);
void generate_next_arrival(void);
void insertevent(struct event* p);

#define BIDIRECTIONAL 0 /* change to 1 if you're doing extra credit */
/* and write a routine called B_output */

void B_output(struct msg message)
{
}

int main(int argc, char** argv)
{
    struct event* eventptr;
    struct msg msg2give;
    struct pkt pkt2give;

    int i, j;
    char c;

    init(argc, argv);
    A_init();
    B_init();

    while (1)
    {
        eventptr = evlist; /* get next event to simulate */
        if (eventptr == NULL)
            goto terminate;
        evlist = evlist->next; /* remove this event from event list */
        if (evlist != NULL)
            evlist->prev = NULL;
        if (TRACE >= 2)
        {
            printf("\nEVENT time: %f,", eventptr->evtime);
            printf("  type: %d", eventptr->evtype);
            if (eventptr->evtype == 0)
                printf(", timerinterrupt  ");
            else if (eventptr->evtype == 1)
                printf(", fromlayer5 ");
            else
                printf(", fromlayer3 ");
            printf(" entity: %d\n", eventptr->eventity);
        }
        time = eventptr->evtime; /* update time to next event time */
        if (eventptr->evtype == FROM_LAYER5)
        {
            if (nsim < nsimmax)
            {
                if (nsim + 1 < nsimmax)
                    generate_next_arrival(); /* set up future arrival */
                /* fill in msg to give with string of same letter */
                j = nsim % 26;
                for (i = 0; i < 20; i++)
                    msg2give.data[i] = 97 + j;
                msg2give.data[19] = 0;
                if (TRACE > 2)
                {
                    printf("          MAINLOOP: data given to student: ");
                    for (i = 0; i < 20; i++)
                        printf("%c", msg2give.data[i]);
                    printf("\n");
                }
                nsim++;
                if (eventptr->eventity == A)
                    A_output(msg2give);
                else
                    B_output(msg2give);
            }
        }
        else if (eventptr->evtype == FROM_LAYER3)
        {
            pkt2give.seqnum = eventptr->pktptr->seqnum;
            pkt2give.acknum = eventptr->pktptr->acknum;
            pkt2give.checksum = eventptr->pktptr->checksum;
            for (i = 0; i < 20; i++)
                pkt2give.payload[i] = eventptr->pktptr->payload[i];
            if (eventptr->eventity == A) /* deliver packet by calling */
                A_input(pkt2give);       /* appropriate entity */
            else
                B_input(pkt2give);
            free(eventptr->pktptr); /* free the memory for packet */
        }
        else if (eventptr->evtype == TIMER_INTERRUPT)
        {
            if (eventptr->eventity == A)
                A_timerinterrupt();
            else
                B_timerinterrupt();
        }
        else
        {
            printf("INTERNAL PANIC: unknown event type \n");
        }
        free(eventptr);
    }

terminate:
    printf(
        "在 %f 个时间单位，第五层发送 %d 条msg后模拟停止\n",
        time, nsim);
}

void init(int argc, char** argv) /* initialize the simulator */
{
    int i;
    float sum, avg;
    float jimsrand();

    if (argc != 6)
    {
        printf("使用方法: %s\nnum_sim  prob_loss  prob_corrupt  interval  debug_level\n", argv[0]);
        exit(1);
    }

    nsimmax = atoi(argv[1]);
    lossprob = atof(argv[2]);
    corruptprob = atof(argv[3]);
    lambda = atof(argv[4]);
    TRACE = atoi(argv[5]);
    printf("模拟第五层发送消息次数，num_sim: %d\n", nsimmax);
    printf("数据分组丢失概率，prob_loss: %f\n", lossprob);
    printf("数据分组损坏概率，prob_corrupt: %f\n", corruptprob);
    printf("第五层发送消息平均间隔，interval: %f\n", lambda);
    printf("debug等级，debug_level: %d\n", TRACE);

    srand(9999); /* init random number generator */
    sum = 0.0;   /* test random number generator for students */
    for (i = 0; i < 1000; i++)
        sum = sum + jimsrand(); /* jimsrand() should be uniform in [0,1] */
    avg = sum / 1000.0;
    if (avg < 0.25 || avg > 0.75)
    {
        printf("It is likely that random number generation on your machine\n");
        printf("is different from what this emulator expects.  Please take\n");
        printf("a look at the routine jimsrand() in the emulator code. Sorry. \n");
        exit(1);
    }

    ntolayer3 = 0;
    nlost = 0;
    ncorrupt = 0;

    time = 0.0;              /* initialize time to 0.0 */
    generate_next_arrival(); /* initialize event list */
}

/****************************************************************************/
/* jimsrand(): return a float in range [0,1].  The routine below is used to */
/* isolate all random number generation in one location.  We assume that the*/
/* system-supplied rand() function return an int in therange [0,mmm]        */
/****************************************************************************/
float jimsrand(void)
{
    double mmm = RAND_MAX;
    float x;          /* individual students may need to change mmm */
    x = rand() / mmm; /* x should be uniform in [0,1] */
    return (x);
}

/********************* EVENT HANDLINE ROUTINES *******/
/*  The next set of routines handle the event list   */
/*****************************************************/

void generate_next_arrival(void)
{
    double x, log(), ceil();
    struct event* evptr;
    float ttime;
    int tempint;

    if (TRACE > 2)
        printf("          GENERATE NEXT ARRIVAL: creating new arrival\n");

    x = lambda * jimsrand() * 2; /* x is uniform on [0,2*lambda] */
                                 /* having mean of lambda        */
    evptr = (struct event*)malloc(sizeof(struct event));
    evptr->evtime = time + x;
    evptr->evtype = FROM_LAYER5;
    if (BIDIRECTIONAL && (jimsrand() > 0.5))
        evptr->eventity = B;
    else
        evptr->eventity = A;
    insertevent(evptr);
}

void insertevent(struct event* p)
{
    struct event* q, * qold;

    if (TRACE > 2)
    {
        printf("            INSERTEVENT: time is %lf\n", time);
        printf("            INSERTEVENT: future time will be %lf\n", p->evtime);
    }
    q = evlist; /* q points to header of list in which p struct inserted */
    if (q == NULL)
    { /* list is empty */
        evlist = p;
        p->next = NULL;
        p->prev = NULL;
    }
    else
    {
        for (qold = q; q != NULL && p->evtime > q->evtime; q = q->next)
            qold = q;
        if (q == NULL)
        { /* end of list */
            qold->next = p;
            p->prev = qold;
            p->next = NULL;
        }
        else if (q == evlist)
        { /* front of list */
            p->next = evlist;
            p->prev = NULL;
            p->next->prev = p;
            evlist = p;
        }
        else
        { /* middle of list */
            p->next = q;
            p->prev = q->prev;
            q->prev->next = p;
            q->prev = p;
        }
    }
}

void printevlist(void)
{
    struct event* q;
    int i;
    printf("--------------\nEvent List Follows:\n");
    for (q = evlist; q != NULL; q = q->next)
    {
        printf("Event time: %f, type: %d entity: %d\n", q->evtime, q->evtype,
            q->eventity);
    }
    printf("--------------\n");
}

/********************** Student-callable ROUTINES ***********************/

/* called by students routine to cancel a previously-started timer */
void stoptimer(int AorB /* A or B is trying to stop timer */)
{
    struct event* q, * qold;

    if (TRACE > 2)
        printf("          STOP TIMER: stopping timer at %f\n", time);
    /* for (q=evlist; q!=NULL && q->next!=NULL; q = q->next)  */
    for (q = evlist; q != NULL; q = q->next)
        if ((q->evtype == TIMER_INTERRUPT && q->eventity == AorB))
        {
            /* remove this event */
            if (q->next == NULL && q->prev == NULL)
                evlist = NULL;        /* remove first and only event on list */
            else if (q->next == NULL) /* end of list - there is one in front */
                q->prev->next = NULL;
            else if (q == evlist)
            { /* front of list - there must be event after */
                q->next->prev = NULL;
                evlist = q->next;
            }
            else
            { /* middle of list */
                q->next->prev = q->prev;
                q->prev->next = q->next;
            }
            free(q);
            return;
        }
    printf("Warning: unable to cancel your timer. It wasn't running.\n");
}

void starttimer(int AorB /* A or B is trying to stop timer */, float increment)
{
    struct event* q;
    struct event* evptr;

    if (TRACE > 2)
        printf("          START TIMER: starting timer at %f\n", time);
    /* be nice: check to see if timer is already started, if so, then  warn */
    /* for (q=evlist; q!=NULL && q->next!=NULL; q = q->next)  */
    for (q = evlist; q != NULL; q = q->next)
        if ((q->evtype == TIMER_INTERRUPT && q->eventity == AorB))
        {
            printf("Warning: attempt to start a timer that is already started\n");
            return;
        }

    /* create future event for when timer goes off */
    evptr = (struct event*)malloc(sizeof(struct event));
    evptr->evtime = time + increment;
    evptr->evtype = TIMER_INTERRUPT;
    evptr->eventity = AorB;
    insertevent(evptr);
}

/************************** TOLAYER3 ***************/
void tolayer3(int AorB /* A or B is trying to stop timer */, struct pkt packet)
{
    struct pkt* mypktptr;
    struct event* evptr, * q;
    float lastime, x;
    int i;

    ntolayer3++;

    /* simulate losses: */
    if (jimsrand() < lossprob)
    {
        nlost++;
        if (TRACE > 0)
            printf("          TOLAYER3: packet being lost\n");
        return;
    }

    /* make a copy of the packet student just gave me since he/she may decide */
    /* to do something with the packet after we return back to him/her */
    mypktptr = (struct pkt*)malloc(sizeof(struct pkt));
    mypktptr->seqnum = packet.seqnum;
    mypktptr->acknum = packet.acknum;
    mypktptr->checksum = packet.checksum;
    for (i = 0; i < 20; i++)
        mypktptr->payload[i] = packet.payload[i];
    if (TRACE > 2)
    {
        printf("          TOLAYER3: seq: %d, ack %d, check: %d ", mypktptr->seqnum,
            mypktptr->acknum, mypktptr->checksum);
        for (i = 0; i < 20; i++)
            printf("%c", mypktptr->payload[i]);
        printf("\n");
    }

    /* create future event for arrival of packet at the other side */
    evptr = (struct event*)malloc(sizeof(struct event));
    evptr->evtype = FROM_LAYER3;      /* packet will pop out from layer3 */
    evptr->eventity = (AorB + 1) % 2; /* event occurs at other entity */
    evptr->pktptr = mypktptr;         /* save ptr to my copy of packet */
                                      /* finally, compute the arrival time of packet at the other end.
                                         medium can not reorder, so make sure packet arrives between 1 and 10
                                         time units after the latest arrival time of packets
                                         currently in the medium on their way to the destination */
    lastime = time;
    /* for (q=evlist; q!=NULL && q->next!=NULL; q = q->next) */
    for (q = evlist; q != NULL; q = q->next)
        if ((q->evtype == FROM_LAYER3 && q->eventity == evptr->eventity))
            lastime = q->evtime;
    evptr->evtime = lastime + 1 + 9 * jimsrand();

    /* simulate corruption: */
    if (jimsrand() < corruptprob)
    {
        ncorrupt++;
        if ((x = jimsrand()) < .75)
            mypktptr->payload[0] = 'Z'; /* corrupt payload */
        else if (x < .875)
            mypktptr->seqnum = 999999;
        else
            mypktptr->acknum = 999999;
        if (TRACE > 0)
            printf("          TOLAYER3: packet being corrupted\n");
    }

    if (TRACE > 2)
        printf("          TOLAYER3: scheduling arrival on other side\n");
    insertevent(evptr);
}

void tolayer5(int AorB, struct msg message)
{
    int i;
    if (TRACE > 2)
    {
        printf("          TOLAYER5: data received: ");
        for (i = 0; i < 20; i++)
            printf("%c", message.data[i]);
        printf("\n");
    }
}