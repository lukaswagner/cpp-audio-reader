#include "base/input.hpp"
#include "base/output.hpp"

template <class I, class O>
class InputOutput : Input<I>, Output<O>
{
};
