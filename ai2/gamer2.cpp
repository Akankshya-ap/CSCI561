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
struct nb
{
    xy np;
    xy parent;
};

mpv k1={{0,0},{0,1},{0,2},{0,3},{0,4},{1,0},{1,1},{1,2},{1,3},{1,4},{2,0},{2,1},{2,2},{2,3},{3,0},{3,1},{3,2},{4,0},{4,1}};
mpv k2={{11,14},{11,15},{12,13},{12,14},{12,15},{13,12},{13,13},{13,14},{13,15},{14,11},{14,12},{14,13},{14,14},{14,15},{15,11},{15,12},{15,13},{15,14},{15,15}};
mpv k[2]={k1,k2};
vector<char> ch={'B','W'};
int xval[2][8]={{1,1,0,-1,1,0,-1,-1},{-1,-1,0,1,-1,0,1,1}};
int yval[2][8]={{1,0,1,1,-1,-1,-1,0},{-1,0,-1,-1,1,1,0,1}};
void printmv(xyp move_pair,float v, int depth)
{
    cout<<move_pair.first.first<<","<<move_pair.first.second<<", "<<move_pair.second.first<<","<<move_pair.second.second<<", "<<v<<" depth "<<depth<<"\n";

}
void printt(mpv l)
{
    for(int i=0;i<l.size();i++)
    {cout<<l[i].first<<" "<<l[i].second<<"\n";}
}
void printb(vector<vi> pos)
{
    for(int i=0;i<16;i++)
        {for(int j=0;j<16;j++)
            cout<<pos[i][j];
        cout<<"\n";}
}
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

    if(onboard(a,b) && pab=='.' && (!check_own_camp(z,a,b) || (check_own_camp(z,a,b) && op(a,x) && op(b,y) && !where)) || (where==2 && check_own_camp(1-z,a,b)))
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

int step_move_game(int z, int x, int y, vector<vi> pos, int where, int i,vp &valid_s)
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
                {
                    valid_s.pb(mp(mp(x,y),mp(a,b)));
                    //str="E "+to_string(y)+","+to_string(x)+" "+to_string(b)+","+to_string(a);
                //cout<<str<<"\n";
                return 1;
                }
            //else not in own camp and original pawn not from opposing camp
            else if(!check_own_camp(z,a,b) and where!=2)
            {
                //cout<<"case222";
                valid_s.pb(mp(mp(x,y),mp(a,b)));
                //str="E "+to_string(y)+","+to_string(x)+" "+to_string(b)+","+to_string(a);
                //cout<<a<<b;
                //cout<<str<<"\n";
                return 1;
            }
            ////if you are in opposing camp but result in opposing camp itself
            else if(where==2 && check_own_camp(1-z,a,b))
            {
                valid_s.pb(mp(mp(x,y),mp(a,b)));
                //str="E "+to_string(y)+","+to_string(x)+" "+to_string(b)+","+to_string(a);
                //cout<<a<<b;
                //cout<<str<<"\n";
                return 1;
            }
        }
        return 0;
}

void jump_game(xy orig,int z, int x, int y, vector<vi> pos, int where, int i,mpv &explored, vp &valid) //,vp &store)
{
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
    {//cout<<a<<b;

            a=a+xval[z][i];
            b=b+yval[z][i];
                /////a,b, jump points
            if(!(find(explored.begin(),explored.end(),mp(a,b))!=explored.end()))
            {

            if(onboard(a,b) && pab=='.' && ((!check_own_camp(z,a,b) && (where==1 || where==0)) || (check_own_camp(z,a,b) && op(a,x) && op(b,y) && !where) || ((where==2 || where==1) && check_own_camp(1-z,a,b) )))
            {

                valid.pb(mp(orig,mp(a,b)));
                //cout<<" "<<x<<y<<"\n";
                //cout<<a<<b<<"\n";
            }
            if(onboard(a,b) && pab=='.')
            {
                explored.pb(mp(a,b));
                //store.pb(mp(mp(x,y),mp(a,b)));
                for(int j=0;j<8;j++)
                    {
                      jump_game(orig,z,a,b,pos,where,j,explored,valid);//,store);
                    }
        }
        }
    }
}

