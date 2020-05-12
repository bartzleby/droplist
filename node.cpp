/* This node class is used to build linked lists for the
 * string_set class.
 *
 * well-formed: a node is well formed only when it 
 *     is non-null and it has a non-null data field
 *     consisting of some string and anon-null next
 *     field consisting of a vector of possibly null
 *     node pointers.
 *
 * Danny Bartz
 * February , 2020
 */

#include "node.h"
#include <vector>
#include <string>


/*******************************************************
 * node member function definitions
 ***************************************************** */

/*
 * Copy Constructor:
 */
cs3505::node::node(const node & other)
{
  *this = other;
}

/*
 * Constructor: create a node object with specified data
 *     and next of spcified size.
 */
cs3505::node::node(const std::string & s, int random_width)
{
  data = s;
  next.resize(random_width);
}

/*
 * Destructor: clean up
 */
cs3505::node::~node()
{
  next.clear();
  data = "";
}

/*
 * Sets this node equal to another.
 */
cs3505::node & cs3505::node::operator= (const node & rhs)
{
  if (this == &rhs)
    return *this;

  this->data = rhs.data;
  this->next.resize(rhs.next.size());
  
  for (int i = 0; i < next.size(); i++)
  {
    if (rhs.next[i] != NULL)
      next[i] = new node(*(rhs.next[i]));
    else
      next[i] = NULL;
  }

}
