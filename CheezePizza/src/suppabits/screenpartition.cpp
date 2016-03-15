#include "cheezepizza.h"
#include "cheezepizzaengine.h"
#include "screenpartition.h"


// ----------------------------------------------------------------------------
// ScreenPartition - Definition
// ----------------------------------------------------------------------------

ScreenPartition::ScreenPartition()
	: Partitions(NULL)
	, RowSize(0)
	, ColumnSize(0)
	, PartitionWidth(0.0f)
	, PartitionHeight(0.0f)
{
}

ScreenPartition::~ScreenPartition()
{
	if(Partitions != NULL)
	{
		delete[] Partitions;
		Partitions = NULL;
	}
}

void ScreenPartition::RecalculateBounds(hgeRect& InBounds, int InRows, int InColumns)
{
	if(InRows > 0 && InColumns > 0)
	{
		Bounds = InBounds;
		RowSize = InRows;
		ColumnSize = InColumns;

		Partitions = new hgeRect[InRows * InColumns];

		const int LastRow = RowSize - 1;
		const int LastColumn = ColumnSize - 1;

		PartitionWidth = Bounds.x2 / static_cast<float>(RowSize);
		PartitionHeight = Bounds.y2 / static_cast<float>(ColumnSize);

		float CurrentX1 = 0.0f;
		float CurrentX2 = PartitionWidth;
		float CurrentY1 = 0.0f;
		float CurrentY2 = PartitionHeight;

		for(int Row = 0; Row < RowSize; Row++)
		{
			for(int Column = 0; Column < ColumnSize; Column++)
			{
				const int CurrentParititon = Row + (Column*RowSize);

				Partitions[CurrentParititon].x1 = CurrentX1;
				Partitions[CurrentParititon].x2 = CurrentX2;
				Partitions[CurrentParititon].y1 = CurrentY1;
				Partitions[CurrentParititon].y2 = CurrentY2;

				CurrentY1 += PartitionHeight;

				// For the last column, use the max vertical bounds to account for every pixel missed by floating point additions
				const int NextColumn = Column + 1;
				CurrentY2 = (NextColumn < LastColumn) ? (CurrentY2+PartitionHeight) : Bounds.y2;
			}

			CurrentX1 += PartitionWidth;

			// For the last row, use the max horizontal bounds to account for every pixel missed by floating point additions
			const int NextRow = Row + 1;
			CurrentX2 = (NextRow < LastRow) ? (CurrentX2+PartitionWidth) : Bounds.x2;

			CurrentY1 = 0.0f;
			CurrentY2 = PartitionHeight;
		}

		/*int Total = Rows * Columns;
		for(int i = 0; i < Total; i++)
		{
			CheezePizzaEngine::Instance().GetHGE().System_Log("PARTITION # %d : x1 = %f | x2 = %f | y1 = %f | y2 = %f", i, Partitions[i].x1, Partitions[i].x2, Partitions[i].y1, Partitions[i].y2);
		}*/
	}
}

int ScreenPartition::GetPartitionIDForPoint(float ScreenPointX, float ScreenPointY) const
{
	int PartitionID = INVALID_PARTITION_ID;

	if( RowSize > 0 && ColumnSize > 0 && Bounds.TestPoint(ScreenPointX, ScreenPointY) )
	{
		int PointRow = static_cast<int>(ScreenPointX / PartitionWidth);

		// Don't let the Row value extend past the max partitions in a row
		PointRow = MinInt(PointRow, RowSize - 1);

		int PointColumn = static_cast<int>(ScreenPointY / PartitionHeight);

		// Don't let the Column value extend past the max partitions in a column
		PointColumn = MinInt(PointColumn, ColumnSize - 1);

		// Since the partitions are stored in a linear array, rows then columns, adding the row value 
		// with the column value (offset by the total number of rows) gives you the array index
		PartitionID = PointRow + (RowSize*PointColumn);
	}

	return PartitionID;
}

// EOF
