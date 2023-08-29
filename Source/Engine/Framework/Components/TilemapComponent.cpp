#include "TilemapComponent.h"

#include "Framework/Actor.h"
#include "Framework/Scene.h"

namespace ane {
    CLASS_DEFINITION(TilemapComponent);

    bool TilemapComponent::Initialize() {
        for (int i = 0; i < tiles.size(); i++) {
            int index = tiles[i];
            if (index == 0) {
                continue;
            }

            auto actor = INSTANTIATE(Actor, tileNames[index]);
            if (actor != nullptr) {
                int x = i % numColumns;
                int y = i / numColumns;

                actor->transform.position = this->owner->transform.position + (Vector2(x, y) * size);
                this->owner->scene->Add(std::move(actor));
            }
        }

        return true;
    }

    void TilemapComponent::Update(float deltaTime) {
        //
    }
        
    void TilemapComponent::Read(const JSON_t& value) {
        READ_DATA(value, numColumns);
        READ_DATA(value, numRows);
        READ_DATA(value, size);

        READ_DATA(value, tileNames);
        READ_DATA(value, tiles);
    }
}