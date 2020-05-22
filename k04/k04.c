#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#define N_HEIGHT 14

typedef struct {
    int id;
    int gender;
    double height;
} Height_t;

Height_t p[N_HEIGHT];
int main(void)
{
    int i,tmp=-1,ID;
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
    
        fgets(buf,sizeof(buf),fp);
        i=0;
        while(fgets(buf,sizeof(buf),fp)){
        sscanf(buf,"%d,%lf",&p[i].gender,&p[i].height);
        i++;
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

     while(fgets(buf,sizeof(buf),fp)){
        sscanf(buf,"%d",&p[i].id);
        i++;
        }
        
     if(fclose(fp) == EOF){
        fputs("file close error\n",stderr);
        exit(EXIT_FAILURE);
    }
    
    printf("Which ID's data do you want? :");
    fgets(buf,sizeof(buf),stdin);
    sscanf(buf,"%d",&ID);

    for(i=0;i<N_HEIGHT;i++){
        if(ID==p[i].id){
            tmp=i;
        }

    }
  
        printf("---\n");
        if(tmp!=-1){
        printf("ID: %d\n",p[tmp].id);
        if(p[tmp].gender==1){
        printf("gender: Male\n");
        }
        else{
        printf("gender: Female\n");
        }
        printf("height: %lf\n",p[tmp].height);
        }
        else{
        printf("No data\n");
        }
        
    return 0;
}
