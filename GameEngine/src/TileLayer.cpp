#include "TileLayer.h"

TileLayer::TileLayer(std::shared_ptr<Shader> shader)
: Layer(std::make_shared<BatchRenderer2D>(), shader, 
Matrix4::createOrthographic(-16.0f, 16.0f, -9.0f, 9.0f, -1.0f, 1.0f)) {}

TileLayer::~TileLayer() {}
