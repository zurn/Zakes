#include "settings.h"

settings::settings(const char * filename)
{
	sfxVol = 0.0;
	musVol = 0.0;
	tutorials = false;
	speed = 0;

	if (!load(filename)) {
		loadDefault();
	}
}

settings::settings()
{
}

settings::~settings()
{
}

bool settings::load(const char * filename)
{
	if (access(filename, F_OK)==-1) {
		printf("No settings file found at found at %s.\n \
				Using default settings.\n", filename);
		return false;
	}

	TiXmlDocument doc(filename);
	doc.LoadFile();

	TiXmlHandle hDoc(&doc);
	TiXmlElement* pElem;
	TiXmlHandle hRoot(0);

	pElem = hDoc.FirstChildElement().Element();
	if (!pElem) { //invalid root node
		printf("Error reading1: %s.\n \
				Using default settings.\n", filename);
		return false;
	}
	hRoot = TiXmlHandle(pElem);
	
	//read volume values
	pElem = hRoot.FirstChild( "volume" ).Element();
	if (!pElem) {
		printf("Error reading: %s.\n \
				Using default settings.\n", filename);
		return false;
	}
	pElem->QueryFloatAttribute("sfx", &sfxVol);
	pElem->QueryFloatAttribute("mus", &musVol);

	int tint = 0;
	//read tutorial toggle
	pElem = hRoot.FirstChild( "tutorials" ).Element();
	if (!pElem) {
		printf("Error reading: %s.\n \
				Using default settings.\n", filename);
		return false;
	}
	pElem->QueryIntAttribute("val", &tint);

	if (tint == 1)
		tutorials = true;
	else
		tutorials = false;

	//read speed setting
	pElem = hRoot.FirstChild( "speed" ).Element();
	if (!pElem) {
		printf("Error reading: %s.\n \
				Using default settings.\n", filename);
		return false;
	}
	pElem->QueryIntAttribute("val", &speed);


//	print();
	return true;
}

bool settings::save(const char * filename)
{
	TiXmlDocument doc;
	TiXmlElement* msg;
	TiXmlDeclaration * decl = new TiXmlDeclaration("1.0", "", "");
	doc.LinkEndChild(decl);

	TiXmlElement * root = new TiXmlElement("settings");
	doc.LinkEndChild(root );

	TiXmlComment * comment = new TiXmlComment();
	comment->SetValue("Settings configuration");
	root->LinkEndChild(comment);

	msg = new TiXmlElement("volume");
	msg->SetDoubleAttribute("sfx", sfxVol);
	msg->SetDoubleAttribute("mus", musVol);
	root->LinkEndChild(msg);

	msg = new TiXmlElement("tutorials");
	msg->SetAttribute("val",tutorials);
	root->LinkEndChild(msg);

	msg = new TiXmlElement("speed");
	msg->SetAttribute("val", speed);
	root->LinkEndChild(msg);

	doc.SaveFile(filename);
	return true;
}

void settings::loadDefault()
{
	sfxVol = 0.5;
	musVol = 0.5;
	tutorials = true;
	speed = 0;
}

void settings::print()
{
	printf("sfx %f\n", sfxVol);
	printf("mus %f\n", musVol);

	printf("tuts %i\n",tutorials);
	printf("speed ");
	switch (speed) {
		case 0: printf("slow\n"); break;
		case 1: printf("medium\n"); break;
		case 2: printf("fast\n"); break;
	}
}

