/* A 'string set' is defined as a set of strings stored
 * in sorted order in a drop list.  See the class video
 * for details.
 *
 * For lists that do not exceed 2^(max_next_width elements+1)
 * elements, the add, remove, and contains functions are 
 * O(lg size) on average.  The operator= and get_elements 
 * functions are O(size).   
 * 
 * Danny Bartz
 * February , 2020
 */

#ifndef STRING_SET_H
#define STRING_SET_H

#include "node.h"
#include <vector>
#include <string>

namespace cs3505
{
  class string_set
    {

      int max_next_width;  // The maximum width of of a drop list in each node

      node *head;          // The head of the list will sit in a sentinal node
                           // (without any data in it).  This sentinal node
                           // will have a maximum width next list.  The head
                           // sentinal node should be in heap.

      int size;            // The number of elements in the set


    public:

      string_set(int max_next_width = 10);   // Constructor.  Notice the default parameter value.
      string_set(const string_set & other);  // Copy constructor
      ~string_set();                         // Destructor

      void add      (const std::string & target);        // Not const - modifies the object
      void remove   (const std::string & target);        // Not const - modifies the object
      bool contains (const std::string & target) const;  // Const - does not change the object
      int  get_size () const;                            // Const - does not change object

      string_set & operator= (const string_set & rhs);   // Not const - modifies this object

      std::vector<std::string> get_elements();           // Returns all the elements in this string_set,
                                                         // in ascending order.  

    private:

      void clean();
      int get_node_width() const;
      bool find(const std::string & s, 
                node* prev[] = NULL,                // if we care only about contains, we don't use prev
                bool populate_prev = false) const;  // 

  };

}

#endif
