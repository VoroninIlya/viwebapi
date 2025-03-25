#pragma once

#include <map>

#include "iviwebapi.hpp"

namespace viwebapi {

  template<typename T, typename M>
  class ViWebApi : public IViWebApi<M> {

    enum class LogLevel{
      Info = 1,
      Debug,
      Trace,
      Error
    };

    ViWebApi() = default;

    std::function<void(uint8_t, const std::string&)> m_printCb;
    std::map<std::string, std::unique_ptr<IViWebApiNode<M>>> m_api{};

  public:

    static ViWebApi<T, M>& getInstance() {
      static ViWebApi<T, M> ret;
      return ret;
    }

    ViWebApi(const ViWebApi<T, M>&) = delete;

    ViWebApi(ViWebApi<T, M>&& o) noexcept {
      for(auto& a : o.m_api) {
        m_api.insert({a.first, std::move(a.second)});
      }
      o.m_api.clear();
    }

    virtual void runtime(
      const std::function<bool(const std::string&)>&,
      const std::function<void(void)>&, M) const override;

    virtual void addApi(const std::string&, std::unique_ptr<IViWebApiNode<M>>) override;
    virtual void removeApi(const std::string&) override;

    virtual void setPrintCb(std::function<void(uint8_t, const std::string&)>) override;

    IViWebApi<M>& operator+=(api_element<M>&) override;
    IViWebApi<M>& operator-=(const api_key&) override;

    ViWebApi<T, M>& operator=(const ViWebApi<T, M>&) = delete;
    ViWebApi<T, M>& operator=(ViWebApi<T, M>&& o) noexcept{
      m_api.clear();
      for(auto& a : o.m_api) {
        m_api.insert({a.first, std::move(a.second)});
      }
      return *this;
    }

    ~ViWebApi() = default;

  };

  template<typename T>
  class ViWebApi<T, void> : public IViWebApi<void>  {

    enum class LogLevel{
      Info = 1,
      Debug,
      Trace,
      Error
    };

    ViWebApi() = default;

    std::function<void(uint8_t, const std::string&)> m_printCb;
    std::map<std::string, std::unique_ptr<IViWebApiNode<void>>> m_api{};

  public:

    static ViWebApi<T, void>& getInstance() {
      static ViWebApi<T, void> ret;
      return ret;
    }

    ViWebApi(const ViWebApi<T, void>&) = delete;

    ViWebApi(ViWebApi<T, void>&& o) noexcept {
      for(auto& a : o.m_api) {
        m_api[a.first] = std::move(a.second);
      }
      o.m_api.clear();
    }

    virtual void runtime(
      const std::function<bool(const std::string&)>&,
      const std::function<void(void)>&) const override;

    virtual void addApi(const std::string&, std::unique_ptr<IViWebApiNode<void>>) override;
    virtual void removeApi(const std::string&) override;

    virtual void setPrintCb(std::function<void(uint8_t, const std::string&)>) override;

    IViWebApi<void>& operator+=(api_element<void>&) override;
    IViWebApi<void>& operator-=(const api_key&) override;

    ViWebApi<T, void>& operator=(const ViWebApi<T, void>&) = delete;
    ViWebApi<T, void>& operator=(ViWebApi<T, void>&& o) noexcept {
      m_api.clear();
      for(auto& a : o.m_api) {
        m_api[a.first] = std::move(a.second);
      }
      return *this;
    }

    ~ViWebApi() = default;

  };
}

#include "../viwebapi.cpp"

