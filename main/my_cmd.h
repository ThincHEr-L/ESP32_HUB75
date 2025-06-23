#ifndef _APP_CMD_
#define _APP_CMD_

typedef void (*cmd_cb)(char*);
typedef struct
{
	char * cmd;
	cmd_cb cb;
}cmd_t;

char *skip(char *buf);
void cmd_proc(char* buffer);
void cmd_err(void);
void uart1_printf(const char *fmt, ...);

#endif
