#include "EditorPlugin.h"
#include <RmlUi/Core/Context.h>
#include <RmlUi/Core/ElementDocument.h>
#include <RmlUi/Core/Factory.h>
#include <RmlUi/Core/Core.h>
#include <RmlUi/Core/SystemInterface.h>

namespace Rml {
namespace Editor {

EditorPlugin* EditorPlugin::instance = nullptr;

static const char* editor_rcss = R"RCSS(
body
{
	width: 100%;
	height: 100%;
}
#tools-bar
{
	position: absolute;
	width: 70px;
	height: 100%;
	background-color: #ddd;
}
#tools-bar pseudo
{
	position: absolute;
	left: 2px;
	top: 2px;
	background-color: #ddd;
	border: 1px #aaa;
}
#workspace
{
	position: absolute;
	left: 71px;
	width: 100%;
	height: 100%;
	background-color:#ff00ff;
}
)RCSS";

static const char* editor_rml = R"RML(
<rml>
	<body>
		<div id = "tools-bar">
			<pseudo><img id = "tools-bar-text" src = "assets/high_scores_alien_1.tga" /></pseudo>
		</div>
		<div id = "workspace">
		</div>
	</body>
</rml>
)RML";

EditorPlugin::EditorPlugin()
{
	host_context = nullptr;
	document = nullptr;
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
bool EditorPlugin::Initialise(Context* context, Rml::ElementDocument* workspace_document)
{
	host_context = context;
	this->workspace_document = workspace_document;

	document = host_context->CreateDocument();
	if (!document)
		return false;

	document->SetInnerRML(editor_rml);
	document->Show();

	SharedPtr<StyleSheetContainer> style_sheet = Factory::InstanceStyleSheetString(String(editor_rcss));
	if (!style_sheet)
		return false;

	document->SetStyleSheetContainer(std::move(style_sheet));

	//
	document->AddEventListener(EventId::Click, this);
	return true;
}

void EditorPlugin::__ProcessClickEvent(Event& event)
{
	SystemInterface *system_interface = Rml::GetSystemInterface();
	if (!system_interface)
		return;

	Element* e = event.GetTargetElement();
	Rml::String s = event.GetTargetElement()->GetId();
	if(event.GetTargetElement()->GetId() == "tools-bar-text")
	{
		system_interface->SetMouseCursor("cross");
		
		Rml::Element* element = document->GetElementById("workspace");
		element->RemoveProperty(Rml::PropertyId::Display);

		workspace_document->GetElementById("windows")->SetProperty(PropertyId::ZIndex, Property(0.0f, Property::NUMBER));
	}
	else if(event.GetTargetElement()->GetId() == "workspace")
	{
		system_interface->SetMouseCursor("");

		Rml::Element* element = document->GetElementById("workspace");
		element->SetProperty(Rml::PropertyId::Display, Property(Style::Display::None));

		workspace_document->GetElementById("windows")->SetProperty(PropertyId::ZIndex, Property(1.0f, Property::NUMBER));
	}
}

void EditorPlugin::ProcessEvent(Event& event)
{
	switch (event.GetId()) {
	case EventId::Click:
	{
		__ProcessClickEvent(event);
	}
	break;

	}
}

}
} // namespace Rml
