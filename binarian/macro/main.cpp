#include <stdio.h>
#include <stdlib.h>
#include <sys/ptrace.h> /* ptrace() */

#include <sys/wait.h>   /* wait() */
#include <sys/types.h>
#include <sys/reg.h>   /* struct user_regs_struct */

/* _exit(1) implementation in shellcode */

static char shellcode[] =
    "\x31\xc0" 		/* xor  %eax,%eax */
    "\x40" 			/* inc  %eax */
    "\xcd\x80" 		/* int  $0x80 */ ;


#include <stdarg.h>
#define OUT_MSG(x, ...) printf("* " x "\n",## __VA_ARGS__)
#define ERR_MSG(x) printf("\t[Error] " x "\n")

int main(int argc, char *argv[])
{
    int pid, offset;
    OUT_MSG("TEst"); 
    return 0;
}
