#include "LongFloat.h"
#include "float.h"
#include "limits.h"



lfloat dtolf(double num ,int pft){

    lfloat converted_num;

    converted_num.digits = 0;
    converted_num.pft = pft;
    if(pft !=0){
        num*=pow(10,(-pft));
    }
    long  hrs = 10;
    int temp = 1;

    while(num != ((long)num)){
        num*= hrs;
        hrs*=hrs;
        temp*=2;
    }
    hrs = 10;
    int temp2 = 1;

    while((long)num%10 == 0){
        num/=hrs;
        temp-=temp2;
        if(num!=(long)num){
            while(num != ((long)num)){
                // printf(" num is %E \n",num);
                num*=10;
                temp++;
            }
            break;
        }
        hrs*=hrs;
        temp2*=2;
    }

    converted_num.digits = (long)num;
    converted_num.pft-=(temp-1);

    return converted_num;
}

double lftod(lfloat num);

lfloat multilf(lfloat arg1 , lfloat arg2){
    lfloat res;
    res.digits = arg1.digits*arg2.digits;
    res.pft = arg1.pft + arg2.pft;

    return res;
}

lfloat devidlf(lfloat arg1 , lfloat arg2){
    
    long limit = (LONG_MAX/10)-9;
    lfloat res;
    res.digits = 0;
    
    while(1){
        long temp_dig = arg1.digits/arg2.digits;
        if(res.digits>limit){
            arg1.pft++;
            break;
        }
        res.digits*=10;
        res.digits+=temp_dig;
        arg1.digits = arg1.digits%arg2.digits;
        if(arg1.digits == 0){
            break;
        }
        arg1.digits*=10;
        arg1.pft--;
    }

    res.pft = arg1.pft - arg2.pft;

    return res;

}

lfloat sublf(lfloat arg1 , lfloat arg2);

lfloat addlf(lfloat arg1 , lfloat arg2);

int main(){
    double t = 1.116*pow(10,-54);
    lfloat l = dtolf(7,0);
    double md = 9.109383*pow(10,-28);
    lfloat m = dtolf(22,0);
    printf("%ld , %d\n",l.digits,l.pft);
    lfloat res = devidlf(m,l);

    printf("double %.*E \n",22.0/7,DECIMAL_DIG);
    printf("double %.*E\n",(double)(res.digits)*pow(10,res.pft),DECIMAL_DIG);
    printf("long limit = %ld , %d \n",res.digits,res.pft);
    return 0;
}