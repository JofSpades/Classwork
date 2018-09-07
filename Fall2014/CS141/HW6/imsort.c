//
//  imsort.c
//  hw6
//
//  Created by Maxwell Petersen on 12/4/14.
//  Copyright (c) 2014 Maxwell Petersen. All rights reserved.
//

#include <stdio.h>
#include "list.h"

int main(){

    printf("LOADING INPUT AND SETTING UP\nPLEASE WAIT...\n");

    LIST **in;
    LIST **secnd;
    int cnt = 0;
    int inp;
    int t = 1;


    
    while(scanf("%i", &inp) == 1){

        in[cnt] = lst_create();
        
        lst_push_back(in[cnt], inp);

        cnt++;
        
    }
    
    printf("LOAD COMPLETE\nNOW SORTING\n");

    while(cnt > 1){

        for(int i = 0; i <= cnt; i += (2 * t)){

            lst_merge_sorted(in[i], in[i + (1 * t)]);
            
            lst_print(in[i]);

            /*if(i * 2 < cnt){
                
                if(i == 0){
                    
                    in[0] = secnd[i];
                    
                    in[i] = secnd[i];
             
                } else {
                
                    in[i * 2] = secnd[i];
                
                    in[i] = secnd[i];
                }
                
            }*/

        }
        
        t++;

        cnt /= 2;

    }

    lst_print(in[0]);

    printf("END\n");
    
    return 0;

}