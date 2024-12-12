#include <stddef.h>

#include "../../include/config.h"
#include "../../include/file.h"
#include "../../include/log.h"
#include "../../include/ssl.h"

/* get_cert()
 *
 * gets the certificate from config specified path
 *
 * returns it as a char *.
 */

char *get_cert() {
  Config config;
  read_config(&config);

  char *cert_path = config.ssl.cert_path;
  if (!cert_path) {
    flscio_log(Error, "No certificate path specified");
    return NULL;
  }

  char *content = read_file(cert_path);
  if (!content) {
    flscio_log(Error, "No certificate found.");
    return NULL;
  }

  return content;
}

/* get_key()
 *
 * gets the key from config specified path
 *
 * returns it as a char *.
 */

char *get_key() {
  Config config;
  read_config(&config);

  char *key_path = config.ssl.key_path;
  if (!key_path) {
    flscio_log(Error, "No key path specified");
    return NULL;
  }

  char *content = read_file(key_path);
  if (!content) {
    flscio_log(Error, "No key found.");
    return NULL;
  }

  return content;
}
