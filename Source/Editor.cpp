#include "Editor.h"
#include "EditorPlugin.h"
#include <RmlUi/Core/Log.h>

namespace Rml {
namespace Editor {

/// 
bool Initialise(Context* context, Rml::ElementDocument* workspace_document)
{
	return EditorPlugin::GetInstance()->Initialise(context, workspace_document);
}

/// 
bool Shutdown()
{
	return true;
}

}
} // namespace Rml