#include "../include/configbutton.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "pndman.h"

int activate(void *internal) {
  pndman_package *pnd;
  char command[256];
  pndman_repository *repository = pndman_repository_init();
  
  for(pnd = repository->pnd; pnd; pnd = pnd->next)
  {
    if(strcmp(pnd->id, "pndmanager-bzar"))
      break;
  }
  
  if(!pnd)
    return 1;
  
  sprintf(command, "pnd_run %s/%s", pnd->mount, pnd->path);
  system(command);
  
  return 0;
}

int getinfo(PLUGIN_INFO *info) {
  pndman_device *device, *d;
  pndman_repository *repository;
  
  if (info->submenu == NULL) {
    pndman_set_verbose(PNDMAN_LEVEL_CRAP);
    info->label = malloc(128);
  }
  
  device = pndman_device_detect(NULL);
  repository = pndman_repository_init();
  pndman_repository_add("http://repo.openpandora.org/client/masterlist", repository);
  
  for(d = device; d; d = d->next)
  {
    pndman_device_read_repository(repository, d);
  }
  
  for (d = device; d; d = d->next) pndman_package_crawl(0, d, repository);
  pndman_repository_check_local(repository);
  
  int numUpdates = pndman_repository_check_updates(repository);
  sprintf((char *) info->label, "%i upgradable packages", numUpdates);

  pndman_repository_free_all(repository);
  pndman_device_free_all(device);
  

  return 0;
}
