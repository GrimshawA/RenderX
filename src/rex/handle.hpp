#ifndef REX_HANDLE_HPP_
#define REX_HANDLE_HPP_

namespace rex
{
	/*
		\brief Opaque reference used by library users to reference render side resources
	*/
	class handle
	{
    public:
        template<typename T>
        T* cast() const
        {
            return static_cast<T*>(_d1);
        }

	private:
		void* _d1;
		void* _d2;
	};
}

#endif // REX_HANDLE_HPP_
