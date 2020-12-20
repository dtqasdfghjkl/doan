#include<iostream>
#include<iostream>
#include<queue>
#define MAXN 100
using namespace std;
int n,xa,xb,ya,yb,a[MAXN*MAXN];

struct X
{
    int x;
    long long h;
};

struct cmp
{
    bool operator() (X a, X b)
    {
        return a.h > b.h;
    }
};

long long heuristic(int x,int y)
{
    return (x-xb)*(x-xb)+(y-yb)*(y-yb);
}

int cha[MAXN*MAXN];

bool GBFS()
{
    int ma = n*n;
    int ends = (xb-1)*n+yb;
    bool close[(n+1)*(n+1)];
    priority_queue< X, vector<X>, cmp > open;
    X curP = {(xa-1)*n+ya,heuristic(xa,ya)};

    open.push(curP);

    while(!open.empty())
    {
        curP = open.top();
        open.pop();
        X nextP;
        close[curP.x] = 1;
      //  cout<<curP.x<<" "<<curP.h<<endl;
        nextP.x = curP.x+n;
        nextP.h = heuristic((nextP.x-1)/n+1,(nextP.x-1)%n+1);
        if(nextP.x <= ma && !close[nextP.x] && a[nextP.x] == 0)
        {
            cha[nextP.x] = curP.x;
            if(nextP.x == ends)return 1;
            open.push(nextP);
            //close[nextP.x] = 1;
        }

        nextP.x = curP.x-n;
        nextP.h = heuristic((nextP.x-1)/n+1,(nextP.x-1)%n+1);
        if(nextP.x > 0 && !close[nextP.x] && a[nextP.x] == 0)
        {
            cha[nextP.x] = curP.x;
            if(nextP.x == ends)return 1;
            open.push(nextP);
           // close[nextP.x] = 1;
        }

        nextP.x = curP.x+1;
        nextP.h = heuristic((nextP.x-1)/n+1,(nextP.x-1)%n+1);
        if(nextP.x%n != 1 && !close[nextP.x] && a[nextP.x] == 0)
        {
            cha[nextP.x] = curP.x;
            if(nextP.x == ends)return 1;
            open.push(nextP);
           // close[nextP.x] = 1;
        }

        nextP.x = curP.x-1;
        nextP.h = heuristic((nextP.x-1)/n+1,(nextP.x-1)%n+1);
        if(nextP.x > 0)
        if(nextP.x%n != 0 && !close[nextP.x] && a[nextP.x] == 0)
        {
            cha[nextP.x] = curP.x;
            if(nextP.x == ends)return 1;
            open.push(nextP);
            //close[nextP.x] = 1;
        }
    }
    return 0;
}

void trace(int v)
{
    a[v] = 5;
    if(v ==(xa-1)*n+ya)return;
    trace(cha[v]);
}

int main()
{
    cin>>n;
    cin>>xa>>ya>>xb>>yb;
    int k = 1,x;
    for(int i = 1;i <= n;i++)
        for(int j = 1;j <= n;j++)
        {
            cin>>x;
            a[k++]  = x;
        }
    if(!GBFS())
    {
        cout<<"khong tim thay duong di";
        return 0;
    }
    trace((xb-1)*n+yb);
    k = 1;
    cout<<endl<<"Duong di tim duoc(ki hieu so 5):"<<endl<<endl;
    for(int i = 1;i <= n;i++)
    {
        for(int j = 1;j <= n;j++)
            cout<<a[k++]<<" ";
        cout<<endl;
    }
}
/*
8
1 1
5 7
0 0 0 0 0 0 0 0
0 0 1 0 0 0 0 0
0 0 1 0 1 1 0 0
0 0 1 0 1 0 0 0
0 0 0 0 1 0 0 0
0 0 0 0 1 0 0 0
0 0 0 1 1 0 0 0
0 0 0 0 0 0 0 0
*/
