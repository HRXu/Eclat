#pragma once

class Readin
{
public:
	enum file{
		chess=0,
		connect,
		kosarak,
		kosarak2,
		mushroom,
		pumsb,
		pumsb_star,
		retail
	};
	static bool Open(file f);

};

