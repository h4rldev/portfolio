#ifndef SSL_H_IMPLEMENTATION
#define SSL_H_IMPLEMENTATION

/* get_private_key()
 *
 * gets the private key from default path (no custom path should be specified)
 *
 * returns it as a char *.
 */

char *get_private_key();

/* get_public_key()
 *
 * gets the public key from default path (no custom path shall be specified)
 *
 * returns it as a char *
 */

char *get_public_key();

/* generate_key_pair()
 *
 * generates a public and private key
 *
 * returns status;
 */

int generate_key_pair();
#endif // !SSL_H_IMPLEMENTATION
