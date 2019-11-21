#include<iostream>
#include<stdio.h>
#include <fstream>
#include<vector>
#include<algorithm>
#include<string>
#include <bits/stdc++.h>
#define pb push_back
#define vi vector<char>
#define mp make_pair
#define xy pair<int,int>
#define mpv vector<xy>
#define pab pos[a][b]
using namespace std;
struct nb
{
    xy np;
    xy parent;
};

mpv k1={{0,0},{0,1},{0,2},{0,3},{0,4},{1,0},{1,1},{1,2},{1,3},{1,4},{2,0},{2,1},{2,2},{2,3},{3,0},{3,1},{3,2},{4,0},{4,1}};
mpv k2={{11,14},{11,15},{12,13},{12,14},{12,15},{13,12},{13,13},{13,14},{13,15},{14,11},{14,12},{14,13},{14,14},{14,15},{15,11},{15,12},{15,13},{15,14},{15,15}};
mpv k[2]={k1,k2};

int xval[2][8]={{1,1,0,1,0,-1,-1,-1},{-1,-1,0,-1,0,1,1,1}};
int yval[2][8]={{1,0,1,-1,-1,-1,0,1},{-1,0,-1,1,1,-1,0,1}};

bool check_own_camp(int z,int i,int j)
{
    return (find(k[z].begin(), k[z].end(),mp(i,j))!=k[z].end());
}
bool onboard(int a, int b)
{
    //cout<<4;
    if(a>=0 && a<16 && b>=0 && b<16)
        return true;
    else return false;
}
mpv jump(int z, int x, int y, vector<vi> pos, int where, int i,mpv &explored)
{
    mpv jump_steps;

    std::function<bool(int,int)> op;
    if(!z)
        op = std::greater_equal<int>();
    else
        op = std::less_equal<int>();
    int a,b;
    string str;
    a=x+xval[z][i],b=y+yval[z][i];
    //cout<<"jump"<<x<<y<<" "<<a<<b<<'\n';

    if(onboard(a,b) && pab!='.' )
    {
        //cout<<a<<b;
    a=a+xval[z][i];
    b=b+yval[z][i];

    if(!(find(explored.begin(),explored.end(),mp(a,b))!=explored.end()))
    {

    if(onboard(a,b) && pab=='.' && (!check_own_camp(z,a,b) || (check_own_camp(z,a,b) && op(a,x) && op(b,y) && !where) || (where==2 && check_own_camp(1-z,a,b))))
    {
        //cout<<a<<b<<'\n';
        //own[i].parent=mp(a,b);
        explored.pb(mp(a,b));
        jump_steps.pb(mp(x,y));
        jump_steps.pb(mp(a,b));
        //cout<<jump_steps[0].first<<jump_steps[0].second<<"\n";

        return jump_steps;
        //str="J "+to_string(y)+","+to_string(x)+" "+to_string(b)+","+to_string(a);
        //str=str+"J "+to_string(y)+","+to_string(x)+" "+to_string(b)+","+to_string(a);
        //cout<<str;

        //return str;
    }
    else if(onboard(a,b) && pab=='.')
    {
        explored.pb(mp(a,b));
        for(int j=0;j<8;j++)
            {
              mpv yj=jump(z,x,y,pos,where,j,explored);
            if(!yj.empty())
               {jump_steps.pb(mp(a,b));
               jump_steps.insert(jump_steps.end(),yj.begin(),yj.end());
               return jump_steps;
               }
            }
    }
    }
    }
    return {};
}
string step_move(int z, int x, int y, vector<vi> pos, int where, int i)
{
    std::function<bool(int,int)> op;
    if(!z)
        op = std::greater_equal<int>();
    else
        op = std::less_equal<int>();
    int a,b;
    string str;

    a=x+xval[z][i],b=y+yval[z][i];
        //cout<<"step"<<x<<y<<" "<<a<<b<<'\n';
        /////Step_move
        if(onboard(a,b) && pab=='.')
        {
            /////If moving in own camp, move further awaayyyy
            if(check_own_camp(z,a,b) && op(a,x) && op(b,y) && !where)
                {str="E "+to_string(y)+","+to_string(x)+" "+to_string(b)+","+to_string(a);
                //cout<<a<<b;
                return str;
                }
            //else not in own camp and original pawn not from opposing camp
            else if(!check_own_camp(z,a,b) and where!=2)
            {
                //cout<<"case222";
                str="E "+to_string(y)+","+to_string(x)+" "+to_string(b)+","+to_string(a);
                //cout<<a<<b;
                return str;
            }
            ////if you are in opposing camp but result in opposing camp itself
            else if(where==2 && check_own_camp(1-z,a,b))
            {
                str="E "+to_string(y)+","+to_string(x)+" "+to_string(b)+","+to_string(a);
                //cout<<a<<b;
                return str;
            }
        }
        return "";
}
string valid_move(int z,nb own, vector<vi> pos,int where)
{
    //////getting operator function

    string str="";
    //cout<<x<<y<<'\n';
    mpv explored;
    int x,y;
    for(int i=0;i<8;i++)
    {   //stepmove
        x=own.np.first;
        y=own.np.second;

        //jump move
        mpv jump_s=jump(z,x,y,pos,where,i,explored);
        if(!jump_s.empty())
            { int k;
            for(k=1;k<jump_s.size()-1;k++)
            {
                str=str+"J "+to_string(jump_s[k-1].second)+","+to_string(jump_s[k-1].first)+" "+to_string(jump_s[k].second)+","+to_string(jump_s[k].first)+"\n";
                //cout<<str;
            }
            str=str+"J "+to_string(jump_s[k-1].second)+","+to_string(jump_s[k-1].first)+" "+to_string(jump_s[k].second)+","+to_string(jump_s[k].first);
            //cout<<str;
            return str;
            }

        str=step_move(z,x,y,pos,where,i);
        if(!str.empty())
            return str;

    }
    return "";
}
int generate_move(int z, char c,vector<nb> own,vector<vi> pos)
{
    ofstream f2;
    f2.open("output.txt", std::ios_base::app);
    string p;
    vector<nb> opp;
    vector<nb> midway;
    for(int i=0;i<19;i++)
    {       //if(pos[k[z][i].first][k[z][i].second]==c)
            //cout<<i<<" ";
            //////own camp
        if(find(k[z].begin(),k[z].end(),own[i].np)!=k[z].end())
            {//cout<<1<<'\n';
                p=valid_move(z,own[i],pos,0);
                //cout<<p;
            if(!p.empty())
                break;}
        else if(find(k[1-z].begin(),k[1-z].end(),own[i].np)!=k[1-z].end())
            {   //cout<<own[i].np.first<<own[i].np.second<<"\n";
                opp.pb(own[i]);}
        else
            midway.pb(own[i]);
    }
    if(!p.empty())
    {
        midway.clear();
        opp.clear();
    }
    for(int i=0;i<midway.size();i++)
    {
        //cout<<2<<'\n';
        p=valid_move(z,midway[i],pos,1);
            if(!p.empty())
                break;
    }
    if(!p.empty())
    {opp.clear();}
    for(int i=0;i<opp.size();i++)
    {
        //cout<<3<<'\n';
        p=valid_move(z,opp[i],pos,2);
            if(!p.empty())
                break;
    }
    if(!p.empty())
        f2<<p;
    else f2<<"Nomove";
    return 0;
}