vp valid_moves(int z,xy own, vector<vi> pos,int where)
{
    int count_m=0;
    //string str="";
    int x,y;
        x=own.first;
        y=own.second;
        mpv explored;
        vp valid_j;
        vp valid_s;
        //vp store;
        explored.pb(mp(x,y));


            for(int i=0;i<8;i++)
            {   //stepmove
                //str="";
                jump_game(mp(x,y),z,x,y,pos,where,i,explored,valid_j); //,store);

                step_move_game(z,x,y,pos,where,i,valid_s);
            }

    valid_j.insert(valid_j.end(),valid_s.begin(),valid_s.end());

    return valid_j;
    //return valid_s.size()+valid_j.size();
}
float manhattan1( vector<vi> pos, int z,char c)
{
    float r=0.0;
    int q;
    if(z==0) q=15;
    else q=0;
    for(int i=0;i<16;i++)
    {for(int j=0;j<16;j++)
        {if(pos[i][j]==c)
            {r=r+32-(abs(i-q)+abs(j-q));}}}

        //cout<<own[i].first<<own[i].second<<"\n";

    return r/(19.0*10);

}
float farthest(vector<vi> pos, int z, char c)
{
    int maxi=0;
    int q;
    if(z==0) q=15;
    else q=0;
    for(int i=0;i<16;i++)
    {
        for(int j=0;j<16;j++)
        {if(pos[i][j]==c)
            {if((abs(i-q)+abs(j-q)<maxi))
               maxi=(abs(i-q)+abs(j-q));}
        }
    }
    return maxi;

}
/*
int trap(vector<vi> pos, int z, char c)
{
    int trap[]={{0,1},{1,1},{1,0},{2,0},{0,2},{2,2}};
    if(z==0)
    {
        if(pos[15][15]=='.' || pos[15][15]!=c)
            return 0;
        for(int i=0;i<trap.size();i++)
        {
            if(pos[trap[i][0]][trap[i][1]]=='.' || pos[trap[i][0]][trap[i][1]]!=c)
                return 0;
        }
         return -500;

    }
    if(z==1)
    {
        if(pos[0][0]=='.' || pos[0][0]!=c)
            return 0;
        for(int i=0;i<trap.size();i++)
        {
            if(pos[15-trap[i][0]][15-trap[i][1]]=='.' || pos[15-trap[i][0]][15-trap[i][1]]!=c)
                return 0;
        }
        return -500;

    }

}*/
int check_number_in_goal(vector<vi> pos, int z, char c)
{
    int goal;
    for(int i=0;i<19;i++)
    {
    if(pos[k[1-z][i].first][k[1-z][i].second]==c)
        goal++;
    }
    return goal;
}
float l2maxim(vector<vi> pos, int z, char c)
{
    mpv goal;
    //cout<<"yes";
    int maxi2=0;
    for(int i=0;i<19;i++)
    {
        //cout<<k[1-z][i].first<<k[1-z][i].second;
    if(pos[k[1-z][i].first][k[1-z][i].second]!=c)
        {goal.pb(k[1-z][i]); }
        //cout<<"pppp";}
    }
    //cout<<"Sizee  "<<goal.size();
    int total=0;
    int maxi=0;
    for(int i=0;i<16;i++)
    {    for(int j=0;j<16;j++)
        {   maxi2=0;
            if(pos[i][j]==c && !(find(k[1-z].begin(),k[1-z].end(),mp(i,j))!=k[1-z].end()))
            {for(int l=0;l<goal.size();l++)
        {
            maxi=32-abs(i-goal[l].first)-abs(j-goal[l].second);
            if(maxi<maxi2)
                maxi2=maxi;
                //cout<<i<<j<<maxi2;
                }}
              total+=maxi2;  }}


    return total;
}

