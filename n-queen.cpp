#include<iostream>
#include<stdlib.h>
#include<ctime>
#define MAXN 100
using namespace std;

int n;

int cheoduoi[2*MAXN],cheotren[2*MAXN];

struct State
{
    int arr[MAXN];
    int h;
};


void xem()
{

    cout<<endl;
    cout<<"cheo tren: ";
    for(int i = 1;i <= n*2-1;i++)
    {
        cout<<cheotren[i];
    }
    cout<<endl;
    cout<<"cheo duoi: ";
    for(int i = 1;i <= n*2-1;i++)
    {
        cout<<cheoduoi[i];
    }
    cout<<endl<<"------------"<<endl;
}
int heuristic(int *arr)
{
    int h = 0;
    for(int i = 1;i <= n;i++)
    {
        int c = arr[i];
        h+=cheotren[c+i-1]+cheoduoi[n-i+c]-2;
    }
    return h;
}

State getNext(State cur)
{
    State temp = cur;
    int c = cur.arr[1];
    for(int i = 1;i <= n;i++)
        for(int j = 1;j <= n;j++)
        {
            temp = cur;
            swap(temp.arr[i],temp.arr[j]);
            cheotren[cur.arr[i]+i-1]--;
            cheoduoi[n-i+cur.arr[i]]--;
            cheotren[cur.arr[j]+j-1]--;
            cheoduoi[n-j+cur.arr[j]]--;
            cheotren[temp.arr[i]+i-1]++;
            cheoduoi[n-i+temp.arr[i]]++;
            cheotren[temp.arr[j]+j-1]++;
            cheoduoi[n-j+temp.arr[j]]++;
            temp.h = heuristic(temp.arr);
            if(temp.h < cur.h)
                return temp;
            cheotren[cur.arr[i]+i-1]++;
            cheoduoi[n-i+cur.arr[i]]++;
            cheotren[cur.arr[j]+j-1]++;
            cheoduoi[n-j+cur.arr[j]]++;
            cheotren[temp.arr[i]+i-1]--;
            cheoduoi[n-i+temp.arr[i]]--;
            cheotren[temp.arr[j]+j-1]--;
            cheoduoi[n-j+temp.arr[j]]--;
        }
    temp.h = -1;
    return temp;
}

State sol(int n)
{
    for(int i = 1;i <= n*2+1;i++)cheoduoi[i] = cheotren[i] = 0;
    // tao trang thai ban dau
    State curState;
    bool ck[100];
    for(int i = 1;i <= n;i++)ck[i] = 0;
    for(int i = 1;i <= n;i++)
    {
        curState.arr[i] = rand() % n + 1;
        while(ck[curState.arr[i]])curState.arr[i] = rand() % n + 1;
        int c = curState.arr[i];
        ck[curState.arr[i]] = 1;
        cheotren[i+c-1]++;
        cheoduoi[n-i+c]++;
    }

    //tinh ham danh gia
    curState.h = heuristic(curState.arr);

    //sinh trang thai moi cho den khi đến trang thai dich
    while(curState.h > 0)
    {
        curState = getNext(curState);
    }
    return curState;
}
main()
{
    srand(time(NULL));
    cin>>n;
    State x = sol(n);
    while(x.h == -1)x = sol(n);

    for(int i = 1;i <= n;i++)
    {
        for(int j = 1;j <= n;j++)
        {
            if(x.arr[i] == j)cout<<"Q ";
            else cout<<". ";
        }
        cout<<endl;
    }
    cout<<endl<<x.h;
}
