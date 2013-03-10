#pragma once

namespace ske
{
	template <class T>
	void SafeRelease(T* &x)
	{
		if (x)
		{
			x->Release();
			x = nullptr;
		}
	}

	class Deleter
	{
	public:
		template<typename T>
		void operator()(T* t) { SafeDelete(t); }
	};

	template <typename T, size_t N>
	size_t ArrSize(const T (&lhs)[N])
	{
		(void)lhs;
		return N;
	}

	template <class T>
	void SafeDelete(T* &x)
	{
		if (x)
		{
			delete x;
			x = nullptr;
		}
	}
}