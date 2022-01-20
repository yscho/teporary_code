#include <iostream>
#include <vector>

using namespace std;

#define MAX_N    100
#define MAX_TOOL 50

struct ProcessStep {
    int PS_number;

};

class stepTool {
    int ProcessN;

};

//1)     다음 공정 설비가 비어있으면, 바로 해당 설비로 이동하여 가공을 시작한다.
//다음 공정 설비가 동일 시점에 가공을 완료했으면, 빈 설비로 간주한다.

//2개 이상의 설비가 빈 경우 가공시간(pt)이 제일 짧은 설비로 이동하여 가공한다.
vector<ProcessStep*> vPS_arr;

void init(int N) { //공정의 수
    vPS_arr.clear();
    for (int i = 0; i < N; i++)
    {
        vPS_arr.push_back(new ProcessStep);
    }

}

void setupTool(int T, int stepNo[5000], int procTime[5000]) {
//T: 모든 공정의 설비 수의 합(3 ≤ T ≤ 5, 000)
//stepNo : 각 설비의 “공정번호”의 배열로 길이는 T이다. (0 ≤ “공정번호” < N)
  //  procTime : 각 설비의 가공시간(pt)의 배열로 길이는 T이다. (5 ≤ pt ≤ 6, 000)

}

void addLot(int time, int number) {
    //time: Lot이 공정0에 추가된 시점의 timestamp (0 ≤ time ≤ 100,000)
    //number: 공정0에 추가된 Lot의 수
    //
}

int simulate(int time, int wip[MAX_N]) {
    return 0;
}