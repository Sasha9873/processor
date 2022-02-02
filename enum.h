#define DEFCMD(name, num,...)\
	CMD_##name = num,

enum comands{
	#include "commands.h"
};

#undef DEFCMD