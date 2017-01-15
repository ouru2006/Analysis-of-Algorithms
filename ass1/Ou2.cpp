/*
 *Ru Ou
 *V00835123
 *CSC425 ASS2
 */
#include <stdio.h>
#include <stdlib.h>
#define NMAX 2187
#define DEBUG 0

int read_graph(int *n, int **G, int degree[NMAX]);
void find_dom_set(int level,int n, int **G, int n_dominated, int num_choice[NMAX], int num_dominated[NMAX], int size, int dom[NMAX], int *min_size, int min_dom[NMAX], int degree[NMAX]);
void print_set(int a, int b[NMAX]);
int check_graph(int n, int **G);
void print_graph(int n, int **G);
int main(int argc, char *argv[])
{
    int i,n, **G, *degree, n_graph, *p, n_dominated, *num_choice, *num_dominated, *min_dom, *dom, min_size, size, graph, verbose;
    

    G=new int *[NMAX];
    for(i=0;i<NMAX;i++){
        G[i]=new int[NMAX];
    }
    degree = new int[NMAX];
    n_graph = 1 ;
    
    //data structures
    p=new int[NMAX];//a random permutation
    n_dominated = 0;
    num_choice = new int[NMAX];
    num_dominated=new int[NMAX];
    min_dom=new int[NMAX];
    dom = new int[NMAX]; //current dom list
    size = 0; //current dom number
    //check usage
    if (argc != 1)
    {
        printf("Usage: %s < in.txt > out.txt\n", argv[0]);
        exit(0);
    }
    graph=read_graph(&n, G, degree);
    while (graph==1)
    {
        //check graph validity
        if(!check_graph(n,G)){
            printf("Graph %5d: BAD GRAPH\n", n_graph);
            return(-1);
        }
        find_dom_set(0, n, G, n_dominated, num_choice, num_dominated, size, dom, &min_size, min_dom,degree);
        //print result
        //printf("Graph %3d n= %3d: (Size %3d) ",n_graph,n,min_size);
        //
        //order[min_size]++;
        print_graph(n, G);
        print_set(min_size, min_dom);
        
        graph=read_graph(&n, G, degree);
        n_graph++;
        
        
    }
    if(graph==-1){
        printf("Graph %5d: BAD GRAPH\n", n_graph);
        return(-1);
    }
    
        
}

//from lecture sildes
void find_dom_set(int level, int n,int **G, int n_dominated, int num_choice[NMAX], int num_dominated[NMAX], int size, int dom[NMAX], int *min_size, int min_dom[NMAX], int degree[NMAX]){
    int i;
    //Initial the data structures
    if(level==0){
        for(i=0; i< n; i++){
            num_dominated[i]=0;
            min_dom[i]=i;
            num_choice[i]=degree[i];
            dom[i]=0;
        }
        *min_size=n;
    }
#if DEBUG

#endif
    
    for(i=0;i<n;i++)
        if(num_choice[i]==0)
            return;
    int n_extra = (n-n_dominated+degree[level])/(degree[level]+1);
    if(size + n_extra >= *min_size){
        return;
    }else if(n_dominated==n || level==n){
        if(size < *min_size){
            for(i=0;i<n;i++)
                min_dom[i]=dom[i];
            *min_size = size;
        }
        return;
    }
    //The exhaustive backtrack
    int u=level;
    //try as blue
    num_choice[u]--;
    for(i=0;i<n;i++)
        if(G[u][i]==1){
            num_choice[i]--;
        }
    find_dom_set(level+1, n, G, n_dominated, num_choice, num_dominated, size, dom, min_size, min_dom,degree);
    
    num_choice[u]++;
    for(i=0;i<n;i++)
        if(G[u][i]==1){
            num_choice[i]++;
        }
 
    //try vertex u as red
    size++;
    dom[size-1]=u;
    num_dominated[u]++;
    for(i=0;i<n;i++)
        if(G[u][i]==1){
            num_dominated[i]++;
        }
    //Update n_dominated.
    n_dominated = 0;
    for(i=0;i<n;i++)
        if(num_dominated[i] > 0)
            n_dominated++;
    find_dom_set(level+1, n, G, n_dominated, num_choice, num_dominated, size, dom, min_size, min_dom, degree);
    
    size--;
    num_dominated[u]--;
    for(i=0;i<n;i++)
        if(G[u][i]==1){
            num_dominated[i]--;
        }
    //Update n_dominated.
    n_dominated = 0;
    for(i=0;i<n;i++)
        if(num_dominated[i] > 0)
            n_dominated++;
    return;
  
}

int read_graph(int *n,  int **G, int degree[NMAX])
{
    int i, j, u, d;
    if (scanf("%d", n)!=1) return(0);
    //check If NMAX is not big enough
    if(*n > NMAX || *n<1){
        printf("*** Error- n= %d is out of range [1, %d]\n",*n,NMAX);
        return(-1);
    }
    // initialize
    for (i=0; i < *n; i++){
        degree[i] = 0;
        for (j=0; j < *n; j++)
            G[i][j] = 0;
    }
    
    for (i=0; i < *n; i++)
    {
        if(scanf("%d", &d)!=1){
            printf("*** Error- degree value missing for vertex %3d\n",i);
            return(-1);
        }
        if(d >= *n || d<0){
            printf("*** Error- Degree of vertex %3d = %3d is out of range [0, %3d]\n",i,d,*n-1);
            return(-1);
        }
        degree[i] = d + 1;
        for (j=0; j < d; j++)
        {
            if (scanf("%d", &u)!= 1){
                printf("*** Error- Neighbour value missing for vertex %3d\n",j);
                return(-1);
            }
            //check negative or big
            if (u >= *n|| u<0){
                printf("*** Error- Neighbour %3d of vertex %d = %3d is out of range [0, %3d]\n",j,i,u,*n-1);
                return(-1);
            }
            
            G[i][u]++;
        }
    }
    
    return(1);
}

//checking for loops, multiple edges, ensuring the graph is symmetric
int check_graph(int n, int **G){
    int i,j;
    for(i=0;i<n;i++){
        //check loop
        if(G[i][i]!=0){
            printf("*** Error- adjacency matrix is non-zero on the diagonal (loop): A[%2d][%2d] =%2d\n",i,i,G[i][i]);
            return(0);
        }
        for(j=0;j<n;j++){
            //multiple edges,symmetric
            if(G[i][j]>1 ){
                printf("*** Error- adjacency matrix has multiple edges A[%2d][%2d] =%2d\n",i,j,G[i][j]);
                return(0);
            }else if(G[i][j]!=G[j][i]){
                printf("*** Error- adjacency matrix is not symmetric: A[%2d][%2d] =%2d, A[%2d][%2d]=%2d\n",i,j,G[i][j],j,i,G[j][i]);
                return(0);
            }
        }
    }
    return(1);
}
void print_graph(int n, int **G) {
    int i, j, d;
    printf("%d\n", n);
    for (i=0; i < n; i++)
    {
        d=0;
        for (j=0; j < n; j++)
        d+= G[i][j];
        printf("%2d ", d);
        for (j=0; j < n; j++)
        {
            if (G[i][j]) printf("%d ", j);
        }
        printf("\n");
    }
    printf("\n");
}
void print_set(int a, int b[NMAX]){
    //printf("dom set：\n");
    printf("%2d ",a);
    for(int i=0; i<a; i++)
        printf("%d ",b[i]);
    printf("\n\n");
    
}
