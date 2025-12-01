#include "glcore/core/layer_stack.hh"

#include "glcore/core/layer.hh"

namespace core {

LayerStack::LayerStack() {}

LayerStack::~LayerStack() {}

void LayerStack::push_layer(Scope<Layer> layer) {}

void LayerStack::pop_layer(Scope<Layer> layer) {}

void LayerStack::push_overlay(Scope<Layer> layer) {}

void LayerStack::pop_overlay(Scope<Layer> overlay) {}

}  // namespace core
