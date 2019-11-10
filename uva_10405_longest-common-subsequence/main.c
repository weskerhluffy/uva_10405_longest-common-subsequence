/*
//
//  main.c
//  uva_10405_longest-common-subsequence
//
//  Created by ernesto alvarado on 10/11/19.
//  Copyright © 2019 ernesto alvarado. All rights reserved.
//

// XXX: https://onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=1346
 */

#include <stdio.h>
#include <stdlib.h>

#define max(a,b) ((a)>(b)?a:b)

char *ltrim(char *str, const char *seps)
{
    size_t totrim;
    if (seps == NULL) {
        seps = "\t\n\v\f\r ";
    }
    totrim = strspn(str, seps);
    if (totrim > 0) {
        size_t len = strlen(str);
        if (totrim == len) {
            str[0] = '\0';
        }
        else {
            memmove(str, str + totrim, len + 1 - totrim);
        }
    }
    return str;
}
char *rtrim(char *str, const char *seps)
{
    int i;
    if (seps == NULL) {
        seps = "\t\n\v\f\r ";
    }
    i = strlen(str) - 1;
    while (i >= 0 && strchr(seps, str[i]) != NULL) {
        str[i] = '\0';
        i--;
    }
    return str;
}
char *trim(char *str, const char *seps)
{
    return ltrim(rtrim(str, seps), seps);
}

void imprime_matrix(int **m,int filas,int cols){
    int i,j;
    printf("matrix:\n");
    for(i=0;i<filas;i++){
        for(j=0;j<cols;j++){
            printf("%02d ",m[i][j]);
        }
        printf("\n");
    }
}

int lcs(char *s1,char *s2){
    int s1_len=strlen(s1);
    int s2_len=strlen(s2);
    int i=0,j=0,cdp=0;
    int **dp=NULL;
    
    if(!s1_len || !s2_len){
        return 0;
    }
    
    dp=calloc(s1_len,sizeof(int*));
    for(i=0;i<s1_len;i++){
        dp[i]=calloc(s2_len,sizeof(int));
    }
    dp[0][0]=s1[0]==s2[0];
    
    for(j=1;j<s2_len;j++){
        cdp=max(dp[0][j-1], s1[0]==s2[j]);
        dp[0][j]=cdp;
    }
    for(i=1;i<s1_len;i++){
        dp[i][0]=max(dp[i-1][0], s1[i]==s2[0]);
    }
    
    for(i=1;i<s1_len;i++){
        for(j=1;j<s2_len;j++){
            cdp=0;
            char c1=s1[i];
            char c2=s2[j];
            if(c1==c2){
                cdp=dp[i-1][j-1]+1;
            }
            else{
                cdp=max(dp[i][j-1],dp[i-1][j]);
            }
            dp[i][j]=cdp;
        }
    }
    int r=dp[s1_len-1][s2_len-1];
    free(dp);
    return r;
}

int main(int argc, const char * argv[]) {
#ifdef __APPLE__
    if (getenv ("STDIN"))
    {
        if (!freopen (getenv ("STDIN"), "r", stdin))
        {
            printf ("no se pudo stdin con %s", getenv ("STDIN"));
            exit (1);
        }
    }
    if (getenv ("STDOUT"))
    {
        if (!freopen (getenv ("STDOUT"), "w", stdout))
        {
            printf ("no se pudo stdin con %s", getenv ("STDOUT"));
            exit (1);
        }
    }
    if (getenv ("STDERR"))
    {
        if (!freopen (getenv ("STDERR"), "w", stderr))
        {
            printf ("no se pudo stdin con %s", getenv ("STDERR"));
            exit (1);
        }
    }
#endif
    char *buffer1;
    char *buffer2;
    size_t bufsize = 1001;
    
    buffer1 = (char *)malloc(bufsize * sizeof(char));
    buffer2 = (char *)malloc(bufsize * sizeof(char));
    
    while(getline(&buffer1,&bufsize,stdin)>0){
        bufsize=1001;
        getline(&buffer2, &bufsize, stdin);
        bufsize=1001;
        int r=lcs(trim(buffer1,NULL), trim(buffer2,NULL));
        printf("%d\n",r);
    }
    return 0;
}
