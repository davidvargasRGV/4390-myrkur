#ifndef _PROTOCOL_H
#define _PROTOCOL_H

/* NMDC commands */
#define NMDC_CHAT		(1ULL << 0)	/* <nick> message| */
#define NMDC_TO			(1ULL << 1)
#define NMDC_CTM		(1ULL << 2)
#define NMDC_RCTM		(1ULL << 3)
#define NMDC_PING		(1ULL << 4)
#define NMDC_GETPASS		(1ULL << 5)
#define NMDC_MYPASS		(1ULL << 6)
#define NMDC_LOGEDIN		(1ULL << 7)
#define NMDC_GET		(1ULL << 8)
#define NMDC_SEND		(1ULL << 9)
#define NMDC_FILELEN		(1ULL << 10)
#define NMDC_GETLISTLEN		(1ULL << 11)
#define NMDC_LISTLEN		(1ULL << 12)
#define NMDC_DIRECTION		(1ULL << 13)
#define NMDC_CANCEL		(1ULL << 14)
#define NMDC_CANCELED		(1ULL << 15)
#define NMDC_BADPASS		(1ULL << 16)
#define NMDC_HUBFULL		(1ULL << 17)
#define NMDC_DENIED		(1ULL << 18)
#define NMDC_MAXEDOUT		(1ULL << 19)
#define NMDC_FAILED		(1ULL << 20)
#define NMDC_ERROR		(1ULL << 21)
#define NMDC_SEARCH		(1ULL << 22)
#define NMDC_SR			(1ULL << 23)
#define NMDC_MYINFO		(1ULL << 24)
#define NMDC_GETINFO		(1ULL << 25)
#define NMDC_HELLO		(1ULL << 26)	/* $Hello user| */
#define NMDC_VERSION		(1ULL << 27)
#define NMDC_HUBNAME		(1ULL << 28)	/* $HubName name| */
#define NMDC_GETNICKLIST	(1ULL << 29)
#define NMDC_NICKLIST		(1ULL << 30)	/* $NickList nick$$nick2$$nick3[...]| */
#define NMDC_OPLIST		(1ULL << 31)	/* $OpList nick$$nick2$$nick3[...]| */
#define NMDC_KICK		(1ULL << 32)
#define NMDC_CLOSE		(1ULL << 33)
#define NMDC_OPFORCEMV		(1ULL << 34)
#define NMDC_FORCEMV		(1ULL << 35)
#define NMDC_QUIT		(1ULL << 36)
#define NMDC_LOCK		(1ULL << 37)	/* $Lock lock Pk=pk| */
#define NMDC_KEY		(1ULL << 38)
#define NMDC_MCTM		(1ULL << 39)
#define NMDC_MSEARCH		(1ULL << 40)

extern int nmdc_cmd_hubname(struct client_t *client, const char *param);
extern int nmdc_cmd_lock(struct client_t *client, const char *param);
extern int nmdc_cmd_hello(struct client_t *client, const char *param);
extern int nmdc_cmd_nicklist(struct client_t *client, const char *param);
extern int nmdc_cmd_oplist(struct client_t *client, const char *param);
extern int nmdc_cmd_myinfo(struct client_t *client, const char *param);

extern int nmdc_compare(const void *a, const void *b);

#endif
