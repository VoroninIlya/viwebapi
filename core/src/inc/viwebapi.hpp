#pragma once

#include <functional>
#include <memory>
#include <string>
#include <map>

#include "iviwebapinode.hpp"

namespace viwebapi {

  template<typename T, typename M = void>
  class ViWebApi {

  public:
    
    using api_key = std::string;

    using api_element = struct {
      const api_key& key;
      std::unique_ptr<IViWebApiNode<T, M>> node;
    };

    static ViWebApi<T, M>& getInstance() {
      static ViWebApi<T, M> ret;
      return ret;
    }

    void runtime(
      const std::function<bool(const std::string&)>&,
      const std::function<void(void)>&,
      M);
      
    void addApi(const std::string&, std::unique_ptr<IViWebApiNode<T, M>>);
    void removeApi(const std::string&);

    ViWebApi<T, M>& operator+=(api_element& api);
    ViWebApi<T, M>& operator-=(const api_key& api);

    ViWebApi(const ViWebApi<T, M>&) = delete;
    ViWebApi<T, M>& operator=(const ViWebApi<T, M>&) = delete;

    ~ViWebApi() = default;

  private:
    ViWebApi() = default;

    std::map<std::string, std::unique_ptr<IViWebApiNode<T, M>>> m_api{};
  };
}

#include "../viwebapi.cpp"

