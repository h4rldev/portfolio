#include <stddef.h>

#include "../../include/ssl.h"

/* get_private_key()
 *
 * gets the public key from default path (no custom path should be specified)
 *
 * returns it as char*.
 */

char *get_private_key() { return NULL; }

/* generate_public_key()
 *
 * takes a private_key but can be nullable if it's in a path.
 *
 * returns error status, will not return pub_key;
 */

char *generate_public_key(char *private_key);

/* generate_private_key()
 *
 * generates a private_key using certbot and places it in default path
 *
 * returns error status c:
 */

int generate_private_key();

/* generate_key_pair()
 *
 * generates a public and private key
 *
 * returns the pubkey and saves the private key in default folder;
 */

char *generate_key_pair();
