#include "Semaphore.h"
#include <iostream>
#include <thread>
#include <vector>

/*! \brief Mutual Exclusion
 *  \author James Nolan
 *  \date 12nd November 2020
*/

static const int num_threads = 100;
int sharedVariable=0;

/*! displays a message that is split in to 2 sections to show how a rendezvous works*/
void updateTask(std::shared_ptr<Semaphore> firstSem, int numUpdates)
{

  for (int i = 0; i < numUpdates; i++)
  {
    //UPDATE SHARED VARIABLE HERE!
    firstSem->Wait();
    sharedVariable++;
    firstSem->Signal();
  }
}

int main(void)
{
  std::vector<std::thread> vt(num_threads);
  std::shared_ptr<Semaphore> aSemaphore(new Semaphore(1));
  /**< Launch the threads  */
  int i = 0;
  for (std::thread &t : vt)
  {
    t = std::thread(updateTask, aSemaphore, 1000);
  }
  std::cout << "Launched from the main\n";
  /**< Join the threads with the main thread */
  for (auto &v : vt)
  {
    v.join();
  }
  std::cout << sharedVariable << std::endl;
  return 0;
}
