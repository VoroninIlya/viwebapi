#pragma once

#include <functional>
#include "iviwebapinode.hpp"

namespace viwebapi {

  template<typename T, typename M>
  class ViWebApiNode : public IViWebApiNode<T, M> {
    static_assert(std::is_void_v<M>, "Not allowed Void type");
    static_assert(std::is_reference_v<M>, "Not allowed Reference type");

  public:
    
    ViWebApiNode() = default;
    ViWebApiNode(const ViWebApiNode&) = delete;
    ViWebApiNode& operator=(const ViWebApiNode&) = delete;
    ViWebApiNode(std::function<T(M)> f) : IViWebApiNode<T,M>(f) {};

    virtual ~ViWebApiNode() = default;
  };

  template<typename T, typename M>
  class ViWebApiNode<T, M&> : public IViWebApiNode<T, M&> {
    static_assert(!std::is_reference_v<M>, "Not allowed non-Reference type");
    
  public:
    
    ViWebApiNode() = default;
    ViWebApiNode(const ViWebApiNode&) = delete;
    ViWebApiNode& operator=(const ViWebApiNode&) = delete;
    ViWebApiNode(std::function<T(M&)> f) : IViWebApiNode<T,M&>(f) {};

    virtual ~ViWebApiNode() = default;
  };

  template<typename T>
  class ViWebApiNode<T, void> : public IViWebApiNode<T, void> {

  public:
    
    ViWebApiNode() = default;
    ViWebApiNode(const ViWebApiNode&) = delete;
    ViWebApiNode& operator=(const ViWebApiNode&) = delete;
    ViWebApiNode(std::function<T()> f) : IViWebApiNode<T, void>(f) {};

    virtual ~ViWebApiNode() = default;
  };
  
}