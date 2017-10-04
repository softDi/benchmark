
run:     file format elf64-x86-64


Disassembly of section .init:

0000000000400548 <_init>:
  400548:	48 83 ec 08          	sub    $0x8,%rsp
  40054c:	48 8b 05 a5 0a 20 00 	mov    0x200aa5(%rip),%rax        # 600ff8 <_DYNAMIC+0x200>
  400553:	48 85 c0             	test   %rax,%rax
  400556:	74 05                	je     40055d <_init+0x15>
  400558:	e8 23 00 00 00       	callq  400580 <__gmon_start__@plt>
  40055d:	48 83 c4 08          	add    $0x8,%rsp
  400561:	c3                   	retq   

Disassembly of section .plt:

0000000000400570 <__gmon_start__@plt-0x10>:
  400570:	ff 35 92 0a 20 00    	pushq  0x200a92(%rip)        # 601008 <_GLOBAL_OFFSET_TABLE_+0x8>
  400576:	ff 25 94 0a 20 00    	jmpq   *0x200a94(%rip)        # 601010 <_GLOBAL_OFFSET_TABLE_+0x10>
  40057c:	0f 1f 40 00          	nopl   0x0(%rax)

0000000000400580 <__gmon_start__@plt>:
  400580:	ff 25 92 0a 20 00    	jmpq   *0x200a92(%rip)        # 601018 <_GLOBAL_OFFSET_TABLE_+0x18>
  400586:	68 00 00 00 00       	pushq  $0x0
  40058b:	e9 e0 ff ff ff       	jmpq   400570 <_init+0x28>

0000000000400590 <puts@plt>:
  400590:	ff 25 8a 0a 20 00    	jmpq   *0x200a8a(%rip)        # 601020 <_GLOBAL_OFFSET_TABLE_+0x20>
  400596:	68 01 00 00 00       	pushq  $0x1
  40059b:	e9 d0 ff ff ff       	jmpq   400570 <_init+0x28>

00000000004005a0 <malloc@plt>:
  4005a0:	ff 25 82 0a 20 00    	jmpq   *0x200a82(%rip)        # 601028 <_GLOBAL_OFFSET_TABLE_+0x28>
  4005a6:	68 02 00 00 00       	pushq  $0x2
  4005ab:	e9 c0 ff ff ff       	jmpq   400570 <_init+0x28>

00000000004005b0 <__libc_start_main@plt>:
  4005b0:	ff 25 7a 0a 20 00    	jmpq   *0x200a7a(%rip)        # 601030 <_GLOBAL_OFFSET_TABLE_+0x30>
  4005b6:	68 03 00 00 00       	pushq  $0x3
  4005bb:	e9 b0 ff ff ff       	jmpq   400570 <_init+0x28>

00000000004005c0 <free@plt>:
  4005c0:	ff 25 72 0a 20 00    	jmpq   *0x200a72(%rip)        # 601038 <_GLOBAL_OFFSET_TABLE_+0x38>
  4005c6:	68 04 00 00 00       	pushq  $0x4
  4005cb:	e9 a0 ff ff ff       	jmpq   400570 <_init+0x28>

00000000004005d0 <strtol@plt>:
  4005d0:	ff 25 6a 0a 20 00    	jmpq   *0x200a6a(%rip)        # 601040 <_GLOBAL_OFFSET_TABLE_+0x40>
  4005d6:	68 05 00 00 00       	pushq  $0x5
  4005db:	e9 90 ff ff ff       	jmpq   400570 <_init+0x28>

Disassembly of section .text:

