#include "ObjectMazeBuilder.hpp"

mazeObject* ObjectMazeMap::get(int x, int y)
{
	if (x<0 || x>=width() || y<0 || y>=height()) return nullptr;
	return &m_map[x][y];
}

unsigned int ObjectMazeMap::width()
{
	return m_map.size();
}

unsigned int ObjectMazeMap::height()
{
	return m_map[0].size();
}

void ObjectMazeMap::init(MazeBuilder& maze, DrawableHolder rootWall, DrawableHolder lineWall, DrawableHolder cornerWall, DrawableHolder xmas_tree) 
{
	const int wallOffset = 4*2;

	bool** v_walls;
	bool** h_walls;
	int mazeW;
	int mazeH;

	maze.getWalls(v_walls, h_walls, mazeW, mazeH);
	m_map = std::vector<std::vector<mazeObject>>(mazeW, std::vector<mazeObject>(mazeH));

	for (int y = 0; y < mazeH; y++)
		for (int x = 0; x < mazeW; x++)
		{
			if (!(h_walls[x][y] || v_walls[x][y]))
			{
				m_map[x][y].model = rootWall;
				m_map[x][y].model.setPosition(glm::vec3(x * wallOffset, 0, y * wallOffset));
				m_map[x][y].wt = Root;
				m_map[x][y].fw = { x * wallOffset-1, y * wallOffset-1, x * wallOffset + 1, y * wallOffset + 1 };
			}
			else
			{
				if (h_walls[x][y] && v_walls[x][y])
				{
					m_map[x][y].model = cornerWall;
					m_map[x][y].model.setRotation(-90, glm::vec3(0,1,0));
					m_map[x][y].model.setPosition(glm::vec3(x * wallOffset, 0, y * wallOffset));
					m_map[x][y].wt = Corner;
					m_map[x][y].fw = { x * wallOffset-1, y * wallOffset-1, x * wallOffset + wallOffset, y * wallOffset + 1 };
					m_map[x][y].sw = { x * wallOffset-1, y * wallOffset-1, x * wallOffset + 1, y * wallOffset + wallOffset };
					DrawableHolder temp_dh;
					temp_dh = xmas_tree;
					temp_dh.setPosition(m_map[x][y].model.getPosition()+glm::vec3(2,-2,2));
    				temp_dh.setScale(glm::vec3(0.5));
					m_map[x][y].child.reset(new DrawableHolder(temp_dh));
				}
				else
				{
					if (h_walls[x][y])
					{
						m_map[x][y].model = lineWall;
						m_map[x][y].model.setRotation(90, glm::vec3(0,1,0));
						m_map[x][y].model.setPosition(glm::vec3(x * wallOffset+3, 0, y * wallOffset));
						m_map[x][y].wt = Horizontal;
						m_map[x][y].fw = { x * wallOffset-1, y * wallOffset-1, x * wallOffset + wallOffset, y * wallOffset + 1 };
					}
					if (v_walls[x][y])
					{
						m_map[x][y].model = lineWall;
						m_map[x][y].model.setPosition(glm::vec3(x * wallOffset, 0, y * wallOffset+3));
						m_map[x][y].wt = Vertical;
						m_map[x][y].fw = { x * wallOffset-1, y * wallOffset-1, x * wallOffset + 1, y * wallOffset + wallOffset };
					}
					
				}

			}
			m_map[x][y].sector10 = glm::ivec2(x/10,y/10);
			 
		}
}

std::vector<std::vector<mazeObject>>& ObjectMazeMap::getMap() 
{
	return m_map;
}

ObjectMazeMap::ObjectMazeMap(MazeBuilder& maze, DrawableHolder rootWall, DrawableHolder lineWall, DrawableHolder cornerWall, DrawableHolder xmas_tree) 
{
	init(maze, rootWall, lineWall, cornerWall, xmas_tree);
}

ObjectMazeMap::ObjectMazeMap() 
{
	
}
