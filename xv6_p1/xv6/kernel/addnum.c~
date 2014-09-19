#include "types.h"
#include "x86.h"
#include "defs.h"
#include "param.h"
#include "mmu.h"
#include "proc.h"
#include "sysfunc.h"

int
sys_addnum(void)
{
	int inc;
	if(argint(0, &inc) < 0){
		return -1;
	}
	proc->p_counter = proc->p_counter + inc;
	return proc->p_counter;
}
