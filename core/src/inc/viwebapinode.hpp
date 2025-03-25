#pragma once

#include <functional>
#include "iviwebapinode.hpp"

namespace viwebapi {

  template<typename T, typename M>
  class ViWebApiNode : public IViWebApiNode<M> {
    static_assert(!std::is_void_v<M>, "Not allowed Void type");
    static_assert(!std::is_reference_v<M>, "Not allowed Reference type");

    std::function<T(M)> m_activity;

  public:
    
    ViWebApiNode() = default;
    ViWebApiNode(const ViWebApiNode&) = delete;
    ViWebApiNode& operator=(const ViWebApiNode&) = delete;
    ViWebApiNode(std::function<T(M)> f) : m_activity(f) {};

    void invoke(M m) const override {
      if(m_activity) m_activity(m);
    }

    virtual ~ViWebApiNode() = default;
  };

  template<typename T, typename M>
  class ViWebApiNode<T, M&> : public IViWebApiNode<M&> {
    static_assert(!std::is_reference_v<M>, "Not allowed non-Reference type");
    
    std::function<T(M&)> m_activity;

  public:
    
    ViWebApiNode() = default;
    ViWebApiNode(const ViWebApiNode&) = delete;
    ViWebApiNode& operator=(const ViWebApiNode&) = delete;
    ViWebApiNode(std::function<T(M&)> f) : m_activity(f) {};

    void invoke(M& m) const override {
      if(m_activity) m_activity(m);
    }

    virtual ~ViWebApiNode() = default;
  };

  template<typename T, typename M>
  class ViWebApiNode<T, M*> : public IViWebApiNode<M*> {
    static_assert(!std::is_pointer_v<M>, "Not allowed non-Reference type");
    
    std::function<T(M*)> m_activity;

  public:
    
    ViWebApiNode() = default;
    ViWebApiNode(const ViWebApiNode&) = delete;
    ViWebApiNode& operator=(const ViWebApiNode&) = delete;
    ViWebApiNode(std::function<T(M*)> f) : m_activity(f) {};

    void invoke(M* m) const override {
      if(m_activity) m_activity(m);
    }

    virtual ~ViWebApiNode() = default;
  };

  template<typename T>
  class ViWebApiNode<T, void> : public IViWebApiNode<void> {

    std::function<T()> m_activity;

  public:
    
    ViWebApiNode() = default;
    ViWebApiNode(const ViWebApiNode&) = delete;
    ViWebApiNode& operator=(const ViWebApiNode&) = delete;
    ViWebApiNode(std::function<T()> f) : m_activity(f) {};

    void invoke() const override {
      if(m_activity) m_activity();
    }

    virtual ~ViWebApiNode() = default;
  };
  
}