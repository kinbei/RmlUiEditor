#include "EditorPlugin.h"
#include <RmlUi/Core/Context.h>
#include <RmlUi/Core/ElementDocument.h>
#include <RmlUi/Core/Factory.h>

namespace Rml {
namespace Editor {

EditorPlugin* EditorPlugin::instance = nullptr;

static const char* editor_rcss = R"RCSS(
#tools-bar
{
	width: 70px;
	height: 100%;
	background-color: #ddd;
	display: inline-block;
}
#tools-bar pseudo
{
	position: absolute;
	left: 2px;
	top: 2px;
	background-color: #ddd;
	border: 1px #aaa;
	display: inline-block;
}
)RCSS";

static const char* editor_rml = R"RML(
<rml>
	<body>
		<div id="tools-bar">
			<pseudo><img id = "tools-bar-text" src = "assets/high_scores_alien_1.tga" /></pseudo>
			<span id="extra"></span>
		</div>
	</body>
</rml>
)RML";

EditorPlugin::EditorPlugin()
{
	host_context = nullptr;
	editor_context = nullptr;
}

EditorPlugin::~EditorPlugin()
{
}

EditorPlugin* EditorPlugin::GetInstance()
{
	if (!instance)
		instance = new EditorPlugin();

	return instance;
}

///
bool EditorPlugin::Initialise(Context* context)
{
	host_context = context;

	ElementDocument *document = host_context->CreateDocument();
	if (!document)
		return false;

	document->SetInnerRML(editor_rml);
	document->Show();

	SharedPtr<StyleSheetContainer> style_sheet = Factory::InstanceStyleSheetString(String(editor_rcss));
	if (!style_sheet)
		return false;

	document->SetStyleSheetContainer(std::move(style_sheet));
	return true;
}

///
bool EditorPlugin::SetContext(Context* context)
{
	return true;
}

void EditorPlugin::ProcessEvent(Event& event)
{

}

}
} // namespace Rml
