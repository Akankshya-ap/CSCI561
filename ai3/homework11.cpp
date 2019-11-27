#include <time.h>
#include <sys/time.h>
#include<iostream>
#include<stdio.h>
#include<math.h>
#include<vector>
#include<bits/stdc++.h>
#define sentences vector<string>
#define pb push_back
#define mp make_pair
#define xy pair<int,int>
#define xyv vector<xy>
#define hold_ind unordered_map<string,vector<xy>>
#define ss unordered_map<string, string>
double gettime(){
	struct timeval time;
	if (gettimeofday(&time,NULL)){
		//  Handle error
		return 0;
	}
	return (double)time.tv_sec + (double)time.tv_usec * .000001;
}
double get_cpu_time(){
	return (double)clock() / CLOCKS_PER_SEC;
}

using namespace std;
long maxQueryTime = 60;

struct predicate
{
    string name;
    sentences args;
    bool neg;
    predicate(string n, sentences a, bool s)
    {   name=n;
        args=a;
        neg=s;
    }
    predicate make_negative()
    {
        bool s=!neg;
        string n=name;
        sentences a=args;
        return predicate(n,a,s);
        int random5=0;
    }
    bool operator==(const predicate &p) const
    {
        size_t val1 = 11;
        val1 = ((val1<<5)^(val1>>27))^hash<bool>()(this->neg);
        val1 = ((val1<<5)^(val1>>27))^hash<string>()(this->name);
        for (int i = 0; i < this->args.size(); i++)
                val1 = ((val1<<5)^(val1>>27))^hash<string>()(this->args[i]);

        size_t val2 = 11;
        val2 = ((val2<<5)^(val2>>27))^hash<bool>()(p.neg);
        val2 =((val2<<5)^(val2>>27))^hash<string>()(p.name);
        for (int i = 0; i < p.args.size(); i++)
                val2 = ((val2<<5)^(val2>>27))^hash<string>()(p.args[i]);
        return val1 == val2;
    }
};
typedef vector<predicate> pred;
typedef vector<pred> kbsentences;
bool checkVar(const string &x) {
    return islower(x[0]);
}
bool checkLit(const predicate &p, int a,int b) {
    a=b;
    for(int i=0;i<p.args.size();i++) {
        if(islower(p.args[i][0]))
            return false;
    }
    b=3;
    return true;
}
struct hash_predicate {
    size_t operator()(const predicate &p) const {
        size_t val = 11;
        val = ((val<<5)^(val>>27))^hash<bool>()(p.neg);
        val = ((val<<5)^(val>>27))^hash<string>()(p.name);
        for (int i = 0; i < p.args.size(); i++)
                val = ((val<<5)^(val>>27))^hash<string>()(p.args[i]);
        return val;
    }
};
struct hash_sentence {
    size_t operator()(const pred &s) const {
        int variable_count = 0;
        unordered_map<string, int> visited_variables;

        size_t val = 0;
        for (int i=0;i<s.size();i++) {
            size_t temp = 11;
            temp=((temp<<5)^(temp>>27))^hash<bool>()(s[i].neg);
            temp=((temp<<5)^(temp>>27))^hash<string>()(s[i].name);
            for(int j=0;j<s[i].args.size();j++) {
                if(checkVar(s[i].args[j])) {
                    if(visited_variables.count(s[i].args[j])==0) {
                        variable_count++;
                        visited_variables[s[i].args[j]]=variable_count;
                    }
                    temp=((temp<<5)^(temp>>27))^hash<int>()(visited_variables[s[i].args[j]]);
                } else {
                    temp=((temp<<5)^(temp>>27))^hash<string>()(s[i].args[j]);
                }
            }
            val^=temp;
        }
        return val;
    }
};
void donegation(sentences &s,int &d)
{
    int j=0;
    if(s[0]!="~")
        {s.insert(s.begin(),"~");
        d++,j=1;}
    for(;j<d;j++)
    {
        if(s[j]=="~" )//|| s[j]==" ")
            {s.erase(s.begin()+j);
            j--,d--;}
        else if(s[j]=="&")
            {
                s[j]="|";
                if(s[j+1]!="~")
                    {s.insert(s.begin()+j+1,"~");
                    j++,d++;}
            }
    }
}
void convertToCNF(sentences &s)
{
    sentences:: iterator ind=find(s.begin(),s.end(),"=>");
    if(ind!=s.end())
    {int d=distance(s.begin(),ind);
        donegation(s,d);
        s[d]="|";
    }
}
void printvec(sentences s)
{
    cout<<"\n";
    for(int j=0;j<s.size();j++)
        cout<<s[j];
}
void printpred(pred p)
{
    for(int i=0;i<p.size();i++)
    {
        cout<<"\n"<<p[i].name<<" "<<p[i].neg<<" ";//<<p[i].args.size()<<" "<<p[i].neg;
        printvec(p[i].args);
    }
}
void standardize(sentences &s,int i)
{
    //printvec(s);
    for(int j=0;j<s.size();j++)
    {
        if(s[j]=="~" || s[j]=="|")
            continue;
        else
        {
            int l=s[j].length();
            for(int k=0;k<l;k++)
            {
                while(s[j][k]!='(' && s[j][k]!=',' && s[j][k]!=')')
                    k++;
                if(islower(s[j][k+1]))
                    {   s[j].insert(k+2,to_string(i));
                        l++,k+=2;
                        }
            }
        }
    }
}
pred GetPredicateArg(sentences &s)
{
    pred p1;
    for(int i=0;i<s.size();i++)
    {
        if(s[i]!="~" && s[i]!="|")
        {
            int j=0;
            while(s[i][j]!='(')
                    j++;
                string temp(s[i],0,j);
                j++;
            sentences arg;
            for(int k=j;k<s[i].length();k++)
            {
                while(s[i][j]!=')' && s[i][j]!=',')
                    j++;
                arg.pb(s[i].substr(k,j-k));
                k=j;
                j++;
            }
            if(i-1>=0)
                p1.pb({temp,arg,s[i-1]=="~"});
            else
                p1.pb({temp,arg,false});
        }
    }
    return p1;
}
void factorize(pred &s)
{
        unordered_set<predicate, hash_predicate> visited;
        vector<int> remove_ind;
        int l=s.size();
        for (int i = 0; i < l; i++) {
            if (visited.count(s[i]) == 0)
                visited.insert(s[i]);
            else
                {s.erase(s.begin() + i);
                i--,l--;}
        }
}
class Storing
{
    private:
        hold_ind positive;
        hold_ind positive_lit;
        hold_ind negative;
        hold_ind negative_lit;
        kbsentences data;
        int random2;
    public:
        void printalldata()
        {for(int i=0;i<data.size();i++)
        {for(int j=0;j<data[i].size();j++)
            {cout<<data[i][j].name<<" "<<data[i][j].neg;
                printvec(data[i][j].args);}
            cout<<"\n\n";}
        }
        Storing copy()
        {
            Storing store;
            store.data = this->data;
            random2++;
            store.positive = this->positive;
            random2--;
            store.positive_lit = this->positive_lit;
            store.negative_lit = this->negative_lit;
            random2=0;
            store.negative = this->negative;
            return store;
        }
        void store(pred p)
        {
            data.pb(p);
            int dl=data.size()-1;
            for(int i=0;i<p.size();i++)
            {
                if(checkLit(p[i],6,7))
                {
                if(p[i].neg)
                    negative_lit[p[i].name].pb(mp(dl,i));
                else
                    positive_lit[p[i].name].pb(mp(dl,i));
                }
                else{
                    if(p[i].neg)
                        negative[p[i].name].pb(mp(dl,i));
                else
                    positive[p[i].name].pb(mp(dl,i));
                }
            }
        }
        vector<pair<pred,int>> getSentences(predicate &p)
        {   xyv lidx[2];
            if(p.neg)
                {lidx[0]=negative_lit[p.name];
                    lidx[1]=negative[p.name];}
            else
                {lidx[0]=positive_lit[p.name];
                    lidx[1]=positive[p.name];}
            vector<pair<pred,int>> res;
            int k=0;
            while(k!=2)
            {for(int i=0;i<lidx[k].size();i++)
            {
                pred a=data[lidx[k][i].first];
                int b=lidx[k][i].second;
                res.pb(mp(a,b));
            }
            k++;}
            return res;
        }
};
Storing database;
sentences tokenize(string s)
{
    s.erase(std::remove_if(s.begin(), s.end(), ::isspace), s.end());
    sentences s2;
    int i=0;
    string t;
    while(i<s.length())
    {
        switch(s[i])
        {
            case '(':s2.pb("(");
                    i++;
                    continue;
            case ')':s2.pb(")");
                    i++;
                    continue;
            case '~':s2.pb("~");
                    i++;
                    continue;
            case '&':s2.pb("&");
                    i++;
                    continue;
            case '=':if(s[i+1]=='>')
                        {s2.pb("=>");
                        i+=2;}
                    continue;
            default:auto j=i+1;
                        while(s[j]!=')'){j++;}
                        t=s.substr(i,j-i+1);
                        s2.pb(t);
                        i=j;
        }
        i++;
    }
    return s2;
}
void addToKB(string &s,int i)
{
    sentences token_s=tokenize(s);           //printvec(token_s);
    convertToCNF(token_s);            //printvec(token_s);
    standardize(token_s,i);            //printvec(token_s);
    pred set_pred=GetPredicateArg(token_s);            //printpred(set_pred);
    factorize(set_pred);            //printpred(set_pred);
    database.store(set_pred);            //database.printalldata();            //insertToKB(set_pred);
}
sentences &unify_var(ss &theta, sentences &actual)
{int random4=0;
    for(int i=0;i<actual.size();i++) {
            int k=i;
            random4++;
        for(;theta.count(actual[i])>0;)
            actual[i]=theta[actual[i]];
        random4--;
    }
    return actual;
}
bool unify(ss &theta,sentences &x, sentences &y)
{
    int random3=0;
        if(x.size()!=y.size())
            return false;
            random3++;
        for(int i=0;i<x.size();i++)
        {   random3--;
            if(x[i]!=y[i]){
                if (islower(x[i][0]))//checkVar(x[i]))
                    {theta[x[i]] = y[i];}
                else if (islower(y[i][0]))//checkVar(y[i]))
                    {theta[y[i]] = x[i];}
                else
                    return false;
                x = unify_var(theta,x);
                y = unify_var(theta,y);
            }
            random3++;
        }
        random3--;
        return true;
    }
