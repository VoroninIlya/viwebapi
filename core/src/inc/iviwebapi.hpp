#pragma once

#include <string>
#include <memory>
#include <functional>

#include "iviwebapinode.hpp"

namespace viwebapi {

  typedef std::string api_key;

  template<typename M>
  struct api_element {
    const api_key& key;
    std::unique_ptr<IViWebApiNode<M>> node;
  };

  template<typename M>
  struct IViWebApi {

    virtual void runtime(
      const std::function<bool(const std::string&)>&,
      const std::function<void(void)>&, M) const = 0;

    virtual void addApi(const std::string&, std::unique_ptr<IViWebApiNode<M>>) = 0;
    virtual void removeApi(const std::string&) = 0;

    virtual void setPrintCb(std::function<void(uint8_t, const std::string&)>) = 0;

    virtual IViWebApi<M>& operator+=(api_element<M>&) = 0;
    virtual IViWebApi<M>& operator-=(const api_key&) = 0;
  };

  template<>
  struct IViWebApi<void> {

    virtual void runtime(
      const std::function<bool(const std::string&)>&,
      const std::function<void(void)>&) const = 0;

    virtual void addApi(const std::string&, std::unique_ptr<IViWebApiNode<void>>) = 0;
    virtual void removeApi(const std::string&) = 0;

    virtual void setPrintCb(std::function<void(uint8_t, const std::string&)>) = 0;

    virtual IViWebApi<void>& operator+=(api_element<void>&) = 0;
    virtual IViWebApi<void>& operator-=(const api_key&) = 0;
  };

}