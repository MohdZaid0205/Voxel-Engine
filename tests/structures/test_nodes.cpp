#include <gtest/gtest.h>
#include "structures.h"

using namespace Structures;

namespace xNodeAndxLLTests 
{

TEST(UniDirectionalNodeTest, ConstructorInitialisesItem) {
	uNode<int> node(new int(71821));
	EXPECT_EQ(71821,*(node.getItem()));
}

TEST(UniDirectionalNodeTest, ConstructorSavesSameItemPointer) {
	int* storable = new int(221915);
	uNode<int> node(storable);
	EXPECT_EQ(storable, node.getItem());
	EXPECT_EQ(221915, *(node.getItem()));
}

TEST(UniDirectionalNodeTest, ConstructorSavesNextNodePointer) {
	Shared<uNode<int>> node2 (new uNode<int>(new int(0xff)));
	Shared<uNode<int>> node1 (new uNode<int>(new int(0xee), node2));
	EXPECT_TRUE(node2 == node1->getNext());
	EXPECT_TRUE(node2->getItem() == node1->getNext()->getItem());
}

TEST(UniDirectionalNodeTest, SetNextProperlySetsItemAndNext){
	Shared<uNode<int>> node2 (new uNode<int>(new int(0xff)));
	Shared<uNode<int>> node1 (new uNode<int>(new int(0xee)));
	node1->setNext(node2);
	node1->setItem(new int(0xaa));
	EXPECT_TRUE(node2 == node1->getNext());
	EXPECT_EQ(*(node1->getItem()),0xaa);
}

}