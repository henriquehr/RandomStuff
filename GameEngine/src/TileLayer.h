#ifndef TILE_LAYER_H
#define TILE_LAYER_H

#include "Layer.h"
#include "Shader.h"
#include "BatchRenderer2D.h"
#include "Math/Math.h"

class TileLayer : public Layer {
public:
    TileLayer(std::shared_ptr<Shader> shader);
    ~TileLayer();
};
#endif