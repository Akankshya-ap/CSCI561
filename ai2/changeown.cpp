#include<iostream>
#include<stdio.h>
#include <fstream>
#include<vector>
#include<algorithm>
#include <cmath>
#include<limits>
#include <iomanip>
#include <unordered_map>
#include <windows.h>
#include <unistd.h>
#include<math.h>
#include<string>
#include <bits/stdc++.h>
#define pb push_back
#define vi vector<char>
#define mp make_pair
#define xy pair<int,int>
#define xyp pair<xy,xy>
#define mpv vector<xy>
#define vp vector<xyp>
#define pab pos[a][b]
#define cp cout<<"\n"<<"checkkk";
using namespace std;
int main()
{
    xy r=mp(5,4);
    r=mp(0,4);
    mpv own;
    own.pb(mp(0,1));
    own.pb(mp(0,2));
    own.pb(mp(0,3));
    std::vector<xy>::iterator k=find(own.begin(),own.end(),mp(0,3));
    int index = std::distance(own.begin(), k);
    own.erase(own.begin()+index);
    own.pb(mp(0,5));

    for(int i=0;i<own.size();i++)
        cout<<own[i].first<<own[i].second<<"\n";
}
