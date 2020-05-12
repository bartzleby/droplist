/* A 'string set' is defined as a set of strings stored
 * in sorted order in a drop list.  See the class video
 * for details.
 *
 * For lists that do not exceed 2^(max_next_width elements+1)
 * elements, the add, remove, and contains functions are 
 * O(lg size) on average.  The operator= and get_elements 
 * functions are O(size).   
 * 
 * well-formed: a stringset is well formed when it has a head
 *   node which is not null and a non-null size of at least zero.  
 *   Traversing along each node's next[0] will encounter every item 
 *   in the set, with traversal along increasing next indices will
 *   skip increasingly more set elements.
 * 
 * Danny Bartz
 * February , 2020
 */

#include "string_set.h"
#include <stdlib.h> // for rand()
#include <vector>
#include <string>


namespace cs3505
{
  /*******************************************************
   * string_set member function definitions
   ***************************************************** */
  
  /** Constructor:  The parameter indicates the maximum
    *   width of the next pointers in the drop list nodes.
    */
  string_set::string_set(int max_next_width)
    : max_next_width(max_next_width), head(new node("", max_next_width)), size(0)
  {
  }
  
  /** Copy constructor:  Initialize this set
    *   to contain exactly the same elements as
    *   another set.
    */
  string_set::string_set (const string_set & other)
  {
    *this = other;
  }


  /** Destructor:  release any memory allocated
    *   for this object.
    */
  string_set::~string_set()
  {
    clean();
  }


  /** add:  
   *    Add the input string s to the string_set.  
   *    If the element already exists in the set,
   *    nothing is done.
   *
   */
  void string_set::add(const std::string & s)
  {
    node* prev[max_next_width]; // 
    // if string is already in set, do nothing
    if (find(s, prev, true))
      return;

    int rw = get_node_width();
    node* newnode = new node(s, rw);

    // we insert newnode into list
    for (int i = 0; i < rw; i++)
    {
      newnode->next[i] = prev[i]->next[i];
      prev[i]->next[i] = newnode;
    }
 
    size++;
    return;
  }

  /** remove:
   *    Remove the input string s from the string_set
   *    if it exists in the set.
   *
   */
  void string_set::remove (const std::string & target)
  {
    node* prev[max_next_width];

    if (!find(target, prev, true))
      return;

    node* todelete = prev[0]->next[0];

    for (int i = 0; i < todelete->next.size(); i++)
    {
      prev[i]->next[i] = todelete->next[i];
      todelete->next[i] = NULL;
    }

    delete todelete;
    size--;
    return;
  }

  /** contains:
   *    Return true is the target string is in 
   *    the string set, false otherwise.
   *
   */
  bool string_set::contains (const std::string & target) const
  {
    return find(target);
  }

  /** get_size:
   *    Return the number of elements
   *    in the string set.
   *
   */
  int string_set::get_size() const
  {
    return size;
  }

  /* sets this string_set to be the same as another. */
  string_set & string_set::operator= (const string_set & rhs)
  {
    if (this == &rhs)
      return *this;

    clean();

    this->size = 0;
    this->max_next_width = rhs.max_next_width;
    this->head = new node("", max_next_width);
    
    node* nextnode = rhs.head->next[0];

    // copy rhs into this one
    while (nextnode != NULL)
    {
      this->add(nextnode->data);
      nextnode = nextnode->next[0];
    }

  }

  /**
   * Returns a std::vector<std::string> 
   * of the elements contained in the string_set.
   */
  std::vector<std::string> string_set::get_elements()
  {
    int level = 0;
    std::vector<std::string> elements;
 

    node* current = this->head;

    while (current->next[level] != NULL)
    {
      current = current->next[level];
      elements.push_back(current->data);
    }

    return elements;
  }



  /*
   * returns a random width for a node's next vector according to:
   *   every next vector has at least one element.  Subsequent
   *   elements are added with probability one half each.
   */
  int string_set::get_node_width() const
  {
    int r = rand() % (1<<max_next_width);

    int node_length = 1;
    while ((r & (1<<0)) && node_length < this->head->next.size())
    {
      node_length++;
      r = r >> 1;
    }

    return node_length;
  }


  /*
   * Determines whether the string s is in the set.
   * Writes the series of "drop pointers" followed
   * to the would be or actual position of s within
   * the droplist to prev[] if desired.
   */
  bool string_set::find(const std::string & s, node* prev[], bool populate_prev) const
  {
    int level = max_next_width - 1;
    node* testnode = this->head; // we start with head
    node* nextnode;

    while (level >= 0)
    {
      nextnode = testnode->next[level];
      // descend into list at current level:
      while (nextnode != NULL && nextnode->data < s)
      {
        testnode = nextnode;
        nextnode = testnode->next[level];
      }

      if (populate_prev)
        prev[level] = testnode;

      level--;

    }

    if (nextnode == NULL || nextnode->data != s)
      return false;

    return true;
  }



  /*
   * tidy and delete string_set
   */
  void string_set::clean()
  {
    node* todelete = head;
    node* nextnode;
    while (todelete != NULL)
    {
      nextnode = todelete->next[0];
      delete(todelete);
      todelete = nextnode;
    }

    head = NULL;
    max_next_width = 0;
    size = 0;
  }

}
