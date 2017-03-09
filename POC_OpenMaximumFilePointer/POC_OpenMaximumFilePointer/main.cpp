////
////  main.cpp
////  POC_OpenMaximumFilePointer
////
////  Created by Vijay on 27/02/17.
////  Copyright © 2017 Vijay. All rights reserved.
////
//
#include <iostream>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/resource.h>
#include <sys/time.h>
#include <stdlib.h>

struct rlimit rl;

void displayUpperLimit()
{
//      #1
//        printf("Upperlimit = \n");
//        system("ulimit -n");
    
    // #2
    getrlimit (RLIMIT_NOFILE, &rl);
    printf("\n Default value is : %llu\n",rl.rlim_cur);
}

void displayMaximumUpperLimit()
{
    int res = 0;
    int counter = -1;
    char upperLimitStr[20];
    
//    struct rlimit rl1;
//    getrlimit (RLIMIT_NOFILE, &rl);
//    printf("\n Default value is : %llu\n",rl.rlim_cur);
    
    //#1
        do
        {
            counter++;
            sprintf(upperLimitStr, "ulimit -n %d 2>null",counter);
            res = system(upperLimitStr);
        }while(res==0);
    
    //#2
//    do
//    {
//        counter++;
//        rl1.rlim_cur = counter; // 3 are for stdin, stdout, stderr and one extra
//        res = setrlimit (RLIMIT_NOFILE, &rl1);
//    }while(res == 0);
    
    printf("MaximumUpperLimit = %d\n",counter-1);
}

// need to check
void changeUpperLimit(int limit)
{
    //#1
    int res = 0;
    //    char upperLimitStr[20];
    //    sprintf(upperLimitStr, "ulimit -n %d",limit);
    //    res = system(upperLimitStr);
    //    printf("\n ulimit = %d\n\n",res);
    
    //#2
    rl.rlim_cur = limit; // 3 are for stdin, stdout, stderr and one extra
    res = setrlimit (RLIMIT_NOFILE, &rl);
    res = getrlimit (RLIMIT_NOFILE, &rl);
    printf("\n Default value now is : %lldl\n", (long long int)rl.rlim_cur);
    if(res == 0)
    {
        printf("successful\n");
    }
    
    else
    {
        printf("error occured while setting limit\n");
    }
}

void howManyFDYouCanUse()
{
    int i=0;
    FILE *fp;
    char filename[20];
    while(1)
    {
        i++;
        sprintf(filename, "test_%d",i);
        fp = fopen(filename, "w");
        if( fp == NULL)
        {
            break;
        }
        //        sprintf(filename, "rm -rf test_%d",i);
        //        system(filename);
    }
    printf("you can use maxLimit = %d\n",i);
    
}


int main(int argc, const char * argv[]) {
    
//    displayUpperLimit();
    displayMaximumUpperLimit();
//    changeUpperLimit(2500);
//    howManyFDYouCanUse();
    return 0;
}
