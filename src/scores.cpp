
#include "scores.h"

scores::scores()
{
	score_file = "";
}

scores::scores(const char * filename)
{
	score_file = filename;
}

scores::~scores()
{
}

bool scores::load(const char * filename)
{
	TiXmlDocument doc(filename);
	doc.LoadFile();

	TiXmlHandle hDoc(&doc);
	TiXmlElement* pElem;
	TiXmlHandle hRoot(0);

	pElem=hDoc.FirstChildElement().Element();
	// should always have a valid root but handle gracefully if it does
	if (!pElem) {
		printf("Error opening: %s.  Probably going to crash.\n", filename);
		return false;
	}

	hRoot=TiXmlHandle(pElem);


	slow_scores.clear();
	medium_scores.clear();
	fast_scores.clear();

	add_speed(hRoot, SLOW_SPEED);
	add_speed(hRoot, MEDIUM_SPEED);
	add_speed(hRoot, FAST_SPEED);

//	print();
	return true;
}

void scores::add_speed(TiXmlHandle & hRoot, const char * speed)
{
		if (strcmp(speed, SLOW_SPEED) != 0 &&
			strcmp(speed, MEDIUM_SPEED) != 0 &&
			strcmp(speed, FAST_SPEED) != 0) {
			printf("failed function call on scores::add_speed %s\n", speed);
			return;
		}
		TiXmlHandle temp(0);
		entry etemp;
		TiXmlElement * set = hRoot.FirstChild(speed).Element();
		temp = TiXmlHandle(set);
//		const char *pKey=set->Value();
//		const char *pText=set->GetText();
//		printf("set: %s %s\n", pKey, pText);

		TiXmlElement * t2 = temp.FirstChild().Element();
		etemp.clear();
		for (; t2 ; t2 = t2->NextSiblingElement()) {

//			const char *pKey=set->Value();
//			const char *pText=set->GetText();
//			printf("inner set: %s %s\n", pKey, pText);

			std::string key=t2->Value();

			if (key == "score") {
				if (t2->GetText() != NULL) {
					etemp.name = t2->GetText();
				}
				else {
					etemp.name = "";
				}
				t2->QueryIntAttribute("val", &etemp.score);
			}
			
			if (strcmp(speed, SLOW_SPEED) == 0) {
				slow_scores.push_back(etemp);
			}
			if (strcmp(speed, MEDIUM_SPEED) == 0) {
				medium_scores.push_back(etemp);
			}
			if (strcmp(speed, FAST_SPEED) == 0) {
				fast_scores.push_back(etemp);
			}
		}


	if (strcmp(speed, SLOW_SPEED) == 0) {
		sort(slow_scores.begin(), slow_scores.end());
		if (slow_scores.size() > MAX_SCORES)
			slow_scores.resize(MAX_SCORES);
	}
	if (strcmp(speed, MEDIUM_SPEED) == 0) {
		sort(medium_scores.begin(), medium_scores.end());
		if (medium_scores.size() > MAX_SCORES)
			medium_scores.resize(MAX_SCORES);
	}
	if (strcmp(speed, FAST_SPEED) == 0) {
		sort(fast_scores.begin(), fast_scores.end());
		if (fast_scores.size() > MAX_SCORES)
			fast_scores.resize(MAX_SCORES);
	}
}

bool scores::save(const char * filename)
{
	TiXmlDocument doc;
	TiXmlElement* msg;
	TiXmlElement* msg2;
	TiXmlDeclaration * decl = new TiXmlDeclaration("1.0", "", "");
	doc.LinkEndChild(decl);

	TiXmlElement * root = new TiXmlElement("scores");
	doc.LinkEndChild(root );

	msg = new TiXmlElement("slow");
	root->LinkEndChild(msg);

	for (unsigned int i=0; i<slow_scores.size(); i++) {
		msg2 = new TiXmlElement("score");
		msg2->SetAttribute("val", slow_scores[i].score);
		TiXmlText * text = new TiXmlText(slow_scores[i].name.c_str());
		msg2->LinkEndChild(text);
		msg->LinkEndChild(msg2);
	}

	msg = new TiXmlElement("medium");
	root->LinkEndChild(msg);

	for (unsigned int i=0; i<medium_scores.size(); i++) {
		msg2 = new TiXmlElement("score");
		msg2->SetAttribute("val", medium_scores[i].score);
		TiXmlText * text = new TiXmlText(medium_scores[i].name.c_str());
		msg2->LinkEndChild(text);
		msg->LinkEndChild(msg2);
	}

	msg = new TiXmlElement("fast");
	root->LinkEndChild(msg);

	for (unsigned int i=0; i<fast_scores.size(); i++) {
		msg2 = new TiXmlElement("score");
		msg2->SetAttribute("val", fast_scores[i].score);
		TiXmlText * text = new TiXmlText(fast_scores[i].name.c_str());
		msg2->LinkEndChild(text);
		msg->LinkEndChild(msg2);
	}

	doc.SaveFile(filename);
	return true;
}

bool scores::is_new_highscore(int score, int speed, const char * name)
{
	return true;
}


int scores::add_score(int speed, player * p)
{
	int place = -1;

	switch (speed) {
		case 0:
//			printf("slow\n"); 
			place = add_score(slow_scores, p);
		break;
		case 1:
//			printf("medium\n"); 
			place = add_score(medium_scores, p);
		break;
		case 2:
//			printf("fast\n"); 
			place = add_score(fast_scores, p);
		break;
		default: place = 0; break;
	}


//	print();
	return place;
}

bool scores::check_score(std::vector<entry> & entries, player *p)
{
	if (p->cherry_count == 0) {
		return false;
	}
	if (entries.size() < MAX_SCORES) {
		return true;
	}

	entry temp;
	temp.score = p->cherry_count;

	for (unsigned int i=0; i<entries.size(); i++) {
		if (temp > entries[i])
			return true;
	}

	return false;
}

bool scores::is_new_highscore(int speed, player * p)
{
	bool rv = false;
	switch (speed) {
		case 0:
//			printf("slow\n"); 
			rv = check_score(slow_scores, p);
		break;
		case 1:
//			printf("medium\n"); 
			rv = check_score(medium_scores, p);
		break;
		case 2:
//			printf("fast\n"); 
			rv = check_score(fast_scores, p);
		break;
		default: rv = false; break;
	}
	return rv;
}


int scores::add_score(std::vector<entry> & entries, player * p)
{
	entry temp;
	temp.name = p->name;
	temp.score = p->cherry_count;
	entries.push_back(temp);

	sort(entries.begin(), entries.end());
	if (entries.size() > MAX_SCORES)
		entries.resize(MAX_SCORES);

	for (unsigned int i=0; i<entries.size(); i++) {
		if (entries[i] == temp) {
			return i+1;
		}
	}
	return 0;
}

void scores::print()
{
	printf("printing high score read for slow\n");
	for (unsigned int i=0; i<slow_scores.size(); i++) {
		printf("%i. ", i);
		slow_scores[i].print();
	}
	printf("printing high score read for slow end\n\n");


	printf("printing high score read for medium\n");
	for (unsigned int i=0; i<medium_scores.size(); i++) {
		printf("%i. ", i);
		medium_scores[i].print();
	}
	printf("printing high score read for medium end\n\n");

	printf("printing high score read for fast\n");
	for (unsigned int i=0; i<fast_scores.size(); i++) {
		printf("%i. ", i);
		fast_scores[i].print();
	}
	printf("printing high score read for fast end\n\n");
}

