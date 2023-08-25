#include "TextRenderComponent.h"

#include "Framework/Resource/ResourceManager.h"
#include "Framework/Actor.h"

namespace ane {
	CLASS_DEFINITION(TextRenderComponent);

	TextRenderComponent::TextRenderComponent(const TextRenderComponent& other) {
		this->text = other.text;
		this->fontName = other.fontName;
		this->fontSize = other.fontSize;

		this->changed = true;
		this->p_text = std::make_unique<Text>(*other.p_text.get());
	}

	bool TextRenderComponent::Initialize() {
		if(!fontName.empty()) {
			this->p_text = std::make_unique<Text>(GET_RESOURCE(Font, this->fontName, this->fontSize));
		}

		return true;
	}

	void TextRenderComponent::Update(float deltaTime) {
		//
	}

	void TextRenderComponent::Draw(Renderer& renderer) {
		// Update the text if changed
		if(this->changed) {
			this->changed = false;
			// Create text using text string and color
			this->p_text->Create(renderer, this->text, color);
		}

		// Draw text
		this->p_text->Draw(renderer, this->owner->transform);
	}

	void TextRenderComponent::SetText(const std::string& string) {
		// Check if text has changed, if changed set new string and update
		if(string != this->text) {
			this->text = string;
			this->changed = true;
		}
	}

	void TextRenderComponent::Read(const JSON_t& value) {
		READ_DATA(value, text);
		READ_DATA(value, fontName);
		READ_DATA(value, fontSize);
		READ_DATA(value, color);
	}
}