#import <Arduboy2.h>
#import "arduart.h"

Arduboy2 arduboy;
ArduArt arduart(arduboy);

int clear_counter = 0;

// This makes the fps configurable
// and keeps the clear time at 1 second
constexpr const uint8_t fps = 60;

void setup() {
  arduboy.begin();
  arduboy.setFrameRate(fps);
}

void loop() {
  if (!(arduboy.nextFrame())) return;
  arduboy.pollButtons();
  arduboy.clear();

  if (arduboy.justPressed(UP_BUTTON)) {
    arduart.move_me(ArduArt::Dir::Up);
  }

  if (arduboy.justPressed(DOWN_BUTTON)) {
    arduart.move_me(ArduArt::Dir::Down);
  }

  if (arduboy.justPressed(LEFT_BUTTON)) {
    arduart.move_me(ArduArt::Dir::Left);
  }

  if (arduboy.justPressed(RIGHT_BUTTON)) {
    arduart.move_me(ArduArt::Dir::Right);
  }

  if (arduboy.pressed(A_BUTTON)) {
    bool clear = true;
    for (size_t i = 0; i <= arduart.points_size; i++) {

    	// Cache the value, generally performs better
		Point2 point = arduart.points[i];
		
		if (point.x == arduart.cursor.x && point.y == arduart.cursor.y) {
			clear = false;
			
			// Break out of the loop early,
			// no sense doing any more checking than there has to be
			break;
		}
    }
    if (clear) {
    	if(arduart.points_size < arduart.maxPoints)
    	{
			arduart.points[arduart.points_size] = arduart.cursor;
			arduart.points_size++;
    	}
    	else
    	{
    		// Somehow tell the user they can't place any more
    	}
    }
  }

  if (arduboy.pressed(B_BUTTON)) {
    for (size_t i = 0; i < arduart.points_size; i++) {    	
		Point2 point = arduart.points[i];
		if (point.x == arduart.cursor.x && point.y == arduart.cursor.y) {
			arduart.points[i] = Point2(-1, -1);
		}
    }
  }

  if (arduboy.pressed(B_BUTTON) && arduboy.justPressed(UP_BUTTON)) {
    arduart.tileSize++;
  } else if (arduboy.pressed(B_BUTTON) && arduboy.justPressed(DOWN_BUTTON)) {
    arduart.tileSize--;
  }

  if (arduboy.pressed(B_BUTTON) && arduboy.pressed(A_BUTTON)) {
    clear_counter++;
    if (clear_counter == fps) {
      clear_counter = 0;
      for (size_t i = 0; i < arduart.points_size; i++) {
			arduart.points[i] = Point2(-1, -1);
      }
      arduart.points_size = 0;
    }
  }
  
  arduart.draw_cursor();
  arduart.draw_art();
  
  arduboy.display();
}

