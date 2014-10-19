#include<iostream>
#include<cstring>
#include<queue>
#include<set>
using namespace std;

int nfa[100][4],dfa[100][2],dfa_states[100][100],st[100],num_states,n,final_state[100];
queue<int> q;
int e_closure()
{
    int curr,i,j;
    //build e-closure for x
    while(!q.empty())
    {
        curr=q.front();
        q.pop();
        if(!st[curr])
        {
            st[curr]=1;
            if(nfa[curr][2])
                q.push(nfa[curr][2]);
            if(nfa[curr][3])
                q.push(nfa[curr][3]);
        }
    }
    //check if a new state is formed
    for(i=0;i<num_states;i++)
    {
        for(j=0;j<=n;j++)
        {
            if(st[j]!=dfa_states[i][j])
                break;
        }
        if(j>n)
            break;
    }
    if(i==num_states)
    {
        for(j=0;j<=n;j++)
            dfa_states[num_states][j]=st[j];
        num_states++;
        memset(st,0,sizeof(st));
   //     cout<<"total states="<<num_states<<endl;
        return num_states-1;
    }
    else
    {
        memset(st,0,sizeof(st));
        return i;
    }
}

int main()
{
    int t,i,j,k,curr_state,num;
    cout<<"Enter number of test cases: ";
    cin>>t;
    while(t--)
    {
        num=0;
        memset(dfa,0,sizeof(dfa));
        memset(dfa_states,0,sizeof(dfa_states));
        memset(st,0,sizeof(st));
        curr_state=num_states=1;
        cin>>n;
        for(i=1;i<=n;i++)
            cin>>nfa[i][0]>>nfa[i][1]>>nfa[i][2]>>nfa[i][3];
        for(i=1;i<=n;i++)
        {
            if(nfa[i][0]==0 && nfa[i][1]==0 && nfa[i][2]==0 && nfa[i][3]==0)
                final_state[num++]=i;
        }
        q.push(1);
        k=e_closure();
       
      //  cout<<"current state="<<k<<endl;
        while(curr_state<num_states)
        {
            // transition (s,a)
            for(j=0;j<=n;j++)
            {
                if(dfa_states[curr_state][j]==1)
                    if(nfa[j][0])
                    {
                   //     cout<<"added "<<nfa[j][0]<<" for 'a' transition\n";
                        q.push(nfa[j][0]);
                    }
            }
            k=e_closure();
          //  cout<<"current state="<<k<<endl;
           
            dfa[curr_state][0]=k;
            // transition (s,b)
            for(j=0;j<=n;j++)
            {
                if(dfa_states[curr_state][j]==1)
                    if(nfa[j][1])
                    {
                    //    cout<<"added "<<nfa[j][1]<<" for 'b' transition\n";
                        q.push(nfa[j][1]);
                    }
            }
            k=e_closure();
                 
            //cout<<"current state="<<k<<endl;
            dfa[curr_state][1]=k;
            curr_state++;
            
        }
        cout<<"DFA:\n";
        cout<<"St  a   b\n";
        for(i=1;i<num_states;i++)
            cout<<i<<"   "<<dfa[i][0]<<"   "<<dfa[i][1]<<endl;
        cout<<"\nFinal states: ";
        for(i=0;i<=num_states;i++)
        {
            for(j=0;j<=n;j++)
            {
                if(dfa_states[i][j]==1)
                {
                    for(k=0;k<num;k++)
                    {
                        if(final_state[k]==j)
                        {
                            cout<<i<<", ";
                            break;
                        }
                    }
                    if(k<num)
                        break;
                }
            }
        }
    }
    return 0;
}
/*
Test cases:
3
8
0 0 2 8
0 0 3 5
4 0 0 0
0 0 7 0
0 6 0 0
0 0 7 0
0 0 2 8
0 0 0 0

10
0 0 2 8
0 0 3 5
4 0 0 0
0 0 7 0
0 6 0 0
0 0 7 0
0 0 2 8
9 0 0 0
0 10 0 0
0 0 0 0

12
0 0 2 0
0 0 3 7
0 0 4 6
5 0 0 0
0 0 4 6
0 0 11 0
0 0 8 10
0 9 0 0
0 0 8 10
0 0 11 0
0 0 2 12
0 0 0 0
*/
