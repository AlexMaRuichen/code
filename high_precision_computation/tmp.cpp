void operator *=(const bignum &s)
    {
        bignum tmp;
        tmp.nage=(nage==s.nage?false:true);
        tmp.len=len+s.len;
        int temp,temp1;
        for(int i=1;i<=len;i++)
        {
            int j,up=0;
            for(j=1;j<=s.len;j++)
            {
                temp=m[i]*s.m[j]+tmp.m[i+j-1]+up;
                up=temp/maxn;
                tmp.m[i+j-1]=temp%maxn;
            }
            if(up)
                tmp.m[i+j-1]=up;
        }
        (*this)=tmp;
        while(!m[len]&&len>1)
            len--;
        if(len==1&&!m[1])
            nage=false;
        return ;
    }
