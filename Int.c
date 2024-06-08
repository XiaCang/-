#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include"high.h"

void _Init_Int_Op_(){

    IntOperator.FromInt32=_FromInt32;
    IntOperator.FromInt64=_FromInt64;
    IntOperator.FromString=_FromString;
    IntOperator.Print=_PrintInt;
    IntOperator.ToString=_ToString;
    IntOperator.ToInt32=_ToInt32;
    IntOperator.ToInt64=_ToInt64;
    IntOperator.Add=_Add;
    IntOperator.Sub=_Sub;   
    IntOperator.Compare=_Compare;
    IntOperator.Mul=_Mul;
    IntOperator.Mod=_Mod;
    IntOperator.Div=_Div;
    IntOperator.Pow=_Pow;
}

Int _Zero(){
    Int ret;
    ret.len=0;
    ret.isNeg=0;
    memset(ret.data,0,NUMMAXBIT);
    return ret;
}



Int _FromInt32(int n){
    Int ret=_Zero();
    if(n<0){
        n=-n;
        ret.isNeg=1;
    }
    while(n){
        ret.data[ret.len++]=n%10;
        n/=10;
    }
    return ret;
}

Int _FromInt64(long long n){
    Int ret=_Zero();
    if(n<0){
        n=-n;
        ret.isNeg=1;
    }
    while(n){
        ret.data[ret.len++]=n%10;
        n/=10;
    }
    return ret;
}

Int _FromString(char *s){
    int last=0,index=0;
    index=strlen(s)-1;
    Int ret=_Zero();
    if(*s=='0')return ret;
    if(*s=='-'){
        ret.isNeg=1;
        last=1;
    }
    while (index>=last) 
    {
        ret.data[ret.len++]=s[index--]-'0';
    }
    return ret;
}



char *_ToString(Int a){
    int i=0;
    int j=a.len-1;
    char *s=(char*)malloc(sizeof(char)*(a.len+1+a.isNeg));
    if(a.isNeg){
        s[i++]='-';
    }
    while(j>=0){
        s[i++]=a.data[j--]+'0';
    }
    s[i]='\0';
    return s;
}

void _PrintInt(Int n){
    if(n.isNeg){
        printf("-");
    }
    int i=n.len-1;
    if(n.len==0) {printf("0");return;}
    while(i>=0){
        printf("%d",n.data[i--]);
    }
}

Int _OppositeInt(Int a){
    Int ret=_Zero();
    ret.len=a.len;
    if(a.isNeg) ret.isNeg=0;
    else ret.isNeg=1;
    for (int i = 0; i <= ret.len; i++)
    {
        ret.data[i]=a.data[i];
    }
    return ret;
}

int _ToInt32(Int a){
    int _ret=0;
    for (int i = 9>a.len?a.len:9;i>=0; i--)
    {
        _ret=_ret*10+a.data[i];
    }
    if(a.isNeg) _ret=-_ret;
    return _ret;
    
}

long long _ToInt64(Int a){
    long long _ret=0;
    for (int i = 18>a.len?a.len:18;i>=0; i--){
        _ret=_ret*10+a.data[i];
    }
    if(a.isNeg) _ret=-_ret;
    return _ret;
}



Int _Sub(Int a,Int b){
    //a是负数 b是负数 
    if(a.isNeg&&b.isNeg){
        return _Sub(_OppositeInt(b),_OppositeInt(a));
    }

    //a是负数 b是正数
    if(a.isNeg&&!b.isNeg){
        return _OppositeInt(_Add(_OppositeInt(a),b));
    }

    //a是正数 b是负数
    if(!a.isNeg&&b.isNeg){
        return _Add(a,_OppositeInt(b));
    }

    //a是正数 b是正数
    if(!a.isNeg&&!b.isNeg){
        int _=_Compare(a,b);
        if(_==-1){
            return _OppositeInt(_Sub(b,a));
        }
        if(_==0){
            return _FromInt32(0);
        }
        Int ret=_Zero();
        ret.isNeg=0;
        int i=0,carry=0;
        while (i<a.len&&i<b.len)
        {
            ret.data[i]=a.data[i]-b.data[i]-carry;
            if(ret.data[i]<0){
                ret.data[i]+=10;
                carry=1;
            }
            else
                carry=0;
            i++;
        }

        while (i<a.len)
        {
            ret.data[i]=a.data[i]-carry;
            if(ret.data[i]<0){
                ret.data[i]+=10;
                carry=1;
            }
            else
                carry=0;
            i++;
        }

        ret.len=a.len;

        for(int i = a.len-1 ; i >= 0 ; i--)
        {
            if(ret.data[i]==0){
                ret.data[i]=0;
                ret.len--;
            }else{
                break;
            }
        }
        return ret;
    
    }
}

int _Compare(Int a,Int b){
    if(a.isNeg&&!b.isNeg){
        return -1;
    }

    if(!a.isNeg&&b.isNeg){
        return 1;
    }

    if(!a.isNeg&&!b.isNeg){
        if(a.len>b.len) return 1;
        if(a.len<b.len) return -1;
        for (int i = a.len-1; i >= 0; i--)
        {
            if(a.data[i]>b.data[i]) return 1;
            if(a.data[i]<b.data[i]) return -1;
        }
        return 0;
    }

    if(a.isNeg&&b.isNeg){
        if(a.len>b.len) return -1;
        if(a.len<b.len) return 1;
        for (int i = a.len-1; i >= 0; i--)
        {
            if(a.data[i]>b.data[i]) return -1;
            if(a.data[i]<b.data[i]) return 1;
        }
        return 0;
    }
}

