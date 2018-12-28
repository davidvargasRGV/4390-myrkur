/*
 *	./src/client.c
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <pcre.h>

#include <myrkur/client.h>
#include <myrkur/protocol.h>

#define NICK "svefn"

void client_recv(struct client_t *client, unsigned long long int flags)
{
	char *buf = NULL;
	char *pbuf = NULL;
	char *fullcmd = NULL;

	char *lock = NULL;
	char *pk = NULL;

	int size = 1024;
	unsigned long long int flag = 0;

	pcre *re;
	const char *error;
	int erroffset;
	int rc;
	int ovector[30];
	char command[1024];
	char arg[1024];

	buf = (char *) malloc(size + sizeof(char));
	fullcmd = (char *) malloc(size + sizeof(char));
	lock = (char *) malloc(size + sizeof(char));
	pk = (char *) malloc (size + sizeof(char));

	memset(buf, 0, size + sizeof(char));
	memset(fullcmd, 0, size + sizeof(char));
	memset(lock, 0, size + sizeof(char));
	memset(pk, 0, size + sizeof(char));

	while(1) {
		memset(buf, 0, size + sizeof(char));

		read(client->socket, buf, 1024);

		printf("client_recv: '%s'\n\n", buf);

		if (strchr(buf, '|') == NULL) {
			/* TODO: Allow increase of abuffer? */
		} else {
			pbuf = buf;

			/* parse buf */
			while(1) {
				memccpy(fullcmd, pbuf, '|', strlen(pbuf));

				printf("fullcmd = '%s'\n", fullcmd);

				re = pcre_compile("(\\S+)(\\s|)(.*)", 0, &error, &erroffset, NULL);
				rc = pcre_exec(re, NULL, fullcmd, strlen(fullcmd), 0, 0, ovector, 30);

				pcre_copy_substring(fullcmd, ovector, rc, 1, command, 1023);
				pcre_copy_substring(fullcmd, ovector, rc, 3, arg, 1023);

				/* $Lock */
				if (nmdc_compare(command, "$Lock") == 0 && (flags & NMDC_LOCK)) {
					if (nmdc_cmd_lock(client, arg) == 0) {
						memccpy(lock, arg, ' ', strlen(pbuf));

						printf("Received Lock = '%s'\n", lock);

						flag = flag | NMDC_LOCK;
					} else {
						/* error */
					}
				/* $HubName */
				} else if (nmdc_compare(command, "$HubName") == 0) {
					if (nmdc_cmd_hubname(client, arg) == 0) {
						printf("Executed HubName...\n");
					} else {
						/* error */
					}
				/* $Hello */
				} else if (nmdc_compare(command, "$Hello") == 0) {
					if (nmdc_cmd_hello(client, arg) == 0) {
						flag = flag | NMDC_HELLO;
					} else {
						/* error */
					}
				/* $NickList */
				} else if (nmdc_compare(command, "$NickList") == 0) {
					if (nmdc_cmd_nicklist(client, arg) == 0) {
						flag = flag | NMDC_NICKLIST;
					} else {
						/* error */
					}
				/* $OpList */
				} else if (nmdc_compare(command, "$OpList") == 0) {
					if (nmdc_cmd_oplist(client, arg) == 0) {
						flag = flag | NMDC_OPLIST;
					} else {
						/* error */
					}
				/* Other Messages */
				} else {
					/* TODO: check for chat message? */
				}

				printf("command = '%s'\n", command);
				printf("arg = '%s'\n\n", arg);

				memset(fullcmd, 0, size);
				memset(command, 0, 1024);
				memset(arg, 0, 1024);

				if (strchr(pbuf, '|') == NULL) {
					/* TODO: Allow increase of buffer? */
					break;
				}

				pbuf = strchr(pbuf, '|') + sizeof(char);
			}
		}

		/* looking for specific NMDC commands */
		if (flag & flags) {
			break;
		}
	}
}


void client_send(struct client_t *client, char *msg)
{
	size_t size = strlen(msg) + sizeof(char);

	send(client->socket, msg, size, 0);

	printf("client_send(): send '%s'\n", msg);
}

void client_connect(struct client_t *client)
{
	printf("Connecting...\n");

	client_recv(client, (NMDC_LOCK));

	/* TODO: use configuration defined nickname */
	client_send(client, "$ValidateNick " NICK "|");

	client_recv(client, (NMDC_HELLO));

	client_send(client, "$Version 1.0091|");

	client_send(client, "$GetNickList|");

	/* TODO: use configuration defined nickname, description, flag, e-mail, share size */
	client_send(client, "$MyINFO $ALL " NICK " description$ $Cable\001$example@example.com$1234$|");

	client_recv(client, (NMDC_NICKLIST | NMDC_OPLIST));

	printf("Connected...\n");

	client_recv(client, 0);
}
