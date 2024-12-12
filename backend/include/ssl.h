#ifndef SSL_H_IMPLEMENTATION
#define SSL_H_IMPLEMENTATION

/* get_cert()
 *
 * gets the certificate from config specified path
 *
 * returns it as a char *.
 */

char *get_cert();

/* get_key()
 *
 * gets the key from config specified path
 *
 * returns it as a char *
 */

char *get_key();
#endif // !SSL_H_IMPLEMENTATION
