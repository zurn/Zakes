
#ifndef __SCORES_H__
#define __SCORES_H__

#define MAX_SCORES 10

#include "player.h"
#include <string>
#include "entry.h"
#include <vector>

#define SLOW_SPEED "slow"
#define MEDIUM_SPEED "medium"
#define FAST_SPEED "fast"

class scores
{
	public:
		scores();
		scores(const char * filename);
		~scores();

		void print();
		bool load(const char * filename);
		bool save(const char * filename);
		void add_speed(TiXmlHandle & hRoot, const char * speed);

		bool is_new_highscore(int score, int speed, const char * name);
		bool is_new_highscore(int speed, player * p);
		bool check_score(std::vector<entry> & entries, player *p);

		int add_score(int speed, player * p);
		int add_score(std::vector<entry> & entries, player * p);
		//returns 0 for no high score
		//else returns 1 thru 10 for which place it took over

		std::string score_file;
		std::vector<entry> slow_scores;
		std::vector<entry> medium_scores;
		std::vector<entry> fast_scores;

	private:

};
#endif /* __SCORES_H__ */
