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
	bool Initialise(Context* context);

	///
	static EditorPlugin* GetInstance();

	/// Process the incoming Event
	virtual void ProcessEvent(Event& event);

private:
	// The context hosting the Editor documents.
	Context* host_context;
	// The context of Editor.
	Context* editor_context;
	// Singleton instance
	static EditorPlugin* instance;
};

}
} // namespace Rml

#endif