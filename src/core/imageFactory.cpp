
#include "imageFactory.h"

//-------------------------------------------------------------------

imageFactory::imageFactory() {}

//-------------------------------------------------------------------

imageFactory::~imageFactory()
{
	imap::iterator i;

	for(i= surfaces.begin(); i!= surfaces.end(); ++i)
		delete i->second;
}

//-------------------------------------------------------------------

image * imageFactory::load(const char * filename)
{
	image * tmp;
	imap::iterator val = surfaces.find(filename);

	if (val==surfaces.end()) { //didn't find matching image
		tmp = new image;
		if (tmp->load(filename))
			surfaces[filename] = tmp;
		else {
			delete tmp;
			tmp = NULL;
		}
	}
	else{
		tmp = val->second;
	}
	return tmp;
}

//-------------------------------------------------------------------

void imageFactory::unload(const char * filename)
{
	imap::iterator i = surfaces.find(filename);

	if (i!=surfaces.end()) {
		delete i->second;
		surfaces.erase(i);
	}
}

//-------------------------------------------------------------------

