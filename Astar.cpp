#include<iostream>
#include<queue>
#include<map>
#define MAXN 100
using namespace std;
int n,xa,xb,ya,yb,a[MAXN*MAXN],d[MAXN*MAXN];

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
    return (max(x-xb,xb-x)+max(y-yb,yb-y));
}

int cha[MAXN*MAXN];

bool Astar()
{
    int ma = n*n;
    int ends = (xb-1)*n+yb;
    priority_queue< X, vector<X>, cmp > open;
    X curP = {(xa-1)*n+ya,heuristic(xa,ya)};

    open.push(curP);
    d[curP.x] = 0;

    while(!open.empty())
    {
        curP = open.top();
        open.pop();
        X nextP;

        cout<<curP.x<<" "<<curP.h<<" "<<cha[curP.x]<<" "<<d[curP.x]<<endl;
        nextP.x = curP.x+n;
        nextP.h = d[curP.x]+1+heuristic((nextP.x-1)/n+1,(nextP.x-1)%n+1);
        if(nextP.x <= ma && a[nextP.x] == 0)
        {
            if(d[nextP.x] > d[curP.x]+1)
            {
                cha[nextP.x] = curP.x;
                d[nextP.x] = d[curP.x]+1;
                if(nextP.x == ends)return 1;
                open.push(nextP);
            }
        }

        nextP.x = curP.x-n;
        nextP.h = d[curP.x]+1+heuristic((nextP.x-1)/n+1,(nextP.x-1)%n+1);
        if(nextP.x > 0 && a[nextP.x] == 0)
        {
            if(d[nextP.x] > d[curP.x]+1)
            {
                cha[nextP.x] = curP.x;
                d[nextP.x] = d[curP.x]+1;
                if(nextP.x == ends)return 1;
                open.push(nextP);
            }
        }

        nextP.x = curP.x+1;
        nextP.h = d[curP.x]+1+heuristic((nextP.x-1)/n+1,(nextP.x-1)%n+1);
        if(nextP.x%n != 1 && a[nextP.x] == 0)
        {
          //  cout<<d[curP.x]<<endl;
            if(d[nextP.x] > d[curP.x]+1)
            {
                cha[nextP.x] = curP.x;
                d[nextP.x] = d[curP.x]+1;
                if(nextP.x == ends)return 1;
                open.push(nextP);
            }
        }

        nextP.x = curP.x-1;
        nextP.h = d[curP.x]+1+heuristic((nextP.x-1)/n+1,(nextP.x-1)%n+1);
        if(nextP.x > 0)
        if(nextP.x%n != 0 && a[nextP.x] == 0)
        {
            if(d[nextP.x] > d[curP.x]+1)
            {
                cha[nextP.x] = curP.x;
                d[nextP.x] = d[curP.x]+1;
                if(nextP.x == ends)return 1;
                open.push(nextP);
            }
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

main()
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
    for(int i = 1;i <= n*n;i++)d[i] = 10000000;
    if(!Astar())
    {
        cout<<"khong tim thay duong di";
        return 0;
    }
    cout<<endl<<"Duong di tim duoc(ki hieu so 5):"<<endl<<endl;
    trace((xb-1)*n+yb);
    k = 1;
    for(int i = 1;i <= n;i++)
    {
        for(int j = 1;j <= n;j++)
            cout<<a[k++]<<" ";
        cout<<endl;
    }
}
/*
12 12 1 12 12
0 0 0 0 0 0 0 0 0 0 0 0
0 1 1 1 1 1 1 1 1 1 0 0
0 1 0 0 0 0 0 0 0 0 0 0
0 1 1 1 1 1 0 1 0 1 0 0
0 1 0 0 0 0 0 1 1 1 0 0
0 1 0 0 0 0 0 0 0 1 0 0
0 1 1 1 1 1 1 1 0 1 0 0
0 1 0 0 0 0 0 0 0 1 0 0
0 1 0 1 1 1 1 1 1 1 0 0
0 1 0 0 0 0 0 0 0 1 0 0
0 1 1 1 1 1 1 1 0 1 0 0
0 0 0 0 0 0 0 0 0 1 0 0
*/
