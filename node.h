/* This node class is used to build drop lists for the
 * string_set class.
 *
 * Danny Bartz
 * February , 2020
 */

#ifndef NODE_H
#define NODE_H

#include <vector>
#include <string>

namespace cs3505
{

  class node
  {
    friend class string_set;   // This allows functions in string_set to access
			                   //   private data (and constructor) within this class.

    node(const node & other);
    node(const std::string & s, int rw);
   ~node();

    node & operator= (const node & rhs);

    std::string data;
    std::vector<node*> next;

  };
}

#endif
