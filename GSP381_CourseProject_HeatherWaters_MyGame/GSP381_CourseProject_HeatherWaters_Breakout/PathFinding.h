#pragma once
#include <vector>
#include <d3d9.h>
#include <d3dx9tex.h>
#include "SearchCell.h"

class PathFinding
{
public:
	PathFinding(void);
	~PathFinding(void);

	void FindPath(D3DXVECTOR3 currentPos, D3DXVECTOR3 targetPos);
	D3DXVECTOR3 NextPathPos();
	void ClearOpenList()	{ m_openList.clear(); }
	void ClearVisitedList()	{ m_visitedList.clear(); }
	void ClearPathToGoal()	{ m_pathToGoal.clear(); }
	bool m_initializedStartGoal;
	bool m_foundGoal;

private:
	void SetStartAndGoal(SearchCell start, SearchCell goal);
	void PathOpened(int x, int z, float newCost, SearchCell *parent);
	SearchCell *GetNextCell ();
	void ContinuePath();

	SearchCell *m_startCell;
	SearchCell *m_goalCell;
	std::vector<SearchCell*> m_openList;
	std::vector<SearchCell*> m_visitedList;
	std::vector<D3DXVECTOR3*> m_pathToGoal;
};