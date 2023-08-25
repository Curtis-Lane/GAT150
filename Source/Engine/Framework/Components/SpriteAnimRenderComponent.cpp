#include "SpriteAnimRenderComponent.h"

#include "Framework/Resource/ResourceManager.h"
#include "Renderer/Renderer.h"

namespace ane {
	CLASS_DEFINITION(SpriteAnimRenderComponent);
	
	bool SpriteAnimRenderComponent::Initialize() {
		SpriteRenderComponent::Initialize();

		SetSequence(this->defaultSequenceName);
		UpdateSource();

		return true;
	}

	void SpriteAnimRenderComponent::Update(float deltaTime) {
		frameTimer -= deltaTime;
		if(frameTimer <= 0) {
			frameTimer = 1.0f / this->currentSequence->fps;
			frame++;
			if(frame > this->currentSequence->endFrame) {
				frame = (this->currentSequence->loop) ? this->currentSequence->startFrame : this->currentSequence->endFrame;
			}
		}

		UpdateSource();
	}

	void SpriteAnimRenderComponent::SetSequence(const std::string& name) {
		// Prevent set sequence again
		if(this->currentSequence != nullptr && this->currentSequence->name == name) {
			return;
		}

		if(this->sequences.find(name) != this->sequences.end()) {
			// Set new sequence
			this->currentSequence = &(this->sequences[name]);

			// Set texture
			if(this->currentSequence->texture != nullptr) {
				this->texture = this->currentSequence->texture;
			}

			// Reset frame information
			frame = this->currentSequence->startFrame;
			frameTimer = 1.0f / this->currentSequence->fps;
		}
	}

	void SpriteAnimRenderComponent::UpdateSource() {
		Vector2 cellSize = this->texture->GetSize() / Vector2(this->currentSequence->numColumns, this->currentSequence->numRows);

		int column = (frame - 1) % this->currentSequence->numColumns;
		int row = (frame - 1) / this->currentSequence->numColumns;

		source.x = static_cast<int>(column * cellSize.x);
		source.y = static_cast<int>(row * cellSize.y);
		source.w = static_cast<int>(cellSize.x);
		source.h = static_cast<int>(cellSize.y);
	}

	void SpriteAnimRenderComponent::Read(const JSON_t& value) {
		SpriteRenderComponent::Read(value);

		// Read in animation sequences
		if(HAS_DATA(value, sequences) && GET_DATA(value, sequences).IsArray()) {
			for(auto& sequenceValue : GET_DATA(value, sequences).GetArray()) {
				AnimSequence sequence;

				READ_NAME_DATA(sequenceValue, "name", sequence.name);
				READ_NAME_DATA(sequenceValue, "fps", sequence.fps);
				READ_NAME_DATA(sequenceValue, "numColumns", sequence.numColumns);
				READ_NAME_DATA(sequenceValue, "numRows", sequence.numRows);
				READ_NAME_DATA(sequenceValue, "startFrame", sequence.startFrame);
				READ_NAME_DATA(sequenceValue, "endFrame", sequence.endFrame);

				// read texture
				std::string textureName;
				READ_DATA(sequenceValue, textureName);
				sequence.texture = GET_RESOURCE(Texture, textureName, globalRenderer);

				this->sequences[sequence.name] = sequence;
			}
		}

		if(!READ_DATA(value, defaultSequenceName)) {
			// If default sequence not specified, use the first sequence in the sequences map
			defaultSequenceName = this->sequences.begin()->first;
		}
	}
}