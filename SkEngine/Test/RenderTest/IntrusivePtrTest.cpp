#include "Pch.h"
#include "SkIntrusivePtr.h"

using namespace ske;

class IntrusivePtrTest : public ::testing::Test
{
public:
	static size_t s_numObject;
	static size_t s_numDerived;

protected:
	virtual void SetUp()
	{
		s_numObject = 0;
		s_numDerived = 0;
	}

	virtual void TearDown()
	{
		s_numObject = 0;
		s_numDerived = 0;
	}
};

size_t IntrusivePtrTest::s_numObject = 0;
size_t IntrusivePtrTest::s_numDerived = 0;

// Basic object for testing
class Object
{
public:
	Object()
	: m_refCount(0)
	{
		++IntrusivePtrTest::s_numObject;
	}

	size_t GetRefCount() const 
	{ 
		return m_refCount; 
	}

	friend void IntrusivePtrIncRef(Object* p)
	{
		++(p->m_refCount);
	}

	friend void IntrusivePtrDecRef(Object* p)
	{
		--(p->m_refCount);
		if (p->m_refCount == 0)
			delete p;
	}

protected:
	virtual ~Object()
	{
		--IntrusivePtrTest::s_numObject;
	}

private:
	size_t m_refCount;
};

// Testing derived class
class Derived : public Object
{
public:
	Derived()
	{
		++IntrusivePtrTest::s_numDerived;
	}

	virtual ~Derived()
	{
		--IntrusivePtrTest::s_numDerived;
	}
};

typedef IntrusivePtr<Object> ObjectPtr;
typedef IntrusivePtr<Derived> DerivedPtr;

TEST_F(IntrusivePtrTest, SizeTest)
{
	EXPECT_EQ(sizeof(void *), sizeof(ObjectPtr));
}

TEST_F(IntrusivePtrTest, ReferenceCountingTest)
{
	EXPECT_EQ(0, s_numObject);
	{
		ObjectPtr objPtr(new Object);
		EXPECT_EQ(1, objPtr->GetRefCount());
		EXPECT_EQ(1, (*objPtr).GetRefCount());	// test operator*
		EXPECT_EQ(1, s_numObject);
	}
	EXPECT_EQ(0, s_numObject);

	ObjectPtr objPtr(new Object);
	objPtr = nullptr;
	EXPECT_EQ(0, s_numObject);
}

TEST_F(IntrusivePtrTest, NullPtrTest)
{
	ObjectPtr objPtr;
	EXPECT_EQ(nullptr, objPtr.Get());
}

TEST_F(IntrusivePtrTest, NullTestTest)
{
	ObjectPtr a(new Object);
	EXPECT_TRUE(a);
	EXPECT_FALSE(!a);

	ObjectPtr b = nullptr;
	EXPECT_FALSE(b);
	EXPECT_TRUE(!b);
}

TEST_F(IntrusivePtrTest, GetRawPointerTest)
{
	Object* const rawObj = new Object;
	ObjectPtr a(rawObj);

	EXPECT_EQ(rawObj, a.Get());
}

TEST_F(IntrusivePtrTest, AssignmentTest)
{
	ObjectPtr a(new Object);
	ObjectPtr b;
	b = a;
	EXPECT_EQ(a, b);
	EXPECT_EQ(2, a->GetRefCount());

	Object* const rawObj = new Object;
	b = rawObj;
	EXPECT_EQ(rawObj, b.Get());
	EXPECT_EQ(1, a->GetRefCount());
}

TEST_F(IntrusivePtrTest, CopyConstructTest)
{
	ObjectPtr a(new Object);
	ObjectPtr b(a);

	EXPECT_EQ(a, b);
	EXPECT_EQ(2, a->GetRefCount());
}

TEST_F(IntrusivePtrTest, EqualityTest)
{
	ObjectPtr a(new Object);
	ObjectPtr b(a);
	EXPECT_TRUE(a == b);
	EXPECT_FALSE(a != b);
	EXPECT_TRUE(a == b.Get());
	EXPECT_FALSE(a != b.Get());
	EXPECT_TRUE(a.Get() == b);
	EXPECT_FALSE(a.Get() != b);

	ObjectPtr c(new Object);
	EXPECT_TRUE(a != c);
	EXPECT_FALSE(a == c);
}

TEST_F(IntrusivePtrTest, SwapTest)
{
	ObjectPtr a(new Object);
	ObjectPtr b(new Object);

	Object* const aRaw = a.Get();
	Object* const bRaw = b.Get();

	swap(a, b);
	EXPECT_EQ(bRaw, a.Get());
	EXPECT_EQ(aRaw, b.Get());
}

TEST_F(IntrusivePtrTest, InheritanceTest)
{
	EXPECT_EQ(0, s_numObject);
	EXPECT_EQ(0, s_numDerived);
	{
		ObjectPtr objPtr(new Derived);
		EXPECT_EQ(1, objPtr->GetRefCount());
		EXPECT_EQ(1, s_numObject);
		EXPECT_EQ(1, s_numDerived);
	}
	EXPECT_EQ(0, s_numObject);
	EXPECT_EQ(0, s_numDerived);
}

TEST_F(IntrusivePtrTest, UpCastTest)
{
	ObjectPtr objPtr(new Derived);
	DerivedPtr derivedPtr(static_pointer_cast<Derived>(objPtr));
	derivedPtr = dynamic_pointer_cast<Derived>(objPtr);
	EXPECT_EQ(2, objPtr->GetRefCount());
	EXPECT_EQ(1, s_numObject);
	EXPECT_EQ(1, s_numDerived);
}

TEST_F(IntrusivePtrTest, ConstCastTest)
{
	const ObjectPtr cObjPtr(new Derived);
	ObjectPtr ncObjPtr = const_pointer_cast<Object>(cObjPtr);
	EXPECT_EQ(cObjPtr, ncObjPtr);
}

class ObjectEasy : public IntrusiveSharedObject<size_t>
{
public:
	ObjectEasy()
	{
		++IntrusivePtrTest::s_numObject;
	}

	virtual ~ObjectEasy()
	{
		--IntrusivePtrTest::s_numObject;
	}

	size_t GetRefCount() const 
	{ 
		return m_refCount; 
	}
};

typedef IntrusivePtr<ObjectEasy> ObjectEasyPtr;

TEST_F(IntrusivePtrTest, IntrusiveSharedObjectTest)
{
	EXPECT_EQ(0, s_numObject);
	{
		ObjectEasyPtr objPtr(new ObjectEasy);
		EXPECT_EQ(1, objPtr->GetRefCount());
		EXPECT_EQ(1, (*objPtr).GetRefCount());	// test operator*
		EXPECT_EQ(1, s_numObject);
	}
	EXPECT_EQ(0, s_numObject);
}