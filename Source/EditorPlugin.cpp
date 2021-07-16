#include "EditorPlugin.h"
#include <RmlUi/Core/Context.h>
#include <RmlUi/Core/ElementDocument.h>
#include <RmlUi/Core/Factory.h>

namespace Rml {
namespace Editor {

EditorPlugin* EditorPlugin::instance = nullptr;

static const char* toolsbar_rcss = R"RCSS(
body
{
	width: 28dp;
	height: 100%;
	min-width: 80dp;
	margin-top: 0dp;
	margin-right: 20dp;
	margin-left: 0dp;
}
div#rmlui-editor-toolsbar
{
	position: relative;
	width: auto;
	height: 200px;
	overflow: auto;
	background: #565656;
	border-width: 0dp;
	border-top-width: 0px;
}
div#rmlui-editor-toolsbar div div
{
	font-size: 12dp;
	padding-left: 10dp;
}
div#rmlui-editor-toolsbar .name
{
	color: #610;
}

#pseudo pseudo
{
	padding: 0 8dp 0 3dp;
	background-color: #ddd;
	border: 2px #aaa;
	display: inline-block;
}
#pseudo pseudo.active
{
	border-color: #8af;
	background-color: #eef;
}
)RCSS";

static const char* toolsbar_rml = R"RML(
<div id="rmlui-editor-toolsbar">
	<div id="pseudo">
		<pseudo name="hover" class="active" ><img id = "tools-bar-text" src = "assets/high_scores_alien_1.tga" /></pseudo>
		<span id="extra"></span>
	</div>
</div>
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

	document->SetInnerRML(toolsbar_rml);
	document->Show();

	SharedPtr<StyleSheetContainer> style_sheet = Factory::InstanceStyleSheetString(String(toolsbar_rcss));
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
