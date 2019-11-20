#include <iostream>
#include <fstream>
#include<vector>
#include<queue>
#include<stack>
#include<math.h>
#include <bits/stdc++.h>
#include<algorithm>
#define pb push_back
#define vi vector<cor>
#define sp cout<<'\n'
#define cp cout<<"xxx"
#define pxy pos[x1][y1]
#define mp make_pair
#define xy pair<int,int>
#define pqe pair<pair<int,int>,cor*>
using namespace std;
struct cor
{
    int zv;
    int f;
    xy p;
    vector<xy> c;
};
void compute_childbfs(vector<vi> &pos, int x1,int y1, int w, int h, int z)
{
    int a,b;
    /////checking all 8 neighbours as children//////
    for(a=max(x1-1,0);a<min(x1+2,h);++a)
    {
        for(b=max(y1-1,0); b<min(y1+2,w) ;++b)
            {
                if(!(a==x1 && b==y1) && (abs(pxy.zv-pos[a][b].zv)<=z) && pos[a][b].f==-1)
                {
                    pxy.c.pb(mp(a,b));
                    pos[a][b].p=mp(x1,y1);
                    pos[a][b].f=1;
                }
            }
        }
}
void BFS(int w,int h,int x,int y,int z,int n,int *t,vector<vi> pos)
{
    ofstream f2;
    f2.open("output.txt", std::ios_base::app);
    int counter=0;
    queue<xy> q;
    while(counter<2*n)
    {
    queue<xy> q;
    q.push(mp(x,y));
    pos[x][y].f=1;
    vector<xy> path;
    int x2;
    //// Path for each target to be found here /////////
    while(!q.empty())
    {
        xy fro=q.front();
        int x1=fro.first,y1=fro.second;
        q.pop();
        ////if path is found/////
        if(*(t+counter)==x1 && *(t+counter+1)==y1)
        {
            do
            {
                path.pb(mp(x1,y1));
                x2=pxy.p.first;
                y1=pxy.p.second;
                x1=x2;
            }while(!(x1==x && y1==y));
            path.pb(mp(x,y));
            reverse(path.begin(),path.end());
            /////writing path to the output file////////
            for(int i=0;i<path.size();i++)
                f2<<path[i].second<<','<<path[i].first<<' ';
            f2<<'\n';
            break;
        }
        if(pxy.c.empty())
            compute_childbfs(pos, x1,y1,w,h,z);
        for(int i=0;i<pxy.c.size();i++)
            q.push(mp(pxy.c[i].first,pxy.c[i].second));
    }
    if(path.empty())
        f2<<"FAIL\n";
    else
        path.clear();
    counter+=2;
    }
}

