#include<stdio.h>
#include<stdint.h>
typedef struct Image{
    uint32_t w;
    uint8_t apha;
    uint32_t h;
    uint8_t r,g,b;
    uint32_t id;
    uint8_t z;
}Image;

#define offsetof(s,m) (size_t)&(((s *)0)->m)
#define g_offsetof(type, member) __builtin_offsetof (type, member)
int main(){
    Image img;

    printf("Keil C implementation : \n");
    printf("w %u \n", offsetof(Image,w));
    printf("apha %u \n", offsetof(Image,apha));
    printf("h %u \n", offsetof(Image,h));
    printf("r %u \n", offsetof(Image,r));
    printf("g %u \n", offsetof(Image,g));
    printf("b %u \n", offsetof(Image,b));
    printf("id %u \n", offsetof(Image,id));
    printf("z %u \n", offsetof(Image,z));

    printf("GCC built-in mplementation : \n");
    printf("w %u \n", g_offsetof(Image,w));
    printf("apha %u \n", g_offsetof(Image,apha));
    printf("h %u \n", g_offsetof(Image,h));
    printf("r %u \n", g_offsetof(Image,r));
    printf("g %u \n", g_offsetof(Image,g));
    printf("b %u \n", g_offsetof(Image,b));
    printf("id %u \n", g_offsetof(Image,id));
    printf("z %u \n", g_offsetof(Image,z));


    printf("size of image = %u\n",sizeof(Image));

    return 0;
}


