#include <gtest/gtest.h>
#include "assets.hpp"
using namespace Engine;
// Dummy classes for testing
class DummyAssetA {
public:
    int value;
    DummyAssetA(int v) : value(v) {}
};
class DummyAssetB {
public:
    std::string name;
    DummyAssetB(std::string n) : name(n) {}
};
class AssetRegistryTest : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};
TEST_F(AssetRegistryTest, StoreAndLoadByPath) {
    AssetRegistry<DummyAssetA> registry;
    auto asset1 = std::make_shared<DummyAssetA>(10);

    // Store asset
    auto store_result = registry.store("path/to/asset1", asset1);
    ASSERT_TRUE(store_result.has_value());
    idxx id1 = store_result.value();

    // Load asset by path
    auto load_result = registry.load("path/to/asset1");
    ASSERT_TRUE(load_result.has_value());
    EXPECT_EQ(load_result.value()->value, 10);

    // Load asset by id
    auto load_by_id_result = registry.load(id1);
    ASSERT_TRUE(load_by_id_result.has_value());
    EXPECT_EQ(load_by_id_result.value()->value, 10);
}
TEST_F(AssetRegistryTest, StoreDuplicatePath) {
    AssetRegistry<DummyAssetA> registry;
    auto asset1 = std::make_shared<DummyAssetA>(10);
    auto asset2 = std::make_shared<DummyAssetA>(20);

    ASSERT_TRUE(registry.store("path/duplicate", asset1).has_value());

    auto store_result = registry.store("path/duplicate", asset2);
    ASSERT_FALSE(store_result.has_value());
    EXPECT_EQ(store_result.error().name, "AssetRegistrationFailed");
}
TEST_F(AssetRegistryTest, RemoveByPath) {
    AssetRegistry<DummyAssetA> registry;
    auto asset1 = std::make_shared<DummyAssetA>(10);

    auto store_res = registry.store("path/to/remove", asset1);
    ASSERT_TRUE(store_res.has_value());

    auto remove_result = registry.remove("path/to/remove");
    ASSERT_TRUE(remove_result.has_value());

    // Should fail to load now
    auto load_result = registry.load("path/to/remove");
    ASSERT_FALSE(load_result.has_value());
    EXPECT_EQ(load_result.error().name, "AssetNotFoundError");
}
TEST_F(AssetRegistryTest, RemoveById) {
    AssetRegistry<DummyAssetA> registry;
    auto asset1 = std::make_shared<DummyAssetA>(10);

    auto store_result = registry.store("path/to/remove_id", asset1);
    ASSERT_TRUE(store_result.has_value());
    idxx id = store_result.value();

    auto remove_result = registry.remove(id);
    ASSERT_TRUE(remove_result.has_value());

    // Should fail to load now
    auto load_result = registry.load(id);
    ASSERT_FALSE(load_result.has_value());
    EXPECT_EQ(load_result.error().name, "AssetNotLoadedError");
}
TEST_F(AssetRegistryTest, RemoveNonExistent) {
    AssetRegistry<DummyAssetA> registry;

    auto remove_path_res = registry.remove("non/existent");
    ASSERT_FALSE(remove_path_res.has_value());
    EXPECT_EQ(remove_path_res.error().name, "AssetRemovalFailed");

    auto remove_id_res = registry.remove((idxx)999);
    ASSERT_FALSE(remove_id_res.has_value());
    EXPECT_EQ(remove_id_res.error().name, "AssetRemovalFailed");
}
TEST_F(AssetRegistryTest, Clear) {
    AssetRegistry<DummyAssetA> registry;
    auto asset1 = std::make_shared<DummyAssetA>(10);

    auto store_result = registry.store("path/clear", asset1);
    ASSERT_TRUE(store_result.has_value());
    idxx id = store_result.value();

    registry.clear();

    ASSERT_FALSE(registry.load("path/clear").has_value());
    ASSERT_FALSE(registry.load(id).has_value());
}
class AssetManagerTest : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};
TEST_F(AssetManagerTest, StoreAndLoadDifferentTypes) {
    AssetManager manager;

    auto assetA = std::make_shared<DummyAssetA>(42);
    auto assetB = std::make_shared<DummyAssetB>("test_string");

    auto storeA_result = manager.store<DummyAssetA>("path/assetA", assetA);
    ASSERT_TRUE(storeA_result.has_value());
    idxx idA = storeA_result.value();

    auto storeB_result = manager.store<DummyAssetB>("path/assetB", assetB);
    ASSERT_TRUE(storeB_result.has_value());
    idxx idB = storeB_result.value();

    auto loadA_result = manager.load<DummyAssetA>("path/assetA");
    ASSERT_TRUE(loadA_result.has_value());
    EXPECT_EQ(loadA_result.value()->value, 42);

    auto loadB_result = manager.load<DummyAssetB>(idB);
    ASSERT_TRUE(loadB_result.has_value());
    EXPECT_EQ(loadB_result.value()->name, "test_string");
}
TEST_F(AssetManagerTest, RemoveByPathAndId) {
    AssetManager manager;

    auto assetA = std::make_shared<DummyAssetA>(42);
    auto assetB = std::make_shared<DummyAssetB>("test_string");

    auto storeA_res = manager.store<DummyAssetA>("path/assetA", assetA);
    ASSERT_TRUE(storeA_res.has_value());

    auto storeB_result = manager.store<DummyAssetB>("path/assetB", assetB);
    ASSERT_TRUE(storeB_result.has_value());
    idxx idB = storeB_result.value();

    ASSERT_TRUE(manager.remove<DummyAssetA>("path/assetA").has_value());
    ASSERT_TRUE(manager.remove<DummyAssetB>(idB).has_value());

    ASSERT_FALSE(manager.load<DummyAssetA>("path/assetA").has_value());
    ASSERT_FALSE(manager.load<DummyAssetB>(idB).has_value());
}
TEST_F(AssetManagerTest, ClearAll) {
    AssetManager manager;

    auto assetA = std::make_shared<DummyAssetA>(42);
    auto assetB = std::make_shared<DummyAssetB>("test_string");

    auto storeA_res = manager.store<DummyAssetA>("path/assetA", assetA);
    ASSERT_TRUE(storeA_res.has_value());
    auto storeB_res = manager.store<DummyAssetB>("path/assetB", assetB);
    ASSERT_TRUE(storeB_res.has_value());

    manager.clearAll();

    ASSERT_FALSE(manager.load<DummyAssetA>("path/assetA").has_value());
    ASSERT_FALSE(manager.load<DummyAssetB>("path/assetB").has_value());
}
