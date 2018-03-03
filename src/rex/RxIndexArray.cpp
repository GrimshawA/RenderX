#include <RenderX/RxIndexArray.h>

const void* RxIndexArray::data() const
{
    return reinterpret_cast<const void*>(&indices[0]);
}

void RxIndexArray::redirectFromTo(int32_t searchElement, int32_t becomes)
{
    for (std::size_t i = 0; i < indices.size(); ++i)
    {
        if (indices[i] == searchElement)
        {
            indices[i] = becomes;
        }
    }
}

void RxIndexArray::swapIndices(int32_t index1, int32_t index2)
{
    for (std::size_t i = 0; i < indices.size(); ++i)
    {
        if (indices[i] == index1)
        {
            indices[i] = index2;
        }
        else if (indices[i] == index2)
        {
            indices[i] = index1;
        }
    }
}

std::size_t RxIndexArray::size() const
{
    return indices.size();
}
