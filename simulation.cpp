#include <vector>
#include <utility>
#include "simulation.hpp"

void Simulation::Draw()
{
    grid.Draw();
}

void Simulation::SetCellValue(int row, int column, int value)
{
    grid.SetValue(row, column, value);
}

int Simulation::CountLiveNeighbords(int row, int column)
{
    int liveNeighbors = 0;
    std::vector<std::pair<int, int>> neighborOffsets =
    {
        {-1, 0}, // Directly above
        {1, 0}, // Directly below
        {0, -1}, // Directly left
        {0, 1}, // Directly right
        {-1, -1}, // Directly upper left
        {-1, 1}, // Directly upper right
        {1, -1}, // Directly lower left
        {1, 1}, // Directly lower right
    };
    
    for (const auto& offset : neighborOffsets)
    {
        int neighborRow = (row + offset.first + grid.GetRows()) % grid.GetRows();
        int neigborColumn = (column + offset.second + grid.GetColums()) % grid.GetColums();
        liveNeighbors += grid.GetValue(neighborRow, neigborColumn);
    }
    return liveNeighbors;
}

void Simulation::Update()
{
    if(IsRunning())
    {
    for (int row = 0; row < grid.GetRows(); row ++)
        {
            for (int column = 0; column < grid.GetColums(); column++)
            {
            int liveNeighbors = CountLiveNeighbords(row, column);
            int cellValue = grid.GetValue(row, column);

            if(cellValue == 1)
            {
                    if(liveNeighbors > 3 || liveNeighbors < 2)
                    {
                        tempGrid.SetValue(row, column, 0);
                    }
                    else
                    {
                        tempGrid.SetValue(row, column, 1);
                    }
            }
            else
            {
                    if(liveNeighbors == 3)
                    {
                        tempGrid.SetValue(row, column, 1);
                    }
                    else
                    {
                        tempGrid.SetValue(row, column, 0);
                    }
            }
            }
        }
        grid = tempGrid;
    }
}

void Simulation::ClearGrid()
{
    if(!IsRunning())
    {
        grid.Clear();
    }
}

void Simulation::CreateRandomState()
{
    if(!IsRunning())
    {
        grid.FillRandom();
    }
}

void Simulation::ToggleCell(int row, int column)
{
    if(!IsRunning())
    {
        grid.ToggleCell(row, column);
    }
}
