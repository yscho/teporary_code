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

//1)     ���� ���� ���� ���������, �ٷ� �ش� ����� �̵��Ͽ� ������ �����Ѵ�.
//���� ���� ���� ���� ������ ������ �Ϸ�������, �� ����� �����Ѵ�.

//2�� �̻��� ���� �� ��� �����ð�(pt)�� ���� ª�� ����� �̵��Ͽ� �����Ѵ�.
vector<ProcessStep*> vPS_arr;

void init(int N) { //������ ��
    vPS_arr.clear();
    for (int i = 0; i < N; i++)
    {
        vPS_arr.push_back(new ProcessStep);
    }

}

void setupTool(int T, int stepNo[5000], int procTime[5000]) {
//T: ��� ������ ���� ���� ��(3 �� T �� 5, 000)
//stepNo : �� ������ ��������ȣ���� �迭�� ���̴� T�̴�. (0 �� ��������ȣ�� < N)
  //  procTime : �� ������ �����ð�(pt)�� �迭�� ���̴� T�̴�. (5 �� pt �� 6, 000)

}

void addLot(int time, int number) {
    //time: Lot�� ����0�� �߰��� ������ timestamp (0 �� time �� 100,000)
    //number: ����0�� �߰��� Lot�� ��
    //
}

int simulate(int time, int wip[MAX_N]) {
    return 0;
}