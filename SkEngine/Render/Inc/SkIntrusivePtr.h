#pragma once

namespace ske
{
	template <class T>
	class IntrusivePtr
	{
	public:
		IntrusivePtr()
		: m_ptr(nullptr)
		{}

		IntrusivePtr(T* p)
		: m_ptr(p)
		{
			if (m_ptr)
				IntrusivePtrIncRef(m_ptr);
		}

		
		template<class U>
		IntrusivePtr(const IntrusivePtr<U>& other)
		: m_ptr(other.Get())
		{
			if (m_ptr)
				IntrusivePtrIncRef(m_ptr);
		}

		IntrusivePtr(const IntrusivePtr& other)
		: m_ptr(other.Get())
		{
			if (m_ptr)
				IntrusivePtrIncRef(m_ptr);
		}

		~IntrusivePtr()
		{
			if (m_ptr)
				IntrusivePtrDecRef(m_ptr);
		}

		T& operator*() const
		{
			return *m_ptr;
		}

		T* operator->() const
		{
			return m_ptr;
		}

		T* Get() const
		{
			return m_ptr;
		}

		template <class U>
		IntrusivePtr<U>& operator=(const IntrusivePtr<U>& other)
		{
			this_type(other).swap(*this);
			return *this;
		}

		IntrusivePtr& operator=(const IntrusivePtr& other)
		{
			this_type(other).swap(*this);
			return *this;
		}

		IntrusivePtr& operator=(T* other)
		{
			this_type(other).swap(*this);
			return *this;
		}

		typedef IntrusivePtr<T> this_type;
		typedef T* this_type::*unspecified_bool_type;
		operator unspecified_bool_type() const
		{
			return (m_ptr == nullptr)? nullptr : &this_type::m_ptr;
		}

		bool operator!() const
		{
			return (m_ptr == nullptr);
		}

		void swap(IntrusivePtr<T>& other)
		{
			T* temp = m_ptr;
			m_ptr = other.m_ptr;
			other.m_ptr = temp;
		}

	private:
		T* m_ptr;
	};

	template <class T, class U>
	bool operator==(const IntrusivePtr<T>& lhs, const IntrusivePtr<U>& rhs)
	{
		return (lhs.Get() == rhs.Get());
	}

	template <class T, class U>
	bool operator!=(const IntrusivePtr<T>& lhs, const IntrusivePtr<U>& rhs)
	{
		return (lhs.Get() != rhs.Get());
	}

	template <class T, class U>
	bool operator==(const IntrusivePtr<T>& lhs, const U* rhs)
	{
		return (lhs.Get() == rhs);
	}

	template <class T, class U>
	bool operator!=(const IntrusivePtr<T>& lhs, const U* rhs)
	{
		return (lhs.Get() != rhs);
	}

	template <class T, class U>
	bool operator==(const T* lhs, const IntrusivePtr<U>& rhs)
	{
		return (lhs == rhs.Get());
	}

	template <class T, class U>
	bool operator!=(const T* lhs, const IntrusivePtr<U>& rhs)
	{
		return (lhs != rhs.Get());
	}

	template <class T>
	void swap(IntrusivePtr<T>& lhs, IntrusivePtr<T>& rhs)
	{
		lhs.swap(rhs);
	}

	template <class T, class U>
	IntrusivePtr<T> static_pointer_cast(const IntrusivePtr<U>& p)
	{
		return static_cast<T*>(p.Get());
	}

	template <class T, class U>
	IntrusivePtr<T> dynamic_pointer_cast(const IntrusivePtr<U>& p)
	{
		return dynamic_cast<T*>(p.Get());
	}

	template <class T, class U>
	IntrusivePtr<T> const_pointer_cast(const IntrusivePtr<U>& p)
	{
		return const_cast<T*>(p.Get());
	}

	// A handly class for you to inherit from in order to use IntrusivePtr painlessly.
	template <typename CounterType>
	class IntrusiveSharedObject
	{
	public:
		IntrusiveSharedObject() : m_refCount(0) {}
		virtual ~IntrusiveSharedObject() {}

		friend void IntrusivePtrIncRef(IntrusiveSharedObject* p)
		{
			++(p->m_refCount);
		}

		friend void IntrusivePtrDecRef(IntrusiveSharedObject* p)
		{
			--(p->m_refCount);
			if (p->m_refCount == 0)
				delete p;
		}

	protected:
		mutable CounterType m_refCount;
	};

#if 0
	// A handly macro for you, in order to use IntrusivePtr painlessly.
	#define SK_INTRUSIVE_DECLARE_SHARED_OBJECT(class_name) \
		private: \
			friend void IntrusivePtrIncRef(##class_name* const p); \
			friend void IntrusivePtrDecRef(##class_name* const p); \
			mutable size_t m_refCount;

	#define SK_INTRUSIVE_DEFINE_SHARED_OBJECT(class_name) \
		void IntrusivePtrIncRef(##class_name* const p) { \
			++(p->m_refCount); \
		} \
		void IntrusivePtrDecRef(##class_name* const p) { \
			--(p->m_refCount); \
			if (p->m_refCount == 0) \
				delete p; \
		}

	#define SK_INTRUSIVE_INIT_SHARED_OBJECT \
		m_refCount = 0;
#endif
}