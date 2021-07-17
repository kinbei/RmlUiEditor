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
	background-color:transparent;
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

		using namespace Rml;
		Vector2f mouse_pos(event.GetParameter("mouse_x", 0.0f), event.GetParameter("mouse_y", 0.0f));

		Rml::ElementPtr new_element = workspace_document->CreateElement("text");
		new_element->SetInnerRML(R"RCSS(<label><input type = "checkbox" value = "pizza" / > Pizza< / label>)RCSS");
		new_element->SetProperty(PropertyId::Position, Property(Style::Position::Absolute));
		new_element->SetProperty(Rml::PropertyId::Left, Rml::Property(mouse_pos.x - workspace_document->GetAbsoluteLeft(), Rml::Property::DP));
		new_element->SetProperty(Rml::PropertyId::Top, Rml::Property(mouse_pos.y - workspace_document->GetAbsoluteTop(), Rml::Property::DP));

		float max_zindex = 0.0;
		for (int i = 0; i < workspace_document->GetNumChildren(); ++i)
		{
			if (max_zindex < workspace_document->GetChild(i)->GetZIndex())
				max_zindex = workspace_document->GetChild(i)->GetZIndex();
		}
		new_element->SetProperty(PropertyId::ZIndex, Property(max_zindex + 1.0, Property::NUMBER));

		workspace_document->GetElementById("window")->InsertBefore(std::move(new_element), workspace_document->GetElementById("window")->GetFirstChild());
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
