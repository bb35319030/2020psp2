#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

extern double ave_online(double val,double ave,double n);
extern double var_online(double val,double ave,double square_ave, double n);



int main(void)
{
    double val,ave,square_ave=0,Ave=0,Var=0,kogaku_ave=0,kogaku_var=0;
    int n=1;
    char fname[FILENAME_MAX];
    char buf[256];
    FILE* fp;

    printf("input the filename of sample:");
    fgets(fname,sizeof(fname),stdin);
    fname[strlen(fname)-1] = '\0';
    printf("the filename of sample: %s\n",fname);

    fp = fopen(fname,"r");
    if(fp==NULL){
        fputs("File open error\n",stderr);
        exit(EXIT_FAILURE);
    }

    while(fgets(buf,sizeof(buf),fp) != NULL){
        sscanf(buf,"%lf",&val);

        Ave=ave_online(val, ave,n);
        Var=var_online(val,ave,square_ave,n);
        kogaku_ave=Ave;
        kogaku_var=n*Var/(n-1);
        square_ave=ave_online(val*val,square_ave,n);
        n=n+1;
        ave=Ave;
        
    }

    if(fclose(fp) == EOF){
        fputs("file close error\n",stderr);
        exit(EXIT_FAILURE);
    }

    printf("average: %f\n",Ave);
    printf("variance: %f\n",Var);
    printf("kogaku_average: %f\n",kogaku_ave);
    printf("kogaku_variance: %f\n",kogaku_var);

    return 0;
}

double ave_online(double val,double ave,double n){
    return  (n-1) * ave/n  + val/n ;
    }

extern double var_online(double val,double ave,double square_ave, double n){
    return (((n-1) *square_ave /n) + val * val/n) - (((n-1)*ave/n)+val/n)*(((n-1)*ave/n)+val/n);
}