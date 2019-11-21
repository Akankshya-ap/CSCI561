#include<iostream>
#include<stdio.h>
#include <fstream>
#include<vector>
#include<vector>
#include<algorithm>
#include<string>
#include <bits/stdc++.h>
#include<math.h>
#define pb push_back
#define vi vector<char>
#define mp make_pair
#define xy pair<int,int>
#define xyp pair<xy,xy>
#define vp vector<pair<xy,xy>>
#define mpv vector<xy>
#define pab pos[a][b]
using namespace std;
int secc(mpv &explore)
{
    explore.pb(mp(7,8));
    explore.pb(mp(7,9));
return 0;
}
int evaluate(xyp start_end)
{
    return (sqrt(pow(15-start_end.first.first,2)+pow(15-start_end.first.second,2))-sqrt(pow(15-start_end.second.first,2)+pow(15-start_end.second.second,2)));
}
int main()
{

    mpv explore;
    xy p1=mp(1,2);
    xy p2=mp(3,4);
    xy p3=mp(5,6);
    explore.pb(p1);
    explore.pb(p2);
    explore.pb(p3);

    //for(int i=0;i<explore.size();i++)
      //  cout<<explore[i].first<<explore[i].second;
    //int q=secc(explore);
    //cout<<((find(explore.begin(),explore.end(),mp(7,10))!=explore.end()));


    vp expl;
    expl.pb(mp(p1,p2));
    expl.pb(mp(p2,p3));
    for(int i=0;i<expl.size();i++)
        cout<<expl[i].first.first<<expl[i].first.second;

    cout<<'\n'<<evaluate(mp(p1,p2));
    cout<<max(1,2.677);

    return 0;
}
