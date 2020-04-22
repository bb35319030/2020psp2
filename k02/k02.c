#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

extern double p_stdnorm(double z);


int main(void)
{
    double val,Avea=170.8,Vara=5.43,Aveb=169.7,Varb=5.5,likelihoodA,likelihoodB,tmpa,tmpb;
    char fname[FILENAME_MAX];
    char buf[256];
    FILE* fp;
    double L1=1,L2=1;

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
        
        tmpa=(val-Avea)/Vara;
        likelihoodA=p_stdnorm(tmpa)*L1;
        tmpb=(val-Aveb)/Varb;
        likelihoodB=p_stdnorm(tmpb)*L2;
        L1=likelihoodA;
        L2=likelihoodB;


    }

    if(fclose(fp) == EOF){
        fputs("file close error\n",stderr);
        exit(EXIT_FAILURE);
    }

    printf("L_A: %f\n",likelihoodA);
    printf("L_B: %f\n",likelihoodB);

    return 0;
}
double p_stdnorm(double z)
{
    return 1/sqrt(2*M_PI) * exp(-z*z/2);
}


