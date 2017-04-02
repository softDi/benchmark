typedef struct task_t{
    char name[16];
    int pid;
} task_t;

long myfunc(long *pa, long *pb, task_t *pt, long d,
                    long e, long f, long g, long h)
{
    long a=*pa, b=*pb, c=pt->pid;
    long xx = a * b * c * d * e * f * g * h;
    long yy = a + b + c + d + e + f + g + h;
    long zz = xx+yy;
    return zz + 20;
}

int main(){
    long a=1,b=2,c=3;
    task_t t={.pid=978};
    myfunc(&a,&b,&t,4,5,6,7,8);
    return 0;
}
