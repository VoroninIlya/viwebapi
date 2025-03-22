#pragma once

#include <functional>
#include <type_traits>

namespace viwebapi {

  template<typename T, typename M>
  struct IViWebApiNode {
    static_assert(std::is_void_v<M>, "Not allowed Void type");
    static_assert(std::is_reference_v<M>, "Not allowed Reference type");

    IViWebApiNode() = delete;
    IViWebApiNode(std::function<T(M)> a) {
        this->m_activity = a;
    }

    virtual void invoke(M ctx) {
        if(m_activity) this->m_activity(ctx);
    }
    virtual ~IViWebApiNode() = default;

  protected: 
    std::function<T(M)> m_activity;
    std::function<T()> m_void;
  };

  template<typename T, typename M>
  struct IViWebApiNode<T, M&> {
    static_assert(!std::is_reference_v<M>, "Not allowed non-Reference type");

    IViWebApiNode() = delete;
    IViWebApiNode(std::function<T(M&)> a) {
      m_activity = a;
    }

    virtual void invoke(M& ctx) {
        if(m_activity) this->m_activity(ctx);
    }
    virtual ~IViWebApiNode() = default;

  protected: 
    std::function<T(M&)> m_activity;
  };

  template<typename T>
  struct IViWebApiNode<T, void> {

    IViWebApiNode() = delete;
    IViWebApiNode(std::function<T()> a) {
      this->m_activity = a;
    }

    virtual void invoke() {
        if(m_activity) this->m_activity();
    }
    virtual ~IViWebApiNode() = default;

  protected: 
    std::function<T()> m_activity;
  };

}