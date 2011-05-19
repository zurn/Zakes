
#ifndef __GET_NAME_H__
#define __GET_NAME_H__

#include "state.h"
#include "game.h"
#include "keyboard.h"
#include <string>

#define NAME_LENGTH 10

class get_name: public state
{
	public:
		get_name(game * g);
		get_name();
		virtual ~get_name();

		void update();
		void draw();
		void enter();
		void exit();

		game * fsm;


		std::string name;
		font * title;
		font * caption;
		keyboard * options;
		sound * select;
		sound * move;
	private:

};
#endif /* __GET_NAME_H__ */
