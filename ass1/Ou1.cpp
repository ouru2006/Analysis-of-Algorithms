/*
 *Dora Ou
 *V00835123
 *CSC425 ASS1
 */
#include <stdio.h>
#include <stdlib.h> 
#define NMAX 100
#define DEBUG 0

int read_graph(int *n, int *k, int G[NMAX][NMAX],int set[NMAX]);
void print_graph(int n, int G[NMAX][NMAX]);
int certificate(int n, int k, int G[NMAX][NMAX],int set[NMAX]);
int verbose;
int main(int argc, char *argv[])
{
    if (argc != 2)
    { printf("Usage: %s <verbose>\n", argv[0]);
    }
    verbose= atoi(argv[1]);
    
    int n;
    int k; //size of dominating set
    int G[NMAX][NMAX];
    int set[NMAX];//proposed dominating set
    int n_graph;
    n_graph=0;
    while (read_graph(&n, &k, G, set))
    {
        n_graph++;
#if DEBUG
        printf("Input graph %3d:\n", n_graph);
        print_graph(n, G);
#endif
        
        // Read certificate then check it here.
        if(verbose==1){
            printf("Graph %3d:\n", n_graph);
            print_graph(n, G);
            int d=certificate(n,k,G,set);
            if(d==-1){
                printf("Graph %5d: BAD GRAPH\n",n_graph);
                exit(0);//exit when a graph error
            }
            else if(d==0)
                printf("Graph %5d: BAD CERTIFICATE\n",n_graph);
        
            else
                printf("Graph %5d: OK\n", n_graph);
            printf("=============================\n");
        }else if(verbose==0){
            int d=certificate(n,k,G,set);
            printf("%5d %2d\n", n_graph,d);
            if(d==-1)exit(0);
        }
        
    }
}

//check the graph, the set range and certificate if it is dominated
int certificate(int n, int k, int G[NMAX][NMAX],int set[NMAX]){
    int i,j;
    //check the symmetric
    for (i=0; i < n; i++)
        for (j=i+1; j < n; j++)
            if (G[i][j]!=G[j][i]){
                if (verbose==1)
                    printf("*** Error- adjacency matrix is not symmetric: A[ %d][ %d] = %d, A[ %d][ %d]= %d\n", i, j ,G[i][j], j, i, G[j][i]);
                return(-1);
            }
    //print the input domainating set
    if (verbose==1){
        printf("Proposed dominating set:\n");
        for (i=0; i < k; i++){
            printf("%3d ", set[i]);
        }
        printf("\n");
    }
    //check the rang of set
    for (i=0; i<k; i++){
        if(set[i]<0 || set[i]>=n){
            if(verbose==1)
                printf("Error- Value %3d in the certificate is not in the range [0, %3d]\n", set[i],n-1);
            return 0;
        }
    }
    //check if it is dominated
    bool check[NMAX];
    //initialize the check list
    for (i=0; i < n; i++)
        check[i]=false;
    for (i=0; i < k; i++){
        check[set[i]]=true;
        for(j=0; j < n; j++)
            if(G[set[i]][j]) check[j]=true;
    }
    for (i=0; i < n; i++)
        if(!check[i]){
            if(verbose==1)
                printf("Error- Vertex %3d is not dominated\n", i);
            return 0;
        }
    return(1);
}
int read_graph(int *n, int *k, int G[NMAX][NMAX],int set[NMAX])
{
    int i, j, u, d;
    if (scanf("%d", n)!=1) return(0);
    //check If NMAX is not big enough
    if(*n > NMAX){
        printf("Error: NMAX is not big enough. Please increase NMAX and recompile.\n");
        exit(0);
    }
    // IMPORTANT: some compilers initialize // variables but others do not. Be safe and // initialize everything always!!!
    for (i=0; i < *n; i++)
        for (j=0; j < *n; j++)
            G[i][j]=0;
    
    // Error handling not included!
    for (i=0; i < *n; i++)
    {
        scanf("%d", &d); // Read degree
        for (j=0; j < d; j++)
        {
            if (scanf("%d", &u)!= 1)
            {
                exit(0); // Error!
            }
            G[i][u]= 1;
        }
    }
    //read the domainating set
    if(scanf("%d", k)!=1) return(0);
    //initialize the domainating set array
    for(i=0;i < *k; i++)
        set[i]=0;
    for(i=0; i< *k; i++){
        scanf("%d", &d);
        set[i]=d;
    }
    
    return(1);
}

void print_graph(int n, int G[NMAX][NMAX]) {
    int i, j, d;
    for (i=0; i < n; i++)
    {
        d=0;
        for (j=0; j < n; j++)
            d+= G[i][j];
        printf("%3d(%2d): ", i, d);
        for (j=0; j < n; j++)
        {
            if (G[i][j]) printf("%3d ", j);
        }
        printf("\n");
    }
}