#pragma once
#include <gtkmm.h>


//wrapper for property proxies that acts more
//like how I want a data binding to act
//overrides assignment
template <class T> class Binding {
public:
  T value;
  sigc::connection connection;
  sigc::slot<void,const T&> set;

  Binding(){
  }

  Binding(Binding<T>* b){
    value = b->value;
    connection = b->connection;
    set = b->set;
  }


  Binding(T first,Glib::PropertyProxy<T> prop) {
    value = first;
    connection = prop.signal_changed(sigc::mem_fun(*this,&Binding<T>::update));
    set = sigc::mem_fun(prop, &Glib::PropertyProxy<T>::set_value);
    set(first);
  }

  operator T() { return value; }

  Binding<T>& operator=(const T& in){
     value = in;
     set(in);
     return *this;
  }

  void update(T in) { value = in; }

  void disconnect() { connection.disconnect(); }
};

template <class K>
const K get_prop(Glib::PropertyProxy<K> prop){
  return prop.get_value();
}

template <class K>
void set_value(Glib::PropertyProxy<K> proxy, const K value){
  proxy.set_value(value);
}

//generates a binding from an initial value and a slot for receiving
//values and a slot for updating values.
template <class T, class K>
std::shared_ptr<Binding<T>> to_from_binding(T first,
                                            Glib::PropertyProxy<K> prop,
                                            sigc::slot<T, const K> to,
                                            sigc::slot<K, T> from) {
  std::shared_ptr<Binding<T>> out = std::make_shared<Binding<T>>(new Binding<T>());
  out->value = first;
  auto frst = sigc::compose(sigc::mem_fun(*out, &Binding<T>::update),to);
  auto snd = sigc::bind(&get_prop<K>,prop);
  out->connection = prop.signal_changed().connect(sigc::compose(frst,snd));
  out->set = sigc::compose(sigc::bind<0>(&set_value<K>,prop),from);
  out->set(first);
  return out;
}

//changes a binding to one using that passed slots to transmit and
//receive values
template <class T, class K>
  void set_to_from_binding(
                           Binding<T>& b,
                           T first, Glib::PropertyProxy<K> prop,
                           sigc::slot<T, K> to,
                sigc::slot<K, T> from) {
  b.value = first;
  b.connection = prop.signal_changed().connect(
      sigc::compose(sigc::mem_fun(&b, &Binding<T>::update), from));
  b.set = sigc::compose(sigc::mem_fun(prop, &Glib::PropertyProxy<T>::set_value),to);
  b.set(first);
}