int valid_moves(int z,nb own, vector<vi> pos,int where)
{
    //////getting operator function
    int count_m=0;
    string str="";
    //cout<<x<<y<<'\n';

    int x,y;
    for(int i=0;i<8;i++)
    {   //stepmove
        mpv explored;
        x=own.np.first;
        y=own.np.second;
        //jump move
        mpv jump_s=jump(z,x,y,pos,where,i,explored);
        if(!jump_s.empty())
            { count_m++;
                /*int k;
            for(k=1;k<jump_s.size()-1;k++)
            {
                str=str+"J "+to_string(jump_s[k-1].second)+","+to_string(jump_s[k-1].first)+" "+to_string(jump_s[k].second)+","+to_string(jump_s[k].first)+"\n";
                //cout<<str;
            }
            str=str+"J "+to_string(jump_s[k-1].second)+","+to_string(jump_s[k-1].first)+" "+to_string(jump_s[k].second)+","+to_string(jump_s[k].first);
            //cout<<str;
            return str;*/
            }

        str=step_move(z,x,y,pos,where,i);
        if(!str.empty())
            count_m++;
            //return str;
    }
    //cout<<count_m;
    return count_m;
}
int generate_moves(int z, char c,vector<nb> own,vector<vi> pos)
{
    ofstream f2;
    f2.open("output.txt", std::ios_base::app);
    int p;
    vector<nb> opp;
    vector<nb> midway;
    int count_total=0;
    vector<int> moves;
    for(int i=0;i<19;i++)
    {       //if(pos[k[z][i].first][k[z][i].second]==c)
            //cout<<i<<" ";
            //////own camp
        if(find(k[z].begin(),k[z].end(),own[i].np)!=k[z].end())
            {//cout<<1<<'\n';
                p=valid_moves(z,own[i],pos,0);
                //cout<<p;
            if(p)
                {
                    count_total+=p;
                moves.pb(p);}}
        else if(find(k[1-z].begin(),k[1-z].end(),own[i].np)!=k[1-z].end())
            {   //cout<<own[i].np.first<<own[i].np.second<<"\n";
                opp.pb(own[i]);}
        else
            midway.pb(own[i]);
    }
    /*if(!p.empty())
    {
        midway.clear();
        opp.clear();
    }*/
    for(int i=0;i<midway.size();i++)
    {
        //cout<<2<<'\n';
        p=valid_moves(z,midway[i],pos,1);
            if(p)
                {count_total+=p;
                moves.pb(p);}
    }
    /*if(!p.empty())
    {opp.clear();}*/
    for(int i=0;i<opp.size();i++)
    {
        //cout<<3<<'\n';
        p=valid_moves(z,opp[i],pos,2);
            if(p)
                {count_total+=p;
                moves.pb(p);}
    }
    /*if(!p.empty())
        f2<<p;*/
    cout<<count_total;
    //else f2<<"Nomove";
    return 0;
}

int main()
{
    ifstream f1;
    f1.open("1.txt");
    ofstream f2;
    f2.open("output.txt");
    string play_type;
    f1>>play_type;
    string player;
    f1>>player;
    float t;
    f1>>t;
    vi row;
    vector<vi> pos;
    int p=0,z=0;
    char va,c;
    ////storing all z values
    if(player.compare("BLACK")==0)
        c='B';
    else {c='W';z=1;}
    vector<nb> own;
    for(int i=0;i<16;i++)
    {
        for(int j=0;j<16;j++)
        {
            f1>>va;
        row.pb(va);
        if(va==c)
            own.pb({mp(i,j),{}});
        }
        pos.pb(row);
        row.clear();
    }
    if(play_type.compare("SINGLE")==0)
    {
        generate_move(z,c,own,pos);
    }
    if(play_type.compare("GAME")==0)
    {
        generate_moves(z,c,own,pos);
    }

    return 0;
}

