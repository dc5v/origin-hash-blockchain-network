#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <pthread.h>
#include <stdint.h>

#include "network.h"
#include "../util/util.h"

void *network_handle_client(void *arg)
{
  int client_fd = (intptr_t)arg;
  char buffer[1024] = {0};
  int bytes_read;

  while ((bytes_read = read(client_fd, buffer, sizeof(buffer))) > 0)
  {
    log("Received: %s\n", buffer);

    write(client_fd, buffer, bytes_read);
    memset(buffer, 0, sizeof(buffer));
  }

  close(client_fd);
  return NULL;
}

void create_server(int port)
{
  int server_fd, client_fd;
  struct sockaddr_in server_addr, client_addr;
  socklen_t client_len = sizeof(client_addr);

  if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0)
  {
    perror("socket failed");
    exit(EXIT_FAILURE);
  }

  server_addr.sin_family = AF_INET;
  server_addr.sin_addr.s_addr = INADDR_ANY;
  server_addr.sin_port = htons(port);

  if (bind(server_fd, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0)
  {
    perror("bind failed");
    close(server_fd);
    exit(EXIT_FAILURE);
  }

  if (listen(server_fd, 3) < 0)
  {
    perror("listen failed");
    close(server_fd);
    exit(EXIT_FAILURE);
  }

  log("Server started on port %d\n", port);

  while (1)
  {
    if ((client_fd = accept(server_fd, (struct sockaddr *)&client_addr, &client_len)) < 0)
    {
      perror("accept failed");
      continue;
    }

    pthread_t thread_id;
    if (pthread_create(&thread_id, NULL, network_handle_client, (void *)(intptr_t)client_fd) != 0)
    {
      perror("pthread_create failed");
    }
  }

  close(server_fd);
}
