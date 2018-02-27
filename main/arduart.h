#ifndef ARDUART_H
#define ARDUART_H

// Had to name this Point22 because Arduboy2 already has a Point struct
class Point2
{
public:
	int x;
	int y;

	Point2() 
		: x(0), y(0)
	{
	}

	Point2(int x, int y)
		: x(x), y(y)
	{
	}
};

class ArduArt {
	Arduboy2 & arduboy;
	public:
		// Use reference instead of value
		ArduArt(Arduboy2 & n_arduboy)
			: arduboy(n_arduboy) // variable initialisation, gets rid of warnings
		{
		}

		// enum class makes the values scoped
		// : uint8_t forces the size to be 1 byte
		// Names changed to reflect scoped enum convention
		enum class Dir : uint8_t {
			Up,
			Down,
			Left,
			Right
		};
		

		// Replaced coords[0] and coords[1] with this
		Point2 cursor;

		// Constant, should hopefully be made clear by other code
		constexpr static const size_t maxPoints = 80;
		
		// Use this for storing points instead of EEPROM
		Point2 points[maxPoints] = {};
		size_t points_size = 0;
		
		// Renamed TILE_SIZE because it's neither constant nor a macro
		// thus using macro-case is confusing
		int tileSize = 4;

		// Changed to functions because they were always being saved to the same value
		// On the Arduboy, memory is usually more of an issue than speed
		// Renamed because they weren't macros		
		int getGridWidth() { return WIDTH / tileSize; }
		int getGridHeight() { return HEIGHT / tileSize; }
		
		// Changed to functions because they were always being saved to the same value
		int getGridX() { return cursor.x * tileSize; }
		int getGridY() { return cursor.y * tileSize; }
		
		void move_me(Dir dir);
		void keypressed();
		void draw_cursor();
		void draw_art();
};

#endif
