#include "pndman.h"
#include <stdio.h>

int main(int argc, char** argv)
{
  pndman_device *device, *d;
  pndman_repository *repository;
  pndman_sync_handle handle;
 
  device = pndman_device_detect(0);
  pndman_device_add("/tmp", device);

  repository = pndman_repository_init();
  pndman_repository_add("http://repo.openpandora.org/client/masterlist", repository);
  
  for(d = device; d; d = d->next)
  {
    pndman_device_read_repository(repository, d);
  }
  
  for (d = device; d; d = d->next) pndman_package_crawl(0, d, repository);

  pndman_repository_check_local(repository);
  
  pndman_sync_handle_init(&handle);
  handle.repository = repository->next;
  pndman_sync_handle_perform(&handle);
  while (pndman_curl_process() > 0);
  
  for(d = device; d; d = d->next)
  {
    pndman_repository_commit_all(repository, d);
  }
  
  pndman_repository_free_all(repository);
  pndman_device_free_all(device);
  
  return 0;
}