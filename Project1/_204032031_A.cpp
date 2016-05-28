#include "_204032031_A.h"

/*
Direction _204032031_A_::step(Direction lastStep)
{
//	updateAlgorithmInfo(lastStep);
	if (requestedStep != lastStep) {
		// we were moved not according to our plan - reset the phases
		phase = -1;
	}
	++phase;
	// handlePhase in this algorithm decides on the next step
	return handlePhase();
}

void _204032031_A_::updateAlgorithmInfo(Direction lastStep)
{
	++totalSteps;
	position.move(lastStep); // update the robot position, as managed by the algorithm, to the new position
	s = sensor->sense();
	//debug << "position: " << position << ", dirtLevel = " << s.dirtLevel << endl;
	// update the map with the info on the dirt level
	stepsFromDocking = calcStepsToDocking(stepsFromDocking + 1, position);
	houseMapping[position] = { (s.dirtLevel != 0) ? s.dirtLevel - 1 : 0, stepsFromDocking };
	// update all 4 cells around me with Wall information and if possible also with stepsToDocking
	for (Direction d : directions) {
		Point p = position.neighbour(d);
		auto neighbour = houseMapping.find(p);
		if (neighbour == houseMapping.end()) {
			CellInfo& cellInfo = houseMapping[p]; // create CellInfo
			cellInfo.isWall = s.isWall[(int)d];
			if (!s.isWall[(int)d]) {
				cellInfo.stepsToDocking = calcStepsToDocking(stepsFromDocking + 1, p);
			}
		}
	}
}


Direction _204032031_A_::handlePhase() {
		while (phase < 8) {
			requestedStep = dir_by_phase[phase];
			Point newPos = position;
			newPos.move(requestedStep);
			if (phase % 2) {
				// this is a "return step" (odd number)
				// the current algorithm requires that on a "return step"
				// we must return to the cell from where we started the tour
				
				return requestedStep;
			}
			// this is NOT a "return step"
			auto neighbour = houseMapping.find(newPos);
			if ((neighbour != houseMapping.end() && neighbour->second.dirt != -1) || s.isWall[(int)requestedStep]) {
				// if we already have info on this cell dirt level, skip
				// or - if it's a wall, skip
				phase += 2;
			}
			else {
				// we don't have info on this cell and it's not a wall, so let's visit it
				
				return requestedStep;
			}
		}
		// we are here with phase8 - should select the route with max dirt
		return handlePhase8();
}

Direction _204032031_A_::handlePhase8() {
	
	phase = -1; // for next round
	// select the direction with maximum dirt, if all equal prefer currDir
	Direction checkDir = currDir;
	int dirt, max_dirt = -1;
	// loop all 4 directions, with a priority for the current direction
	do {
		Point checkNewPos = position.neighbour(checkDir);
		// we know for sure that the position that we check was mapped already
		// (if this was not the case, we would have use houseMapping.find(checkNewPos) and check != houseMapping.end())
		// but we know that phases 0-7 mapped all 4 directions around this cell
		if (!s.isWall[(int)checkDir] && (dirt = houseMapping[checkNewPos].dirt) > max_dirt) {
			max_dirt = dirt;
			requestedStep = checkDir;
		}
	} while (++checkDir != currDir);
	if (max_dirt == -1) {
		// this is in a rare case of being totally surounded by walls
		requestedStep = Direction::Stay;
		
	}
	
	currDir = requestedStep;
	return requestedStep;
}
/*
int _204032031_A_::calcStepsToDocking(int stepsFromDocking, const Point& position) {
	// if this cell already has a better route - keep it!
	auto thisCellInfo = houseMapping.find(position);
	if (thisCellInfo != houseMapping.end() && thisCellInfo->second.stepsToDocking != -1 &&
		thisCellInfo->second.stepsToDocking < stepsFromDocking) {
		return thisCellInfo->second.stepsToDocking;
	}
	// check if there is a better route via neighbours that we visited already
	int bestRouteSteps = stepsFromDocking;
	for (Point p : position.neighbours()) {
		auto neighbour = houseMapping.find(p);
		if (neighbour != houseMapping.end() && neighbour->second.stepsToDocking != -1 &&
			neighbour->second.stepsToDocking < bestRouteSteps - 1) {
			bestRouteSteps = neighbour->second.stepsToDocking + 1;
		}
	}
	if (bestRouteSteps < stepsFromDocking) {
		updateStepsToDocking(bestRouteSteps, position);
	}
	return bestRouteSteps;
}

void _204032031_A_::updateStepsToDocking(int stepsToDocking, const Point& position) {
	if (houseMapping[position].stepsToDocking > stepsToDocking || houseMapping[position].stepsToDocking == -1) {
		houseMapping[position].stepsToDocking = stepsToDocking;
		for (Point p : position.neighbours()) {
			auto neighbour = houseMapping.find(p);
			if (neighbour != houseMapping.end()) {
				CellInfo cell = neighbour->second;
				if (cell.stepsToDocking > stepsToDocking + 1 || (!cell.isWall && cell.stepsToDocking == -1)) {
					updateStepsToDocking(stepsToDocking + 1, p);
				}
			}
		}
	}
}


const Direction _204032031_A_::dir_by_phase[] = { Direction::East, Direction::West, Direction::North, Direction::South, Direction::West, Direction::East, Direction::South, Direction::North };
*/