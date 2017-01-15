#include <stdio.h> 
#include <stdlib.h> 
#define NMAX 500 
#define DEBUG 1

int min_dom_set(int level){
    if(flag){
        try red
        u= number of undominated vertices
        Δ = maximum degree of a vertex
        Set n_extra=u/(Δ+1);
        If size + n_extra ≥ min
        
        else:
            copy the current dominating set dom to min_dom
            and set min_size= size.
            
        End if
        if(level==0) return 1;
        return min_dom_set(level-1).
    }
    if(level==0){
        n_dominated=0;
        num_choice[v]= degree of v + 1;
        num_dominated[v]= 0;
        size=0;
        dom[i]= no values assigned since size is 0 min_size= n;
        min_dom[i]= i for i= 0 to n-1;
        flag=false;
    }
    if(vertex u=blue){
        vertex u=red;
        add u to dom
        for each neighbour v of u{
            num_dominated[v]++;
        }
        n_dominated update;
        return min_dom_set(level+1);
    }else if(for any vertex v,num_choice[v]==0){
        return min_dom_set(level-1);
        
    }else{
        if(level>=n){
            flag=true;
            return min_dom_set(level-1);
        }
        vertex u = blue;
        for each neighbour v of u{
            num_choice[v]--;
        }
        return min_dom_set(level+1);
    }
}



#if DEBUG
printf("Level %3d: ", level);
print_vector(size, dom);
printf("Number of vertices dominated: %3d\n",
       n_dominated);
printf("Number of choices per vertex:\n"); print_vector(n, num_choice); printf("Number of times dominated:\n"); print_vector(n, num_dominated);
#endif