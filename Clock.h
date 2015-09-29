#ifndef __CLOCK_H__
#define __CLOCK_H__

namespace df {
	// The clock, for timing (such as the game loop)
	class Clock {

	private:
		long int previous_time;  // Previous time delta() called (milli sec).

	public:
		// Sets previous_time to current time.
		Clock();

		// Return time elapsed since delta() was last called, -1 if error.
		// Units are milliseconds.
		long int delta(void);

		// Return time elapsed since delta() was last called.
		// Units are milliseconds.
		long int split(void) const;
	};
} // end of namespace df
#endif // __CLOCK_H__
