#ifndef RMLUI_EDITOR_H
#define RMLUI_EDITOR_H

#include <RmlUi/Core/ElementDocument.h>

namespace Rml {

class Context;

namespace Editor {

/// 
bool Initialise(Context* context, Rml::ElementDocument* workspace_document);

/// 
bool Shutdown();

}
} // namespace Rml

#endif