Int _Add(Int a,Int b){
    if(a.isNeg&&b.isNeg){
        return _OppositeInt(_Add(_OppositeInt(a),_OppositeInt(b)));
    }

    if(a.isNeg&&!b.isNeg){
        return _Sub(b,_OppositeInt(a));
    }

    if(!a.isNeg&&b.isNeg){
        return _Sub(a,b);
    }

    if(!a.isNeg&&!b.isNeg){
        Int ret=_Zero();
        ret.isNeg=0;
        int i=0,carry=0;
        while (i<a.len&&i<b.len)
        {
            ret.data[i]=a.data[i]+b.data[i]+carry;
            if(ret.data[i]>=10){
                ret.data[i]-=10;
                carry=1;
            }
            else
                carry=0;
            i++;
        }

        while (i<a.len){
            ret.data[i]=a.data[i]+carry;
            if(ret.data[i]>=10){
                ret.data[i]-=10;
                carry=1;
            }
            else
                carry=0;
            i++;
        }

        while (i<b.len){
            ret.data[i]=b.data[i]+carry;
            if(ret.data[i]>=10){
                ret.data[i]-=10;
                carry=1;
            }   
            else
                carry=0;

            i++;
        }

        if(carry){
            ret.data[i++]=1;
        }
        
        ret.len=i;
        
        return ret;
    }
}

Int _Mul(Int a,Int b){
    Int ret=_Zero();
    int carry=0;
    if(a.len==0||b.len==0){
        ret.data[0]=0;
        ret.isNeg=0;
        ret.len=0;
        return ret;
    }
    ret.isNeg=a.isNeg^b.isNeg;
    ret.len=a.len+b.len;
    int i,j;
    for (i = 0; i < a.len; i++)
    {
        for (j = 0; j < b.len; j++)
        {
            if(i+j>NUMMAXBIT-1)break;
            ret.data[i+j]+=a.data[i]*b.data[j];
            if(ret.data[i+j]>=10){
                ret.data[i+j+1]+=ret.data[i+j]/10;
                ret.data[i+j]%=10;
            }
        }
    }
    
    while (ret.data[ret.len-1]==0&&ret.len>=0)
    {
        ret.len--;
    }
    return ret;
}



Int _Div(Int a,Int b){
    
    if(b.len==0){
        printf("error");
        return _Zero();
    }
    if(_Compare(a,b)==-1){
        return _Zero();
    }
    
    if(_Compare(a,b)==0){
        return _FromInt32(1);
    }

    Int ret=_Zero();
    ret.isNeg=a.isNeg^b.isNeg;

    int i=0;
    Int tmp=b;
    while(_Compare(a,tmp)>=0){
        tmp=_Mul(tmp,_FromInt32(10));
        i++;
    }
    ret.len=i;
    while(i>=0){
        if(_Compare(a,tmp)>=0){
            ret.data[i]++;
            a=_Sub(a,tmp);
        }else{
            i--;
            for (int _i = 0; _i < tmp.len; _i++)
            {
                tmp.data[_i]=tmp.data[_i+1];
            }
            tmp.data[tmp.len-1]=0;
            tmp.len--;
        }
    }
    
    return ret;
}

Int _Mod(Int a,Int b){
    if(b.len==0){
        return a;
    }

    if(a.len==0){
        return _Zero();
    }

    if(_Compare(a,b)==-1){
        return a;
    }

    if(_Compare(a,b)==0){
        return _Zero();
    }

    Int ret=_Zero();
    ret.isNeg=a.isNeg^b.isNeg;

    int i=0;
    Int tmp=b;
    while(_Compare(a,tmp)>=0){
        tmp=_Mul(tmp,_FromInt32(10));
        i++;
    }
    ret.len=i;
    while(i>=0){
        if(_Compare(a,tmp)>=0){
            ret.data[i]++;
            a=_Sub(a,tmp);
        }else{
            i--;
            for (int _i = 0; _i < tmp.len; _i++)
            {
                tmp.data[_i]=tmp.data[_i+1];
            }
            tmp.data[tmp.len-1]=0;
            tmp.len--;
        }
    }
    
    return a;
}

Int _Pow(Int a,Int b){
    Int res=_FromInt32(1);
    while (_Compare(b,_FromInt32(0))>0)
    {
        if(_Compare(_Mod(b,_FromInt32(2)),_FromInt32(1))==0)
            res=_Mul(res,a);
        a=_Mul(a,a);
        b=_Div(b,_FromInt32(2));
    }
    return res;
}


int main() {
    _Init_Int_Op_();
    Int a,b,c;
    char s1[100],s2[100],op;
    while (1)
    {
        printf(">>");
        scanf("%s %c %s",s1,&op,s2);
        a=_FromString(s1);
        b=_FromString(s2);
        if(op=='+')c=_Add(a,b);
        if(op=='-')c=_Sub(a,b);
        if(op=='*')c=_Mul(a,b);
        if(op=='/')c=_Div(a,b);
        if(op=='%')c=_Mod(a,b);
        if(op=='^')c=_Pow(a,b);
        printf("=");
        _PrintInt(c);
        printf("\n");
    }
    
    

    return 0;
}
