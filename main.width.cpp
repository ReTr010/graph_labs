#include<iostream>
#include<stdlib.h>
using namespace std;
int i,j,n,m;
int r,k=0,os,st;
struct node
{
    int num;
    int p;
    node *next;
    node(int x,int c, node * t)
    {num=x;p=c;next=t;}
};
int first[70];
int second[70];
int s[70];
int Numb[70];
int ms[70][70];
typedef node *lnk;
lnk adj[100];
void PS()
{
    i=0;r=0;
    first[0]=st-1;
    cout<<"\n Breadth search \n"<<first[0]+1<<' ';
    s[0]=first[0];
    while((first[0]+1)||(second[0]+1))
    {
        if(first[0]+1)
        {
            j=0;
            i=0;
            os=-1;
            while(first[j]+1)
            {
                lnk tmp=adj[first[j]];
                first[j]=-1;
                j++;
                while(tmp && tmp->p)
                {
                    second[i]=tmp->num;
                    tmp->p=0;
                    i++;
                    k=0;
                    if(tmp->num!=s[k])
                    {
                        os++;
                        Numb[os]=tmp->num;
                        s[k]=tmp->num;
                    }
                    tmp=tmp->next;
                }
            }
            for(os; os>=0; os--)
                cout<<Numb[os]+1<<' ';
        }
        else
        {

            if(second[0]+1)
            {
                j=0;
                i=0;
                os=-1;
                while(second[j]+1)
                {
                    lnk tmp=adj[second[j]];
                    second[j]=-1;
                    j++;
                    while(tmp && tmp->p)
                    {
                        first[i]=tmp->num;
                        tmp->p=0;
                        i++;
                        k=0;
                        if(tmp->num!=s[k])
                        {
                            os++;
                            Numb[os]=tmp->num;
                            s[k]=tmp->num;
                        }
                        tmp=tmp->next;
                    }
                }
                for(os; os>=0; os--)
                    cout<<Numb[os]+1<<' ';
            }
        }
    }
}

void EN_ss()
{
    int tmp;
    i=0;
    j=0;
    cout<<" Enter adjacency list \n";
    for(int i=0; i<n; i++)
    {
        cout<<i+1<<":";
        cin>>tmp;
        j=0;
        while(tmp)
        {
            ms[i][j]=tmp;
            j++;
            adj[i]=new node(tmp-1,1,adj[i]);
            cin>>tmp;
        }
    }
}

int main()
{
    for(i=0; i<70; i++)
    {
        s[i]=-1;
        first[i]=-1;
        second[i]=-1;
    }
    cout<<"Enter number of vertices: \n";
    cin>>n;
    EN_ss();
    cout<<"Enter starting vertex: \n ";
    cin>>st;
    PS();
    return 0;}