float piecesleft(vector<vi> pos, int z, char c)
{
    int p=0;
    for(int i=0;i<19;i++)
    {

        if(pos[k[1-z][i].first][k[1-z][i].second]!=c)
                p++;
    }
    return p;
}
float eval(vector<vi> pos,mpv own,int z, float menemy,char c)
{
    float m=0.0;

    //printb(pos);
    //cout<<own.size()<<"\n";
    //Sleep(40000);
        //float m=(0.9)*manhattan1(pos,z,c)-menemy;
        //m+=(0.03)*piecesleft(pos,z,c);
    //m+=(0.5)*farthest(pos,z,c);
    //m=m+trap(pos,z,c);

    int goal_own=check_number_in_goal(pos,z,c);
    int goal_opp=check_number_in_goal(pos,1-z,ch[1-z]);
    m+=(manhattan1(pos,z,c));//-menemy);//+(goal_opp-goal_own)/(19*30);

    //m+=0.5*l2maxim(pos,z,c);
    //else

    //cout<<m;
    //Sleep(4000);
    return m;
}
vector<vi> board(vector<vi> pos, xyp start_end)
{
    char c=pos[start_end.first.first][start_end.first.second];
    pos[start_end.first.first][start_end.first.second]='.';
    pos[start_end.second.first][start_end.second.second]=c;

    //cout<<"IN BOARDD "<<start_end.first.first<<" "<<start_end.first.second<<" "<<start_end.second.first<<" "<<start_end.second.second;
    return pos;
}
bool check_from_own_to_outside(int z,int x, int y, int a, int b)
{
    if(check_own_camp(z,x,y) && !check_own_camp(z,a,b))
        return true;
    else return false;
}
vp generate_moves(int z, char c,mpv own,vector<vi> pos)
{
    //ofstream f2;
    //f2.open("output.txt", std::ios_base::app);
    //cout<<"hell"<<own.size();
    int p;
    vp all_vm;
    vp all_vm1;
    vp all_vm2;
    mpv opp;
    mpv midway;
    int count_total=0;
    //vector<int> moves;
    //cout<<666;
    for(int i=0;i<19;i++)
    {
        if(find(k[z].begin(),k[z].end(),own[i])!=k[z].end())
            {//cout<<1<<'\n';
                vp moves=valid_moves(z,own[i],pos,0);
                /*
                if(!moves.empty())
                    all_vm.insert(all_vm.end(),moves.begin(),moves.end());*/
                for(int it=0;it<moves.size();it++)
                {
                if(check_from_own_to_outside(z,moves[it].first.first,moves[it].first.second,moves[it].second.first,moves[it].second.second))
                        all_vm1.insert(all_vm1.end(),moves.begin(),moves.end());
                    else all_vm2.insert(all_vm2.end(),moves.begin(),moves.end());
                //count_total+=all_vm[all_vm.end()-1].total;
                }
                }
        else if(find(k[1-z].begin(),k[1-z].end(),own[i])!=k[1-z].end())
            {
                opp.pb(own[i]);}
        else
            midway.pb(own[i]);
    }
    if(!all_vm1.empty())
        return all_vm1;
    if(!all_vm2.empty())
        return all_vm2;
    /*if(!all_vm.empty())
        return all_vm;*/
    for(int i=0;i<midway.size();i++)
    {
        //cout<<2<<'\n';
        vp moves=valid_moves(z,midway[i],pos,1);
        all_vm.insert(all_vm.end(),moves.begin(),moves.end());
        //count_total+=all_vm[all_vm.end()-1].total;
    }
    if(!all_vm.empty() && piecesleft(pos, z, c)>8)
        return all_vm;
    for(int i=0;i<opp.size();i++)
    {
        //cout<<3<<'\n';
        vp moves=valid_moves(z,opp[i],pos,2);
        all_vm.insert(all_vm.end(),moves.begin(),moves.end());
        //all_vm.pb(valid_moves(z,opp[i],pos,2));
        //count_total+=all_vm[all_vm.end()-1].total;
    }
    //cout<<count_total;
    return all_vm;
}


bool checklm(xyp lm, xyp nm)
{
    if(lm.first.first==nm.second.first && lm.first.second==nm.second.second && lm.second.first==nm.first.first && lm.second.second==nm.first.second)
        return true;
    else return false;
}
vector<pair<xyp,float>> gene;
float MAX_v(vector<vi> pos,xyp move_pair,float alpha, float beta, int depth, int z, char c, mpv own,int d, float menemy,xyp last_move);

mpv get_own(vector<vi> pos, int z, char c)
{
    mpv own;
    for(int i=0;i<16;i++)
          {for(int j=0;j<16;j++)
                {if(pos[i][j]==ch[z])
                    own.pb(mp(i,j));}}
    return own;


}

