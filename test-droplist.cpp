/*
 *
 */

#include <string>
#include <vector>
#include "droplist.h"

#include <iostream>



int main()
{
  int width = 8;
  int fails = 0;

  droplist dl(width);

  // test each sentinal next node* points to NULL:
  for (int i = 0; i < width; i++)
  {
    if (dl.sentinal->next[i] != NULL)
      fails++;
  }


  dl.insert("test");
  dl.insert("test-1");
  dl.insert("test-2");
  dl.insert("test-3");
  dl.insert("test-4");
  dl.insert("test-5");
  dl.insert("test-6");
  dl.insert("test-7");
  dl.insert("test-8");
  dl.insert("test-9");

  // test node width distribution

  std::cout << fails << std::endl;

}
