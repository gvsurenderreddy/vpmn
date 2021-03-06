/***************************************************************************
 *            peer.c
 *
 *  VPMN  -  Virtual Private Mesh Network
 *  Copyright  2008  Pau Rodriguez-Estivill
 *  <prodrigestivill@gmail.com>
 ****************************************************************************/

/*
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <stdlib.h>
#include "debug.h"
#include "router.h"
#include "peer.h"

struct peer_l
{
  struct peer_s *current;
  struct peer_l *next;
};

int peer_addnew(struct peer_s *peer)
{
  //-TODO
  return -1;
}

int peer_add(struct peer_s *peer, struct udpsrvsession_s *session)
{
  int i;
  if (peer->shared_networks_len < 1)
    return -1;

  for (i = 0; i < peer->shared_networks_len; i++)
    router_addroute(&peer->shared_networks[i], peer);
  log_debug("Routes added.\n");
  //-TODO
  return 1;
}

struct peer_s *peer_create()
{
  struct peer_s *newpeer = malloc(sizeof(struct peer_s));
  newpeer->udpsrvsession = NULL;
  newpeer->addrs = NULL;
  newpeer->addrs_len = 0;
  newpeer->shared_networks = NULL;
  newpeer->shared_networks_len = 0;
  newpeer->stat = PEER_STAT_NULL;
  pthread_mutex_init(&newpeer->modify_mutex, NULL);
  return newpeer;
}

void peer_destroy(struct peer_s *oldpeer)
{
  if (oldpeer == NULL)
    return;
  //router_flush (oldpeer); Only by timeout function.
  udpsrvsession_destroy(oldpeer->udpsrvsession);
  if (oldpeer->shared_networks != NULL)
    free(oldpeer->shared_networks);
  if (oldpeer->addrs != NULL)
    free(oldpeer->addrs);
  free(oldpeer);
}