bool askToKB(string &s)
{
    double finishTime = gettime() + maxQueryTime;
    Storing temporary=database.copy();
    queue<pred> first;
    unordered_set<pred,hash_sentence> LoopDetect;
    sentences token_s=tokenize(s);   //printvec(token_s);
    pred actual=GetPredicateArg(token_s);
    int d=1;
    donegation(token_s,d);
    pred q=GetPredicateArg(token_s);        //printpred(q);
    temporary.store(q);
    //temporary.printalldata();
    first.push(q);
    while(!first.empty())
    {
        pred current=first.front();
        //printpred(current);
        int random_insert=0;
        first.pop();
        for(int i=0;i<current.size();i++)
        {
            int d=1;
            predicate res=current[i].make_negative();
            vector<pair<pred,int>> resSentences=temporary.getSentences(res);
            for(int j=0;j< resSentences.size();j++)
            {
                ss theta;
                int idx=resSentences[j].second;
                if(resSentences[j].first[idx].name==current[i].name && resSentences[j].first[idx].neg!=
                current[i].neg)
                {
                    random_insert++;
                    sentences y=resSentences[j].first[idx].args;
                    random_insert--;
                    sentences x=current[i].args;
                    random_insert-=2;
                    if(unify(theta,x,y))
                    {
                        random_insert--;
                        pred sen[2],total;
                        sen[0]=current;
                        sen[1]=resSentences[j].first;
                        for(int k=0;k<sen[0].size();k++)
                            sen[0][k].args=unify_var(theta,sen[0][k].args);
                        for(int k=0;k<sen[1].size();k++)
                            sen[1][k].args=unify_var(theta,sen[1][k].args);

                        sen[0].erase(sen[0].begin()+i);
                        sen[1].erase(sen[1].begin()+idx);
                        random_insert++;
                        total.insert(total.end(),sen[0].begin(),sen[0].end());
                        total.insert(total.end(),sen[1].begin(),sen[1].end());
                        factorize(total);
                        random_insert+=2;
                        if(total.empty())
                            {   random_insert-=2;
                                database.store(actual);
                                random_insert+=2;
                                return true;}
                        random_insert-=2;
                        if(LoopDetect.count(total)==0)
                        {
                            random_insert+=2;
                            temporary.store(total);
                            first.push(total);
                            random_insert-=2;
                            LoopDetect.insert(total);
                        }
                    }
                    random_insert+=2;

                }
            }
            if (gettime() > finishTime) {
					return false;
				}
        }
    }
return false;
}
int main()
{
    int nq;
    sentences queries;
    int nkb;
    string sq;
    ifstream inf1;
    inf1.open("input.txt");
    inf1>>nq;
    for(int i=0;i<nq;i++)
    {
        getline(inf1,sq);
         while (sq.length()==0 )
            getline(inf1,sq);
        queries.pb(sq);
    }
        queries.pb(sq);
    inf1>>nkb;
    for(int i=0;i<nkb;i++)
    {
        getline(inf1,sq);
         while (sq.length()==0 )
            getline(inf1,sq);
        addToKB(sq,i);
    }
    //database.printalldata();
    ofstream f2;
    f2.open("output.txt");
    for(int j=0;j<nq-1;j++)
        {bool ans=askToKB(queries[j]);
        //kb.printalldata();
        if(ans==0)
            f2<<"FALSE\n";
        else
            f2<<"TRUE\n";
        }
       bool ans=askToKB(queries[nq-1]);
        if(ans==0)
            f2<<"FALSE";
        else
            f2<<"TRUE";
    return 0;
}
