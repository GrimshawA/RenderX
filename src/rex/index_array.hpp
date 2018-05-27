#ifndef RXINDEXARRAY_H__
#define RXINDEXARRAY_H__

#include "config.hpp"
#include <vector>
#include <stdint.h>

/**
    \class RxIndexArray
    \brief A in-memory index array
*/
class REX_API RxIndexArray
{
public:

    std::vector<uint16_t> indices;

public:

    /// Get the raw pointer to the indices
    const void* data() const;

    /// Get the number of indices
    std::size_t size() const;

    void redirectFromTo(int32_t searchElement, int32_t becomes);
    /// Whatever pointed at index1, now points at index 2, and vice versa
    void swapIndices(int32_t index1, int32_t index2);
};
#endif // RXINDEXARRAY_H__
