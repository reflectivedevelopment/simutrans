#include "monorailboden.h"

#include "../simworld.h"

#include "../dataobj/loadsave.h"
#include "../dataobj/environment.h"
#include "wege/weg.h"


monorailboden_t::monorailboden_t(koord3d pos,hang_t::typ slope) : grund_t(pos)
{
	this->slope = slope;
}


void monorailboden_t::rdwr(loadsave_t *file)
{
	grund_t::rdwr(file);

	if(file->get_version()<88009) {
		// save slope locally
		if(file->get_version()>88005) {
			uint8 sl;
			file->rdwr_byte(sl);
			// convert slopes from old single height saved game
			slope = (scorner1(sl) + scorner2(sl) * 3 + scorner3(sl) * 9 + scorner4(sl) * 27) * env_t::pak_height_conversion_factor;
		}
		else {
			slope = grund_t::get_grund_hang();
		}
	}
}


void monorailboden_t::calc_bild_internal(const bool calc_only_snowline_change)
{
	set_bild(IMG_LEER);
	clear_back_bild();

	weg_t *const weg = get_weg_nr(0);
	if(  weg  ) {
		if(  !calc_only_snowline_change  ) {
			weg->calc_image();
		}
		else {
			weg->check_season(false);
		}
	}
}
