#include "PathFinding.h"

PathFinding::PathFinding(void)
{
	m_initializedStartGoal = false;
	m_foundGoal = false;
}

PathFinding::~PathFinding(void)
{
}

void PathFinding::FindPath(D3DXVECTOR3 currentPos, D3DXVECTOR3 targetPos)
{
	if ( !m_initializedStartGoal)
	{
		for ( unsigned int i = 0; i < m_openList.size(); i++)
		{
			delete m_openList[i];
		}
		m_openList.clear();

		for ( unsigned int i = 0; i < m_visitedList.size(); i++)
		{
			delete m_visitedList[i];
		}
		m_visitedList.clear();

		for ( unsigned int i = 0; i < m_pathToGoal.size(); i++)
		{
			delete m_pathToGoal[i];
		}
		m_pathToGoal.clear();

		// initialize start
		SearchCell start;
		start.m_xcoord = currentPos.x;		//m_GameWorld->GetCellX(currentPos.x); currentPos.x/CellSIZE;
		start.m_zcoord = currentPos.z;		//m_gameWorld->GetCellY(currentPos.z);

		// initialize goal
		SearchCell goal;
		goal.m_xcoord = targetPos.x;
		goal.m_zcoord = targetPos.z;

		SetStartAndGoal(start, goal);
		m_initializedStartGoal = true;
	}

	if ( m_initializedStartGoal)
		ContinuePath();
}

void PathFinding::SetStartAndGoal(SearchCell start, SearchCell goal)
{
	m_startCell = new SearchCell(start.m_xcoord, start.m_zcoord, NULL);
	m_goalCell = new SearchCell(goal.m_xcoord, goal.m_zcoord, &goal);

	m_startCell->G = 0;
	m_startCell->H = m_startCell->ManhattanDistance(m_goalCell);
	m_startCell->parent = 0;

	m_openList.push_back(m_startCell);
}

SearchCell* PathFinding::GetNextCell()
{
	float bestF = 999999.0f;
	int cellIndex = -1;
	SearchCell* nextCell = NULL;

	for( int i = 0; i < m_openList.size(); i++)
	{
		if (m_openList[i]->GetF() < bestF)
		{
			bestF = m_openList[i]->GetF();
			cellIndex = i;
		}
	}

	if ( cellIndex >= 0)
	{
		nextCell = m_openList[cellIndex];
		m_visitedList.push_back(nextCell);
		m_openList.erase(m_openList.begin() + cellIndex);
	}

	return nextCell;
}

void PathFinding::PathOpened(int x, int z, float newCost, SearchCell *parent)
{
	/*if(CELL_BLOCKED)
	{
	return;
	}*/

	int id = z * WORLD_SIZE + x;
	for ( int i = 0; i < m_visitedList.size(); i++)
	{
		if ( id == m_visitedList[i]->m_id)
		{
			return;
		}
	}

	SearchCell* newChild = new SearchCell(x, z, parent);
	newChild->G = newCost;
	newChild->H = parent->ManhattanDistance(m_goalCell);

	for( int i = 0; i < m_openList.size(); i++)
	{
		if ( id == m_openList[i]->m_id)
		{
			float newF = newChild->G + newCost + m_openList[i]->H;

			if ( m_openList[i]->GetF() > newF)
			{
				m_openList[i]->G = newChild->G + newCost;
				m_openList[i]->parent = newChild;
			}
			else // if the F is not better
			{
				delete newChild;
				return;
			}
		}
	}

	m_openList.push_back(newChild);
}

void PathFinding::ContinuePath()
{
	for ( int i = 0; i < 4; i++)
	{
		if ( m_openList.empty())
			return;

		SearchCell* currentCell = GetNextCell();

		if ( currentCell->m_id == m_goalCell->m_id)
		{
			m_goalCell->parent = currentCell->parent;

			SearchCell* getPath;
			for ( getPath = m_goalCell; getPath != NULL; getPath = getPath->parent)
			{
				m_pathToGoal.push_back(new D3DXVECTOR3(getPath->m_xcoord /* * CELL_SIZE*/, 0, getPath->m_zcoord));
			}

			m_foundGoal = true;
			return;
		}
		else
		{
			// rightSide
			PathOpened(currentCell->m_xcoord + 1, currentCell->m_zcoord, currentCell->G + 1, currentCell);
			// leftSide
			PathOpened(currentCell->m_xcoord - 1, currentCell->m_zcoord, currentCell->G - 1, currentCell);
			// top side
			PathOpened(currentCell->m_xcoord, currentCell->m_zcoord + 1, currentCell->G + 1, currentCell);
			// bottom side
			PathOpened(currentCell->m_xcoord, currentCell->m_zcoord - 1, currentCell->G + 1, currentCell);
			// left-up diagonal
			PathOpened(currentCell->m_xcoord - 1, currentCell->m_zcoord + 1, currentCell->G + 1.414, currentCell);		// each cell cost one, include 2 cells take sqrt
			// right-up diagonal
			PathOpened(currentCell->m_xcoord + 1, currentCell->m_zcoord + 1, currentCell->G + 1.414, currentCell);
			// left-down diagonal
			PathOpened(currentCell->m_xcoord - 1, currentCell->m_zcoord - 1, currentCell->G + 1.414, currentCell);
			// right-down diagonal
			PathOpened(currentCell->m_xcoord + 1, currentCell->m_zcoord - 1, currentCell->G + 1.414, currentCell);

			for (int i = 0; i < m_openList.size(); i++)
			{
				if ( currentCell->m_id == m_openList[i]->m_id)
				{
					m_openList.erase(m_openList.begin() + i);
				}
			}
		}
	}
}

D3DXVECTOR3 PathFinding::NextPathPos()	// (Piggy _piggy)
{
	int index = 1;

	D3DXVECTOR3 nextPos;
	nextPos.x = m_pathToGoal[m_pathToGoal.size()- index]->x;
	nextPos.z = m_pathToGoal[m_pathToGoal.size()- index]->z;

	//D3DXVECTOR3 distance = nextPos - pos;		// AI's position Piggie's position - _piggy.pos;

	//if ( index < m_pathToGoal.size() );
	//{
	//	if ( distance.Length() < radius)	// if ((nextCell - object->Position()).Length() < object->GetRadius())
	//	{
	//		m_pathToGoal.erase(m_pathToGoal.end() - index);
	//	}
	//}

	return nextPos;
}