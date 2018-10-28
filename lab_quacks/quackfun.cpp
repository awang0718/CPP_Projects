/**
 * @file quackfun.cpp
 * This is where you will implement the required functions for the
 *  stacks and queues portion of the lab.
 */

namespace QuackFun {

/**
 * Sums items in a stack.
 * @param s A stack holding values to sum.
 * @return The sum of all the elements in the stack, leaving the original
 *  stack in the same state (unchanged).
 *
 * @note You may modify the stack as long as you restore it to its original
 *  values.
 * @note You may use only two local variables of type T in your function.
 *  Note that this function is templatized on the stack's type, so stacks of
 *  objects overloading the + operator can be summed.
 * @note We are using the Standard Template Library (STL) stack in this
 *  problem. Its pop function works a bit differently from the stack we
 *  built. Try searching for "stl stack" to learn how to use it.
 * @hint Think recursively!
 */
template <typename T>
T sum(stack<T>& s)
{
    if (s.size() == 0)
    	return 0; // stub return value (0 for primitive types). Change this!
                // Note: T() is the default value for objects, and 0 for
                // primitive types

    T popped = s.top();
    s.pop();
    T sum_ = popped + sum(s);   // Recursively add top element to sum of all other elements
    s.push(popped);
    return sum_;
}

/**
 * Checks whether the given string (stored in a queue) has balanced brackets.
 * A string will consist of
 * square bracket characters, [, ], and other characters. This function will return
 * true if and only if the square bracket characters in the given
 * string are balanced. For this to be true,
 * all brackets must be matched up correctly, with no extra, hanging, or unmatched
 * brackets. For example, the string "[hello][]" is balanced, "[[][[]a]]" is balanced,
 * "[]]" is unbalanced, "][" is unbalanced, and "))))[cs225]" is balanced.
 *
 * For this function, you may only create a single local variable of type stack<char>!
 * No other stack or queue local objects may be declared. Note that you may still
 * declare and use other local variables of primitive types.
 *
 * @param input The queue representation of a string to check for balanced brackets in
 * @return Whether the input string had balanced brackets
 */
bool isBalanced(queue<char> input)
{
  stack<char> myStack;

  while(input.size() > 0) {
  	if (input.front() == '[') {	// Pop '[' from queue to stack
  	    myStack.push(input.front());
  	}
  	if (input.front() == ']') {	// Pop ']' from stack
  	    if (myStack.size() == 0)
  		return false;
  	    else
  		myStack.pop();
  	}
  	input.pop();
  }
  return myStack.size() == 0;
}

/**
 * Reverses even sized blocks of items in the queue. Blocks start at size
 * one and increase for each subsequent block.
 * @param q A queue of items to be scrambled
 *
 * @note Any "leftover" numbers should be handled as if their block was 
 *  complete.
 * @note We are using the Standard Template Library (STL) queue in this
 *  problem. Its pop function works a bit differently from the stack we
 *  built. Try searching for "stl stack" to learn how to use it.
 * @hint You'll want to make a local stack variable.
 */
template <typename T>
void scramble(queue<T>& q)
{
  stack<T> s;
  queue<T> q2;

  int nums = 0;
  while (q.size() > 0) {
    nums++;
    if (nums%2 == 1) {  // If nums is odd, pop top elements from queue to back of queue2
      for(int j = 0; j < nums; j++){
        if(q.size() == 0)
           break;
        q2.push(q.front());
        q.pop();
      }
    }
    else {  // If nums is even, pop top elements from queue to stack, then pop to back of queue2
      for(int j = 0; j < nums; j++) {
        if(q.size() == 0)
           break;
        s.push(q.front());
        q.pop();
      }
      while(s.size() > 0) {
        q2.push(s.top());
        s.pop();
      }
    }
  }
  // Push elements from queue2 to queue
  while(q2.size() > 0) {
    q.push(q2.front());
    q2.pop();
  }
}

/**
 * @return true if the parameter stack and queue contain only elements of
 *  exactly the same values in exactly the same order; false, otherwise.
 *
 * @note You may assume the stack and queue contain the same number of items!
 * @note The back of the queue corresponds to the top of the stack!
 * @note There are restrictions for writing this function.
 * - Your function may not use any loops
 * - In your function you may only declare ONE local boolean variable to use in
 *   your return statement, and you may only declare TWO local variables of
 *   parametrized type T to use however you wish.
 * - No other local variables can be used.
 * - After execution of verifySame, the stack and queue must be unchanged. Be
 *   sure to comment your code VERY well.
 */
template <typename T>
bool verifySame(stack<T>& s, queue<T>& q)
{
    if(s.size() == 0)
      return true;

    bool retval = true; // optional
    T temp; // rename me

    temp = s.top();
    s.pop();      // Pop top of stack

    retval = verifySame(s,q);

    s.push(temp);     // Push top of stack back to top
    retval = q.front() == s.top() && retval;    // Make sure the top elements in the stack and queue are always the same

    q.push(q.front());
    q.pop();      // Move front of queue to back of queue

    return retval;

}

}
