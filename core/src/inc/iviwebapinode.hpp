#pragma once

#include <functional>
#include <type_traits>

namespace viwebapi {

  template<typename M>
  struct IViWebApiNode {
    static_assert(!std::is_void_v<M>, "Not allowed Void type");
    static_assert(!std::is_reference_v<M>, "Not allowed Reference type");

    virtual void invoke(M) const = 0;
    virtual ~IViWebApiNode() = default;
  };

  template<typename M>
  struct IViWebApiNode<M&> {
    static_assert(!std::is_reference_v<M>, "Not allowed non-Reference type");

    virtual void invoke(M&) const = 0;
    virtual ~IViWebApiNode() = default;

  };

  template<typename M>
  struct IViWebApiNode<M*> {
    static_assert(!std::is_pointer_v<M>, "Not allowed non-Reference type");

    virtual void invoke(M*) const = 0;
    virtual ~IViWebApiNode() = default;

  };

  template<>
  struct IViWebApiNode<void> {

    virtual void invoke() const = 0;
    virtual ~IViWebApiNode() = default;

  };

}