float MIN_v(vector<vi> pos,xyp move_pair, int alpha, int beta, int depth, int z, char c, mpv own,int d,float menemy,xyp last_move)
{
    //printt(own);
    //printb(pos);
    //Sleep(40000);
    //cout<<"\n In MINNN \n"<<z<<" "<<" "<<c<<" \n";
    if(depth==0) return eval(pos,own,z,menemy,c);
    float v=std::numeric_limits<float>::infinity();
    vp all_vm=generate_moves(z,c,own,pos);
    //vector<pair<vp,float>> gene;
    for(int i=0;i<all_vm.size();i++)
    {
        vector<vi> pos1=board(pos,all_vm[i]);
        mpv own1=get_own(pos1,z,c);
        float k=MAX_v(pos1,all_vm[i],alpha,beta,depth-1,z,c,own1,d,menemy,last_move);
        //printmv(all_vm[i],k,depth);
        v=fmin(v,k);
        //cout<<v;
        if(v<=alpha) return v;
        beta=fmin(beta,v);
    }
    //cout<<v;
    //Sleep(30000);
    return v;

}
float MAX_v(vector<vi> pos,xyp move_pair,float alpha, float beta, int depth, int z, char c, mpv own, int d, float menemy,xyp last_move)
{
    if(depth==0) return eval(pos,own,z,menemy,c);
    float v=-std::numeric_limits<float>::infinity();
    vp all_vm=generate_moves(z,c,own,pos);
    for(int i=0;i<all_vm.size();i++)
    {
        vector<vi> pos1=board(pos,all_vm[i]);
        //printb(pos1);
        //Sleep(4000);
        mpv own1=get_own(pos1,z,c);
        //cout<<own.size();
        //printt(own);
        //Sleep(4000);
        float k=MIN_v(pos1,all_vm[i],alpha,beta,depth-1,z,c,own1,d,menemy,last_move);
        //
        //printmv(all_vm[i],k,depth);
        if(depth==d)
            gene.pb(mp(all_vm[i],k));
        v=fmax(v,k);
        if(v>=beta) return v;
        alpha=fmax(alpha,v);
    }
    return v;
}

struct jump_path
{
   int f=0;
   int px=-1;
   int py=-1;
};
vector<xy> run_BFS(int sx, int sy, int ex, int ey, int z, vector<vi> pos)
{

    queue<xy> q;
    jump_path pos1[16][16];
    int a,b,x2;
    q.push(mp(sx,sy));
    pos1[sx][sy].f=1;
    while(!q.empty())
    {
        //cout<<"\n"<<111<<"\n";
        a=q.front().first;
        b=q.front().second;
        //cout<<a<<b<<'\n';
        if(a==ex && b==ey)
        { //cout<<a<<b;
            vector<xy> path;
        do
            {
                path.pb(mp(a,b));
                x2=pos1[a][b].px;
                b=pos1[a][b].py;
                a=x2;
                //cout<<"in"<<a<<b;
            }while(!(a==sx && b==sy));
            path.pb(mp(a,b));
            reverse(path.begin(),path.end());
            return path;

        }
        q.pop();
        for(int i=0;i<8;i++)
        {
            //cp;
            int nx=a+xval[z][i];
            int ny=b+yval[z][i];
            int nnx=a+2*xval[z][i];
            int nny=b+2*yval[z][i];
            //cout<<nx<<" "<<ny;
            //cout<<xval[z][i];
            //cout<<pos1[a+2*xval[z][i]][b+2*yval[z][i]].f;
            if(onboard(nx,ny) && onboard(nnx,nny) && pos[nx][ny]!='.' && pos[nnx][nny]=='.' && pos1[nnx][nny].f==0)
            {q.push(mp(nnx,nny));
            //cout<<q.front().first<<"  "<<q.front().second<<"\n";
                pos1[nnx][nny].f=1;
                pos1[nnx][nny].px=a;
                pos1[nnx][nny].py=b;
            }
        }
    }
    return {};
}

xyp alpha_beta(int z, char c, mpv own,vector<vi> pos,float menemy, xyp last_move,int d)
{

    //gene.clear();
    //cout<<"\n In Aplhaaa \n"<<z<<" "<<" "<<c<<" \n";
    ofstream f2;
    f2.open("output1.txt", std::ios_base::app);

    float alpha=-std::numeric_limits<float>::infinity();
    float beta=std::numeric_limits<float>::infinity();
    //cout<<own.size();
    //cout<<"start"<<val;
    //int d=3;

    float v=MAX_v(pos,{},alpha,beta,d,z,c,own,d,menemy,last_move);
    cout<<"valuee"<<v<<"\n";
    for(int i=0;i<gene.size();i++)
    {
        //cout<<gene[i].first.first.first<<gene[i].first.first.second<<gene[i].first.second.first<<gene[i].first.second.second<<gene[i].second;
        if(gene[i].second==v)
            {

                int sx=gene[i].first.first.first;
                int sy=gene[i].first.first.second;
                int ex=gene[i].first.second.first;
                int ey=gene[i].first.second.second;

                return(gene[i].first);
                for(int i=0;i<8;i++)
                {
                    if(ex==(sx+xval[z][i]) && ey==(sy+yval[z][i]))
                        {f2<<"E "<<sy<<","<<sx<<" "<<ey<<","<<ex;
                        //return 0;}
                }

                //cout<<sx<<sy<<" "<<ex<<ey<<"\n";
            mpv path=run_BFS(sx,sy,ex,ey,z,pos);
            //cout<<path.size();
            int j=0;
            for(j=0;j<path.size()-2;j++)
                f2<<"J "<<path[j].second<<","<<path[j].first<<" "<<path[j+1].second<<","<<path[j+1].first<<"\n";
            f2<<"J "<<path[j].second<<","<<path[j].first<<" "<<path[j+1].second<<","<<path[j+1].first;
            //return 0;
            //return 0;
            }
    }
    //float v=MAX_v(pos,{},alpha,beta,5,z,c,own);
    //cout<<"value of "<<v;
}
return {};
}
//int count_total;

