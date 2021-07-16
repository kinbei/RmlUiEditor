#ifndef RMLUI_EDITOR_PLUGIN_H
#define RMLUI_EDITOR_PLUGIN_H

#include <RmlUi/Core/EventListener.h>
#include <RmlUi/Core/Plugin.h>

namespace Rml {
namespace Editor {

class EditorPlugin : public Rml::Plugin, public Rml::EventListener
{
public:
	EditorPlugin();
	~EditorPlugin();

	///
	bool Initialise(Context* context, Rml::ElementDocument* workspace_document);

	///
	static EditorPlugin* GetInstance();

	/// Process the incoming Event
	virtual void ProcessEvent(Event& event);

private:
	// The context hosting the Editor documents.
	Context* host_context;
	// The context of Editor.
	Context* editor_context;
	//
	Rml::ElementDocument* workspace_document;
	//
	Rml::ElementDocument* document;
	// Singleton instance
	static EditorPlugin* instance;

	void __ProcessClickEvent(Event& evnet);
};

}
} // namespace Rml

#endif