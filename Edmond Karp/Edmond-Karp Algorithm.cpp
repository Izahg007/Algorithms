#include<iostream>
#include<vector>
#include<queue>
#include<map>
#include <stack>
using namespace std;
#define MAX 10

//User Defined structure for edges.
struct edge{
    int capacity;
    int flow;
    
    void _read(int a){
        this->capacity=a;
    }
    void _write(){
        cout<<this->flow<<"/";
        cout<<this->capacity<<endl;
    }
    edge(){
        this->capacity=0;
        this->flow=0;
    }
};

//Function for finding the Augmented Paths using BFS
vector<int> ek_bfs(int s,int t,vector<vector<edge>>A,int v){
    vector<int>path;
    map<int,int> track;
    vector<int> visited(v,0);
    queue<int> q;
    q.push(s);
    
    while(!q.empty()){
        if(visited[t]==1)
            break;
        int temp=q.front(); q.pop();
        
        
        for(int i=0;i<v;i++){
            if(A[temp][i].flow!=A[temp][i].capacity && A[temp][i].capacity!=0 && visited[i]==0){
                track[i]=temp;
                q.push(i);
                visited[i]=1;
            }
        }
    }

    stack<int>temp;
    temp.push(t);
    int t1=t;
    while(1){
        temp.push(track[t1]);
        if(track[t1]==s)
            break;
        t1=track[t1];
    }
    while(!temp.empty()){
        path.push_back(temp.top());
        temp.pop();
    }
    return path;
}

//The main Edmond-Karp Function for finding the maximun flow through the graph
int Edmond_Karp(int s,int t,vector<vector<edge>>Adj,int v){
    vector<int>path;
    int max_flow=0;
    while(1){
        //Find the augmented path first
        path=ek_bfs(s,t,Adj,v);
        if(Adj[path[0]][path[1]].capacity==0){
            cout<<"no path found\n";
            break;
        }
        else cout<<"path found";
        //Find the minimum edge capacity
        int mincap=INT_MAX;
        for(int i=0;i<(int)path.size()-1;i++){
            if(Adj[path[i]][path[i+1]].capacity<mincap)
                mincap=Adj[path[i]][path[i+1]].capacity;
        }
        //After finding the minimum capacity add the amount to it's flow
        for(int i=0;i<(int)path.size()-1;i++){
            Adj[path[i]][path[i+1]].flow=mincap;
        }
        max_flow+=mincap;
        cout<<"\nFollwing the path\n";
        for(int i=0;i<(int)path.size()-1;i++)
            cout<<path[i]+1<<"->";
        cout<<path[(int)path.size()-1]+1<<endl;
        cout<<"For the min cut:"<<mincap<<endl;
        cout<<"The Current Max Flow:";
        cout<<max_flow<<endl;
        cout<<"----------------------\n";
    }
    return max_flow;
}

int main(){
    int v;
    cout<<"Enter the number of vertices for the graph\n";
    cin>>v;
        vector<vector<edge>> adj(v,vector<edge>(v,edge()));
    cout<<"Enter the adjacency matrix for the network flow graph\n";
    for(int i=0;i<v;i++){
        for(int j=0;j<v;j++){
            int ele;
            cin>>ele;
            adj[i][j]._read(ele);
        }
    }

    int source,sink;
    cout<<"Enter the source and the sink nodes\n";
    cin>>source>>sink;
    
    cout<<Edmond_Karp(source-1,sink-1,adj,v)<<" is the final Max Flow of the Graph"<<endl;
    return 0;
}

