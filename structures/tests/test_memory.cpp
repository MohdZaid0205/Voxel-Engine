#include <gtest/gtest.h>
#include "structures.h"

using namespace Structures;

namespace memoryManagementTests{

TEST(SharedPointerTests, DefaultInitilisationSetsToNull){
	Shared<float> nullcontained = Shared<float>();
	ASSERT_THROW(*(nullcontained),std::runtime_error);
}

TEST(SharedPointerTests, ConstructFromValueCopyToHeap) {
	float pi = 3.147f;
	Shared<float> PI(pi);
	ASSERT_NE(&pi, &(*PI));
	ASSERT_FLOAT_EQ(*PI, 3.147f);
}

TEST(SharedPointerTests, ConstructFromRawPointer) {
	float* raw = new float(2.718f);
	Shared<float> e(raw);
	ASSERT_FLOAT_EQ(*e, 2.718f);
	ASSERT_NE(raw,&(*e));
}

TEST(SharedPointerTests, CopyConstructionCopiesOwnership) {
	Shared<int> original(99);
	Shared<int> copy = original;
	ASSERT_EQ(*original, 99);
	ASSERT_EQ(*copy, 99);
	ASSERT_EQ(&(*original),&(*copy));
}

TEST(SharedPointerTests, AssignmentCopiesOwnership) {
	Shared<int> a(100);
	Shared<int> b;
	b = a;
	ASSERT_EQ(*a, 100);
	ASSERT_EQ(*b, 100);
	ASSERT_EQ(&(*a),&(*b));
}

TEST(SharedPointerTests, SelfAssignmentSafe) {
	Shared<int> self(42);
	self = self;
	ASSERT_EQ(*self, 42);
}

TEST(SharedPointerTests, ArrowOperatorAccessesMembers) {
	struct Dummy {
		int a = 5;
		int square() const { return a * a; }
	};

	Shared<Dummy> obj(new Dummy());
	ASSERT_EQ(obj->a, 5);
	ASSERT_EQ(obj->square(), 25);
}

};
