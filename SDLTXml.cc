#include "SDLTXml.h"

////	SECTION: SDLTXmlManager	////

SDLTXmlManager::SDLTXmlManager(std::string fileUri)
{
	doc.LoadFile(fileUri.c_str());
}

void SDLTXmlManager::Parse()
{
	doc.Accept(visitor);
}
	
//Accessor Functions

tinyxml2::XMLVisitor* SDLTXmlManager::GetVisitor()
{
	return visitor;
}
	
void SDLTXmlManager::SetVisitor(tinyxml2::XMLVisitor *value)
{
	visitor = value;
}

////	ENDSECT: SDLTXmlManager	////

////	SECTION: SDLTSpriteSheetVisitor	////



////	ENDSECT: SDLTSpriteSheetVisitor	////
