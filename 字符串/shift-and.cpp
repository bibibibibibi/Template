int size=128; //此处默认字符集规模为128
//预处理
void preShiftAnd(const char *p,int m,unsigned int *s)
{
    for(int i=0;i<size;i++)
        s[i]=0;
    for(int i=0;i<m;i++)
        s[p[i]]|=1<<i;
}
//Shift-And
int ShiftAnd(const char *t,const char *p)
{
    int tLen=strlen(t);
    int pLen=strlen(p);
    unsigned int state=0;//即D数组
    unsigned int s[size];
    if(tLen<pLen) return -1;
    preShiftAnd(p,pLen,s);//预处理
    for(int i=0;i<tLen;i++)
	{
        state=((state<<1)|1)&s[t[i]];
        if(state&1<<(pLen-1))//最高位出现零
            return i-pLen+1;
    }
    return -1;
}
