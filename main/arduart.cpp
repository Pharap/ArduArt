#import <Arduboy2.h>
#import "arduart.h"

void ArduArt::move_me(Dir dir) {
	switch (dir) {
		case Dir::Up:
			// The compiler picks up on this anyway,
			// but it's better to check for this and
			// avoid the subtraction alltogether
			if (cursor.y > 0) {
				cursor.y--;
			}
			break;
		case Dir::Down:
			if (cursor.y + 1 < getGridHeight()) {
				cursor.y++;
			}
			break;
		case Dir::Left:
			// Same as above
			if (cursor.x > 0) {
				cursor.x--;
			}
			break;
		case Dir::Right:
			if (cursor.x + 1 < getGridWidth()) {
				cursor.x++;
			}
			break;
		default:
			break;
	}
}

void ArduArt::draw_cursor() {
	// Swapped out for the new functions
	// Could have been as easily replaced with the variables
	// (Again, the compiler had already realised this,
	// so this is more of a clarity fix than a way to save memory)
	arduboy.drawRect(getGridX(), getGridY(), tileSize, tileSize, WHITE);
}

void ArduArt::draw_art() {
	// size_t is actually uint16_t, which is actually unsigned int
	// This is better for portability, and possibly more efficient
	for (size_t i = 0; i < points_size; i++) {
		
		Point2 point = points[i];		
		if (point.x != -1 && point.y != -1) {
			arduboy.fillRect(point.x * tileSize, point.y * tileSize, tileSize, tileSize, WHITE);
		}
	}
}
