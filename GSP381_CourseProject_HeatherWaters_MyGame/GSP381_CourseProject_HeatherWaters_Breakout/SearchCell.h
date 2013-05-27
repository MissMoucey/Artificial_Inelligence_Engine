#pragma once

#include <math.h>

#define	WORLD_SIZE 64

struct SearchCell
{
	int m_xcoord;
	int m_zcoord;
	int m_id;
	SearchCell *parent;
	float G;
	float H;		// Heuristic
	
	SearchCell()	: parent(0) {}
	SearchCell( int x, int z, SearchCell *_parent = 0) : m_xcoord(x), m_zcoord(z), 
		parent(_parent), m_id(z * WORLD_SIZE + x), G(0), H(0) {};

	float GetF() {return G + H; }
	float ManhattanDistance(SearchCell *nodeEnd)
	{
		float x = (float) (fabs((float)(this->m_xcoord - nodeEnd->m_xcoord)));
		float z = (float) (fabs((float)(this->m_zcoord - nodeEnd->m_zcoord)));

		return x + z;
	}
};