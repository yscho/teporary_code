#include <deque>

using namespace std;

#define MAXM	3
#define N_MAX 1002
#define MSG_MAX 100002


struct Message {
    int mID, uID1, uID2, timestamp;
    int isRead;
    int isInBox;
    int isSentBox;
} __messagePool[MSG_MAX];
int __messagePoolCnt;

Message* makeNewMessage(int mID, int uID1, int uID2, int timestamp) {
    __messagePool[__messagePoolCnt] = { mID, uID1, uID2, timestamp, 0, 0, 0 };
    return &__messagePool[__messagePoolCnt++];
}

class MessageQueue {
private:
    Message* data[MSG_MAX + 1];
    int cnt;

    bool compare(int i, int j) {
        int t1 = data[i]->timestamp;
        int t2 = data[j]->timestamp;
        if (t1 > t2) return true;
        if (t1 == t2 && data[i]->mID > data[j]->mID) return true;
        return false;
    }

    void swap(int i, int j) {
        Message* temp = data[i];
        data[i] = data[j];
        data[j] = temp;
    }
public:
    void init() {
        cnt = 0;
    }

    void push(Message* msg) {
        data[++cnt] = msg;
        int id = cnt;
        while (id > 1) {
            int parent = id / 2;
            if (compare(id, parent)) break;
            swap(id, parent);
            id = parent;
        }
    }
    
    void pop() {
        data[1] = data[cnt--];
        int id = 1;
        while (id * 2 <= cnt) {
            int left = id * 2;
            int right = id * 2 + 1;
            int child = left;
            if (right <= cnt && compare(left, right)) child = right;
            if (compare(child, id)) break;
            swap(id, child);
            id = child;
        }
    }
    
    Message* top() {
        return data[1];
    }

    int size() {
        return cnt;
    }
};


deque<Message*> sentBox[N_MAX];
deque<Message*> inBox[N_MAX];
MessageQueue messageQueue;
Message* messageMap[MSG_MAX];


void init(int N)
{
    __messagePoolCnt = 0;
    messageQueue.init();
    for (int i = 1; i <= N; i++) {
        sentBox[i].clear();
        inBox[i].clear();
    }
}

void run(int cTimestamp) {
    while (messageQueue.size() > 0) {
        Message* msg = messageQueue.top();
        if (msg->timestamp > cTimestamp) {
            break;
        }
        messageQueue.pop();
        if (!msg->isSentBox) {
            continue;
        }
        inBox[msg->uID2].push_front(msg);
        msg->isInBox = true;
    }
}

void sendMessage(int cTimestamp, int uID1, int uID2, int mID, int scheduleTimestamp)
{
    run(cTimestamp);
    Message* msg = makeNewMessage(mID, uID1, uID2, scheduleTimestamp);
    messageMap[mID] = msg;
    sentBox[uID1].push_front(msg);
    msg->isSentBox = true;
    messageQueue.push(msg);
}

int retrieveSentbox(int cTimestamp, int uID, int mIDList[MAXM], int uIDList[MAXM], int readList[MAXM])
{
    run(cTimestamp);
    Message* data[3];
    int cnt = 0;
    deque<Message*>::iterator iter;
    for (iter = sentBox[uID].begin(); iter != sentBox[uID].end(); iter++) {
        if ((*iter)->isSentBox) {
            mIDList[cnt] = (*iter)->mID;
            uIDList[cnt] = (*iter)->uID2;
            readList[cnt] = (*iter)->isRead;
            cnt++;
        }
        if (cnt == 3) break;
    }
	return cnt;
}

int retrieveInbox(int cTimestamp, int uID, int mIDList[MAXM], int uIDList[MAXM], int readList[MAXM])
{
    run(cTimestamp);
    Message* data[3];
    int cnt = 0;
    deque<Message*>::iterator iter;
    for (iter = inBox[uID].begin(); iter != inBox[uID].end(); iter++) {
        if ((*iter)->isInBox) {
            mIDList[cnt] = (*iter)->mID;
            uIDList[cnt] = (*iter)->uID1;
            readList[cnt] = (*iter)->isRead;
            cnt++;
        }
        if (cnt == 3) break;
    }
	return cnt;
}

int readMessage(int cTimestamp, int uID, int mID)
{
    run(cTimestamp);
    Message* msg = messageMap[mID];
    if (msg->uID1 == uID && msg->isSentBox) {
        return 1;
    }
    else if (msg->uID2 == uID && msg->isInBox) {
        msg->isRead = 1;
        return 1;
    }
	return 0;
}

int deleteMessage(int cTimestamp, int uID, int mID)
{
    run(cTimestamp);
    Message* msg = messageMap[mID];
    if (msg->uID1 == uID && msg->isSentBox) {
        msg->isSentBox = false;
        return 1;
    }
    else if (msg->uID2 == uID && msg->isInBox) {
        msg->isInBox = false;
        return 1;
    }

	return 0;
}
