#include "Editor.h"
#include "EditorPlugin.h"
#include <RmlUi/Core/Log.h>

namespace Rml {
namespace Editor {

/// 
bool Initialise(Context* context) 
{
	return EditorPlugin::GetInstance()->Initialise(context);
}

/// 
bool Shutdown()
{
	return true;
}

}
} // namespace Rml