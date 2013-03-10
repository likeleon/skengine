#include "Pch.h"
#include "SkUtilities.h"

using namespace ske;

TEST(UtilitiesTest, SafeReleaseTest)
{
	class Object
	{
	public:
		Object() : m_released(false) {}

		void Release()
		{
			m_released = true;
		}

		bool m_released;
	};

	Object* obj = new Object;
	std::auto_ptr<Object> objAutoPtr(obj);	// prevent memory leak

	SafeRelease(obj);
	EXPECT_EQ(nullptr, obj);

	EXPECT_EQ(true, objAutoPtr->m_released);
}

TEST(UtilitiesTest, ArraySizeDeterminationTest)
{
	const int ia[10] = {0};
	EXPECT_EQ(10, ArrSize(ia));

	// Compile error
	//const char* dyn = nullptr;
	//ArrSize(dyn);
}

class ObjectDelete
{
public:
	~ObjectDelete()
	{
		s_deleted = true;
	}

	static bool s_deleted;
};
bool ObjectDelete::s_deleted = false;

TEST(UtilitiesTest, SafeDeleteTest)
{
	ObjectDelete::s_deleted = false;

	ObjectDelete* obj = new ObjectDelete;
	SafeDelete(obj);
	EXPECT_TRUE(ObjectDelete::s_deleted);
}