#include "viwebapi.hpp"
#include <string>

using namespace std;

namespace viwebapi {

  template<typename T, typename M>
  void ViWebApi<T, M>::addApi(const string& s, unique_ptr<IViWebApiNode<T, M>> a) {
    m_api[s] = move(a);
  }

  template<typename T, typename M>
  void ViWebApi<T, M>::removeApi(const string& s) {
    m_api.erase(s);
  }

  template<typename T, typename M>
  void ViWebApi<T, M>::runtime(
    const function<bool(const string&)>& matcher, 
    const function<void(void)>& no_matcher, 
     M b) {
    
    for (auto& a : m_api) {
        if(!a.first.empty() && a.second && matcher(a.first)) {
            a.second->invoke(b);
            return;
        }
    }
    no_matcher();
  }

  template<typename T, typename M>
  ViWebApi<T, M>& ViWebApi<T, M>::operator+=(api_element& api) {
    addApi(api.key, move(api.node));
    return *this;
  }

  template<typename T, typename M>
  ViWebApi<T, M>& ViWebApi<T, M>::operator-=(const api_key& api) {
    removeApi(api);
    return *this;
  }

}

