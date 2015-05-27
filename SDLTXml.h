#ifndef SDLT_XML_H
#define SDLT_XML_H

#include "tinyxml2.h"
#include <string>

////	SECTION: SDLTXmlManager	////

class SDLTXmlManager
{
public:
	SDLTXmlManager(std::string fileUri);
	
	void Parse();
	
	//Accessor Functions
	tinyxml2::XMLVisitor*	GetVisitor();	
	void					SetVisitor(tinyxml2::XMLVisitor *value);
	
private:
	tinyxml2::XMLDocument	doc;
	tinyxml2::XMLVisitor	*visitor;
};

////	ENDSECT: SDLTXmlManager	////

////	SECTION: SDLTSpriteSheetVisitor	////

class SDLTSpriteSheetVisitor : public tinyxml2::XMLVisitor
{	
	//Inherited Functions
	bool VisitEnter(const tinyxml2::XMLDocument& doc)           
	{
		return true;
	}
	
	bool VisitExit(const tinyxml2::XMLDocument& doc)            
	{
		return true;
	}

	bool VisitEnter(const tinyxml2::XMLElement& element, const tinyxml2::XMLAttribute* firstAttribute)    
	{
		return true;
	}
	
	bool VisitExit(const tinyxml2::XMLElement& element)         
	{
		return true;
	}

	bool Visit(const tinyxml2::XMLDeclaration& declaration)     
	{
		return true;
	}
	
	bool Visit(const tinyxml2::XMLText& text)                   
	{
		return true;
	}
	
	bool Visit(const tinyxml2::XMLComment& comment)             
	{
		return true;
	}
	
	bool Visit(const tinyxml2::XMLUnknown& unknown)             
	{
		return true;
	}
};

////	ENDSECT: SDLTSpriteSheetVisitor	////

#endif
