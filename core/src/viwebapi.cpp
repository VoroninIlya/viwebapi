#include "viwebapi.hpp"
#include <string>

using namespace std;

namespace viwebapi {

  template<typename T, typename M>
  void ViWebApi<T, M>::addApi(const string& s, unique_ptr<IViWebApiNode<M>> a) {
    if(m_printCb)
      m_printCb(static_cast<uint8_t>(LogLevel::Trace), "Added web api: " + s);
    m_api[s] = move(a);
  }

  template<typename T>
  void ViWebApi<T, void>::addApi(const string& s, unique_ptr<IViWebApiNode<void>> a) {
    if(m_printCb)
      m_printCb(static_cast<uint8_t>(LogLevel::Trace), "Added web api: " + s);
    m_api[s] = move(a);
  }

  template<typename T, typename M>
  void ViWebApi<T, M>::removeApi(const string& s) {
    if(m_printCb)
      m_printCb(static_cast<uint8_t>(LogLevel::Trace), "Removed web api: " + s);
    m_api.erase(s);
  }

  template<typename T>
  void ViWebApi<T, void>::removeApi(const string& s) {
    if(m_printCb)
      m_printCb(static_cast<uint8_t>(LogLevel::Trace), "Removed web api: " + s);
    m_api.erase(s);
  }

  template<typename T, typename M>
  void ViWebApi<T, M>::setPrintCb(std::function<void(uint8_t, const std::string&)> pCb) {
    m_printCb = pCb;
  }

  template<typename T>
  void ViWebApi<T, void>::setPrintCb(std::function<void(uint8_t, const std::string&)> pCb) {
    m_printCb = pCb;
  }

  template<typename T, typename M>
  void ViWebApi<T, M>::runtime(
    const function<bool(const string&)>& matcher, 
    const function<void(void)>& no_matcher, M b) const {
    
    for (auto& a : m_api) {
        if(!a.first.empty() && a.second && matcher(a.first)) {
            if(m_printCb)
              m_printCb(static_cast<uint8_t>(LogLevel::Trace), "Invoke handler for api: " + a.first);
            a.second->invoke(b);
            return;
        }
    }
    no_matcher();
  }

  template<typename T>
  void ViWebApi<T, void>::runtime(
    const std::function<bool(const std::string&)>& matcher,
    const std::function<void(void)>& no_matcher) const {
    for (auto& a : m_api) {
      if(!a.first.empty() && a.second && matcher(a.first)) {
        a.second->invoke();
        return;
      }
    }
    no_matcher();
  }

  template<typename T, typename M>
  IViWebApi<M>& ViWebApi<T, M>::operator+=(api_element<M>& api) {
    addApi(api.key, move(api.node));
    return *this;
  }

  template<typename T>
  IViWebApi<void>& ViWebApi<T, void>::operator+=(api_element<void>& api) {
    addApi(api.key, move(api.node));
    return *this;
  }

  template<typename T, typename M>
  IViWebApi<M>& ViWebApi<T, M>::operator-=(const api_key& api) {
    removeApi(api);
    return *this;
  }

  template<typename T>
  IViWebApi<void>& ViWebApi<T, void>::operator-=(const api_key& api) {
    removeApi(api);
    return *this;
  }
}

