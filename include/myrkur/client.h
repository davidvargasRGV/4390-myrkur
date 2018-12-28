#ifndef _CLIENT_H
#define _CLIENT_H

#define MAX_CMD_LEN	32

struct user_t {
	char *username;
	char *description;
	char *connection;
	char flags;
	char *email;
	int sharesize;
};

struct host_t {
	char *ip;
	char *port;
};

struct client_t {
	int socket;
	int port;

	struct user_t *user;		/* TODO: use configuration defined user settings */
	struct host_t *victim;
};

extern void client_connect(struct client_t *client);
extern void client_send(struct client_t *client, char *msg);

#endif