struct CustomCompare
{
    bool operator()(pqe &lhs, pqe &rhs)
    {
        return lhs.second->f>rhs.second->f;
    }

};
void compute_childucs(vector<vi> &pos, int x1,int y1, int w, int h, int z)
{
    int a,b;
    pxy.c.clear();
    /////checking all 8 neighbours as children//////
    for(a=max(x1-1,0);a<min(x1+2,h);++a)
    {
        for(b=max(y1-1,0); b<min(y1+2,w) ;++b)
            {
                if(!(a==x1 && b==y1) && (abs(pxy.zv-pos[a][b].zv)<=z))
                {
                    //cout<<"child "<<a<<b;
                    pxy.c.pb(mp(a,b));
                }
            }
        }
}
void initializef(vector<vi> &pos)
{
    for (std::vector<vi>::iterator it=pos.begin(), end=pos.end(); it!=end; ++it)
        {
            for(std::vector<cor>::iterator it2=it->begin();it2!=it->end();it2++)
                (*it2).f=-1;
        }
}
void UCSastar(int k,int w,int h,int x,int y,int z,int n,int *t,vector<vi> pos)
{
    int x1,y1,d;
    cor sv;
    ofstream f2;
    f2.open("output.txt", std::ios_base::app);
    int counter=0;

    while(counter<2*n)
    {
        priority_queue<pqe, vector<pqe>, CustomCompare> q;
        pos[x][y].f=0;
        int x4=*(t+counter),y4=*(t+counter+1);
        //cout<< pos[x][y].f;
        //cp;
        q.push(mp(mp(x,y),&pos[x][y]));
        //cout<<"counttt";
        vector<xy> path;
        int x2,x3,y3;
        //// Path for each target to be found here /////////
        while(!q.empty())
        {
            pqe fro=q.top();
            x1=fro.first.first;
            y1=fro.first.second;
            q.pop();
            //cout<<x1<<" "<<y1<<" "<<pxy.f<<" \n";
            //cout<<x1<<" "<<y1<<" ";
            ////if path is found/////
            if(x4==x1 && y4==y1)
            {
                do
                {
                    path.pb(mp(x1,y1));
                    x2=pxy.p.first;
                    y1=pxy.p.second;
                    x1=x2;
                }while(!(x1==x && y1==y));
                path.pb(mp(x,y));
                reverse(path.begin(),path.end());
                /////writing path to the output file////////
                for(int i=0;i<path.size();i++)
                    f2<<path[i].second<<','<<path[i].first<<' ';
                f2<<'\n';
                break;
            }

            compute_childucs(pos, x1,y1,w,h,z);
            //cout<<pxy.c.size()<<"\n";
            for(int i=0;i<pxy.c.size();i++)
            {
                x3=pxy.c[i].first;
                y3=pxy.c[i].second;
                if(k==2)
                    d=0;
                else
                    d=abs(pxy.zv-pos[x3][y3].zv)+floor(sqrt(pow(x3-x4,2)+pow(y3-y4,2)));
                if(abs(x3-x1)+abs(y3-y1)==2)
                    d+=14;
                else
                    d+=10;
                ///////condition 1..... child is not in open or closed
                if(pos[x3][y3].f==-1)
                {
                   pos[x3][y3].f=pxy.f+d;
                   pos[x3][y3].p.first=x1;
                    pos[x3][y3].p.second=y1;
                   q.push(mp(mp(x3,y3),&pos[x3][y3]));
                }
                ///////////condition 2 and 3
                else
                {
                    if(pos[x3][y3].f>(pxy.f+d))
                    {
                        pos[x3][y3].p.first=x1;
                        pos[x3][y3].p.second=y1;
                        pos[x3][y3].f=pxy.f+d;
                        q.push(mp(mp(x3,y3),&pos[x3][y3]));
                    }
                }
            }
        }
        if(path.empty())
            f2<<"FAIL\n";
        else
            path.clear();
        counter+=2;
        //cout<<counter;
        initializef(pos);
    }
}
int main()
{
    ifstream f1;
    f1.open("4.txt");
    ofstream f2;
    f2.open("output.txt");
    string m;
    f1>>m;
    int w,h,x,y,z,n,g;
    vi row;
    vector<vi> pos;
    f1>>w>>h>>y>>x>>z>>n;;
    if(!w>0 || !h>0 || !(x>=0 && x<w) || !(y>=0 && y<h) || !(z>=0) || !n>0)
        f2<<"FAIL";
    int t[n][2];
    int p=-1;
    /////storing target values
    while(++p<n)
    {
        f1>>t[p][1]>>t[p][0];
        if(!(t[p][0]>=0 && t[p][0]<h) || !(t[p][1]>=0 && t[p][1]<w))
            f2<<"FAIL";
    }
    p=0;
    int va=0;
    ////storing all z values
    while(p++<h*w)
    {
        f1>>va;
        row.pb({va,-1,mp(-1,-1),{}});
        if(p%w==0)
        {
            pos.pb(row);
            row.clear();
        }
    }
    if(!m.compare("BFS"))
        BFS(w,h,x,y,z,n,*t,pos);
    else if(!m.compare("UCS"))
        UCSastar(2,w,h,x,y,z,n,*t,pos);
    else if(!m.compare("A*"))
        UCSastar(3,w,h,x,y,z,n,*t,pos);
    return 0;

}