int main()
{
    ifstream f1;
    f1.open("1.txt");
    ofstream f2;
    f2.open("output1.txt");
    //f2.close();
    string play_type;
    f1>>play_type;
    string player;
    f1>>player;
    float t;
    f1>>t;
    vi row;
    vector<vi> pos;
    xyp last_move,last_move_b,last_move_w;
    //vector<vi> actual;
    int p=0,z=0;
    char va,c,copp;
    ////storing all z values
    if(player.compare("BLACK")==0)
        {c='B';copp='W';}
    else if(player.compare("WHITE")==0)
    {c='W';z=1; copp='B';}
    //cout<<z;
    mpv own;
    mpv enemy;
    for(int i=0;i<16;i++)
    {
        for(int j=0;j<16;j++)
        {
            f1>>va;
            row.pb(va);
        if(va==c)
            own.pb(mp(i,j));
        if(va==copp)
            enemy.pb(mp(i,j));
        }
        pos.pb(row);
        row.clear();
    }
    //printt(own);
    //printt(enemy);
    if(z==1)
        reverse(own.begin(),own.end());

    //cout<<"helllooo";
    //cout<<z<<"\n";
    /*
    if(play_type.compare("SINGLE")==0)
    {
        generate_move(z,c,own,pos);
    }*/

    if(play_type.compare("SINGLE")==0)
    {
        //.generate_move(z,c,own,pos);
        float menemy=0;//manhattan1(pos,1-z,copp);
        alpha_beta(z,c,own,pos,menemy,last_move,1);
    }
    int turn=0;

    if(play_type.compare("GAME")==0)
    {
    while(true)
    {

    turn++;
        own.clear();
        //printt(own);
        enemy.clear();
        for(int i=0;i<16;i++)
          {for(int j=0;j<16;j++)
                {if(pos[i][j]==c)
                    own.pb(mp(i,j));
                if(pos[i][j]==copp)
                    enemy.pb(mp(i,j));}
          }
        float menemy=0;//manhattan1(pos,1-z,copp);
        //cout<<menemy;
        //float val=0.0;
        int q;
        int d=2;
        if (z==0) {q=15;d=2;}
        else q=0;
        if(z==1)
        reverse(own.begin(),own.end());
        //cout<<q;
        //val=manhattan1(own,z);
        /*for(int i=0;i<own.size();i++)
            cout<<own[i].np.first<<own[i].np.second<<"\n";
        cout<<own.size();*/
        //cout<<z;
        //cout<<c<<"\n";
        //printt(own);
        gene.clear();
        xyp r=alpha_beta(z,c,own,pos,menemy,last_move,d);
        //Sleep(400000000000);
        //last_move.clear();
        if(z==0)
        {last_move_b=r;
        last_move=last_move_w;}
        else {last_move_w=r;
        last_move=last_move_b;}
        cout<<c<<" "<<r.first.first<<","<<r.first.second<<" "<<r.second.first<<","<<r.second.second<<"\n";
        pos=board(pos,r);
        printb(pos);
        //Sleep(4000000000000000000);
        //cout<<"\n";
        int i;
        for( i=0;i<19;i++)
        {
            if(pos[k[z][i].first][k[z][i].second]!=copp)
                break;

        }
        if(i==19 && turn>2) return 1;
        for( i=0;i<19;i++)
        {
           if(pos[k[1-z][i].first][k[1-z][i].second]!=c)
                break;
        }
        if(i==19 && turn>2) return 1;
        z=1-z;
        //cout<<z;
        char ck=c;
        c=copp;
        copp=ck;
        //Sleep(100);
        //Sleep(150000000000000);
    }

    }

    return 0;
}


