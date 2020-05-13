<<<<<<< HEAD
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#define Height 15

typedef struct {
    int id;
    int gender;
    double height;
} Height_t;

Height_t p[Height];
int main(void)
{
    int i,tmp,ID;
    char fname[FILENAME_MAX];
    char buf[256];
    FILE* fp;

    printf("Input the filename of sample height :");
    fgets(fname,sizeof(fname),stdin);
    fname[strlen(fname)-1] = '\0';

    fp = fopen(fname,"r");
    if(fp==NULL){
        fputs("File open error\n",stderr);
        exit(EXIT_FAILURE);
    }
    for(i=0;i<15;i++){
        sscanf(buf,"%d,%lf",&p[i].gender,&p[i].height);
    }
     if(fclose(fp) == EOF){
        fputs("file close error\n",stderr);
        exit(EXIT_FAILURE);
    }

    printf("Input the filename of sample ID :");
    fgets(fname,sizeof(fname),stdin);
    fname[strlen(fname)-1] = '\0';

    fp = fopen(fname,"r");
    if(fp==NULL){
        fputs("File open error\n",stderr);
        exit(EXIT_FAILURE);
    }
    for(i=0;i<14;i++){
        sscanf(buf,"%d",&p[i].id);
        
    }
     if(fclose(fp) == EOF){
        fputs("file close error\n",stderr);
        exit(EXIT_FAILURE);
    }
    
    printf("Which ID's data do you want? :");
    fgets(buf,sizeof(buf),stdin);
    sscanf(buf,"%d",&ID);

    for(i=0;i<14;i++){
        if(ID==p[i].id){
            tmp=i;
        }

    }
  
        printf("---\n");
        if(tmp>0){
        printf("ID: %d\n",p[tmp].id);
        if(p[tmp+1].gender==1){
        printf("gender: Male\n");
        }
        else{
        printf("gender: Female\n");
        }
        printf("height: %lf\n",p[tmp+1].height);
        }
        else{
        printf("No data\n");
        }
        
    return 0;
}
=======

>>>>>>> a3699f8eb3c1e93e3052fdcccde4324e6c63c4f4
