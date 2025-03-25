#include "viwebapi.hpp"
#include "viwebapinode.hpp"
#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <type_traits>

using namespace viwebapi;

template <typename T>
class ViWebApiTypedTest : public ::testing::Test {};

using ViWebApiTypes = ::testing::Types<
  std::pair<std::monostate, int>,
  std::pair<std::monostate, std::monostate>,
  std::pair<int, std::monostate>,
  std::pair<void*, void*>>;

TYPED_TEST_SUITE(ViWebApiTypedTest, ViWebApiTypes);

TYPED_TEST(ViWebApiTypedTest, FullTest) {
  using T1 = std::conditional_t<std::is_same_v<typename TypeParam::first_type, std::monostate>, void, typename TypeParam::first_type>;
  using T2 = std::conditional_t<std::is_same_v<typename TypeParam::second_type, std::monostate>, void, typename TypeParam::second_type>;;

  using api = ViWebApi<T1, T2>;
  using node = ViWebApiNode<T1, T2>;

  api webapi = std::move(api::getInstance());

  std::string apiPath = "/";

  api_element<T2> elem{apiPath, nullptr};

  if constexpr (std::is_void_v<T2>) {

    elem.node = std::move(std::make_unique<node>([](void) -> T1 {
      if constexpr (!std::is_void_v<T1>) {
        return T1();
      }
    }));

  } else {
    elem.node = std::move(std::make_unique<node>([](T2 m) -> T1 {
      if constexpr (!std::is_void_v<T1>) {
        return T1();
      }
    }));
  }

  webapi += elem;
  std::string tmp;
  bool calledNotmatcher = false;

  auto callRuntime = [&](bool retVal) {
    if constexpr (std::is_void_v<T2>) {

      webapi.runtime(
        [&](const std::string& s) -> bool {
          tmp = s;
          return retVal;
        },
        [&]() {
          calledNotmatcher = true;
        }
      );
  
    } else if constexpr (std::is_pointer_v<T2>) {
  
      webapi.runtime(
        [&](const std::string& s) -> bool {
          tmp = s;
          return retVal;
        },
        [&]() {
          calledNotmatcher = true;
        },
        nullptr
      );
  
    } else {
      webapi.runtime(
        [&](const std::string& s) -> bool {
          tmp = s;
          return retVal;
        },
        [&]() {
          calledNotmatcher = true;
        },
        0
      );
    }
  };

  callRuntime(false);

  ASSERT_EQ(tmp, apiPath);
  ASSERT_EQ(true, calledNotmatcher);

  calledNotmatcher = false;
  
  callRuntime(true);

  ASSERT_EQ(false, calledNotmatcher);

  webapi -= apiPath;

  callRuntime(true);

}

/*
class ViWebApiTestParametrized : public ::testing::TestWithParam<std::tuple<>> {
  protected:
  int testInt1 = 1;
  int testInt2 = 2;
  int testInt3 = 3;
  int testInt4 = 4;

  api1 webapiVoidInt = std::move(api1::getInstance());
  api2 webapiVoidVoid = std::move(api2::getInstance());
  api3 webapiIntVoid = std::move(api3::getInstance());
  api4 webapiPtrPtr = std::move(api4::getInstance());

  std::string apiPath = "/";

  api_element<int> elem1 {
    apiPath,
    std::make_unique<node1>(std::bind(&ViWebApiTest::testFunc1, this,  std::placeholders::_1))
  };

  api_element<void> elem2 {
    apiPath,
    std::make_unique<node2>(std::bind(&ViWebApiTest::testFunc2, this,  std::placeholders::_1))
  };

  api_element<void> elem3 {
    apiPath,
    std::make_unique<node3>(std::bind(&ViWebApiTest::testFunc3, this,  std::placeholders::_1))
  };

  api_element<void*> elem4 {
    apiPath,
    std::make_unique<node4>(std::bind(&ViWebApiTest::testFunc3, this,  std::placeholders::_1))
  };

public:
  void testFunc1(int i) {
    ASSERT_EQ(testInt1, i);
  }

  void testFunc2() {
  }

  int testFunc3() {
    
  }

  void* testFunc4(void* ptr) {
    ASSERT_TRUE(ptr != (void*)&testInt4), nullptr; 
    return nullptr;
  }

  void SetUp() override {}

  void TearDown() override {}
}
*/
