#pragma once

#include "layer.hh"

namespace core {
class LayerStack {
public:
  LayerStack();
  virtual ~LayerStack();

  // Logic
  void push_layer(Scope<Layer> layer);
  void pop_layer(Scope<Layer> layer);

  // Overlay (always on top)
  void push_overlay(Scope<Layer> layer);
  void pop_overlay(Scope<Layer> overlay);

  auto begin() { return layers_.begin(); }
  auto end() { return layers_.end(); }

  auto begin() const { return layers_.begin(); }
  auto end() const { return layers_.end(); }

  auto rbegin() { return layers_.rbegin(); }
  auto rend() { return layers_.rend(); }

  auto rbegin() const { return layers_.rbegin(); }
  auto rend() const { return layers_.rend(); }

private:
  std::vector<Scope<Layer>> layers_;
  unsigned int layer_insert_index_ = 0;
};
}  // namespace core