00000000004005e0 <main>:
#include<cmath>
#include<cstdlib>
#include<stdio.h>
#include<stdint.h>
int main(int argc, char* argv[]){
  4005e0:	41 56                	push   %r14

    if(argc < 2){
  4005e2:	83 ff 01             	cmp    $0x1,%edi
#include<cmath>
#include<cstdlib>
#include<stdio.h>
#include<stdint.h>
int main(int argc, char* argv[]){
  4005e5:	41 55                	push   %r13
  4005e7:	41 54                	push   %r12
  4005e9:	55                   	push   %rbp
  4005ea:	53                   	push   %rbx
  4005eb:	48 89 f3             	mov    %rsi,%rbx

    if(argc < 2){
  4005ee:	0f 8e 9d 00 00 00    	jle    400691 <main+0xb1>
#ifdef __USE_EXTERN_INLINES
__BEGIN_NAMESPACE_STD
__extern_inline int
__NTH (atoi (const char *__nptr))
{
  return (int) strtol (__nptr, (char **) NULL, 10);
  4005f4:	48 8b 7b 08          	mov    0x8(%rbx),%rdi
  4005f8:	31 f6                	xor    %esi,%esi
  4005fa:	ba 0a 00 00 00       	mov    $0xa,%edx
  4005ff:	e8 cc ff ff ff       	callq  4005d0 <strtol@plt>
        printf("Usage : ./matrix width_of_square_matrix\n");
    }
    uint32_t width = atoi(argv[1]);

    double *a = (double*) malloc(width*width*sizeof(double));
  400604:	89 c5                	mov    %eax,%ebp
  400606:	49 89 c5             	mov    %rax,%r13
int main(int argc, char* argv[]){

    if(argc < 2){
        printf("Usage : ./matrix width_of_square_matrix\n");
    }
    uint32_t width = atoi(argv[1]);
  400609:	89 c3                	mov    %eax,%ebx

    double *a = (double*) malloc(width*width*sizeof(double));
  40060b:	0f af e8             	imul   %eax,%ebp
  40060e:	48 c1 e5 03          	shl    $0x3,%rbp
  400612:	48 89 ef             	mov    %rbp,%rdi
  400615:	e8 86 ff ff ff       	callq  4005a0 <malloc@plt>
    double *b = (double*) malloc(width*width*sizeof(double));
  40061a:	48 89 ef             	mov    %rbp,%rdi
    if(argc < 2){
        printf("Usage : ./matrix width_of_square_matrix\n");
    }
    uint32_t width = atoi(argv[1]);

    double *a = (double*) malloc(width*width*sizeof(double));
  40061d:	49 89 c6             	mov    %rax,%r14
    double *b = (double*) malloc(width*width*sizeof(double));
  400620:	e8 7b ff ff ff       	callq  4005a0 <malloc@plt>
    double *c = (double*) malloc(width*width*sizeof(double));
  400625:	48 89 ef             	mov    %rbp,%rdi
        printf("Usage : ./matrix width_of_square_matrix\n");
    }
    uint32_t width = atoi(argv[1]);

    double *a = (double*) malloc(width*width*sizeof(double));
    double *b = (double*) malloc(width*width*sizeof(double));
  400628:	49 89 c4             	mov    %rax,%r12
    double *c = (double*) malloc(width*width*sizeof(double));
  40062b:	e8 70 ff ff ff       	callq  4005a0 <malloc@plt>
	double *B = b;
    double *C = c;
    


    for(int i=0; i<width; i++){
  400630:	45 85 ed             	test   %r13d,%r13d
    }
    uint32_t width = atoi(argv[1]);

    double *a = (double*) malloc(width*width*sizeof(double));
    double *b = (double*) malloc(width*width*sizeof(double));
    double *c = (double*) malloc(width*width*sizeof(double));
  400633:	48 89 c5             	mov    %rax,%rbp
	double *B = b;
    double *C = c;
    


    for(int i=0; i<width; i++){
  400636:	74 27                	je     40065f <main+0x7f>
  400638:	31 f6                	xor    %esi,%esi
#include<cmath>
#include<cstdlib>
#include<stdio.h>
#include<stdint.h>
int main(int argc, char* argv[]){
  40063a:	31 c9                	xor    %ecx,%ecx
  40063c:	0f 1f 40 00          	nopl   0x0(%rax)
  400640:	31 d2                	xor    %edx,%edx
  400642:	66 0f 1f 44 00 00    	nopw   0x0(%rax,%rax,1)


    for(int i=0; i<width; i++){
        for(int j=0; j<width; j++){
            for(int k=0; k<width; k++){
                asm("nop");
  400648:	90                   	nop
        C[ i*width + j ] += A[ i*width + k ] * B[ k*width + j ] ;
                asm("nop");
  400649:	90                   	nop
    


    for(int i=0; i<width; i++){
        for(int j=0; j<width; j++){
            for(int k=0; k<width; k++){
  40064a:	83 c2 01             	add    $0x1,%edx
  40064d:	39 d3                	cmp    %edx,%ebx
  40064f:	77 f7                	ja     400648 <main+0x68>
    double *C = c;
    


    for(int i=0; i<width; i++){
        for(int j=0; j<width; j++){
  400651:	83 c1 01             	add    $0x1,%ecx
  400654:	39 cb                	cmp    %ecx,%ebx
  400656:	77 e8                	ja     400640 <main+0x60>
	double *B = b;
    double *C = c;
    


    for(int i=0; i<width; i++){
  400658:	83 c6 01             	add    $0x1,%esi
  40065b:	39 f3                	cmp    %esi,%ebx
  40065d:	77 db                	ja     40063a <main+0x5a>
//            printf("%lf ",C[ i*width + j ]);
//        }
//        printf("\n");
//    }

    if(A){ free(A); };
  40065f:	4d 85 f6             	test   %r14,%r14
  400662:	74 08                	je     40066c <main+0x8c>
  400664:	4c 89 f7             	mov    %r14,%rdi
  400667:	e8 54 ff ff ff       	callq  4005c0 <free@plt>
    if(B){ free(B); };
  40066c:	4d 85 e4             	test   %r12,%r12
  40066f:	74 08                	je     400679 <main+0x99>
  400671:	4c 89 e7             	mov    %r12,%rdi
  400674:	e8 47 ff ff ff       	callq  4005c0 <free@plt>
    if(C){ free(C); };
  400679:	48 85 ed             	test   %rbp,%rbp
  40067c:	74 08                	je     400686 <main+0xa6>
  40067e:	48 89 ef             	mov    %rbp,%rdi
  400681:	e8 3a ff ff ff       	callq  4005c0 <free@plt>

    return 0;
}
  400686:	5b                   	pop    %rbx
  400687:	5d                   	pop    %rbp
  400688:	41 5c                	pop    %r12
  40068a:	41 5d                	pop    %r13
  40068c:	31 c0                	xor    %eax,%eax
  40068e:	41 5e                	pop    %r14
  400690:	c3                   	retq   
#include<stdio.h>
#include<stdint.h>
int main(int argc, char* argv[]){

    if(argc < 2){
        printf("Usage : ./matrix width_of_square_matrix\n");
  400691:	48 8d 3d 88 01 00 00 	lea    0x188(%rip),%rdi        # 400820 <__dso_handle+0x8>
  400698:	e8 f3 fe ff ff       	callq  400590 <puts@plt>
  40069d:	e9 52 ff ff ff       	jmpq   4005f4 <main+0x14>

00000000004006a2 <_start>:
  4006a2:	31 ed                	xor    %ebp,%ebp
  4006a4:	49 89 d1             	mov    %rdx,%r9
  4006a7:	5e                   	pop    %rsi
  4006a8:	48 89 e2             	mov    %rsp,%rdx
  4006ab:	48 83 e4 f0          	and    $0xfffffffffffffff0,%rsp
  4006af:	50                   	push   %rax
  4006b0:	54                   	push   %rsp
  4006b1:	49 c7 c0 00 08 40 00 	mov    $0x400800,%r8
  4006b8:	48 c7 c1 90 07 40 00 	mov    $0x400790,%rcx
  4006bf:	48 c7 c7 e0 05 40 00 	mov    $0x4005e0,%rdi
  4006c6:	e8 e5 fe ff ff       	callq  4005b0 <__libc_start_main@plt>
  4006cb:	f4                   	hlt    
  4006cc:	0f 1f 40 00          	nopl   0x0(%rax)

00000000004006d0 <deregister_tm_clones>:
  4006d0:	b8 57 10 60 00       	mov    $0x601057,%eax
  4006d5:	55                   	push   %rbp
  4006d6:	48 2d 50 10 60 00    	sub    $0x601050,%rax
  4006dc:	48 83 f8 0e          	cmp    $0xe,%rax
  4006e0:	48 89 e5             	mov    %rsp,%rbp
  4006e3:	77 02                	ja     4006e7 <deregister_tm_clones+0x17>
  4006e5:	5d                   	pop    %rbp
  4006e6:	c3                   	retq   
  4006e7:	b8 00 00 00 00       	mov    $0x0,%eax
  4006ec:	48 85 c0             	test   %rax,%rax
  4006ef:	74 f4                	je     4006e5 <deregister_tm_clones+0x15>
  4006f1:	5d                   	pop    %rbp
  4006f2:	bf 50 10 60 00       	mov    $0x601050,%edi
  4006f7:	ff e0                	jmpq   *%rax
  4006f9:	0f 1f 80 00 00 00 00 	nopl   0x0(%rax)

0000000000400700 <register_tm_clones>:
  400700:	b8 50 10 60 00       	mov    $0x601050,%eax
  400705:	55                   	push   %rbp
  400706:	48 2d 50 10 60 00    	sub    $0x601050,%rax
  40070c:	48 c1 f8 03          	sar    $0x3,%rax
  400710:	48 89 e5             	mov    %rsp,%rbp
  400713:	48 89 c2             	mov    %rax,%rdx
  400716:	48 c1 ea 3f          	shr    $0x3f,%rdx
  40071a:	48 01 d0             	add    %rdx,%rax
  40071d:	48 d1 f8             	sar    %rax
  400720:	75 02                	jne    400724 <register_tm_clones+0x24>
  400722:	5d                   	pop    %rbp
  400723:	c3                   	retq   
  400724:	ba 00 00 00 00       	mov    $0x0,%edx
  400729:	48 85 d2             	test   %rdx,%rdx
  40072c:	74 f4                	je     400722 <register_tm_clones+0x22>
  40072e:	5d                   	pop    %rbp
  40072f:	48 89 c6             	mov    %rax,%rsi
  400732:	bf 50 10 60 00       	mov    $0x601050,%edi
  400737:	ff e2                	jmpq   *%rdx
  400739:	0f 1f 80 00 00 00 00 	nopl   0x0(%rax)

0000000000400740 <__do_global_dtors_aux>:
  400740:	80 3d 05 09 20 00 00 	cmpb   $0x0,0x200905(%rip)        # 60104c <_edata>
  400747:	75 11                	jne    40075a <__do_global_dtors_aux+0x1a>
  400749:	55                   	push   %rbp
  40074a:	48 89 e5             	mov    %rsp,%rbp
  40074d:	e8 7e ff ff ff       	callq  4006d0 <deregister_tm_clones>
  400752:	5d                   	pop    %rbp
  400753:	c6 05 f2 08 20 00 01 	movb   $0x1,0x2008f2(%rip)        # 60104c <_edata>
  40075a:	f3 c3                	repz retq 
  40075c:	0f 1f 40 00          	nopl   0x0(%rax)

0000000000400760 <frame_dummy>:
  400760:	48 83 3d 88 06 20 00 	cmpq   $0x0,0x200688(%rip)        # 600df0 <__JCR_END__>
  400767:	00 
  400768:	74 1e                	je     400788 <frame_dummy+0x28>
  40076a:	b8 00 00 00 00       	mov    $0x0,%eax
  40076f:	48 85 c0             	test   %rax,%rax
  400772:	74 14                	je     400788 <frame_dummy+0x28>
  400774:	55                   	push   %rbp
  400775:	bf f0 0d 60 00       	mov    $0x600df0,%edi
  40077a:	48 89 e5             	mov    %rsp,%rbp
  40077d:	ff d0                	callq  *%rax
  40077f:	5d                   	pop    %rbp
  400780:	e9 7b ff ff ff       	jmpq   400700 <register_tm_clones>
  400785:	0f 1f 00             	nopl   (%rax)
  400788:	e9 73 ff ff ff       	jmpq   400700 <register_tm_clones>
  40078d:	0f 1f 00             	nopl   (%rax)

0000000000400790 <__libc_csu_init>:
  400790:	41 57                	push   %r15
  400792:	41 89 ff             	mov    %edi,%r15d
  400795:	41 56                	push   %r14
  400797:	49 89 f6             	mov    %rsi,%r14
  40079a:	41 55                	push   %r13
  40079c:	49 89 d5             	mov    %rdx,%r13
  40079f:	41 54                	push   %r12
  4007a1:	4c 8d 25 38 06 20 00 	lea    0x200638(%rip),%r12        # 600de0 <__frame_dummy_init_array_entry>
  4007a8:	55                   	push   %rbp
  4007a9:	48 8d 2d 38 06 20 00 	lea    0x200638(%rip),%rbp        # 600de8 <__init_array_end>
  4007b0:	53                   	push   %rbx
  4007b1:	4c 29 e5             	sub    %r12,%rbp
  4007b4:	31 db                	xor    %ebx,%ebx
  4007b6:	48 c1 fd 03          	sar    $0x3,%rbp
  4007ba:	48 83 ec 08          	sub    $0x8,%rsp
  4007be:	e8 85 fd ff ff       	callq  400548 <_init>
  4007c3:	48 85 ed             	test   %rbp,%rbp
  4007c6:	74 1e                	je     4007e6 <__libc_csu_init+0x56>
  4007c8:	0f 1f 84 00 00 00 00 	nopl   0x0(%rax,%rax,1)
  4007cf:	00 
  4007d0:	4c 89 ea             	mov    %r13,%rdx
  4007d3:	4c 89 f6             	mov    %r14,%rsi
  4007d6:	44 89 ff             	mov    %r15d,%edi
  4007d9:	41 ff 14 dc          	callq  *(%r12,%rbx,8)
  4007dd:	48 83 c3 01          	add    $0x1,%rbx
  4007e1:	48 39 eb             	cmp    %rbp,%rbx
  4007e4:	75 ea                	jne    4007d0 <__libc_csu_init+0x40>
  4007e6:	48 83 c4 08          	add    $0x8,%rsp
  4007ea:	5b                   	pop    %rbx
  4007eb:	5d                   	pop    %rbp
  4007ec:	41 5c                	pop    %r12
  4007ee:	41 5d                	pop    %r13
  4007f0:	41 5e                	pop    %r14
  4007f2:	41 5f                	pop    %r15
  4007f4:	c3                   	retq   
  4007f5:	90                   	nop
  4007f6:	66 2e 0f 1f 84 00 00 	nopw   %cs:0x0(%rax,%rax,1)
  4007fd:	00 00 00 

0000000000400800 <__libc_csu_fini>:
  400800:	f3 c3                	repz retq 

Disassembly of section .fini:

0000000000400804 <_fini>:
  400804:	48 83 ec 08          	sub    $0x8,%rsp
  400808:	48 83 c4 08          	add    $0x8,%rsp
  40080c:	c3                   	retq   
