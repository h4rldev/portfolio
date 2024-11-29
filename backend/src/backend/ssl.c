#include <stddef.h>
#include <stdio.h>
#include <string.h>

#include "../../include/config.h"
#include "../../include/ssl.h"

/* get_private_key()
 *
 * gets the private key from default path (no custom path should be specified)
 *
 * returns it as a char *.
 */

char *get_private_key() { return NULL; }

/* get_public_key()
 *
 * gets the public key from default path (no custom path shall be specified)
 *
 * returns it as a char *
 */

char *get_public_key() { return NULL; }

/* generate_key_pair()
 *
 * generates a public and private key
 *
 * returns the pubkey and saves the private key in default folder;
 */

int generate_key_pair() {
  Config config;
  read_config(&config);

  char *program = "certbot";
  char command_buf[1024] = {0};
  char buf[1024] = {0};

  snprintf(command_buf, 1024,
           "sudo %s certonly --standalone --non-interactive --agree-tos "
           "--config-dir "
           ". --work-dir . "
           "--logs-dir . -m %s -d %s",
           program, config.ssl.email, config.ssl.domain);

  FILE *fd = popen(command_buf, "r");
  while (fgets(buf, 1024, fd) != NULL)
    puts(buf);

  pclose(fd);

  return 0;
}
